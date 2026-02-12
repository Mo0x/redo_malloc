/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:22:55 by mgovinda          #+#    #+#             */
/*   Updated: 2023/10/20 17:32:49 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	length;
	size_t	dst_length;

	i = 0;
	j = ft_strlen(dst);
	dst_length = ft_strlen(dst);
	length = ft_strlen(dst) + ft_strlen(src);
	if (size == 0 || size <= dst_length)
		return (ft_strlen(src) + size);
	while (i < size - dst_length - 1 && src[i])
	{
		dst[j + i] = src[i];
		i++;
	}
	dst[j + i] = 0;
	return (length);
}
