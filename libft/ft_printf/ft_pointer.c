/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:17:55 by mgovinda          #+#    #+#             */
/*   Updated: 2023/11/10 17:45:27 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_sizeaddr(unsigned long addr)
{
	int	ret;

	ret = 0;
	while (addr)
	{
		addr /= 16;
		ret++;
	}
	return (ret);
}

static void	ft_putaddr(int fd, unsigned long addr)
{
	char	*base;

	base = "0123456789abcdef";
	if (addr > 15)
	{
		ft_putaddr(fd, addr / 16);
		ft_putaddr(fd, addr % 16);
	}
	else
		ft_putchar_fd(base[addr], fd);
}

int	ft_pointer(int fd, unsigned long addr)
{
	int		ret;

	ret = 2;
	ft_putstr_fd("0x", 1);
	if (addr == 0)
	{
		ft_putchar_fd('0', fd);
		ret++;
	}
	else
	{
		ft_putaddr(fd, addr);
		ret += ft_sizeaddr(addr);
	}
	return (ret);
}
