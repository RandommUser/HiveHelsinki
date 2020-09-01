/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 16:34:06 by phakakos          #+#    #+#             */
/*   Updated: 2020/08/29 16:34:08 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/*
** custom exit command
*/

void	mexit(int num)
{
	if (num == ERR_MAP)
		ft_putstr("Error in the map\n");
	if (num == ERR_MEMORY)
		ft_putstr("Error allocating required memory\n");
	if (num == ERR_MLX)
		ft_putstr("Error with MLX connection\n");
	if (num == ERR_READER)
		ft_putstr("Error reading the input\n");
	exit(num);
}

/*
** swapping between normal and 4view
*/

void	view_mode(t_mlx *mlx)
{
	if (mlx->mode == 2)
	{
		map_reset(mlx, mlx->smap);
		map0_reset(mlx, mlx->map[1]);
		map0_reset(mlx, mlx->map[2]);
		map0_reset(mlx, mlx->map[3]);
		mlx->map[1]->mode = mlx->map[0]->mode;
		mlx->map[2]->mode = mlx->map[0]->mode;
		mlx->map[3]->mode = mlx->map[0]->mode;
		mlx->map[4]->mode = mlx->map[0]->mode;
	}
	else
	{
		map_reset(mlx, mlx->map[1]);
		map_reset(mlx, mlx->map[2]);
		map_reset(mlx, mlx->map[3]);
		map_reset(mlx, mlx->map[4]);
		mlx->map[1]->mode = 2;
		mlx->map[2]->mode = 1;
		mlx->map[3]->mode = 1;
		mlx->map[4]->mode = 1;
	}
	mlx->mode = mlx->mode == 1 ? 2 : 1;
	mlx->smap = mlx->mode == 1 ? mlx->map[0] : mlx->map[1];
}

/*
** rotation cube calculation
*/

t_loca	rotation_cube(t_vec4 loc, t_map *map, int color)
{
	loc.vec[0] *= WIDTH;
	loc.vec[1] *= WIDTH;
	loc.vec[2] *= WIDTH;
	if (map->mode == 1)
	{
		loc = mat4_vec4(rot_matrix(map->rot.vec), loc);
		loc = mat4_vec4(map->origin, loc);
	}
	else
	{
		loc = mat4_vec4(rot_matrix(map->cam.rot.vec), loc);
		loc.vec[0] += map->cam.loc.vec[0];
		loc.vec[1] += map->cam.loc.vec[1];
	}
	loc = mat4_vec4(mat4_pro(), loc);
	color = color == -1 ? DEF_COLOR : color;
	return (map_point(loc, color));
}
