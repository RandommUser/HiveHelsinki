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

t_mat4		rot_matrix(float rot[4])
{
	t_mat4	trans;

	trans = mat4_iden();
	trans = mat4_mat4(trans, mat4_rotx(rot[0]));
	trans = mat4_mat4(trans, mat4_roty(rot[1]));
	trans = mat4_mat4(trans, mat4_rotz(rot[2]));
	return (trans);
}

void		to_image(t_mlx *mlx, t_vec4 spot)
{
	
	if (spot.vec[0] >= 0 && spot.vec[0] < mlx->width && spot.vec[1] >= 0 && spot.vec[1] < mlx->height)
	{
		if (mlx->height_map[((mlx->size_line / 4) * (int)spot.vec[1]) +
			(int)spot.vec[0]] < spot.vec[2])
		{
			mlx->img_dat[0][((mlx->size_line / 4) * (int)spot.vec[1]) +
			(int)spot.vec[0]] = spot.vec[3];
			mlx->height_map[((mlx->size_line / 4) * (int)spot.vec[1]) +
			(int)spot.vec[0]] = spot.vec[2];
		}/*
		spot.vec[0] = spot.vec[0] - (int)spot.vec[0] >= 0.5 ? (int)spot.vec[0] + 1 : (int)spot.vec[0];
		spot.vec[1] = spot.vec[1] - (int)spot.vec[1] >= 0.5 ? (int)spot.vec[1] + 1 : (int)spot.vec[1];
		if (spot.vec[0] >= 0 && spot.vec[0] < mlx->width && spot.vec[1] >= 0 && spot.vec[1] < mlx->height)
		{
			if (mlx->height_map[((mlx->size_line / 4) * (int)spot.vec[1]) +
				(int)spot.vec[0]] < spot.vec[2])
			{
				mlx->img_dat[0][((mlx->size_line / 4) * (int)spot.vec[1]) +
				(int)spot.vec[0]] = spot.vec[3];
				mlx->height_map[((mlx->size_line / 4) * (int)spot.vec[1]) +
				(int)spot.vec[0]] = spot.vec[2];
			}
		}*/
	}
}

void		three_d(t_mlx *mlx, t_vec4 spot)
{
	int		color;

	color = mlx_get_color_value(mlx->mlx_ptr, (int)normalize(mlx->iter - spot.vec[2], (double[4]){0, mlx->iter, 0x000000, 0xff0000}));
	spot.vec[0] -= mlx->width / 2;
	spot.vec[1] -= mlx->height / 2;
	spot.vec[2] /= 2;
	//spot = mat4_vec4(rot_matrix(mlx->rot), spot);
	spot.vec[0] += mlx->width / 2;
	spot.vec[1] += mlx->height / 2;
	spot.vec[3] = color;
	to_image(mlx, spot);
}

