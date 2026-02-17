#include "libft.h"
#include <stddef.h>

void  ft_putszt_fd(size_t n, int fd)
{
  if (n > 9)
  {
    ft_putszt_fd(n / 10, fd);
    ft_putszt_fd(n % 10, fd);
  }
  else
    ft_putchar_fd(n + '0', fd);
}
