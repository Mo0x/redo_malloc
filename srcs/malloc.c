#include "libft_malloc.h"
#include <asm-generic/errno-base.h>
#include <stdatomic.h>
#include <stdint.h>

/*
	doc: https://www.gingerbill.org/series/memory-allocation-strategies/

	Alloc strategy :
	for TINY and SMALL we will use free list based allocation.
	for LARGE we do one mmap call.
	We align with 16.
*/

/*
	Large memory diagram : 
	[ zone_header ][ block_header ][ padding ][ user payload ][ block_footer ]
	For LARGE :
	-a LARGE allocation uses one dedicated mmap zone
	-that zone contains exactly one block
	-zone_size = total mapped bytes of the whole zone
	-block_size = bytes from block header start to block footer end
	-requested_size = exact user request before alignment
	-returned pointer = aligned user pointer inside that one block
*/


/*
	checklist for the LARGE path:

	raw request valid?
	aligned payload valid?
	block size valid?
	zone size valid?
	page-rounded zone size valid?
	mmap length > 0?
*/
void 	*malloc_large(size_t size, t_global_allocator *alloc)
{
	uintptr_t ret = NULL;
	size_t metadata_size = sizeof(t_zone_header) + sizeof(t_block_header) + alloc->worst_padding + sizeof(t_block_footer);
	if (size > SIZE_MAX - metadata_size)
	{
		errno = ENOMEM;
		return (void *)ret;
	}
	size_t real_size = size + metadata_size;
	size_t remainder = real_size % alloc->page_size;
	size_t rounded_size = 0;
	if (!remainder)
		rounded_size = real_size;
	else
	{
		size_t extra = alloc->page_size - remainder;
		if (real_size > SIZE_MAX - extra)
		{
			errno = ENOMEM;
			return (void *)ret;
		}
		else
			rounded_size = real_size + extra;
	} 

	ret = mmap(???, rounded_size)
}

void	*malloc(size_t size)
{
	t_global_allocator *alloc = get_alloc();
	int flag_fail = 0; 
	void *ret_ptr = NULL;
	void *header_ptr = NULL;

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
