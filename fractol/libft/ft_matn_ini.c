/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matn_ini.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 13:31:14 by phakakos          #+#    #+#             */
/*   Updated: 2020/08/31 13:31:16 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_matn	*matn_cpy(float *src, size_t n)
{
	t_matn	*ret;
	size_t	row;
	size_t	col;
	size_t	i;

	if (!src || !(ret = (t_matn*)malloc(sizeof(t_matn*))))
		return (NULL);
	if (!(ret->mat = (float**)malloc(sizeof(float*) * n)))
		return (matn_free(ret, -1));
	row = -1;
	i = -1;
	while (++row < n && (col = -1))
	{
		if (!(ret->mat[row] = (float*)malloc(sizeof(float) * n)))
			return (matn_free(ret, row));
		while (++col < n && ++i >= 0)
		{
			ret->mat[row][col] = src[i];
		}
	}
	return (ret);
}

t_matn	*matn_ini(size_t n)
{
	t_matn	*ret;
	size_t	row;

	if (!(ret = (t_matn*)malloc(sizeof(t_matn*))))
		return (NULL);
	if (!(ret->mat = (float**)malloc(sizeof(float*) * n)))
		return (matn_free(ret, -1));
	row = -1;
	while (++row < n)
	{
		if (!(ret->mat[row] = (float*)malloc(sizeof(float) * n)))
			return (matn_free(ret, row));
		ft_memset(ret->mat[row], 0, sizeof(float) * n);
	}
	return (ret);
}

t_matn	*matn_iden(size_t n)
{
	t_matn	*ret;

	if (!(ret = matn_ini(n)))
		return (NULL);
	matn_scale_flat(ret, 1, n);
	return (ret);
}

t_matn	*matn_scale_ini(float s, size_t n)
{
	t_matn	*ret;
	size_t	i;

	if (!(ret = matn_ini(n)))
		return (NULL);
	i = -1;
	while (++i < n)
		ret->mat[i][i] = s;
	return (ret);
}

t_matn	*matn_scale_sini(float *s, size_t n)
{
	t_matn	*ret;
	size_t	i;

	if (!(ret = matn_ini(n)))
		return (NULL);
	i = -1;
	while (++i < n)
		ret->mat[i][i] = s[i];
	return (ret);
}
