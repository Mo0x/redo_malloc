/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:03:54 by mgovinda          #+#    #+#             */
/*   Updated: 2024/02/20 16:08:29 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


/*overflow and underflow*/
static int	ft_isspace(char c)
{
	if (c == ' ' || (c > 8 && c < 14))
		return (1);
	return (0);
}

long long	ft_atoll(const char *nptr)
{
	int	is_neg;
	long long	ret;
	int	i;

	ret = 0;
	is_neg = 1;
	i = 0;
	if (!nptr)
		return (0);
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
