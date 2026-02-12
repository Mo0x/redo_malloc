/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:12:18 by mgovinda          #+#    #+#             */
/*   Updated: 2023/10/20 15:43:07 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	int		i;
	void	*ret;

	ret = dest;
	i = 0;
	if (src == NULL && dest == NULL)
		return (ret);
	while (i < (int) n)
	{
		*(unsigned char *)dest = *(unsigned char *)src;
		dest++;
		src++;
		i++;
	}
	return (ret);
}
