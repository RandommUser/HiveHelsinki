/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_resets.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 17:07:11 by phakakos          #+#    #+#             */
/*   Updated: 2020/08/29 17:07:12 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/*
** map 4 default state
*/

void	map4_reset(t_mlx *mlx, t_map *map)
{
	map_gen_reset(mlx, map);
	if (mlx->width % 2 == 0)
		map->pos.vec[0] -= 1;
	if (mlx->height % 2 == 0)
		map->pos.vec[1] -= 1;
	map->pos.vec[2] += mlx->width / 2 + 1;
	map->pos.vec[3] += mlx->height / 2 + 1;
	map->origin = mat4_trans((float[3]){map->pos.vec[2] + map->pos.vec[0] / 2,
		map->pos.vec[3] + map->pos.vec[1] / 2, 1});
	map->cam.loc = vec4_ini((float[4]){map->pos.vec[2] + map->pos.vec[0] / 2,
		map->pos.vec[3] + map->pos.vec[1] / 2, 0, 1});
	map->cam.rot = vec4_ini((float[4]){-90, -90, -180, ROTA_W});
	map->rot = vec4_ini((float[4]){-90, -90, -180, ROTA_W});
	zoom_check(map);
}

/*
** map 3 default state
*/

void	map3_reset(t_mlx *mlx, t_map *map)
{
	map_gen_reset(mlx, map);
	if (mlx->height % 2 == 0)
		map->pos.vec[1] -= 1;
	map->pos.vec[3] += mlx->height / 2 + 1;
	map->origin = mat4_trans((float[3]){map->pos.vec[2] + map->pos.vec[0] / 2,
		map->pos.vec[3] + map->pos.vec[1] / 2, 1});
	map->cam.loc = vec4_ini((float[4]){map->pos.vec[2] + map->pos.vec[0] / 2,
		map->pos.vec[3] + map->pos.vec[1] / 2, 0, 1});
	map->cam.rot = vec4_ini((float[4]){-90, -90, -180, ROTA_W});
	map->rot = vec4_ini((float[4]){-180, -90, 180, ROTA_W});
	zoom_check(map);
}

/*
** map 2 default state
*/

void	map2_reset(t_mlx *mlx, t_map *map)
{
	map_gen_reset(mlx, map);
	map->pos.vec[2] += mlx->width / 2 + 1;
	if (mlx->width % 2 == 0)
		map->pos.vec[0] -= 1;
	map->origin = mat4_trans((float[3]){map->pos.vec[2] + map->pos.vec[0] / 2,
		map->pos.vec[3] + map->pos.vec[1] / 2, 1});
	map->cam.loc = vec4_ini((float[4]){map->pos.vec[2] + map->pos.vec[0] / 2,
		map->pos.vec[3] + map->pos.vec[1] / 2, 0, 1});
	map->cam.rot = vec4_ini((float[4]){-90, -90, -180, ROTA_W});
	map->rot = vec4_ini((float[4]){-180, 0, -90, ROTA_W});
	zoom_check(map);
}

/*
** map 1 default state
*/

void	map1_reset(t_mlx *mlx, t_map *map)
{
	map_gen_reset(mlx, map);
	map->origin = mat4_trans((float[3]){map->pos.vec[2] + map->pos.vec[0] / 2,
		map->pos.vec[3] + map->pos.vec[1] / 2, 1});
	map->cam.loc = vec4_ini((float[4]){map->pos.vec[2] + map->pos.vec[0] / 2,
		map->pos.vec[3] + map->pos.vec[1] / 2, 0, 1});
	map->cam.rot = vec4_ini((float[4]){40, 85, 25, ROTA_W});
	map->cam.plan.vec[2] = 55;
	zoom_check(map);
}

/*
** map 0 default state
*/

void	map0_reset(t_mlx *mlx, t_map *map)
{
	map_gen_reset(mlx, map);
	map->rot = vec4_ini((float[4]){ROTA_X, ROTA_Y, ROTA_Z, ROTA_W});
	map->pos = vec4_ini((float[4]){mlx->width, mlx->height, 0, 0});
	zoom_check(map);
	map->cam.loc = vec4_ini((float[4]){(int)(map->pos.vec[0] / 2),
		(int)(map->pos.vec[1] / 2), 0, 1});
	map->cam.rot = vec4_ini((float[4]){90, 90, 0, 1});
	map->origin = mat4_trans((float[3]){mlx->width / 2, mlx->height / 2, 1});
}
