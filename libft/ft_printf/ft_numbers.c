/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numbers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:17:15 by mgovinda          #+#    #+#             */
/*   Updated: 2023/11/10 17:45:05 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_number(int fd, int nb)
{
	int	ret;

	ret = 0;
	if (nb == 0)
	{
		ft_putchar_fd('0', fd);
		return (1);
	}
	if (nb < 0)
		ret++;
	ft_putnbr_fd(nb, fd);
	while (nb)
	{
		nb /= 10;
		ret++;
	}
	return (ret);
}

unsigned int	ft_unsigned(int fd, unsigned int nb)
{
	unsigned int	ret;
	unsigned int	copy;

	if (nb == 0)
	{
		ft_putchar_fd('0', fd);
		return (1);
	}
	copy = nb;
	ret = 0;
	if (nb > 9)
	{
		ft_unsigned(fd, nb / 10);
		ft_unsigned(fd, nb % 10);
	}
	else
		ft_putchar_fd(nb + '0', fd);
	while (copy)
	{
		copy /= 10;
		ret++;
	}
	return (ret);
}
