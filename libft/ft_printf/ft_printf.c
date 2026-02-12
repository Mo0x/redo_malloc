/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:09:31 by mgovinda          #+#    #+#             */
/*   Updated: 2023/11/10 17:43:09 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_char(int fd, char c)
{
	ft_putchar_fd(c, fd);
	return (1);
}

int	ft_arg(int fd, va_list ap, char fmt)
{
	int		cchar;

	cchar = 0;
	if (fmt == 'c')
		cchar = ft_char(fd, va_arg(ap, int));
	else if (fmt == 's')
		cchar = ft_string(fd, va_arg(ap, char *));
	else if (fmt == 'i' || fmt == 'd')
		cchar = ft_number(fd, va_arg(ap, int));
	else if (fmt == 'u')
		cchar = (int)ft_unsigned(fd, va_arg(ap, unsigned int));
	else if (fmt == 'p')
		cchar = ft_pointer(fd, (unsigned long int)va_arg(ap, void *));
	else if (fmt == 'x' || fmt == 'X')
		cchar = ft_hexa(fd, va_arg(ap, unsigned int), fmt);
	else if (fmt == '%')
		cchar = ft_printpc(fd);
	return (cchar);
}

int	ft_printf(int fd, const char *fmt, ...)
{
	va_list	ap;
	int		cchar;
	int		i;

	i = 0;
	cchar = 0;
	va_start(ap, fmt);
	if (!fmt)
		return (-1);
	while (fmt[i])
	{
		if (fmt[i] == '%' && fmt[i + 1])
		{
			cchar += ft_arg(fd, ap, fmt[i + 1]);
			i++;
		}
		else
		{
			ft_putchar_fd(fmt[i], fd);
			cchar++;
		}
		i++;
	}
	va_end(ap);
	return (cchar);
}
