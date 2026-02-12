/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 20:35:37 by mgovinda          #+#    #+#             */
/*   Updated: 2023/10/21 16:08:49 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*ret;
	size_t	i;
	size_t	j;

	i = 0;
	if (!*little && ft_strlen(little) == 0)
		return ((char *)big);
	while (*(big + i) && i < len)
	{
		j = 0;
		ret = (char *)big + i;
		while (*(big + i + j) == *(little + j) && *(big + i + j)
			&& (i + j) < len)
			j++;
		if (!*(little + j))
			return (ret);
		i++;
	}
	return (0);
}
