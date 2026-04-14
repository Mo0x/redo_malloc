#include "libft_malloc.h"
#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>

static void put_hex_uintptr_fd(uintptr_t n, int fd)
{
	char c;
	if (n >= 16)
		put_hex_uintptr_fd(n / 16, fd);
	c = "0123456789abcdef"[n % 16];
	write(fd, &c, 1);
}

void print_addr_fd(void* to_print, int fd)
{
	uintptr_t addr;
	write(fd, "0x", 2);
	addr = (uintptr_t)to_print;
	put_hex_uintptr_fd(addr,fd);
}

static void print_nl(int fd)
{
	write(fd, "\n", 1);
}

static size_t print_alloc_line_block(t_block_header *block)
{
	uintptr_t user_raw = get_raw_user_ptr(block);
	uintptr_t user_start = get_ret_ptr(user_raw, block->padding);
	print_addr_fd((void *)user_start, 1);
	write(1, " - ", 3);
	uintptr_t user_end = user_start + block->requested_size; 
	print_addr_fd((void *) user_end, 1);
	write(1, " : ", 3);
	ft_putszt_fd(block->requested_size, 1);
	write(1, " bytes", 6);
	print_nl(1);	
	return (block->requested_size);
}

static size_t show_large_zone(t_zone_header *zone)
{
	t_global_allocator *alloc = get_alloc();
	write (1, "LARGE : ", ft_strlen("LARGE : "));
	print_addr_fd((void *)zone, 1);
	print_nl(1);

	t_block_header *block = compute_block_from_zone(zone, alloc->alignment); 
	return print_alloc_line_block(block);
}


void  show_alloc_mem()
{
	t_global_allocator *alloc = get_alloc();
	t_zone_header *curr = alloc->tiny_head;
	size_t total = 0;
	while (curr != NULL)
	{
		write(1, "TINY : ", ft_strlen("TINY : "));
		curr = curr->next;
		
	}
	curr = alloc->small_head;
	while(curr != NULL)
	{
		write(1, "SMALL : ", ft_strlen("SMALL : "));
		curr = curr->next;
	}
	curr = alloc->large_head;
	while (curr != NULL)
	{
		if(safe_add_size(total, show_large_zone(curr), &total) == -1)
		{
			//perhaps some erno value here ?
			write(2, "overflow\n", 9);
			return ;
		}
		curr = curr->next;		
	}
	write(1, "Total : ", ft_strlen("Total : "));	
	ft_putszt_fd(total,  1);	
	write(1, " bytes\n", ft_strlen(" bytes\n"));
}
