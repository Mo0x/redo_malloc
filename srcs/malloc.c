#include "libft_malloc.h"
#include <stdint.h>

/*
	doc: https://www.gingerbill.org/series/memory-allocation-strategies/

	Alloc strategy :
	for TINY and SMALL we will use free list based allocation.
	for LARGE we do one mmap call.
	We align with 16.
*/

// idk if it will be usefull
int  is_power_of_2(uintptr_t x)
{
	 return (x & (x - 1)) == 0;
}

void  *malloc(size_t size)
{
	t_global_allocator *alloc = get_alloc();
	int flag_fail = 0; 
	if (!alloc->is_init)
	{
		flag_fail = init_global_allocator(alloc);
		if (flag_fail == -1)
		{
			//TODO set errno here, will have to check which one it is
			return NULL;
		}
	}
	if (size < alloc->n)
	{
		//tiny zone
		write(2, "Not operational yet\n", ft_strlen("Not operational yet\n"));
	}
	else if (size < alloc->m)
	{
		//small zone
		write(2, "Not operational yet\n", ft_strlen("Not operational yet\n"));
	}
	else
	{
		//large zone
	}
}
