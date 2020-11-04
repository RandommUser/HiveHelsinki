/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loops.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 15:51:15 by phakakos          #+#    #+#             */
/*   Updated: 2020/10/20 15:51:16 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	window_anim(t_mlx *mlx)
{
	int		iter;

	iter = mlx->iter;
	if (++mlx->anim_iter <= mlx->iter)
	{
		mlx_image_set(mlx->img_dat, mlx->width, mlx->height, DEF_BG);
		mlx->iter = mlx->anim_iter;
		draw(mlx);
		mlx->iter = iter;
		return (1);
	}
	else if (mlx->zo)
	{
		if (mlx->zoom >= 1)
			mlx->zo = 0;
		else
		{
			mlx_image_set(mlx->img_dat, mlx->width, mlx->height, DEF_BG);
			zoom(mlx, '+');
			return (1 - draw(mlx));
		}
	}
	return (0);
}

/*
** Animate increasing iteration
*/

int			iter_anim(void *param)
{
	t_mlx	**mlxs;
	t_mlx	*mlx;
	int		i;

	mlxs = param;
	i = -1;
	while ((mlx = mlxs[++i]))
	{
		if (mlx->colort)
			return (0);
		if (!window_anim(mlx))
			if (mlx->func == &fractal_barn && !mlx->jupt)
				draw(mlx);
	}
	return (0);
}

/*
** Close window (in loop, by pressing X)
*/

int			window_close(void *param)
{
	t_mlx	*mlx;
	t_box	box;

	mlx = param;
	mlx_destroy_image(mlx->mlx_ptr, mlx->mlx_img);
	mlx_destroy_window(mlx->mlx_ptr, mlx->mlx_win);
	if (mlx->height_map)
		free(mlx->height_map);
	(*mlx->windows)--;
	if (!(*mlx->windows))
		run_exit(X_EXIT, "loops.c window_close() last window\n");
	box.j = 0;
	while (mlx->mlxs[box.j] && mlx->mlxs[box.j] != mlx)
		box.j++;
	box.k = box.j;
	while (mlx->mlxs[box.k])
		box.k++;
	box.k--;
	mlx->mlxs[box.j] = mlx->mlxs[box.k];
	mlx->mlxs[box.k] = NULL;
	free(mlx);
	mlx = NULL;
	return (0);
}
