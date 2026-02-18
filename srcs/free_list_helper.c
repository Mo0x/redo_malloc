#include "libft_malloc.h"

 void  free_list(t_free_list *fl)
 {
  fl->used = 0;
  t_free_list_node *first_node = (t_free_list_node *)fl->data;
  
 }
