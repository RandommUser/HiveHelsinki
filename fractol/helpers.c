/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 11:07:16 by phakakos          #+#    #+#             */
/*   Updated: 2020/09/16 11:07:17 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/*
** Return color based on iter position
*/

int			iter_color(t_frac *frac, t_vec4 point)
{
	return (mlx_get_color_value(frac->mlx->mlx_ptr, (int)frac->mlx->clr_func(
		frac->iter - point.vec[2], (long double[4]){0, frac->iter,
		frac->mlx->color[1], frac->mlx->color[0]})));
}

/*
** Calculate current rotation matrix
*/

t_mat4		rot_matrix(long double rot[3])
{
	t_mat4	trans;

	trans = mat4_iden();
	trans = mat4_mat4(trans, mat4_rotx(rot[0]));
	trans = mat4_mat4(trans, mat4_roty(rot[1]));
	trans = mat4_mat4(trans, mat4_rotz(rot[2]));
	return (trans);
}

/*
** Set heigh_map to set value
*/

void		height_reset(long double *arr, long double val, int w, int h)
{
	int	i;

	i = -1;
	while (++i < w * h)
		arr[i] = val;
}

long double	map(long double p, long double arr[4])
{
	p = (p - arr[0]) / (arr[1] - arr[0]);
	p = (arr[3] - arr[2]) * p + arr[2];
	return (p);
}

/*
** map() but proper color flow
*/

long double	map_color(long double p, long double arr[4])
{
	t_rgb colors[2];

	colors[0] = rgb_conv((long)arr[2]);
	colors[1] = rgb_conv((long)arr[3]);
	p = (p - arr[0]) / (arr[1] - arr[0]);
	colors[0].red = (colors[1].red - colors[0].red) * p + colors[0].red;
	colors[0].green = (colors[1].green - colors[0].green) * p +
		colors[0].green;
	colors[0].blue = (colors[1].blue - colors[0].blue) * p + colors[0].blue;
	return (trgb_conv(colors[0]));
}
