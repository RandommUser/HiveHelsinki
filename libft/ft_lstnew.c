/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 14:22:02 by phakakos          #+#    #+#             */
/*   Updated: 2019/11/08 18:55:10 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*rtn;

	if (!(rtn = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (!content)
	{
		rtn->content = NULL;
		rtn->content_size = 0;
	}
	else
	{
		if (!(rtn->content = (void *)malloc(content_size)))
		{
			free(rtn);
			return (NULL);
		}
		rtn->content = ft_memcpy(rtn->content, content, content_size);
		rtn->content_size = content_size;
	}
	rtn->next = NULL;
	return (rtn);
}
