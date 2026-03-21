#include "libft_malloc.h"
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

void  *malloc(size_t size)
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
		//large zone
		header_ptr = mmap(header+ptr, size, ?????);
		if (!alloc->large_head)
		{
			header_ptr = init_zone(alloc->large_head); //future function that will initiate the head of a zone
			
		}
		else
		{
			//some list add back of some kind 

		}		
		
	}
}
