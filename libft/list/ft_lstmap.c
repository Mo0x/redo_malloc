/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:36:41 by mgovinda          #+#    #+#             */
/*   Updated: 2023/10/27 18:20:51 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*current;
	void	*data;

	new = NULL;
	if (!lst && !f && !del)
		return (NULL);
	while (lst)
	{
		data = f(lst->content);
		current = ft_lstnew(data);
		if (!current)
		{
			ft_lstclear(&new, del);
			del(data);
			return (NULL);
		}
		ft_lstadd_back(&new, current);
		lst = lst->next;
	}
	return (new);
}
