#include "libft_malloc.h"

#define TINY_THRESHOLD 128
#define SMALL_THRESHOLD 1024
#define ALIGNMENT 16

void init_global_allocator(t_global_allocator *alloc)
{
	alloc->tiny_head = NULL;
	alloc->small_head = NULL;
	alloc->large_head = NULL;
	
	alloc->page_size = sysconf(_SC_PAGESIZE);
	alloc->n = TINY_THRESHOLD;
	alloc->m = SMALL_THRESHOLD;

	int worst_padding = ALIGNMENT - 1;
	
	size_t worst_tiny_block = sizeof(t_block_header) + worst_padding + alloc->n + sizeof(t_block_footer);
	alloc->N = sizeof(t_block_header) + 
	
}
