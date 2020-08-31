/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 17:07:01 by phakakos          #+#    #+#             */
/*   Updated: 2020/08/29 17:07:04 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/*
** general map setting reset
** mapN_reset helper -> map_reset helper
*/

void	map_gen_reset(t_mlx *mlx, t_map *map)
{
	map->cam.plan = vec4_ini((float[4]){0, 100, FOV_DEF, -1});
	map->h_mod = H_MOD;
	map->zoom = ZOOM_DEF;
	map->limit = 1;
	if (map != mlx->map[0])
	{
		map->pos.vec[0] = mlx->width / 2 - 1;
		map->pos.vec[1] = mlx->height / 2 - 1;
		map->pos.vec[2] = 0;
		map->pos.vec[3] = 0;
	}
}

/*
** smart map reset call
*/

void	map_reset(t_mlx *mlx, t_map *map)
{
	if (map == mlx->map[1])
		map1_reset(mlx, map);
	else if (map == mlx->map[2])
		map2_reset(mlx, map);
	else if (map == mlx->map[3])
		map3_reset(mlx, map);
	else if (map == mlx->map[4])
		map4_reset(mlx, map);
	else
		map0_reset(mlx, map);
}

/*
** initial settings (re)set
*/

void	settings_reset(t_map *map, t_mlx *mlx)
{
	mlx->mode = 1;
	mlx->smap = mlx->map[0];
	map->thick = 0;
	map->rot = vec4_ini((float[4]){ROTA_X, ROTA_Y, ROTA_Z, ROTA_W});
	map->mode = MODE_DEF;
	map->h_mod = H_MOD;
	map->pos = vec4_ini((float[4]){mlx->width, mlx->height, 0, 0});
	map->zoom = ZOOM_DEF;
	zoom_check(map);
	map->cam.loc = vec4_ini((float[4]){(int)(map->pos.vec[0] / 2),
		(int)(map->pos.vec[1] / 2), 0, 1});
	map->cam.plan = vec4_ini((float[4]){0, 100, FOV_DEF, -1});
	map->cam.rot = vec4_ini((float[4]){90, 90, 0, 1});
	map->origin = mat4_trans((float[3]){mlx->width / 2, mlx->height / 2, 1});
	map->limit = 1;
	map->color = 0;
	mlx->map[1] = map_copy(mlx);
	mlx->map[2] = map_copy(mlx);
	mlx->map[3] = map_copy(mlx);
	mlx->map[4] = map_copy(mlx);
}
