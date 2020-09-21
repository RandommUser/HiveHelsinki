/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 16:30:05 by phakakos          #+#    #+#             */
/*   Updated: 2020/09/21 16:30:07 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static t_mat4	rot_matrix(float rot[4])
{
	t_mat4	trans;

	trans = mat4_iden();
	trans = mat4_mat4(trans, mat4_rotx(rot[0]));
	trans = mat4_mat4(trans, mat4_roty(rot[1]));
	trans = mat4_mat4(trans, mat4_rotz(rot[2]));
	return (trans);
}

void		three_d(t_mlx *mlx, t_vec4 spot)
{
	int		color;

	color = mlx_get_color_value(mlx->mlx_ptr, (int)normalize(mlx->iter - spot.vec[2], (double[4]){0, mlx->iter, 0x000000, 0xff0000}));
	spot.vec[0] -= mlx->width / 2;
	spot.vec[1] -= mlx->height / 2;
	spot = mat4_vec4(rot_matrix(mlx->rot), spot);
	spot.vec[0] += mlx->width / 2;
	spot.vec[1] += mlx->height / 2;
	if (spot.vec[0] >= 0 && spot.vec[0] < mlx->width && spot.vec[1] >= 0 && spot.vec[1] < mlx->height)
	{
		mlx->img_dat[0][((mlx->size_line / 4) * (int)spot.vec[1]) +
			(int)spot.vec[0]] = color;
	}
}
