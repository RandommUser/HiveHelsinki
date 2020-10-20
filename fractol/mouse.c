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

static void	mouse_debug(t_mlx *mlx, int x, int y, int button)
{
	if (mlx->verbose)
	{
		ft_putstr("pressed ");
		ft_putnbr(button);
		ft_putstr(" at x ");
		ft_putnbr(x);
		ft_putstr(" y ");
		ft_putnbr(y);
		ft_putchar('\n');
	}
}

static void	off_set(t_mlx *mlx, int x, int y, char c)
{
	if (c == '+')
	{
		mlx->offx += (mlx->width / 2 - x) * mlx->zoom;
		mlx->offy += (mlx->height / 2 - y) * mlx->zoom;
	}
	else if (c == '=')
	{
		mlx->offx = (x - mlx->width / 2) * mlx->zoom;
		mlx->offy = (y - mlx->height / 2) * mlx->zoom;
	}
}

int	mouse(int button, int x, int y, void *param)
{
	t_mlx		*mlx;

	mlx = param;
	mlx_image_set(mlx->img_dat, mlx->width, mlx->height, DEF_BG);
	mlx->anim_iter = mlx->iter;
	mouse_debug(mlx, x, y, button);
	if (mlx->colort)
	{
		if (button == MOU_L)
			color_pick(mlx, x, y);
		return (0);
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
	draw(mlx);
	aim_rec(mlx);
	return (0);
}
