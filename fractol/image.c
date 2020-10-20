/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 14:32:43 by phakakos          #+#    #+#             */
/*   Updated: 2020/10/20 14:32:44 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static t_vec4	do_rot(t_mlx *mlx, t_vec4 spot)
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

void			to_image(t_mlx *mlx, t_vec4 spot)
{
	if (mlx->func != &fractal_barn && (mlx->rot[0] != ROT_X ||
		mlx->rot[1] != ROT_Y || mlx->rot[2] != ROT_Z))
		spot = do_rot(mlx, spot);
	if (spot.vec[0] >= 0 && spot.vec[0] < mlx->width && spot.vec[1] >= 0 &&
		spot.vec[1] < mlx->height)
	{
		if (mlx->height_map && mlx->height_map[((mlx->size_line / 4) *
			(int)spot.vec[1]) + (int)spot.vec[0]] < spot.vec[2])
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
