/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 16:14:34 by phakakos          #+#    #+#             */
/*   Updated: 2020/10/20 16:14:35 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/*
** Move
*/

static void	off_set(t_mlx *mlx, char a, char c)
{
	if (a == 'x')
	{
		if (c == '+')
			mlx->off.x += OFF_STEP * mlx->zoom;
		else if (c == '-')
			mlx->off.x -= OFF_STEP * mlx->zoom;
	}
	else if (a == 'y')
	{
		if (c == '+')
			mlx->off.y += OFF_STEP * mlx->zoom;
		else if (c == '-')
			mlx->off.y -= OFF_STEP * mlx->zoom;
	}
}

/*
** Rotate set axis
*/

static void	rot(t_mlx *mlx, int i, char c)
{
	if (c == '+')
		mlx->rot[i] += ROTA_STEP;
	else if (c == '-')
		mlx->rot[i] -= ROTA_STEP;
	mlx->rot[i] -= mlx->rot[i] >= 360 ? 360 : 0;
	mlx->rot[i] += mlx->rot[i] <= -360 ? 360 : 0;
}

/*
** mlx_key_loop function, Return of the King
** animate, screen extra, debug, manual julia
*/

static int	input_cc(int key, t_mlx *mlx)
{
	if (key == K_P)
		mlx->anim_iter = ANIM_IT_START;
	else if (key == K_SBS)
		mlx->extra--;
	else if (key == K_SBC)
		mlx->extra++;
	else if (key == K_V)
		mlx->verbose = mlx->verbose ? 0 : 1;
	else if (key == K_COM)
		julia_manual(mlx, 0, '-');
	else if (key == K_DOT)
		julia_manual(mlx, 0, '+');
	else if (key == K_O)
		mlx->zo = 1;
	else
		return (-1);
	return (draw(mlx));
}

/*
** mlx_key_loop function, continued
** rotate, reset, julia variable select, julia live change toggle, color mode
*/

static int	input_c(int key, t_mlx *mlx)
{
	if (key == NUM_2)
		rot(mlx, 0, '+');
	else if (key == NUM_8)
		rot(mlx, 0, '-');
	else if (key == NUM_4)
		rot(mlx, 1, '-');
	else if (key == NUM_6)
		rot(mlx, 1, '+');
	else if (key == NUM_9)
		rot(mlx, 2, '+');
	else if (key == NUM_1)
		rot(mlx, 2, '-');
	else if (key == K_R)
		mlx_def_value(mlx);
	else if (key == K_SPB)
		mlx->jupt = mlx->jupt ? 0 : 1;
	else if (key == K_LCN)
		mlx->jur = mlx->jur ? 0 : 1;
	else if (key == K_T)
		mlx->colort = mlx->colort == 2 ? 0 : mlx->colort + 1;
	else if (key == K_C)
		mlx->clr_func = mlx->clr_func == &map_color ? &map : &map_color;
	else
		return (input_cc(key, mlx));
	return (draw(mlx));
}

/*
** mlx_key_loop function
** Exit, change iter, zoom, move
*/

int			input(int key, void *param)
{
	t_mlx	*mlx;

	mlx = loop_start(param, key, -1, -1);
	if (key == ESC_KEY)
		run_exit(0, "");
	if (key == NUM_P)
		iter(mlx, '+');
	else if (key == NUM_M)
		iter(mlx, '-');
	else if (key == PG_UP)
		zoom(mlx, '-');
	else if (key == PG_DW)
		zoom(mlx, '+');
	else if (key == AR_DW)
		off_set(mlx, 'y', '+');
	else if (key == AR_UP)
		off_set(mlx, 'y', '-');
	else if (key == AR_RG)
		off_set(mlx, 'x', '+');
	else if (key == AR_LF)
		off_set(mlx, 'x', '-');
	else
		return (input_c(key, mlx));
	return (draw(mlx));
}
