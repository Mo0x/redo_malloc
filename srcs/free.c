#include "libft_malloc.h"
#include <stdint.h>

// static int ptr_is_in_zone(t_zone_header *zone, uintptr_t ptr)
// {
// 	uintptr_t zone_start = (uintptr_t)zone;
// 	uintptr_t zone_end = zone_start + zone->zone_size;
// 	if (ptr >= zone_start && ptr < zone_end)
// 	{
// 		return 1;
// 	}
// 	return 0;
// }

int free_large(void *ptr, t_global_allocator *alloc)
{
	uintptr_t user_ptr;
	t_zone_header *zone = alloc->large_head;
	t_zone_header *prev = NULL;
	while (zone != NULL)
	{
		t_block_header *block = zone->block_header;
		user_ptr = (uintptr_t)block + sizeof(t_block_header) + block->padding;
		if (user_ptr == (uintptr_t)ptr)
		{
			if (prev == NULL)
				alloc->large_head = zone->next;
			else
				prev->next = zone->next;
			munmap (zone, zone->zone_size);
			return 1;
		}
		prev = zone; 
		zone = zone->next;
	}
	return 0;
}

void free(void *ptr)
{
	t_global_allocator *alloc = get_alloc();	
	if (ptr == NULL)
		return ;
	if (free_large(ptr, alloc))
		return ;
}
