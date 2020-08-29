/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 15:53:04 by phakakos          #+#    #+#             */
/*   Updated: 2020/06/03 18:22:59 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/*
** "drawing" to image
** draw_line1 helper -> (draw_linez1 helper ->) draw helper -> draw_selected -> draw_map
*/

void	draw_to_image(t_mlx *mlx, t_map *map, t_loca spot)
{
	int		writer;
	char	*image;

	if (!mlx->mlx_img)
		return ;
	if (spot.loc.vec[0] >= map->pos.vec[2] && spot.loc.vec[0] <= map->pos.vec[2]
	 + map->pos.vec[0] && spot.loc.vec[1] >= map->pos.vec[3] && spot.loc.vec[1] 
	 <= map->pos.vec[3] + map->pos.vec[1] /*&& spot.loc.vec[2] >= 
	 map->cam.plan.vec[3]*/)
	{
		writer = (int)spot.loc.vec[0] * 4 + mlx->size_line * (int)spot.loc.vec[1];
		image = mlx->img_dat;
		if (!mlx->endian) // rework?
		{
			image[writer++] = spot.color.blue;
			image[writer++] = spot.color.green;
			image[writer++] = spot.color.red;
			image[writer++] = 0;
		}
		else
		{
			image[writer++] = 0;
			image[writer++] = spot.color.red;
			image[writer++] = spot.color.green;
			image[writer++] = spot.color.blue;
		}
	}
}

/*
** calculate the color change between points
** draw_line1 helper -> (draw_linez1 helper ->) draw helper -> draw_selected -> draw_map
*/

t_rgb	color_flow(t_loca start, t_loca diff, t_loca curr, t_loca end)
{
	t_rgb	rtn;
	float	prog;

	if (ft_abs(diff.loc.vec[0]) > ft_abs(diff.loc.vec[1]))
	{
		prog = ft_abs(curr.loc.vec[0] - end.loc.vec[0]);
		prog = prog == 0 ? 0 : 1 - prog / ft_abs(diff.loc.vec[0]);
	}
	else
	{
		prog = ft_abs(curr.loc.vec[1] - end.loc.vec[1]);
		prog = prog == 0 ? 0 : 1 - prog / ft_abs(diff.loc.vec[1]);
	}
	rtn.red = (1 - prog) * start.color.red + end.color.red * prog;
	rtn.green = (1 - prog) * start.color.green + end.color.green * prog;
	rtn.blue = (1 - prog) * start.color.blue + end.color.blue * prog;
	return (rtn);
}

/*
** move x/y position while drawing
** draw_line1 helper -> (draw_linez1 helper ->) draw helper -> draw_selected -> draw_map
*/

float	move_line(t_vec4 start, t_vec4 diff, float curr, int i)
{
	int		y;
	float	rtn;

	y = i == 1 ? 0 : 1;
	rtn = start.vec[y];
	rtn += diff.vec[y] * (curr - start.vec[i]) / diff.vec[i];
	return (rtn);
}

/*
** move Z position while drawing
** draw_line1 helper -> (draw_linez1 helper ->) draw helper -> draw_selected -> draw_map
*/

float	move_height(t_vec4 start, t_vec4 diff, float curr, int i)
{
	float	rtn;

	rtn = start.vec[2];
	rtn += diff.vec[2] * (curr - start.vec[i]) / diff.vec[i];
	return (rtn);
}

/*
** just draw line
** (draw_linez1 helper ->) draw helper -> draw_selected -> draw_map
*/

void	draw_line1(t_mlx *mlx, t_map *map, t_loca start, t_loca end)
{
	t_loca	diff;
	t_loca	curr;
	int		i;
	int		y;

	curr = start;
	diff.loc.vec[0] = end.loc.vec[0] - start.loc.vec[0];
	diff.loc.vec[1] = end.loc.vec[1] - start.loc.vec[1];
	diff.loc.vec[2] = end.loc.vec[2] - start.loc.vec[2];
	if (!(i = 1) || diff.loc.vec[1] == 0 || (diff.loc.vec[0] != 0 && 
	ft_abs(diff.loc.vec[0]) > ft_abs(diff.loc.vec[1])))
		i = 0;
	y = i == 0 ? 1 : 0;
	while (curr.loc.vec[i] != end.loc.vec[i])
	{
		curr.loc.vec[y] = move_line(start.loc, diff.loc, curr.loc.vec[i], i);
		curr.loc.vec[2] = move_height(start.loc, diff.loc, curr.loc.vec[i], i);
		curr.color = color_flow(start, diff, curr, end);
		draw_to_image(mlx, map, curr);
		curr.loc.vec[i] = curr.loc.vec[i] < end.loc.vec[i] ? curr.loc.vec[i] 
			+ 1 : curr.loc.vec[i] - 1;
	}
	draw_to_image(mlx, map, curr);
}

