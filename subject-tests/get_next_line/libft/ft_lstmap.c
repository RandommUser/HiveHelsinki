/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 14:38:06 by phakakos          #+#    #+#             */
/*   Updated: 2019/11/11 12:12:27 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static t_list	*lst_undo(t_list *lst)
{
	if (lst->next)
		lst_undo(lst->next);
	if (lst->content_size > 0)
		free(lst->content);
	free(lst);
	return (NULL);
}

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*start;
	t_list	*temp;
	t_list	*rtn;
	t_list	*current;

	if (!lst || !f)
		return (NULL);
	temp = f(lst);
	if (!(start = ft_lstnew(temp->content, temp->content_size)))
		return (NULL);
	lst = lst->next;
	current = start;
	temp = NULL;
	while (lst)
	{
		temp = f(lst);
		if (!(rtn = ft_lstnew(temp->content, temp->content_size)))
			return (lst_undo(start));
		current->next = rtn;
		current = current->next;
		temp = NULL;
		rtn = NULL;
		lst = lst->next;
	}
	return (start);
}
