/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 13:52:54 by phakakos          #+#    #+#             */
/*   Updated: 2020/08/11 13:52:55 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/*
** #include <stdio.h>
** void    matn_put(t_matn *matn, size_t n)
** {
** 	size_t	row;
** 	size_t	col;
**
**     row = -1;
** 	while (++row < n && (col = -1))
**     {
** 		while (++col < n)
**             printf("[%f]", matn->mat[row][col]);
**         printf("\n");
**     }
**     printf("\n");
** }
*/

void	*matn_free(t_matn *matn, size_t n)
{
	while (n-- > 0)
		free(matn->mat[n]);
	if (!n)
		free(matn->mat);
	ft_memdel((void**)matn);
	return (NULL);
}

void	matn_scale_set(t_matn *matn, float *s, size_t n)
{
	size_t	i;

	i = -1;
	while (++i < n)
		matn->mat[i][i] = s[i];
}

void	matn_scale_flat(t_matn *matn, float s, size_t n)
{
	size_t	i;

	i = -1;
	while (++i < n)
		matn->mat[i][i] = s;
}

t_matn	*matn_matn(t_matn *mat1, t_matn *mat2, size_t n)
{
	t_matn	*ret;
	size_t	row;
	size_t	col;
	size_t	i;

	if (!(ret = (t_matn*)malloc(sizeof(t_matn*))))
		return (NULL);
	if (!(ret->mat = (float**)malloc(sizeof(float*) * n)))
		return (matn_free(ret, -1));
	row = -1;
	while (++row < n && (col = -1))
	{
		if (!(ret->mat[row] = (float*)malloc(sizeof(float) * n)))
			return (matn_free(ret, row));
		ft_memset(ret->mat[row], 0, sizeof(float) * n);
		while (++col < n && (i = -1))
		{
			while (++i < n)
			{
				ret->mat[row][col] += mat1->mat[row][i] * mat2->mat[i][col];
			}
		}
	}
	return (ret);
}

t_vecn	*matn_vecn(t_matn *mat, t_vecn *vec, size_t n)
{
	t_vecn	*ret;
	size_t	row;
	size_t	col;

	if (!(ret = vecn_ini(n)))
		return (NULL);
	row = -1;
	while (++row < n && (col = -1))
	{
		while (++col < n)
		{
			ret->vec[row] += mat->mat[row][col] * vec->vec[col];
		}
	}
	return (ret);
}