/*
** test for one of the line points to be within map
** pos test helper -> draw_linez helper -> draw helper -> draw_selected -> draw_map
*/

int		within_map(float map[4], float spot[4])
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
** pos test helperd -> raw_linez helper -> draw helper -> draw_selected -> draw_map
*/

t_vec4	corner_line_a(float map[4], float start[4], float end[4])
{
	t_vec4	a;

	a = vec4_ini((float[4]){map[2], map[3], 0, 0});
	if ((start[0] < map[2] + map[0] && end[0] > map[2]  + map[0]) || 
		(start[0] > map[2] + map[0] && end[0] < map[2]  + map[0]))
		a.vec[0] += map[0];
	else if ((start[1] < map[3] + map[1] && end[1] > map[3] + map[1]) || 
		(start[1] > map[3] + map[1] && end[1] < map[3] + map[1]))
		a.vec[1] += map[1];
	return (a);
}

/*
** find the second corner point to test against
** pos test helperd -> raw_linez helper -> draw helper -> draw_selected -> draw_map
*/

t_vec4	corner_line_b(float map[4], float start[4], float end[4])
{
	t_vec4	b;

	b = vec4_ini((float[4]){map[2], map[3], 0, 0});
	if ((start[0] < map[2] && end[0] > map[2]) || (start[0] > map[2] && 
		end[0] < map[2]))
		b.vec[1] += map[1];
	else if ((start[0] < map[2] + map[0] && end[0] > map[2]  + map[0]) || 
		(start[0] > map[2] + map[0] && end[0] < map[2]  + map[0]))
		b = vec4_ini((float[4]){b.vec[0] + map[0], b.vec[3] + map[1], 0, 0});
	else if ((start[1] < map[3] && end[1] > map[3] ) || (start[1] > map[3] && 
		end[1] < map[3] ))
		b.vec[0] += map[0];
	else if ((start[1] < map[3] + map[1] && end[1] > map[3] + map[1]) || 
		(start[1] > map[3] + map[1] && end[1] < map[3] + map[1]))
		b = vec4_ini((float[4]){b.vec[2] + map[0], b.vec[1] + map[1], 0, 0});
	return (b);
}

/*
** test position to be within the map borders
** draw_linez helper -> draw helper -> draw_selected -> draw_map
*/

int		pos_test(float map[4], float start[4], float end[4])
{
	t_vec4	a;
	t_vec4	b;
	t_vec4	c;
	t_vec4	d;
	int		ret;

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

/*
** draw lines as if zoomed
** draw_linez1 helper -> draw helper -> draw_selected -> draw_map
*/

void	draw_thicc(t_mlx *mlx, t_map *map, t_loca start, t_loca end)
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
		draw_line1(mlx, map, nstart, nend);
		i = angle - i;
		i += 16 / map->zoom >= precision ? 16 / map->zoom : precision;
	}
}

/*
** line drawing with thick lines check
** draw helper -> draw_selected -> draw_map
*/

void	draw_linez1(t_mlx *mlx, t_map *map, t_loca start, t_loca end)
{
	if ((start.loc.vec[0] < 0 && end.loc.vec[0] < 0) || 
		(start.loc.vec[0] > mlx->width && end.loc.vec[0] > mlx->width) ||
		(start.loc.vec[1] < 0 && end.loc.vec[1] < 0) || 
		(start.loc.vec[1] > mlx->height && end.loc.vec[1] > mlx->height))
		return ;
	else if (!pos_test(map->pos.vec, start.loc.vec, end.loc.vec))
		return ;
	draw_line1(mlx, map, start, end);
	if (map->thick)
		draw_thicc(mlx, map, start, end);
}

/*
** render rotation cube
** draw helper
*/