void		three_d_two(t_mlx *mlx, t_frac *frac) // pass width - 1; height - 1;
{
	t_mat4	rot;
	t_vec4	spots[2];	// start, end
	double	pos[5];		//i, x, y, w / 2, h / 2
	int		color;

	rot = rot_matrix(mlx->rot);
	pos[0] = -1;
	pos[3] = (int)(mlx->width / 2);
	pos[4] = (int)(mlx->height / 2);
	pos[2] = frac->y - pos[4];
	pos[1] = -(pos[3]);
	while (++pos[0] < frac->size)
	{
		color = mlx_get_color_value(mlx->mlx_ptr, (int)normalize(mlx->iter - frac->num[(int)pos[0]], (double[4]){0, mlx->iter, 0x000000, 0xff0000}));
		spots[0] = mat4_vec4(rot, vec4_ini((float[4]){pos[1], pos[2], frac->num[(int)pos[0]] / 2, 1}));
		spots[0].vec[0] += pos[3];
		spots[0].vec[1] += pos[4];
		spots[0].vec[0] = spots[0].vec[0] - (int)spots[0].vec[0] >= 0.5 ? (int)spots[0].vec[0] + 1 : (int)spots[0].vec[0];
		spots[0].vec[1] = spots[0].vec[1] - (int)spots[0].vec[1] >= 0.5 ? (int)spots[0].vec[1] + 1 : (int)spots[0].vec[1];
		spots[0].vec[3] = color;
		to_image(mlx, spots[0]);/*
		if (pos[1] + pos[3] > 0)
		{
			color = mlx_get_color_value(mlx->mlx_ptr, (int)normalize(mlx->iter - frac->num[(int)pos[0] - 1], (double[4]){0, mlx->iter, 0x000000, 0xff0000}));
			spots[1] = mat4_vec4(rot, vec4_ini((float[4]){(pos[1] - 1), pos[2], frac->num[(int)pos[0] - 1] / 2, 1}));
			spots[1].vec[0] += pos[3];
			spots[1].vec[1] += pos[4];
			spots[1].vec[0] = spots[1].vec[0] - (int)spots[1].vec[0] >= 0.5 ? (int)spots[1].vec[0] + 1 : (int)spots[1].vec[0];
			spots[1].vec[1] = spots[1].vec[1] - (int)spots[1].vec[1] >= 0.5 ? (int)spots[1].vec[1] + 1 : (int)spots[1].vec[1];
			spots[1].vec[3] = color;
			draw_line(mlx, spots[0], spots[1]);
		}
		if (pos[2] + pos[4] > 0)
		{
			color = mlx_get_color_value(mlx->mlx_ptr, (int)normalize(mlx->iter - frac->num[(int)pos[0] - (mlx->size_line / 4)], (double[4]){0, mlx->iter, 0x000000, 0xff0000}));
			spots[1] = mat4_vec4(rot, vec4_ini((float[4]){pos[1], (pos[2] - 1), frac->num[(int)pos[0] - (mlx->size_line / 4)] / 2, 1}));
			spots[1].vec[0] += pos[3];
			spots[1].vec[1] += pos[4];
			spots[1].vec[0] = spots[1].vec[0] - (int)spots[1].vec[0] >= 0.5 ? (int)spots[1].vec[0] + 1 : (int)spots[1].vec[0];
			spots[1].vec[1] = spots[1].vec[1] - (int)spots[1].vec[1] >= 0.5 ? (int)spots[1].vec[1] + 1 : (int)spots[1].vec[1];
			spots[1].vec[3] = color;
			draw_line(mlx, spots[0], spots[1]);
		}
		if (pos[1] + pos[3] > 0 && pos[2] + pos[4] > 0)
		{
			color = mlx_get_color_value(mlx->mlx_ptr, (int)normalize(mlx->iter - frac->num[(int)pos[0] - (mlx->size_line / 4) - 1], (double[4]){0, mlx->iter, 0x000000, 0xff0000}));
			spots[1] = mat4_vec4(rot, vec4_ini((float[4]){(pos[1] - 1), (pos[2] - 1), frac->num[(int)pos[0] - (mlx->size_line / 4) - 1] / 2, 1}));
			spots[1].vec[0] += pos[3];
			spots[1].vec[1] += pos[4];
			spots[1].vec[0] = spots[1].vec[0] - (int)spots[1].vec[0] >= 0.5 ? (int)spots[1].vec[0] + 1 : (int)spots[1].vec[0];
			spots[1].vec[1] = spots[1].vec[1] - (int)spots[1].vec[1] >= 0.5 ? (int)spots[1].vec[1] + 1 : (int)spots[1].vec[1];
			spots[1].vec[3] = color;
			draw_line(mlx, spots[0], spots[1]);
		}*/
		if (pos[1] + pos[3] == mlx->width)
		{
			pos[1] = -(pos[3]);
			pos[2]++;
		}
		pos[1]++;
	}
}
