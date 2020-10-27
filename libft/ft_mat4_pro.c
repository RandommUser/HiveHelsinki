/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mat4_pro.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 13:16:28 by phakakos          #+#    #+#             */
/*   Updated: 2020/08/31 13:16:30 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

t_mat4	mat4_perps(t_vec4 vec)
{
	t_mat4	proj;

	proj = mat4_scales((long double[4]){1, 1, 0, 1});
	proj.mat[0][2] = vec.vec[0] / vec.vec[1];
	proj.mat[1][2] = vec.vec[1] / vec.vec[2];
	proj.mat[2][2] = 1 / vec.vec[2];
	return (proj);
}

t_mat4	mat4_pro(void)
{
	t_mat4	proj;

	proj = mat4_scales((long double[4]){1, 1, 1, 0});
	proj.mat[3][2] = 1;
	return (proj);
}

/*
** near, far, fov, ? || width / height
*/

t_mat4	mat4_perps2(t_vec4 vec, long double ar)
{
	t_mat4		proj;
	long double	tant;
	long double	range;

	tant = tan((double)vec.vec[2] * (3.14159265 / 180) / 2);
	range = vec.vec[0] - vec.vec[1];
	proj = mat4_ini();
	proj.mat[2][3] = 1;
	proj.mat[0][0] = 1 / (tant * ar);
	proj.mat[1][1] = 1 / tant;
	proj.mat[2][2] = (-(vec.vec[0]) - vec.vec[1]) / range;
	proj.mat[3][2] = 2 * vec.vec[1] * vec.vec[0] / range;
	return (proj);
}

/*
** focal, skew, cam x, cam y
*/

t_mat4	mat4_pinhole(t_vec4 vec, long double ar)
{
	t_mat4	proj;

	proj = mat4_iden();
	proj.mat[0][0] = vec.vec[0];
	proj.mat[0][1] = vec.vec[1];
	proj.mat[0][2] = vec.vec[2];
	proj.mat[1][1] = vec.vec[0] * ar;
	proj.mat[1][2] = vec.vec[3];
	return (proj);
}
