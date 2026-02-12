/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:35:46 by mgovinda          #+#    #+#             */
/*   Updated: 2023/11/10 17:42:55 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_string(int fd, char *string)
{
	int	ret;

	ret = 0;
	if (string == NULL)
	{
		ft_putstr_fd("(null)", fd);
		return (6);
	}
	ret = ft_strlen(string);
	ft_putstr_fd(string, fd);
	return (ret);
}
