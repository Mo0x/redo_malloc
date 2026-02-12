/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 17:30:37 by mgovinda          #+#    #+#             */
/*   Updated: 2024/02/05 14:45:20 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define BUFFER_SIZE 1024

static char	*ft_get_line_and_clean(int fd, char **garbage)
{
	char	*ret;
	char	*trashbag;
	int		i;

	i = 0;
	if (!garbage[fd])
		return (NULL);
	while (garbage[fd][i] && garbage[fd][i] != '\n')
		i++;
	if (garbage[fd][i] == '\n')
		i++;
	ret = ft_substr(garbage[fd], 0, i);
	trashbag = ft_substr(garbage[fd], i, ft_strlen(&garbage[fd][i]));
	free(garbage[fd]);
	garbage[fd] = trashbag;
	if (!ret || !trashbag || ft_strlen(ret) == 0)
	{
		free(garbage[fd]);
		free(ret);
		garbage[fd] = NULL;
		return (NULL);
	}
	return (ret);
}

static char	*ft_read_line(int fd, char **garbage, char *buffer)
{
	char	*tmp;
	int		byte_read;

	byte_read = 1;
	while (byte_read >= 0)
	{
		ft_memset(buffer, 0, BUFFER_SIZE + 1);
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read < 0)
		{
			free(garbage[fd]);
			return (NULL);
		}
		if (!garbage[fd])
			garbage[fd] = ft_strdup(buffer);
		else
		{
			tmp = ft_strjoin(garbage[fd], buffer);
			free(garbage[fd]);
			garbage[fd] = tmp;
		}
		if (garbage[fd] && (byte_read == 0 || ft_strchr(garbage[fd], '\n')))
			return (garbage[fd]);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*garbage[1024];
	char		*ret;
	char		*buffer;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	garbage[fd] = ft_read_line(fd, garbage, buffer);
	free(buffer);
	if (!garbage[fd])
		return (NULL);
	ret = ft_get_line_and_clean(fd, garbage);
	return (ret);
}
