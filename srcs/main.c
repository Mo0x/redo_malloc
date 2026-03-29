#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include "../includes/libft_malloc.h"

int main (void)
{
  //long page_size = sysconf(_SC_PAGESIZE);
  //printf("size = %ld\n ===== \n", page_size);
  char *large_alloc;
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

  free(NULL);
  free(large_alloc);

  return 0;
}
