#include "libft_malloc.h"
#include <bits/types/stack_t.h>
#include <stdatomic.h>
#include <stdint.h>
#include <sys/mman.h>
#include <unistd.h>

/*
	doc: https://www.gingerbill.org/series/memory-allocation-strategies/

	Alloc strategy :
	for TINY and SMALL we will use free list based allocation.
	for LARGE we do one mmap call.
	We align with 16.
*/

/*
	Large memory diagram :
	[ zone_header ][ zone_to_block_padding ][ block_header ][ user_padding ]
	[ user area ............................................. ][ block_footer ]

	For large:
	- one LARGE allocation uses one dedicated mmap zone
	- that zone contains exactly one block
	- zone_size = total mapped bytes of the whole zone
	- block_size = bytes from block header start to block footer end
	- requested_size = exact user request before alignment
	- returned pointer = aligned user pointer inside that one block
	- the block footer is stored at the very end of the mapped zone
*/

t_block_header *get_block_from_free_node(t_free_list_node *node)
{
	uintptr_t header_addr = (uintptr_t)node - sizeof(t_block_header);
	return (t_block_header *)header_addr;
}

static void *malloc_large_fail(void *map_ret, size_t rounded_size)
{
	if (map_ret && map_ret != MAP_FAILED)
		munmap(map_ret, rounded_size);
	return NULL;
}

static t_zone_header *get_large_zone_from_map(void *map_ret)
{
	return (t_zone_header *)map_ret;
}

// We add a padding between zone_header and block_header
t_block_header *compute_first_block_from_zone(t_zone_header *zone, size_t alignment)
{
	uintptr_t	raw_block;
	ssize_t		padding;

	raw_block = (uintptr_t)zone + sizeof(t_zone_header);
	padding = calc_padding_from_address(raw_block, alignment);
	if (padding < 0)
		return NULL;
	return ((t_block_header *)(raw_block + (uintptr_t)padding));
}


/*
	checklist for the LARGE path:

	raw request valid?
	aligned payload valid?
	block size valid?
	zone size valid?
	page-rounded zone size valid?
	mmap length > 0?
*/

// helpers not needed for large alloc, perhaps reuse for tiny/small, we will see


