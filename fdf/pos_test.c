/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pos_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 11:32:38 by phakakos          #+#    #+#             */
/*   Updated: 2020/08/31 11:32:39 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/*
** test for one of the line points to be within map
** pos test helper -> draw_linet helper -> draw helper -> draw_selected ->
**		 draw_map
*/

static int		within_map(float map[4], float spot[4])
{
	if (spot[0] < map[2] ||
		spot[0] > map[0] + map[2])
		return (0);
	if (spot[1] < map[3] ||
		spot[1] > map[1] + map[3])
		return (0);
	return (1);
}

/*
** find the first corner point to test against
** pos test helperd -> draw_linet helper -> draw helper -> draw_selected ->
**	 	draw_map
*/

static t_vec4	corner_line_a(float map[4], float start[4], float end[4])
{
	t_vec4	a;

	a = vec4_ini((float[4]){map[2], map[3], 0, 0});
	if ((start[0] < map[2] + map[0] && end[0] > map[2] + map[0]) ||
		(start[0] > map[2] + map[0] && end[0] < map[2] + map[0]))
		a.vec[0] += map[0];
	else if ((start[1] < map[3] + map[1] && end[1] > map[3] + map[1]) ||
		(start[1] > map[3] + map[1] && end[1] < map[3] + map[1]))
		a.vec[1] += map[1];
	return (a);
}

/*
** find the second corner point to test against
** pos test helperd -> draw_linet helper -> draw helper -> draw_selected ->
**		 draw_map
*/

static t_vec4	corner_line_b(float map[4], float start[4], float end[4])
{
	t_vec4	b;

	b = vec4_ini((float[4]){map[2], map[3], 0, 0});
	if ((start[0] < map[2] && end[0] > map[2]) || (start[0] > map[2] &&
		end[0] < map[2]))
		b.vec[1] += map[1];
	else if ((start[0] < map[2] + map[0] && end[0] > map[2] + map[0]) ||
		(start[0] > map[2] + map[0] && end[0] < map[2] + map[0]))
		b = vec4_ini((float[4]){b.vec[0] + map[0], b.vec[3] + map[1], 0, 0});
	else if ((start[1] < map[3] && end[1] > map[3]) || (start[1] > map[3] &&
		end[1] < map[3]))
		b.vec[0] += map[0];
	else if ((start[1] < map[3] + map[1] && end[1] > map[3] + map[1]) ||
		(start[1] > map[3] + map[1] && end[1] < map[3] + map[1]))
		b = vec4_ini((float[4]){b.vec[2] + map[0], b.vec[1] + map[1], 0, 0});
	return (b);
}

/*
** test position to be within the map borders
** draw_linet helper -> draw helper -> draw_selected -> draw_map
*/

int				pos_test(float map[4], float start[4], float end[4])
{
	t_vec4	a;
	t_vec4	b;
	t_vec4	c;
	t_vec4	d;

	if (within_map(map, start) || within_map(map, end))
		return (1);
	a = corner_line_a(map, start, end);
	b = corner_line_b(map, start, end);
	c = vec4_ini(start);
	d = vec4_ini(end);
	if (a.vec[0] == b.vec[0] && a.vec[1] == b.vec[1])
		return (1);
	if (vec4_ccw(c, d, a) * vec4_ccw(c, d, b) >= 0)
		return (0);
	if (vec4_ccw(a, b, c) * vec4_ccw(a, b, d) >= 0)
		return (0);
	return (1);
}
