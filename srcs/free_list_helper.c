#include "libft_malloc.h"

 void  free_list_free_all(t_free_list *fl)
 {
	fl->used = 0;
	t_free_list_node *first_node = (t_free_list_node *)fl->data;
	first_node->block_size = fl->size;
	first_node->next = NULL;
	fl->head = first_node;
 }

 void free_list_init(t_free_list *fl, void *data, size_t size)
 {
 	fl->data = data;
 	fl->size = size;
 	free_list_free_all(fl);
 }
