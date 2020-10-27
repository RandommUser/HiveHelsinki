/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 16:14:40 by phakakos          #+#    #+#             */
/*   Updated: 2020/10/20 16:14:41 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/*
** Mouse off set changes
*/

static void		off_set(t_mlx *mlx, int x, int y, char c)
{
	if (c == '+')
	{
		mlx->off.x += (mlx->width / 2 - x) * mlx->zoom;
		mlx->off.y += (mlx->height / 2 - y) * mlx->zoom;
	}
	else if (c == '=')
	{
		mlx->off.x = (x - mlx->width / 2) * mlx->zoom;
		mlx->off.y = (y - mlx->height / 2) * mlx->zoom;
	}
}

/*
** Mouse action loop function
** Move position to center, center to mouse, zoom
*/

int				mouse(int button, int x, int y, void *param)
{
	t_mlx		*mlx;

	mlx = loop_start(param, button, x, y);
	if (mlx->colort)
	{
		if (button == MOU_L)
			color_pick(mlx, x, y);
	}
	else if (button == MOU_L)
		off_set(mlx, x, y, '+');
	else if (button == MOU_R)
		off_set(mlx, x, y, '=');
	else if (button == MOU_S_U)
	{
		off_set(mlx, x, y, '+');
		zoom(mlx, '-');
	}
	else if (button == MOU_S_D)
	{
		off_set(mlx, x, y, '+');
		zoom(mlx, '+');
	}
	else
		return (-1);
	return (draw(mlx));
}
