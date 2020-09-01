/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 16:38:37 by phakakos          #+#    #+#             */
/*   Updated: 2020/08/29 16:38:38 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/*
** window pixel data
*/

t_loca	map_point(t_vec4 vec, int color)
{
	t_loca	rtn;

	if (vec.vec[0] - (int)vec.vec[0] > 0.5)
		rtn.loc.vec[0] = (int)vec.vec[0] + 1;
	else
		rtn.loc.vec[0] = (int)vec.vec[0];
	if (vec.vec[1] - (int)vec.vec[1] > 0.5)
		rtn.loc.vec[1] = (int)vec.vec[1] + 1;
	else
		rtn.loc.vec[1] = (int)vec.vec[1];
	if (vec.vec[2] - (int)vec.vec[2] > 0.5)
		rtn.loc.vec[2] = (int)vec.vec[2] + 1;
	else
		rtn.loc.vec[2] = (int)vec.vec[2];
	rtn.color = rgb_conv(color);
	return (rtn);
}

/*
** map rotation matrix
*/

t_mat4	rot_matrix(float rot[4])
{
	t_mat4	trans;

	trans = mat4_iden();
	trans = mat4_mat4(trans, mat4_rotx(rot[0]));
	trans = mat4_mat4(trans, mat4_roty(rot[1]));
	trans = mat4_mat4(trans, mat4_rotz(rot[2]));
	return (trans);
}

/*
** projection 1
*/

t_loca	point_loca(t_point *point, t_map *map, t_mat4 trans)
{
	t_vec4	vec;
	t_mat4	zoom;
	int		color;

	color = point->color == -1 ? height_color(point->loc.vec[2]
		* map->h_mod, MIN_COLOR, MAX_COLOR, HEIGHT) : point->color;
	vec = vec4_ini((float[4]){(point->loc.vec[0] - map->size.x) * WIDTH,
		(point->loc.vec[1] - map->size.y) * WIDTH,
		point->loc.vec[2] * WIDTH * map->h_mod, point->loc.vec[3]});
	zoom = mat4_scales((float[4]){map->zoom, map->zoom, map->zoom, 1});
	vec = mat4_vec4(trans, vec);
	vec = mat4_vec4(zoom, vec);
	vec.vec[0] += map->origin.mat[0][3];
	vec.vec[1] += map->origin.mat[1][3];
	return (map_point(vec, color));
}

/*
** projection 2
*/

t_loca	point_loca_orth(t_point *point, t_map *map, t_mat4 rot)
{
	t_vec4	vec;
	t_mat4	trans;
	int		color;

	color = !map->color && point->color == -1 ? height_color(point->loc.vec[2]
		* map->h_mod, MIN_COLOR, MAX_COLOR, HEIGHT) : point->color;
	vec = vec4_ini((float[4]){(point->loc.vec[0] - map->size.x) * WIDTH,
		(point->loc.vec[1] - map->size.y) * WIDTH, (point->loc.vec[2] *
		map->h_mod - map->size.z) * WIDTH, point->loc.vec[3]});
	trans = mat4_mat4(mat4_scales((float[4]){map->zoom, map->zoom, map->zoom,
		1}), rot);
	trans = mat4_mat4(trans, mat4_perps2(map->cam.plan,
		map->pos.vec[0] / map->pos.vec[1]));
	vec = mat4_vec4(trans, vec);
	vec.vec[0] += map->cam.loc.vec[0];
	vec.vec[1] += map->cam.loc.vec[1];
	color = map->color ? height_color(vec.vec[2], 0x303030, 0xffffff,
		map->cam.plan.vec[3] * -100) : color;
	return (map_point(vec, color));
}

/*
** projection 3
*/

t_loca	point_loca_pin(t_point *point, t_map *map, t_mat4 rot)
{
	t_vec4	vec;
	t_mat4	trans;
	int		color;

	color = !map->color && point->color == -1 ? height_color(point->loc.vec[2]
		* map->h_mod, MIN_COLOR, MAX_COLOR, HEIGHT) : point->color;
	vec = vec4_ini((float[4]){(point->loc.vec[0] - map->size.x) * WIDTH,
		(point->loc.vec[1] - map->size.y) * WIDTH, (point->loc.vec[2] *
		map->h_mod - map->size.z) * WIDTH, point->loc.vec[3]});
	vec = mat4_vec4(rot, vec);
	trans = mat4_pinhole(vec4_ini((float[4]){map->cam.plan.vec[2],
		map->cam.loc.vec[2], vec.vec[0], vec.vec[1]}),
		map->pos.vec[0] / map->pos.vec[1]);
	trans = mat4_mat4(trans, mat4_scales((float[4]){map->zoom / 10,
		map->zoom / 10, map->zoom / 10, 1}));
	vec = mat4_vec4(trans, vec);
	vec.vec[0] += map->cam.loc.vec[0];
	vec.vec[1] += map->cam.loc.vec[1];
	color = map->color ? height_color(vec.vec[2], 0x303030, 0xffffff,
		map->cam.plan.vec[3] * -100) : color;
	return (map_point(vec, color));
}
