/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 16:36:02 by phakakos          #+#    #+#             */
/*   Updated: 2020/10/20 16:36:03 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void		julia_manual(t_mlx *mlx, char a, char c)
{
	if (a == 0)
	{
		a = mlx->func == &fractal_jul ? 'n' : a;
		a = mlx->func == &fractal_mult ? 'r' : a;
	}
	if (a == 'n')
	{
		if (c == '+')
			mlx->jul.n += JULIA_STEP;
		else if (c == '-')
			mlx->jul.n -= JULIA_STEP;
	}
	else if (a == 'r')
	{
		if (c == '+')
			mlx->jul.r += MULT_STEP;
		else if (c == '-')
			mlx->jul.r -= MULT_STEP;
	}
}

/*
** General mlx loop initiation
** Reset current image. Set current anim_iter to stop animation
** Print variable if verbose
** special exception to not wipe image if barnsley loop is being toggled off
*/

t_mlx		*loop_start(void *param, int key, int x, int y)
{
	t_mlx		*mlx;

	mlx = param;
	if (!(key == K_SPB && mlx->func == &fractal_barn && !mlx->jupt))
		mlx_image_set(mlx->img_dat, mlx->width, mlx->height, DEF_BG);
	mlx->anim_iter = mlx->iter;
	mlx->zo = 0;
	if (mlx->verbose)
	{
		if (key >= 0)
		{
			ft_putstr("key ");
			ft_putnbr(key);
			ft_putchar(' ');
		}
		if (x >= 0 && y >= 0)
		{
			ft_putstr("at x ");
			ft_putnbr(x);
			ft_putstr(" y ");
			ft_putnbr(y);
		}
		ft_putchar('\n');
	}
	return (mlx);
}

/*
** In/decrease iteration cap
*/

void		iter(t_mlx *mlx, char c)
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
}

/*
** Zoom in/out
*/

void		zoom(t_mlx *mlx, char c)
{
	if (c == '+')
		mlx->zoom = mlx->zoom * (1 + ZOOM_STEP);
	else if (c == '-')
		mlx->zoom = mlx->zoom * (1 - ZOOM_STEP);
}
