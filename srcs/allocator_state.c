#include "libft_malloc.h"

#define TINY_THRESHOLD 128
#define SMALL_THRESHOLD 1024
#define ALIGNMENT 16

static t_global_allocator alloc;

t_global_allocator *get_alloc()
{
	return &alloc;
}

static int	safe_add_size(size_t a, size_t b, size_t *out)
{
	if (a > SIZE_MAX - b)
		return -1;
	*out = a + b;
	return 0;
}

static int	safe_mul_size(size_t a, size_t b, size_t *out)
{
	if (a != 0 && b > SIZE_MAX / a)
		return -1;
	*out = a * b;
	return 0;
}


static int	round_up_size(size_t value, size_t multiple, size_t *out)
{
	size_t remainder;
	size_t extra;

	if (multiple == 0)
		return -1;
	remainder = value % multiple;
	if (remainder == 0)
	{
		*out = value;
		return 0;
	}
	extra = multiple - remainder;
	return safe_add_size(value, extra, out);
}

//return -1 if failed init
// int init_global_allocator(t_global_allocator *alloc)
// {
// 	//careful here this trick won't work with thread
// 	if (alloc->is_init == 1)
// 		return 0;
// 	if (!is_power_of_2((uintptr_t)ALIGNMENT))
// 		return -1;
// 	alloc->tiny_head = NULL;
// 	alloc->small_head = NULL;
// 	alloc->large_head = NULL;

// 	long tmp_page_size = sysconf(_SC_PAGESIZE);
// 	if (tmp_page_size == -1)
// 		return -1;
// 	if (tmp_page_size == 0)
// 		return -1;
// 	alloc->page_size = tmp_page_size;
// 	alloc->n = TINY_THRESHOLD;
// 	alloc->m = SMALL_THRESHOLD;

// 	alloc->alignment = ALIGNMENT;
// 	size_t worst_padding = ALIGNMENT - 1;
// 	alloc->worst_padding = worst_padding;
	
// 	size_t worst_tiny_block = sizeof(t_block_header) + worst_padding + alloc->n + sizeof(t_block_footer);
// 	size_t worst_small_block = sizeof(t_block_header) + worst_padding + alloc->m + sizeof(t_block_footer);

// 	if (worst_tiny_block > SIZE_MAX / 100)
// 		return -1;
// 	if (sizeof(t_zone_header) > SIZE_MAX  - (worst_tiny_block * 100))
// 		return -1;
// 	size_t N = sizeof(t_↑ $105zone_header) + (worst_tiny_block * 100);
// 	size_t remainder = N % alloc->page_size;
// 	if (remainder == 0)
// 		alloc->N = N;
// 	else
// 	{
// 		size_t extra = alloc->page_size - remainder;
// 		if (sizeof(t_zone_header) > SIZE_MAX - extra)
// 			return -1;
// 	}
// 	alloc->N = N % alloc->page_size == 0 ? N : ((N / alloc->page_size) + 1 ) * alloc->page_size; 

// 	if (worst_small_block > SIZE_MAX /100)
// 		return -1;
// 	if (sizeof(t_zone_header) > SIZE_MAX - (worst_small_block * 100))
// 		return -1;
// 	size_t M = sizeof(t_zone_header) + (worst_small_block * 100);
// 	alloc->M = M % alloc->page_size == 0 ? M : ((M / alloc->page_size) + 1) * alloc->page_size;
	
// 	// future mutex done here
	
// 	alloc->is_init = 1;
// 	return 0;
// v}

// return -1 if failed init
int	init_global_allocator(t_global_allocator *alloc)
{
	long	tmp_page_size;
	size_t	worst_padding;
	size_t	worst_tiny_block;
	size_t	worst_small_block;
	size_t	tmp;
	size_t	N;
	size_t	M;

	if (alloc->is_init == 1)
		return 0;
	if (!is_power_of_2((uintptr_t)ALIGNMENT))
		return -1;
	alloc->tiny_head = NULL;
	alloc->small_head = NULL;
	alloc->large_head = NULL;
	tmp_page_size = sysconf(_SC_PAGESIZE);
	if (tmp_page_size <= 0)
		return -1;
	alloc->page_size = (size_t)tmp_page_size;
	alloc->n = TINY_THRESHOLD;
	alloc->m = SMALL_THRESHOLD;
	alloc->alignment = ALIGNMENT;
	worst_padding = ALIGNMENT - 1;
	alloc->worst_padding = worst_padding;

	worst_tiny_block = sizeof(t_block_header);
	if (safe_add_size(worst_tiny_block, worst_padding, &worst_tiny_block) == -1)
		return -1;
	if (safe_add_size(worst_tiny_block, alloc->n, &worst_tiny_block) == -1)
		return -1;
	if (safe_add_size(worst_tiny_block, sizeof(t_block_footer), &worst_tiny_block) == -1)
		return -1;

	worst_small_block = sizeof(t_block_header);
	if (safe_add_size(worst_small_block, worst_padding, &worst_small_block) == -1)
		return -1;
	if (safe_add_size(worst_small_block, alloc->m, &worst_small_block) == -1)
		return -1;
	if (safe_add_size(worst_small_block, sizeof(t_block_footer), &worst_small_block) == -1)
		return -1;

	if (safe_mul_size(worst_tiny_block, BLOCKS_PER_ZONE, &tmp) == -1)
		return -1;
	if (safe_add_size(sizeof(t_zone_header), tmp, &N) == -1)
		return -1;
	if (round_up_size(N, alloc->page_size, &alloc->N) == -1)
		return -1;

	if (safe_mul_size(worst_small_block, BLOCKS_PER_ZONE, &tmp) == -1)
		return -1;
	if (safe_add_size(sizeof(t_zone_header), tmp, &M) == -1)
		return -1;
	if (round_up_size(M, alloc->page_size, &alloc->M) == -1)
		return -1;

	alloc->is_init = 1;
	return 0;
}
