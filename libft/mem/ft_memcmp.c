/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 19:52:22 by mgovinda          #+#    #+#             */
/*   Updated: 2023/10/20 20:30:27 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < (n - 1))
	{
		if (*((unsigned char *)(s1 + i)) != *((unsigned char *)(s2 + i)))
			return (*((unsigned char *)(s1 + i)) - \
				*((unsigned char *)(s2 + i)));
		i++;
	}
	return (*((unsigned char *)(s1 + i)) - *((unsigned char *)(s2 + i)));
}
