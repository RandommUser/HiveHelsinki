/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 16:33:50 by phakakos          #+#    #+#             */
/*   Updated: 2020/08/29 16:33:52 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/*
** mouse and keyboard action
** 0) thick lines 1) rotation cube toggle 2) fov limitor 3) map mode toggle
** 4) map color toggle (depth/height)
*/

void	actions1(int func, t_map *map)
{
	if (func == 0)
		map->thick = map->thick ? 0 : 1;
	else if (func == 1)
		map->rot.vec[3] = map->rot.vec[3] == 1 ? 2 : 1;
	else if (func == 2)
		map->limit = map->limit == 1 ? 0 : 1;
	else if (func == 3)
	{
		map->mode++;
		map->mode = map->mode > 3 ? 1 : map->mode;
	}
	else if (func == 4)
		map->color = map->color == 0 ? 1 : 0;
}

/*
** 0) moving vanishing point 1) map zoom 2) FOV change 3) height modifier
*/

void	actions2(int func, t_map *map, float dir)
{
	if (func == 0)
		map->cam.plan.vec[3] += dir > 0 ? 1 : -1;
	else if (func == 1)
		map->zoom = dir > 0 ? map->zoom * 1.2 : map->zoom / 1.2;
	else if (func == 2 && map->mode > 1)
	{
		map->cam.plan.vec[2] += FOV_STEP * dir;
		if ((map->limit && map->cam.plan.vec[2] >= 180) ||
			(map->limit && map->cam.plan.vec[2] <= 0))
			map->cam.plan.vec[2] -= FOV_STEP * dir;
	}
	else if (func == 3)
	{
		map->h_mod *= dir;
	}
}

/*
** 0) map rotating 1) map move
*/

void	actions3(int func, t_map *map, int ang, int dir)
{
	if (func == 0)
	{
		if (map->mode > 1)
		{
			map->cam.rot.vec[ang] += ROTA_STEP / 2 * dir;
			if (map->cam.rot.vec[ang] <= -360 || map->cam.rot.vec[ang]
				>= 360)
				map->cam.rot.vec[ang] = (ft_abs(map->cam.rot.vec[ang])
					- 360) * dir;
		}
		else
		{
			map->rot.vec[ang] += (ROTA_STEP * dir);
			if (map->rot.vec[ang] <= -360 || map->rot.vec[ang] >= 360)
				map->rot.vec[ang] = (ft_abs(map->rot.vec[ang]) - 360) * dir;
		}
	}
	else if (func == 1)
	{
		if (map->mode > 1)
			map->cam.loc.vec[ang] += WIDTH * dir;
		else
			map->origin.mat[ang][3] += WIDTH * dir;
	}
}

/*
** 0) map mouse select 1) key map select
*/

void	actions4(int func, t_mlx *mlx, int x, int y)
{
	size_t	i;

	if (func == 0 && mlx->mode == 2)
	{
		i = 0;
		while (++i < 5)
		{
			if (x >= mlx->map[i]->pos.vec[2] && x <= (mlx->map[i]->pos.vec[2]
				+ mlx->map[i]->pos.vec[0]))
				if (y >= mlx->map[i]->pos.vec[3] && y <=
					(mlx->map[i]->pos.vec[3] + mlx->map[i]->pos.vec[1]))
				{
					mlx->smap = mlx->map[i];
					return ;
				}
		}
	}
	else if (func == 1)
	{
		if (mlx->mode == 2 && x > 0 && x < 5)
			mlx->smap = mlx->map[x];
		else if (mlx->mode == 1 && mlx->smap != mlx->map[--x])
			map_anim(mlx, mlx->smap, mlx->map[x]);
	}
}

/*
** 0) mouse move 1) camera plain changes
*/

void	actions5(int func, t_map *map, int x, int y)
{
	if (func == 0)
	{
		if (map->mode > 1)
		{
			map->cam.loc.vec[0] = x;
			map->cam.loc.vec[1] = y;
		}
		else
		{
			map->origin.mat[0][3] = x;
			map->origin.mat[1][3] = y;
		}
	}
	else if (func == 1 && map->mode > 1)
	{
		map->cam.plan.vec[x] += WIDTH / 2 * y;
		if (map->cam.plan.vec[0] == map->cam.plan.vec[1])
			map->cam.plan.vec[x] -= WIDTH / 2 * y;
	}
}
