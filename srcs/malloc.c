#include "libft_malloc.h"

/*
  TODO find ideal size for TINY, SMALL and LARGE, should be a multiple of 4096
  EACH zones must contain at least 100 allocations
*/

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

