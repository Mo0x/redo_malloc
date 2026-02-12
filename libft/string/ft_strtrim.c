/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:32:10 by mgovinda          #+#    #+#             */
/*   Updated: 2023/10/25 17:06:40 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	int		i;
	int		length;
	int		j;

	if (set == 0)
		return (ft_strdup(s1));
	if (s1 == 0)
		return (NULL);
	length = (int)ft_strlen(s1);
	i = 0;
	j = 0;
	while (ft_isset(s1[i], set))
		i++;
	if (i == length)
		return (ft_calloc(1, 1));
	while (ft_isset(s1[length - 1], set))
		length--;
	ret = (char *)malloc(sizeof(char) * (length - i + 1));
	if (!ret)
		return (NULL);
	while (i < length)
		ret[j++] = s1[i++];
	ret[j] = 0;
	return (ret);
}
