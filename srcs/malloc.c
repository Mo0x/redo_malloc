#include "libft_malloc.h"
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
static t_block_header *compute_large_block_from_zone(t_zone_header *zone, size_t alignment)
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

// static uintptr_t get_raw_user_ptr(t_block_header *block)
// {
// 	return ((uintptr_t)block + sizeof(t_block_header));
// }

// static ssize_t compute_user_padding(uintptr_t raw_user, size_t alignment)
// {
// 	return (calc_padding_from_address(raw_user, alignment));
// }

// static uintptr_t get_ret_ptr(uintptr_t raw_user, size_t padding)
// {
// 	return (raw_user + padding);
// }

void 	*malloc_large(size_t size, t_global_allocator *alloc)
{
	uintptr_t ret = 0;
	void *map_ret = 0; 
	size_t metadata_size = sizeof(t_zone_header) + sizeof(t_block_header) + (2 * alloc->worst_padding) + sizeof(t_block_footer);

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
	t_block_header *block = compute_large_block_from_zone(zone, alloc->alignment);
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
		block->padding = user_padding;
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
		write(2, "Not operational yet\n", ft_strlen("Not operational yet\n"));
		return ret_ptr;
	}
	else if (size < alloc->m + 1)
	{
		//small zone
		write(2, "Not operational yet\n", ft_strlen("Not operational yet\n"));
		return ret_ptr;
	}
	else
	{
		ret_ptr = malloc_large(size, alloc);
		return ret_ptr;
	}
}
