#ifndef MALLOC_H
#define MALLOC_H

# include "../libft/includes/libft.h"
#include <stdatomic.h>
#include <stddef.h>
# include <sys/mman.h>
# include <sys/resource.h>
# include <unistd.h>
# include <stdint.h>

typedef struct s_free_list_header
{
  size_t  block_size;
  size_t  padding;
}  t_free_list_header;

typedef struct s_free_list_node
{
  struct s_free_list_node *next;
  size_t                  block_size;
} t_free_list_node;

typedef enum e_placement_policy
{
	placement_policy_find_first,
	placement_policy_find_best
} t_placement_policy;

typedef struct  s_free_list
{
	void								*data;
	size_t							size;
	size_t							used;

	t_free_list_node		*head;
	t_placement_policy	policy;
} t_free_list;

void  free(void *ptr);
void  *malloc(size_t size);
void  *realloc(void *ptr, size_t size);
void  show_alloc_mem();

#endif
