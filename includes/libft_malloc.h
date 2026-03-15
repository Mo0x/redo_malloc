#ifndef MALLOC_H
#define MALLOC_H

# include "../libft/includes/libft.h"
# include <stdatomic.h>
# include <stddef.h>
# include <sys/mman.h>
# include <sys/resource.h>
# include <unistd.h>
# include <stdint.h>

/*
Diagram to understand how tiny/small zone looks like:
[ zone_header ][ block_header ][ padding ][ user payload ][ block_footer ][ block_header ] ...
*/

//Structures
typedef struct	s_block_header
{
	// int		is_free; //0 = used, 1 (or any other value) = free
	// Actually may use the block_size to store is_free, if block are aligned
	// every block_size end with 0x....0000, can use this last bit with 0 free and 1 not free
	size_t	block_size; //size from start of header to end of footer
	size_t	padding; //bytes between end of header and returned pointer
	size_t	requested_size;
}	t_block_header;

typedef struct s_block_footer
{
	size_t	block_size; //same as in header
}	t_block_footer;

typedef struct	s_free_list_node
{
	struct s_free_list_node	*next;
}	t_free_list_node;

typedef enum	e_placement_policy
{
	placement_policy_find_first,
	placement_policy_find_best
}	t_placement_policy;

typedef enum	e_zone_type
{
	TINY,
	SMALL,
	LARGE
}	t_zone_type;

typedef struct 					s_zone_header
{
	t_zone_type					type;
	size_t						zone_size;
	struct s_zone_header		*next;
	struct s_free_list_node		*head;
	
} 								t_zone_header;

//Global Allocator

typedef struct s_global_allocator
{
	struct s_zone_header	*tiny_head;
	struct s_zone_header	*small_head;
	struct s_zone_header	*large_head;
	size_t					page_size;
	size_t					n; //tiny from 1 .. n
	size_t					m; //small from n+1 .. m
	size_t					N; //total mmap size of one TINY zone
	size_t					M; //total mmap size of one SMALL zone
	// field for mutx too but i need to refresh myself on mutex, will put it later if i dot this bonus
	
}	t_global_allocator;

//Mandatory part
void	free(void *ptr);
void 	*malloc(size_t size);
void 	*realloc(void *ptr, size_t size);
void 	show_alloc_mem();

//helpers

#endif
