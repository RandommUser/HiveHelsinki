/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_live.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 14:00:51 by phakakos          #+#    #+#             */
/*   Updated: 2020/10/21 14:00:52 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/*
** Calculating real and imaginary number for Julia formula
*/

static void	julia_num(t_mlx *mlx)
{
	mlx->jul.cx = map(mlx->mouse_pos.x - mlx->width / 2, (long double[4])
		{-(mlx->width / 2), mlx->width / 2, -(mlx->jul.r), mlx->jul.r});
	mlx->jul.cy = map(mlx->mouse_pos.y - mlx->height / 2, (long double[4])
		{-(mlx->height / 2), mlx->height / 2, -(mlx->jul.r), mlx->jul.r});
}

/*
** Set mouse_pos
** Used to create real and imaginary numbers for Julia
*/

static void	mouse_pos(t_mlx *mlx, int x, int y)
{
	mlx->mouse_pos.x = x;
	mlx->mouse_pos.y = y;
}

/*
** Mouse move loop
** set Julia variables if toggled on
*/

int			mouse_live(int x, int y, void *param)
{
	t_mlx	*mlx;

	mlx = param;
	if (!(x >= 0 && x < mlx->width && y >= 0 && y < mlx->height) ||
		!(!mlx->colort && mlx->jupt && mlx->func != &fractal_barn))
		return (-1);
	mlx = loop_start(param, -1, x, y);
	if (!mlx->jur)
	{
		if (mlx->func == &fractal_mult)
			mlx->jul.r = map(x, (long double[4]){0, mlx->width, MULT_MIN,
				MULT_MAX});
		else
			mouse_pos(mlx, x, y);
	}
	else if (mlx->func == &fractal_jul)
	{
		mlx->jul.r = map(x, (long double[4]){0, mlx->width, 1,
			sqrt(JULIA_MAX_R)});
		mlx->jul.r *= map(y, (long double[4]){0, mlx->height, 1,
			sqrt(JULIA_MAX_R)});
	}
	julia_num(mlx);
	return (draw(mlx));
}
