/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 13:52:47 by phakakos          #+#    #+#             */
/*   Updated: 2020/08/11 13:52:48 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/*
** #include <stdio.h>
** void    vecn_put(t_vecn *vecn, size_t n)
** {
**     size_t  i;
**
**     i = -1;
**     while (++i < n)
**         printf("[%f]", vecn->vec[i]);
**     printf("\n");
** }
*/

void	vecn_free(t_vecn *vecn)
{
	free(vecn->vec);
	ft_memdel((void**)vecn);
}

t_vecn	*vecn_cpy(float *vecn, size_t n)
{
	t_vecn	*ret;
	size_t	i;

	if (!vecn || !(ret = malloc((sizeof(t_vecn)))))
		return (NULL);
	if (!(ret->vec = (float*)malloc(sizeof(float) * n)))
	{
		free(ret);
		return (NULL);
	}
	i = -1;
	while (++i < n)
		ret->vec[i] = vecn[i];
	return (ret);
}

t_vecn	*vecn_ini(size_t n)
{
	t_vecn	*ret;
	size_t	i;

	if (!(ret = malloc((sizeof(t_vecn)))))
		return (NULL);
	if (!(ret->vec = (float*)malloc(sizeof(float) * n)))
	{
		free(ret);
		return (NULL);
	}
	i = -1;
	while (++i < n)
		ret->vec[i] = 0;
	return (ret);
}
