/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 14:31:45 by phakakos          #+#    #+#             */
/*   Updated: 2019/11/08 18:54:36 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*lst;

	if (!alst || !del)
		return ;
	lst = *alst;
	if (lst->next)
		ft_lstdel(&lst->next, del);
	del(lst->content, lst->content_size);
	free(*alst);
	*alst = NULL;
}