void	draw_rota(t_mlx *mlx, t_map *map)
{
	t_loca	this;
	t_loca	next;

	this = rotation_cube(vec4_ini((float[4]){0, 0, 0, 1}), map, 0x00ff00);
	next = rotation_cube(vec4_ini((float[4]){0, -2, 0, 1}), map, 0x00ff00);
	draw_line1(mlx, map, this, next);
	this = map_point(this.loc, 0xff0000);
	next = rotation_cube(vec4_ini((float[4]){2, 0, 0, 1}), map, 0xff0000);
	draw_line1(mlx, map, this, next);
	this = map_point(this.loc, 0x0000ff);
	next = rotation_cube(vec4_ini((float[4]){0, 0, 2, 1}), map, 0x0000ff);
	draw_line1(mlx, map, this, next);

}
// mode 1 map_matrix, mode 2/3 camera_matrix
// draw_selected helper -> draw_map helper
void	draw(t_map *map, t_mlx *mlx, t_mat4 matrix, void *fu_ptr)
{
	t_point	*row;
	t_point	*curr;
	t_loca	this;
	t_loca	next;
	t_loca	(*loca)(t_point*, t_map*, t_mat4);

	row = map->start;
	loca = fu_ptr;
	while (row && (curr = row))
	{
		while (curr)
		{
			this = (*loca)(curr, map, matrix);
			if (curr->right)
				draw_linez1(mlx, map, this, (*loca)(curr->right, map, matrix));
			if (curr->bottm)
				draw_linez1(mlx, map, this, (*loca)(curr->bottm, map, matrix));
			curr = curr->right;
		}
		row = row->bottm;
	}
	if (map->rot.vec[3] == 2)
		draw_rota(mlx, map);
}

/*
** smart draw selector
** draw_map helper
*/

void	draw_selected(t_mlx *mlx, t_map *map)
{
	if (map->mode == 1)
		draw(map, mlx, rot_matrix(map->rot.vec), point_loca);
	else if (map->mode == 2)
		draw(map, mlx, rot_matrix(map->cam.rot.vec), point_loca_orth);
	else if (map->mode == 3)
		draw(map, mlx, rot_matrix(map->cam.rot.vec), point_loca_pin);
}

/*
** 4-view borders
** draw_map helper
*/

void	fview_border(t_mlx *mlx, float map[4])
{
	draw_linez1(mlx, mlx->map[0], map_point(vec4_ini((float[4]){0, mlx->height 
		/ 2, 0, 1}), 0xffffff), map_point(vec4_ini((float[4]){mlx->width, 
		mlx->height / 2, 0, 1}), 0xffffff));
	draw_linez1(mlx, mlx->map[0], map_point(vec4_ini((float[4]){mlx->width / 2,
		 0, 0, 1}), 0xffffff), map_point(vec4_ini((float[4]){mlx->width / 2,
		  mlx->height, 0, 1}), 0xffffff));
	draw_linez1(mlx, mlx->map[0], map_point(vec4_ini((float[4]){map[2], map[3],
		 0, 1}), 0xffffff), map_point(vec4_ini((float[4]){map[2] + map[0], 
		 map[3], 0, 1}), 0xffffff));
	draw_linez1(mlx, mlx->map[0], map_point(vec4_ini((float[4]){map[2], map[3],
	 	0, 1}), 0xffffff), map_point(vec4_ini((float[4]){map[2], map[3] + map[1],
	 	 0, 1}), 0xffffff));
	draw_linez1(mlx, mlx->map[0], map_point(vec4_ini((float[4]){map[2], map[3]
		 + map[1], 0, 1}), 0xffffff), map_point(vec4_ini((float[4]){map[2] + 
		 map[0], map[3] + map[1], 0, 1}), 0xffffff));
	draw_linez1(mlx, mlx->map[0], map_point(vec4_ini((float[4]){map[2] + map[0]
		, map[3], 0, 1}), 0xffffff), map_point(vec4_ini((float[4]){map[2] + 
		map[0], map[3] + map[1], 0, 1}), 0xffffff));
}

void	draw_map(t_mlx *mlx)
{
	mlx_clear_window(mlx->mlx_ptr, mlx->mlx_win);
	mlx->mlx_img = mlx_new_image(mlx->mlx_ptr, mlx->width, mlx->width);
	mlx->img_dat = mlx_get_data_addr(mlx->mlx_img, &mlx->bpp, &mlx->size_line,
		 &mlx->endian);
	if (mlx->mode == 2)
	{
		draw_selected(mlx, mlx->map[1]);
		draw_selected(mlx, mlx->map[2]);
		draw_selected(mlx, mlx->map[3]);
		draw_selected(mlx, mlx->map[4]);
		fview_border(mlx, mlx->smap->pos.vec);
	}
	else {
		draw_selected(mlx, mlx->smap);
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->mlx_win, mlx->mlx_img, 0, 0);
}
