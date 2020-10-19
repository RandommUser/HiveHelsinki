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

t_mat4		rot_matrix(long double rot[3])
{
	t_mat4	trans;

	trans = mat4_iden();
	trans = mat4_mat4(trans, mat4_rotx(rot[0]));
	trans = mat4_mat4(trans, mat4_roty(rot[1]));
	trans = mat4_mat4(trans, mat4_rotz(rot[2]));
	return (trans);
}

void		to_color(t_mlx *mlx, t_vec4 spot)
{
	mlx->clr_dat[((mlx->clr_line / 4) * (int)spot.vec[1]) +
	(int)spot.vec[0]] = spot.vec[3];
}

void	mat4_put(t_mat4 mat4)//
{
	size_t	row;
	size_t	col;
	size_t	n;

	row = -1;
	n = 4;
	while (++row < n && (col = -1))
	{
		while (++col < n)
			printf("[%Lf]", mat4.mat[row][col]);
		printf("\n");
	}
	printf("\n");
}


t_vec4		do_rot(t_mlx *mlx, t_vec4 spot)
{
	t_box	box;

	box.w = mlx->width / 2;
	box.h = mlx->height / 2;
	spot.vec[0] -= box.w;
	spot.vec[1] -= box.h;
	spot = mat4_vec4(rot_matrix(mlx->rot), spot);
	spot.vec[0] += box.w;
	spot.vec[1] += box.h;
	if (spot.vec[0] - (int)spot.vec[0] >= 0.5)
		spot.vec[0]++;
	if (spot.vec[1] - (int)spot.vec[1] >= 0.5)
		spot.vec[1]++;
	return (spot);
}

void		to_image(t_mlx *mlx, t_vec4 spot)
{
	if (mlx->func != &fractal_barn && (mlx->rot[0] != ROT_X || mlx->rot[1] != ROT_Y || mlx->rot[2] != ROT_Z))
		spot = do_rot(mlx, spot);
	if (spot.vec[0] >= 0 && spot.vec[0] < mlx->width && spot.vec[1] >= 0 && spot.vec[1] < mlx->height)
	{
		if (mlx->height_map && mlx->height_map[((mlx->size_line / 4) * (int)spot.vec[1]) +
			(int)spot.vec[0]] < spot.vec[2])
		{
			mlx->height_map[((mlx->size_line / 4) * (int)spot.vec[1]) +
			(int)spot.vec[0]] = spot.vec[2];
		}
		else if (mlx->height_map)
			return ;
		mlx->img_dat[((mlx->size_line / 4) * (int)spot.vec[1]) +
			(int)spot.vec[0]] = spot.vec[3];
	}
}
