#include "libft_malloc.h"

int  is_power_of_2(uintptr_t x)
{
	if (x == 0)
		return 0;
	return (x & (x - 1)) == 0;
}

//padding here is only byte between header and the user pointer aligned
ssize_t calc_padding_from_address(uintptr_t ptr, uintptr_t alignment)
{
	if (!(is_power_of_2(alignment)))
		return -1;
	uintptr_t p = ptr;
	uintptr_t a = alignment; 
	uintptr_t modulo = p & (a - 1); // == p % a as a is power of 2

	if (!modulo)
		return 0;
	else
		return (a - modulo);
}

// IF -1 set errno ENOMEM !
ssize_t round_requested_size_to_alignment(size_t requested, uintptr_t alignment)
{
	// if (!(is_power_of_2(alignment)))
	// 	return -1;
	uintptr_t modulo = requested & (alignment - 1);

	if (!(modulo))
		return requested;
	else
	{
		if (requested >  SIZE_MAX + (alignment + modulo))
		{
			//errno = ENOMEM; 
			return -1;
		}
		return (requested + (alignment - modulo)); //have to make sure we don't overflow idk how 
	}
}

uintptr_t get_raw_user_ptr(t_block_header *block)
{
 	return ((uintptr_t)block + sizeof(t_block_header));
}

ssize_t compute_user_padding(uintptr_t raw_user, size_t alignment)
{
	return (calc_padding_from_address(raw_user, alignment));
}

uintptr_t get_ret_ptr(uintptr_t raw_user, size_t padding)
{
	return (raw_user + padding);
}

int is_aligned(uintptr_t ptr, size_t alignment)
{
	return (ptr % alignment == 0 ? 1 : 0);
}
