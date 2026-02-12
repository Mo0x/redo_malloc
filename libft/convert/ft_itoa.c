/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:00:21 by mgovinda          #+#    #+#             */
/*   Updated: 2023/10/25 18:55:23 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_zero(void)
{
	char	*ret;

	ret = malloc(sizeof(char) * 2);
	if (!ret)
		return (NULL);
	ret[0] = '0';
	ret[1] = 0;
	return (ret);
}

char	*ft_revtab(char *src)
{
	int		i;
	int		length;
	char	tmp;

	length = (int)ft_strlen(src) - 1;
	i = 0;
	while (i < length)
	{
		tmp = src[length];
		src[length] = src[i];
		src[i] = tmp;
		i++;
		length--;
	}
	return (src);
}

char	*ft_itoa(int n)
{
	int				is_neg;
	char			tmp[12];
	int				i;
	unsigned int	nb;

	i = 0;
	is_neg = 0;
	if (n < 0)
	{
		is_neg = 1;
		nb = -n;
	}
	else
		nb = n;
	if (nb == 0)
		return (ft_zero());
	while (nb)
	{
		tmp[i++] = (nb % 10) + '0';
		nb /= 10;
	}
	if (is_neg)
		tmp[i++] = '-';
	tmp[i] = 0;
	return (ft_strdup(ft_revtab(tmp)));
}