void 	*malloc_large(size_t size, t_global_allocator *alloc)
{
	// perhaps move all declaration at the top, 42 norm style, will see
	uintptr_t ret = 0;
	void *map_ret = 0; 
	size_t metadata_size;
	size_t two_paddings;

	metadata_size = sizeof(t_zone_header);
	if (safe_add_size(metadata_size, sizeof(t_block_header), &metadata_size) == -1)
	{
		errno = ENOMEM;
		return (NULL);
	}
	if (safe_add_size(alloc->worst_padding, alloc->worst_padding, &two_paddings) == -1)
	{
		errno = ENOMEM;
		return (NULL);
	}
	if (safe_add_size(metadata_size, two_paddings, &metadata_size) == -1)
	{
		errno = ENOMEM;
		return (NULL);
	}
	if (safe_add_size(metadata_size, sizeof(t_block_footer), &metadata_size) == -1)
	{
		errno = ENOMEM;
		return (NULL);
	}

	size_t real_size = 0;
	size_t rounded_size = 0;

	if (safe_add_size(size, metadata_size, &real_size) == -1)
	{
		errno = ENOMEM;
		return (NULL);
	}
	if (round_up_size(real_size, alloc->page_size, &rounded_size) == -1)
	{
		errno = ENOMEM;
		return (NULL);
	}
 
	// MAP_PRIVATE means you get a private copy-on-write mapping: changes are not shared with other processes and are not written back to an underlying file.
	// MAP_ANON means the mapping is not backed by any file and is zero-initialized
	map_ret = mmap(NULL, rounded_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (map_ret == MAP_FAILED)
		return NULL;
	// Now zone is mapped -> we prepare the zone of the metadata;
	t_zone_header *zone = get_large_zone_from_map(map_ret);
	t_block_header *block = compute_first_block_from_zone(zone, alloc->alignment);
	if (!block)
		return (malloc_large_fail(map_ret, rounded_size));
	if (!is_aligned((uintptr_t)block, alloc->alignment))
		return (malloc_large_fail(map_ret, rounded_size));
		
	uintptr_t raw_user = (uintptr_t)block + sizeof(t_block_header);
	ssize_t user_padding = calc_padding_from_address(raw_user, alloc->alignment);
	if (user_padding < 0)
		return (malloc_large_fail(map_ret, rounded_size));

	ret = raw_user + (uintptr_t)user_padding; 
	if (!is_aligned(ret, alloc->alignment))
		return (malloc_large_fail(map_ret, rounded_size));
	
	uintptr_t zone_end = (uintptr_t)zone + rounded_size; 
	uintptr_t footer_start = zone_end - sizeof(t_block_footer);
	t_block_footer *footer = (t_block_footer *)footer_start;
	size_t block_size = zone_end - (uintptr_t)block;
	if (block_size % alloc->alignment)
		return (malloc_large_fail(map_ret, rounded_size));
	if (ret > footer_start)
		return (malloc_large_fail(map_ret, rounded_size));
	size_t payload_capacity = footer_start - ret;

	if (size > payload_capacity)
		return (malloc_large_fail(map_ret, rounded_size));

	
	//fill block
	{
		block->block_size = block_size;
		block->padding = (size_t)user_padding;
		block->requested_size = size;
	}
	//fill footer
	{
		footer->block_size = block_size;
	}
	
	//fill zone
	{
		zone->type = LARGE;
		zone->zone_size = rounded_size;
		zone->next = alloc->large_head;
		zone->free_list_node = NULL;
		zone->block_header = block;
	}
	alloc->large_head = zone;
	return (void *)ret;
}

/*
	-> choose tiny or small
	-> search existing zones of that type
	-> inside each zone, search a free block big enough
	-> if found, allocate from that free block
	    -> maybe split it
	    -> update free list
	    -> fill allocated block metadata
	    -> return user pointer
	-> if none found, mmap a new zone
	    -> initialize zone with one large free block
	    -> allocate from that block
	    -> return user pointer
*/

t_zone_header *create_pool_zone(t_zone_type zone_type,
	t_zone_header **head,
	t_global_allocator *alloc)
{
	void				*map_ret;
	size_t				zone_size;
	uintptr_t			zone_end;
	t_zone_header		*zone;
	t_block_header		*block;
	t_block_footer		*footer;
	t_free_list_node	*first_node;
	size_t				block_size;

	if (zone_type == TINY)
		zone_size = alloc->N;
	else
		zone_size = alloc->M;
	map_ret = mmap(NULL, zone_size, PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	if (map_ret == MAP_FAILED)
		return (NULL);
	zone = (t_zone_header *)map_ret;
	block = compute_first_block_from_zone(zone, alloc->alignment);
	if (!block)
		return (malloc_large_fail(map_ret, zone_size));
	zone_end = (uintptr_t)zone + zone_size;
	block_size = zone_end - (uintptr_t)block;
	if (block_size < sizeof(t_block_header)
		+ sizeof(t_free_list_node)
		+ sizeof(t_block_footer))
		return (malloc_large_fail(map_ret, zone_size));
	footer = (t_block_footer *)(zone_end - sizeof(t_block_footer));
	first_node = (t_free_list_node *)((uintptr_t)block + sizeof(t_block_header));
	block->block_size = block_size;
	block->padding = 0;
	block->requested_size = 0;
	footer->block_size = block_size;
	first_node->next = NULL;
	zone->type = zone_type;
	zone->zone_size = zone_size;
	zone->free_list_node = first_node;
	zone->block_header = block;
	zone->next = *head;
	*head = zone;
	return (zone);
}

void *malloc_tiny(size_t size, t_global_allocator *alloc)
{
	uintptr_t ret = 0;
	void *map_ret = NULL;
	(void)ret;
	return map_ret;
}

void	*malloc(size_t size)
{
	t_global_allocator *alloc = get_alloc();
	int flag_fail = 0; 
	void *ret_ptr = NULL;
	//void *header_ptr = NULL;
	if (size == 0)
		size = 1; // Policy from is, will see if that makes sense to keep it

	if (!alloc->is_init)
	{
		flag_fail = init_global_allocator(alloc);
		if (flag_fail == -1)
		{
			//TODO set errno here, will have to check which one it is
			return ret_ptr;
		}
	}
	if (size < alloc->n + 1)
	{
		//tiny zone
		ret_ptr = malloc_tiny(size, alloc);
		write(2, "TINY Not operational yet\n", ft_strlen("TINY Not operational yet\n"));
		return ret_ptr;
	}
	else if (size < alloc->m + 1)
	{
		//small zone
		write(2, "SMALL Not operational yet\n", ft_strlen("SMALL Not operational yet\n"));
		return ret_ptr;
	}
	else
	{
		ret_ptr = malloc_large(size, alloc);
		return ret_ptr;
	}
}
