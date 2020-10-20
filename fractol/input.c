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

static void	key_debug(t_mlx *mlx, int key)
{
	if (mlx->verbose)
	{
		ft_putstr("key ");
		ft_putnbr(key);
		ft_putchar('\n');
	}
}

static void	off_set(t_mlx *mlx, char a, char c)
{
	if (a == 'x')
	{
		if (c == '+')
			mlx->offx += OFF_STEP * mlx->zoom;
		else if (c == '-')
			mlx->offx -= OFF_STEP * mlx->zoom;
		printf("offx%c%c %Lf\n", c, c, mlx->offx);//
	}
	else if (a == 'y')
	{
		if (c == '+')
			mlx->offy += OFF_STEP * mlx->zoom;
		else if (c == '-')
			mlx->offy -= OFF_STEP * mlx->zoom;
		printf("offy%c%c %Lf\n", c, c, mlx->offy);//
	}
}

static void	iter(t_mlx *mlx, char c)
{
	if (c == '+')
	{
		mlx->iter += ITER_STEP;
		mlx->iter = mlx->iter > MAX_ITER ? MAX_ITER : mlx->iter;
		mlx->anim_iter = mlx->iter;
	}
	else if (c == '-')
	{
		mlx->iter -= 50;
		mlx->iter = mlx->iter <= 0 ? MIN_ITER : mlx->iter;
		mlx->anim_iter = mlx->iter;
	}
	printf("iter%c%c %d\n", c, c, mlx->iter);//
}

static void	rot(t_mlx *mlx, int i, char c)
{
	if (c == '+')
	{
		mlx->rot[i] += ROTA_STEP;
		mlx->rot[i] -= mlx->rot[i] >= 360 ? 360 : 0;
	}
	else if (c == '-')
	{
		mlx->rot[i] -= ROTA_STEP;
		mlx->rot[i] += mlx->rot[i] <= -360 ? 360 : 0;
	}
}

int			input(int key, void *param)
{
	t_mlx	*mlx;

	mlx = param;
	key_debug(mlx, key);
	mlx_image_set(mlx->img_dat, mlx->width, mlx->height, DEF_BG);
	mlx->anim_iter = mlx->iter;
	if (key == ESC_KEY)
		run_exit(0, "");
	if (key == K_R)
		mlx_def_value(mlx);
	else if (key == NUM_P)
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
	else if (key == NUM_4)
		rot(mlx, 1, '+');
	else if (key == NUM_6)
		rot(mlx, 1, '-');
	else if (key == NUM_2)
		rot(mlx, 0, '+');
	else if (key == NUM_8)
		rot(mlx, 0, '-');
	else if (key == NUM_9)
		rot(mlx, 2, '+');
	else if (key == NUM_1)
		rot(mlx, 2, '-');
	else if (key == K_SPB)
		mlx->jupt = mlx->jupt ? 0 : 1;
	else if (key == K_LCN)
		mlx->jur = mlx->jur ? 0 : 1;
	else if (key == K_COM)
	{
		if (mlx->func == &fractal_jul)
			mlx->jul.n -= JULIA_STEP;
		else if (mlx->func == &fractal_mult)
			mlx->jul.r -= MULT_STEP;
	}
	else if (key == K_DOT)
	{
		if (mlx->func == &fractal_jul)
			mlx->jul.n += JULIA_STEP;
		else if (mlx->func == &fractal_mult)
			mlx->jul.r += MULT_STEP;
	}
	else if (key == K_T)
		mlx->colort = mlx->colort == 2 ? 0 : mlx->colort + 1;
	else if (key == K_C)
		mlx->clr_func = mlx->clr_func == &map_color ? &map : &map_color;
	else if (key == K_P)
		mlx->anim_iter = ANIM_IT_START;
	else if (key == K_SBS)
		mlx->extra--;
	else if (key == K_SBC)
		mlx->extra++;
	else if (key == K_V)
		mlx->verbose = mlx->verbose ? 0 : 1;
	else
		return (-1);
	draw(mlx);
	return (0);
}
