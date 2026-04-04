#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include "../includes/libft_malloc.h"

int main (void)
{
  //long page_size = sysconf(_SC_PAGESIZE);
  //printf("size = %ld\n ===== \n", page_size);
  char *large_alloc;
  char *large_alloc1;
  char *large_alloc2;
  //t_global_allocator *alloc = get_alloc();

  large_alloc = malloc(1000000);
  if (!large_alloc)
  {
  	// write(2, "malloc failed", ft_strlen("malloc failed\n"));
  }
  else
  {
  	for (int i = 0; i < 1000000; i++)
  		large_alloc[i] = 'a';
  	large_alloc[999999] = 0;
  	large_alloc[2] = 0;
	write(1, large_alloc, ft_strlen(large_alloc));
	write(1, "\n", 1);
  }

  large_alloc1 = malloc(1000001);
  large_alloc2 = malloc(1000002);
  large_alloc1[2] = 'b';
  large_alloc2[3] = 'c';
    //lib64free(large_alloc1);
  //  free(large_alloc2);
  //free(large_alloc);
  //free(large_alloc);
 // write(2, ft_itoa((int)(uintptr_t)large_alloc), 32);
 show_alloc_mem();

  return 0;
}
