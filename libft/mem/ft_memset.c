/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:24:43 by mgovinda          #+#    #+#             */
/*   Updated: 2023/10/23 16:23:10 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	void	*ret;
	size_t	i;

	ret = s;
	i = 0;
	while (i < n)
	{
		*(unsigned char *)s = c;
		i++;
		s++;
	}
	return (ret);
}
