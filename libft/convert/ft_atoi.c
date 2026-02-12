/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 16:12:59 by mgovinda          #+#    #+#             */
/*   Updated: 2024/02/23 15:16:14 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static int	ft_isspace(char c)
{
	if (c == ' ' || (c > 8 && c < 14))
		return (1);
	return (0);
}


static int ft_overflow(int prev, int to_add, int is_neg)
{
	if (is_neg == 1)
	{
		if (prev > INT_MAX - to_add)
			return (1);
	}
	else 
	{
		if (prev < INT_MIN - to_add)
			return (1);
	}
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	is_neg;
	int	ret;
	int	i;

	ret = 0;
	is_neg = 1;
	i = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			is_neg = -1;
		i++;
	}
	while ((nptr[i] > 47 && nptr[i] < 58) && nptr[i])
		ret = (ret * 10) + (nptr[i++] - '0');
	return (ret * is_neg);
}
static int	ft_overdetected(int is_neg)
{
	if (is_neg == 1)
		return (INT_MAX);
	else
		return (INT_MIN);
}
int	ft_atoi_safe(const char *nptr, int *over)
{
	int	is_neg;
	int	ret;
	int	i;

	ret = 0;
	is_neg = 1;
	i = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			is_neg = -1;
		i++;
	}
	while ((nptr[i] > 47 && nptr[i] < 58) && nptr[i])
	{
		if (ft_overflow(ret, nptr[i++] - '0', is_neg))
		{
			*over = 1;
			return (ft_overdetected(is_neg));
		}
		ret = (ret * 10) + (nptr[i++] - '0');
	}
	return (ret * is_neg);
}
