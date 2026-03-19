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

}
