#include "libft_malloc.h"
#include <stdint.h>

/*
  doc: https://www.gingerbill.org/series/memory-allocation-strategies/
  TODO find ideal size for TINY, SMALL and LARGE, should be a multiple of 4096
  EACH zones must contain at least 100 allocations
*/

// idk if it will be usefull
int  is_power_of_2(uintptr_t x)
{
  return (x & (x - 1)) == 0;
}

void  *malloc(size_t size)
{
  if (size < 4096 + 1)
  {
    //TINY
  }
  else if (size < 65536 + 1)
  {
    //SMALL 
  }
  else
  {
    //LARGE
  }
}
