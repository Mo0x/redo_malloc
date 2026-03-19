#include "libft_malloc.h"

#define TINY_THRESHOLD 128
#define SMALL_THRESHOLD 1024
#define ALIGNMENT 16

static t_global_allocator alloc;

struct s_zone_header *get_tiny_head()
{
	return alloc->tiny_header;
}
struct s_zone_header *get_small_head();
struct s_zone_header *get_large_head();
size_t get_page_size();
size_t get_small_n();
size_t get_small_m();
size_t get_big_n();
size_t get_big_m();

//return -1 if failed init
int init_global_allocator(t_global_allocator *alloc)
{
	//careful here this trick won't work with thread
	if (alloc->init_done == 1)
		return 0;
	alloc->tiny_head = NULL;
	alloc->small_head = NULL;
	alloc->large_head = NULL;

	long tmp_page_size = sysconf(_SC_PAGESIZE);
	if (tmp_page_size == -1)
		return -1;
	alloc->page_size = tmp_page_size;
	alloc->n = TINY_THRESHOLD;
	alloc->m = SMALL_THRESHOLD;

	size_t worst_padding = ALIGNMENT - 1;
	
	size_t worst_tiny_block = sizeof(t_block_header) + worst_padding + alloc->n + sizeof(t_block_footer);
	size_t worst_small_block = sizeof(t_block_header) + worst_padding + alloc->m + sizeof(t_block_footer);

	size_t N = sizeof(t_zone_header) + (worst_tiny_block * 100);
	alloc->N = N % alloc->page_size == 0 ? N : ((N / alloc->page_size) + 1 )* alloc->page_size; 

	size_t M = sizeof(t_zone_header) + (worst_small_block * 100);
	alloc->M = M % alloc->page_size == 0 ? M : ((M / alloc->page_size) + 1) * alloc->page_size;
	
	// future mutex done here
	
	alloc->init_done = 1;
	return 0;
}
