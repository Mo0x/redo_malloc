/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:04:44 by mgovinda          #+#    #+#             */
/*   Updated: 2024/02/22 16:24:40 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	if (c == ' ' || (c > 8 && c < 14))
		return (1);
	return (0);
}

static double ft_decimal (char *s)
{
	long double	ret;
	double		i;

	i = 10;
	ret = 0;
	while (ft_isdigit((int)(*s)))
	{
		ret += (1.0 / i) * ((*s) - '0');
		i *= 10;
		s++;
	}
	return ((double)ret);
}


double	ft_atod(char *str)
{
	int		is_neg;
	double	ret;
	int		i;
	double	deci;

	ret = 0;
	is_neg = 1;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			is_neg = -1;
		i++;
	}
	while ((str[i] > 47 && str[i] < 58) && str[i])
		ret = (ret * 10) + (str[i++] - '0');
	if (str[i] == '.' && str[i])
		deci = ft_decimal(str + i + 1);
	return ((ret + deci) * is_neg);
}
