/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_misc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 16:42:15 by phakakos          #+#    #+#             */
/*   Updated: 2020/08/29 16:42:16 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/* 
** automated zoom finder
** mapN_reset helper -> map_reset helper
*/

void	zoom_check(t_map *map)
{
	float	height;
	float	width;

	width = map->size.x * 2 * WIDTH * map->zoom;
	height = map->size.y * WIDTH * map->zoom;
	while (width < map->pos.vec[0] && height < map->pos.vec[1])
	{
		map->zoom *= 1.2;
		width = map->size.x * 2 * WIDTH * map->zoom;
		height = map->size.y * 2 * WIDTH * map->zoom;
	}
	while (width >= map->pos.vec[0] || height >= map->pos.vec[1])
	{
		map->zoom /= 1.2;
		width = map->size.x * 2 * WIDTH * map->zoom;
		height = map->size.y * 2 * WIDTH * map->zoom;
	}
	map->zoom /= 1.5;
	width = map->size.x * 2 * WIDTH * map->zoom;
	height = map->size.y * 2 * WIDTH * map->zoom;
}

/*
** coordinate position struct
*/

t_coord	coords(int x, int y)
{
	t_coord	rtn;

	rtn.x = x;
	rtn.y = y;
	return (rtn);
}

/*
** map middle point calculation
*/

void	map_size(t_map **map)
{
	t_point	*start;
	float	x;
	float	y;

	start = (*map)->start;
	x = 0;
	y = 0;
	while (start->right && (++x))
		start = start->right;
	while (start->bottm && (++y))
		start = start->bottm;
	(*map)->size.x = x / 2;
	(*map)->size.y = y / 2;
	(*map)->size.z = 0;
}

/*
** map dublication
*/

t_map	*map_copy(t_mlx *mlx)
{
	t_map	*new;

	if (!(new = (t_map*)malloc(sizeof(t_map))))
		exit(ERR_MEMORY);
	new->start = mlx->smap->start;
	new->pos = mlx->smap->pos;
	new->pos.vec[0] = mlx->width / 2 - 1;
	new->pos.vec[1] = mlx->height / 2 - 1;
	new->pos.vec[2] = 0;
	new->pos.vec[3] = 0;
	new->rot = mlx->smap->rot;
	new->zoom = mlx->smap->zoom;
	new->mode = mlx->smap->mode;
	new->color = mlx->smap->color;
	new->h_mod = mlx->smap->h_mod;
	new->cam = mlx->smap->cam;
	new->size = mlx->smap->size;
	new->limit = mlx->smap->limit;
	new->thick = mlx->smap->thick;
	return (new);
}
