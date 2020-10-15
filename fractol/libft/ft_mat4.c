/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mat4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 16:05:20 by phakakos          #+#    #+#             */
/*   Updated: 2020/08/12 16:05:21 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

/*
** #include <stdio.h>
** void	mat4_put(t_mat4 mat4)
** {
** 	size_t	row;
** 	size_t	col;
** 	size_t	n;
**
** 	row = -1;
** 	n = 4;
** 	while (++row < n && (col = -1))
** 	{
** 		while (++col < n)
** 			printf("[%f]", mat4.mat[row][col]);
** 		printf("\n");
** 	}
** 	printf("\n");
** }
*/

t_mat4	mat4_ini(void)
{
	t_mat4	ret;
	size_t	row;
	size_t	col;
	size_t	n;

	row = -1;
	n = 4;
	while (++row < n && (col = -1))
		while (++col < n)
			ret.mat[row][col] = 0;
	return (ret);
}

t_mat4	mat4_iden(void)
{
	t_mat4	ret;
	size_t	i;
	size_t	n;

	i = -1;
	n = 4;
	ret = mat4_ini();
	while (++i < n)
		ret.mat[i][i] = 1;
	return (ret);
}

t_mat4	mat4_mat4(t_mat4 mat1, t_mat4 mat2)
{
	t_mat4	ret;
	size_t	row;
	size_t	col;
	size_t	i;
	size_t	n;

	ret = mat4_ini();
	row = -1;
	n = 4;
	while (++row < n && (col = -1))
	{
		while (++col < n && (i = -1))
			while (++i < n)
				ret.mat[row][col] += mat1.mat[row][i] * mat2.mat[i][col];
	}
	return (ret);
}

t_vec4	mat4_vec4(t_mat4 mat4, t_vec4 vec4)
{
	t_vec4	ret;
	size_t	row;
	size_t	col;
	size_t	n;

	n = 4;
	row = -1;
	ret = vec4_ini((long double[4]){0, 0, 0, 0});
	while (++row < n && (col = -1))
		while (++col < n)
			ret.vec[row] += mat4.mat[row][col] * vec4.vec[col];
	return (ret);
}

t_mat4	mat4_rot_inverse(t_mat4 mat)
{
	t_mat4		ret;
	long double	det;
	int			i;
	int			y;

	ret = mat4_ini();
	i = -1;
	while (++i < 3)
		det = 0 + (mat.mat[0][i] * (mat.mat[1][(i + 1) % 3] *
			mat.mat[2][(i + 2) % 3] - mat.mat[1][(i + 2) % 3] *
			mat.mat[2][(i + 1) % 3]));
	if (!(i = -1) || det == 0)
		return (ret);
	while (++i < 3 && (y = -1))
	{
		while (++y < 3)
			ret.mat[i][y] = ((mat.mat[(y + 1) % 3][(i + 1) % 3] *
				mat.mat[(y + 2) % 3][(i + 2) % 3]) -
				(mat.mat[(y + 1) % 3][(i + 2) % 3] *
				mat.mat[(y + 2) % 3][(i + 1) % 3])) / det;
	}
	return (ret);
}
