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

/*
** Animate increasing iteration
*/

int		iter_anim(void *param) // make reset image?
{
	t_mlx	*mlx;
	int		iter;

	mlx = param;
	iter = mlx->iter;
	if (!mlx->colort && ++mlx->anim_iter <= mlx->iter)
	{
		mlx->iter = mlx->anim_iter;
		draw(mlx);
		mlx->iter = iter;
	}
	return (0);
}

/*
** Calculate more points for Barnsley
*/

int		draw_leaf(void *param)
{
	t_mlx	*mlx;

	mlx = param;
	if (mlx->jupt)
		draw(mlx);
	return (0);
}

/*
** Close window (in loop, by pressing X)
*/

int		window_close(void *param)
{
	t_mlx	*mlx;

	mlx = param;
	mlx_destroy_image(mlx->mlx_ptr, mlx->mlx_img);
	mlx_destroy_window(mlx->mlx_ptr, mlx->mlx_win);
	if (mlx->height_map)
		free(mlx->height_map);
	(*mlx->windows)--;
	if (!(*mlx->windows))
		run_exit(X_EXIT, "loops.c window_close() last window\n");
	free(mlx);
	mlx = NULL;
	return (0);
}
