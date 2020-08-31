/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 11:36:36 by phakakos          #+#    #+#             */
/*   Updated: 2020/08/31 11:36:38 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/*
** render rotation cube
** draw helper
*/

void		draw_rota(t_mlx *mlx, t_map *map)
{
	t_loca	this;
	t_loca	next;

	this = rotation_cube(vec4_ini((float[4]){0, 0, 0, 1}), map, 0x00ff00);
	next = rotation_cube(vec4_ini((float[4]){0, -2, 0, 1}), map, 0x00ff00);
	draw_line(mlx, map, this, next);
	this = map_point(this.loc, 0xff0000);
	next = rotation_cube(vec4_ini((float[4]){2, 0, 0, 1}), map, 0xff0000);
	draw_line(mlx, map, this, next);
	this = map_point(this.loc, 0x0000ff);
	next = rotation_cube(vec4_ini((float[4]){0, 0, 2, 1}), map, 0x0000ff);
	draw_line(mlx, map, this, next);
}

/*
** draw lines as if zoomed
** draw_linet helper -> draw helper -> draw_selected -> draw_map
*/

static void	draw_thick(t_mlx *mlx, t_map *map, t_loca start, t_loca end)
{
	double	i;
	t_loca	nstart;
	t_loca	nend;
	double	angle;
	double	precision;

	i = 0;
	precision = 2;
	angle = 180 - atan2(end.loc.vec[0] - start.loc.vec[0],
		end.loc.vec[1] - start.loc.vec[1]) * (180 / 3.14159265);
	while (i < 180)
	{
		nstart = start;
		nend = end;
		i += angle;
		nstart.loc.vec[0] += (int)(map->zoom * cos(i * 3.14159265 / 180));
		nstart.loc.vec[1] += (int)(map->zoom * sin(i * 3.14159265 / 180));
		i = angle - (i - angle);
		nend.loc.vec[0] += (int)(map->zoom * cos(i * 3.14159265 / 180));
		nend.loc.vec[1] += (int)(map->zoom * sin(i * 3.14159265 / 180));
		draw_line(mlx, map, nstart, nend);
		i = angle - i;
		i += 16 / map->zoom >= precision ? 16 / map->zoom : precision;
	}
}

/*
** line drawing with thick lines check
** draw helper -> draw_selected -> draw_map
*/

void		draw_linet(t_mlx *mlx, t_map *map, t_loca start, t_loca end)
{
	if ((start.loc.vec[0] < 0 && end.loc.vec[0] < 0) ||
		(start.loc.vec[0] > mlx->width && end.loc.vec[0] > mlx->width) ||
		(start.loc.vec[1] < 0 && end.loc.vec[1] < 0) ||
		(start.loc.vec[1] > mlx->height && end.loc.vec[1] > mlx->height))
		return ;
	else if (!pos_test(map->pos.vec, start.loc.vec, end.loc.vec))
		return ;
	draw_line(mlx, map, start, end);
	if (map->thick)
		draw_thick(mlx, map, start, end);
}
