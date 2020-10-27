/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_picker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 14:17:00 by phakakos          #+#    #+#             */
/*   Updated: 2020/10/20 14:17:01 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/*
** Writing to the color image
** color_show -> color_spot helper
*/

static void		to_color(t_mlx *mlx, t_vec4 spot)
{
	mlx->clr_dat[((mlx->clr_line / 4) * (int)spot.vec[1]) +
	(int)spot.vec[0]] = spot.vec[3];
}

/*
** Color picker bar color calculation
** color_show helper
*/

static void		color_spot(t_mlx *mlx, t_dot coord, t_rgb color, char c)
{
	if (c == 1)
	{
		to_color(mlx, vec4_ini((long double[4]){coord.x, coord.y, 0,
			rgb_color(255 - coord.y + COLOR_OUTL, 0, 0)}));
		if (255 - coord.y + COLOR_OUTL == color.red)
			to_color(mlx, vec4_ini((long double[4]){coord.x, coord.y, 0,
				rgb_color(255 - color.red, 0, 0)}));
	}
	else if (c == 2)
	{
		to_color(mlx, vec4_ini((long double[4]){coord.x, coord.y, 0,
			rgb_color(0, 255 - coord.y + COLOR_OUTL, 0)}));
		if (255 - coord.y + COLOR_OUTL == color.green)
			to_color(mlx, vec4_ini((long double[4]){coord.x, coord.y, 0,
				rgb_color(0, 255 - color.green, 0)}));
	}
	else if (c == 3)
	{
		to_color(mlx, vec4_ini((long double[4]){coord.x, coord.y, 0,
			rgb_color(0, 0, 255 - coord.y + COLOR_OUTL)}));
		if (255 - coord.y + COLOR_OUTL == color.blue)
			to_color(mlx, vec4_ini((long double[4]){coord.x, coord.y, 0,
				rgb_color(0, 0, 255 - color.blue)}));
	}
}

/*
** Color picker renderinng call
*/

void			color_show(t_mlx *mlx)
{
	t_rgb	color;
	t_dot	coord;
	int		loop;

	if (!mlx->colort)
		return ;
	color = rgb_conv(mlx->color[mlx->colort - 1]);
	loop = 0;
	coord.x = 0;
	while (++loop <= 3)
	{
		coord.x += COLOR_OUTL - 1;
		while (++coord.x < COLOR_OUTL * loop + COLOR_WID * loop)
		{
			coord.y = COLOR_OUTL - 1;
			while (++coord.y <= 255 + COLOR_OUTL)
				color_spot(mlx, coord, color, loop);
		}
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->mlx_win, mlx->clr_swat,
		mlx->width / 2 - (3 * COLOR_WID + 4 * COLOR_OUTL) / 2,
		mlx->height / 2 - (255 + 2 * COLOR_OUTL) / 2);
}

/*
** Color picker mouse event
*/

void			color_pick(t_mlx *mlx, int x, int y)
{
	t_rgb color;

	color = rgb_conv(mlx->color[mlx->colort - 1]);
	if (x >= mlx->width / 2 - (3 * COLOR_WID + 2 * COLOR_OUTL) / 2 &&
	x <= mlx->width / 2 + (3 * COLOR_WID + 2 * COLOR_OUTL) / 2 &&
	y >= mlx->height / 2 - (255) / 2 &&
	y <= mlx->height / 2 + (255) / 2 + 1)
	{
		x -= mlx->width / 2 - (3 * COLOR_WID + 2 * COLOR_OUTL) / 2;
		y -= mlx->height / 2 - (255) / 2;
		if (x < COLOR_WID * 1 + COLOR_OUTL * 0)
			mlx->color[mlx->colort - 1] = rgb_color(255 - y, color.green,
				color.blue);
		else if (x > COLOR_WID * 1 + COLOR_OUTL * 1 && x < COLOR_WID * 2 +
			COLOR_OUTL * 1)
			mlx->color[mlx->colort - 1] = rgb_color(color.red, 255 - y,
				color.blue);
		else if (x > COLOR_WID * 2 + COLOR_OUTL * 2 && x < COLOR_WID * 3 +
			COLOR_OUTL * 2)
			mlx->color[mlx->colort - 1] = rgb_color(color.red, color.green,
				255 - y);
	}
}
