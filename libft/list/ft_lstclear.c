/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:01:12 by mgovinda          #+#    #+#             */
/*   Updated: 2024/02/01 17:37:54 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;

	(void)del;
	if (lst && (*del))
	{
		while (*lst)
		{
			current = *lst;
			*lst = current->next;
			free(current);
		}
	}
	lst = NULL;
}
