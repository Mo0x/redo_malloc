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

ssize_t round_requested_size_to_alignment(size_t requested, uintptr_t alignment)
{
	if (!(is_power_of_2(alignment)))
		return -1;
	uintptr_t modulo = requested & (alignment - 1);

	if (!(requested % alignment))
		return requested;
	else
	{
		if (requested >  SSIZE_MAX + (alignment - modulo))
		{
			errno = ENOMEM; 
			return -1;
		}
		return (requested + (alignment - modulo)); //have to make sure we don't overflow idk how 
	}
}
