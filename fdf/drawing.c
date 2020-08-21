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
//printf("curr|x:%d y:%d |end|x:%d y:%d\n", curr.x, curr.y, end.x, end.y);
//printf("prog|red:%d|green:%d|blue%d|prog:%f\n", rtn.red, rtn.green, rtn.blue,prog);
	return (rtn);
}

void	draw_spot(t_mlx *mlx, t_map *map, t_loca curr)
{
	double	pi;
	int		z;
	double	i;
	int		x;
	int		y;
   
	pi = 3.1415926535;
	z = 1;
	while (z++ < map->zoom)
	{
		i = 0;
		while (i < 360)
		{
			x = z * cos(i * pi / 180);
			y = z * sin(i * pi / 180);
			if (x % 1 == 0 && y % 1 == 0 && x >= map->pos.vec[2] && x <= map->pos.vec[2] + map->pos.vec[0] &&
			y >= map->pos.vec[3] && y <= map->pos.vec[3] + map->pos.vec[1])
				mlx_pixel_put(mlx->mlx_ptr, mlx->mlx_win, curr.loc.vec[0] + x, curr.loc.vec[1] + y, trgb_conv(curr.color));
		//	i += 0.1;
			i += 30;
		}
	}
	mlx_pixel_put(mlx->mlx_ptr, mlx->mlx_win, curr.loc.vec[0], curr.loc.vec[1], trgb_conv(curr.color));
}

void	draw_line1(t_mlx *mlx, t_map *map, t_loca start, t_loca end)
{
	t_loca	diff;
	t_loca	curr;

	if (start.loc.vec[0] == -1 || end.loc.vec[0] == -1)
		return ;
	curr.loc.vec[0] = start.loc.vec[0];
	curr.loc.vec[1] = start.loc.vec[1];
	curr.loc.vec[2] = start.loc.vec[2];
	curr.color = start.color;
//	diff.color = rgb_calc(end.color, start.color, '-');
	diff.loc.vec[0] = end.loc.vec[0] - start.loc.vec[0];
	diff.loc.vec[1] = end.loc.vec[1] - start.loc.vec[1];
	diff.loc.vec[2] = end.loc.vec[2] - start.loc.vec[2];
	if ((ft_abs(diff.loc.vec[0]) > ft_abs(diff.loc.vec[1]) && diff.loc.vec[0] != 0) || diff.loc.vec[1] == 0)
	{
		while (curr.loc.vec[0] != end.loc.vec[0])
		{
			curr.loc.vec[1] = start.loc.vec[1] + diff.loc.vec[1] * (curr.loc.vec[0] - start.loc.vec[0]) / diff.loc.vec[0];
			curr.loc.vec[2] = start.loc.vec[2] + diff.loc.vec[2] * (curr.loc.vec[0] - start.loc.vec[0]) / diff.loc.vec[0];
			curr.color = color_flow(start, diff, curr, end);
			//if (curr.x + mlx->zoom >= 0 && curr.x - mlx->zoom <= mlx->width && 
			//		curr.y + mlx->zoom >= 0 && curr.y - mlx->zoom <= mlx->height)
			//	draw_spot(mlx, curr);
		if ((int)curr.loc.vec[1] % 1 == 0 && curr.loc.vec[0] >= map->pos.vec[2] && curr.loc.vec[0] <= map->pos.vec[2] + map->pos.vec[0] &&
				curr.loc.vec[1] >= map->pos.vec[3] && curr.loc.vec[1] <= map->pos.vec[3] + map->pos.vec[1] && curr.loc.vec[2] >= map->cam.plan.vec[3])
				mlx_pixel_put(mlx->mlx_ptr, mlx->mlx_win, curr.loc.vec[0], curr.loc.vec[1], trgb_conv(curr.color));
			curr.loc.vec[0] = curr.loc.vec[0] < end.loc.vec[0] ? curr.loc.vec[0] + 1 : curr.loc.vec[0] - 1;
		}
	}
	else
	{
		while (curr.loc.vec[1] != end.loc.vec[1])
		{
			curr.loc.vec[0] = start.loc.vec[0] + diff.loc.vec[0] * (curr.loc.vec[1] - start.loc.vec[1]) / diff.loc.vec[1];
			curr.loc.vec[2] = start.loc.vec[2] + diff.loc.vec[2] * (curr.loc.vec[1] - start.loc.vec[1]) / diff.loc.vec[1];
			curr.color = color_flow(start, diff, curr, end);
			//if (curr.x + mlx->zoom >= 0 && curr.x - mlx->zoom <= mlx->width &&
			//		curr.y + mlx->zoom >= 0 && curr.y - mlx->zoom <= mlx->height)
			//	draw_spot(mlx, curr);
		if ((int)curr.loc.vec[0] % 1 == 0 && curr.loc.vec[0] >= map->pos.vec[2] && curr.loc.vec[0] <= map->pos.vec[2] + map->pos.vec[0] &&
				curr.loc.vec[1] >= map->pos.vec[3] && curr.loc.vec[1] <= map->pos.vec[3] + map->pos.vec[1] && curr.loc.vec[2] >= map->cam.plan.vec[3])
				mlx_pixel_put(mlx->mlx_ptr, mlx->mlx_win, curr.loc.vec[0], curr.loc.vec[1], trgb_conv(curr.color));
			curr.loc.vec[1] = curr.loc.vec[1] < end.loc.vec[1] ? curr.loc.vec[1] + 1 : curr.loc.vec[1] - 1;
		}
	}
}

void	draw_linez1(t_mlx *mlx, t_map *map, t_loca start, t_loca end)
{
//	double	pi;
	double	i;
	t_loca	nstart;
	t_loca	nend;
	double	angle;

//	pi = 3.14159265;
//if (x % 1 == 0 && y % 1 == 0 && x >= map->pos.vec[2] && x <= map->pos.vec[2] + map->pos.vec[0] &&
//			y >= map->pos.vec[3] && y <= map->pos.vec[3] + map->pos.vec[1]);
/*	while (start.loc.vec[0] > map->pos.vec[2] + map->pos.vec[0] || start.loc.vec[0] < map->pos.vec[2])
	{
		start.loc.vec[0] += end.loc.vec[0] > start.loc.vec[0] ? 1 : -1;
		if (start.loc.vec[0] == end.loc.vec[0])
			return ;
	}
	while (end.loc.vec[0] > map->pos.vec[2] + map->pos.vec[0] || end.loc.vec[0] < map->pos.vec[2])
	{
		end.loc.vec[0] += start.loc.vec[0] > end.loc.vec[0] ? 1 : -1;
		if (start.loc.vec[0] == end.loc.vec[0])
			return ;
	}

	while (start.loc.vec[1] > map->pos.vec[3] + map->pos.vec[1] || start.loc.vec[1] < map->pos.vec[3])
	{
		start.loc.vec[1] += end.loc.vec[1] > start.loc.vec[1] ? 1 : -1;
		if (start.loc.vec[1] == end.loc.vec[1])
			return ;
	}
	while (end.loc.vec[1] > map->pos.vec[3] + map->pos.vec[1] || end.loc.vec[1] < map->pos.vec[3])
	{
		end.loc.vec[1] += start.loc.vec[1] > end.loc.vec[1] ? 1 : -1;
		if (start.loc.vec[1] == end.loc.vec[1])
			return ;
	}
*/
	draw_line1(mlx, map, start, end);
//	if (mlx->zoom <= 1)
//		return ;
//	i = 0;
//	angle = 180 - atan2(end.x - start.x, end.y - start.y) * (180 / pi);
//	while (i < 180)
//	{
//		nstart = start;
//		nend = end;
//		i += angle;
//		nstart.x += (int)(mlx->zoom * cos(i * pi / 180));
//		nstart.y += (int)(mlx->zoom * sin(i * pi / 180));
//		//i += i < 180 ? 180 : -180;
//		i = angle - (i - angle);
//		nend.x += (int)(mlx->zoom * cos(i * pi / 180));
//		nend.y += (int)(mlx->zoom * sin(i * pi / 180));
//		draw_line1(mlx, nstart, nend);
//		i = angle - i;
//		if (mlx->zoom < 8)
//			i += 8;
//		else if (mlx->zoom < 16)
//			i += 4;
//		else if (mlx->zoom < 32)
//			i += 1;
//		else if (mlx->zoom < 128)
//			i += 0.5;
//		else
//			i += 0.1;
//		//i -= i >= 180 ? 180 : -180;
//		//i += 1;
//	}
}

void	zoom_check(t_map *map)
{
	float	height;
	float	width;

	width = map->size.x * 4 * WIDTH * map->zoom;
	height = map->size.y * 4 * WIDTH * map->zoom;
	while (width < map->pos.vec[0] && height < map->pos.vec[1])
	{
		map->zoom *= 1.2;
		width = map->size.x * 4 * WIDTH * map->zoom;
		height = map->size.y * 4 * WIDTH * map->zoom;
		printf("w %f h %f \n", map->pos.vec[0],map->pos.vec[1] );
		printf("widht %f height %f zoom %f\n", width, height, map->zoom);
	}
	while (width >= map->pos.vec[0] || height >= map->pos.vec[1])
	{
		printf("w %f h %f \n", map->pos.vec[0],map->pos.vec[1] );
		printf("widht %f height %f zoom %f\n", width, height, map->zoom);
		map->zoom /= 1.2;
		width = map->size.x * 4 * WIDTH * map->zoom;
		height = map->size.y * 4 * WIDTH * map->zoom;
		printf("widht %f height %f zoom %f\n", width, height, map->zoom);
	}
	map->zoom /= 2; // NOT GOOD
	width = map->size.x * 4 * WIDTH * map->zoom;
	height = map->size.y * 4 * WIDTH * map->zoom;
	printf("final\nw %f h %f \n", map->pos.vec[0],map->pos.vec[1] );
	printf("widht %f height %f zoom %f\n", width, height, map->zoom);
}

t_map	*map_copy(t_mlx *mlx)
{
	t_map	*new;

	if (!(new = (t_map*)malloc(sizeof(t_map))))
		return (NULL);
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
	return (new);
}

void	map_reset(t_mlx *mlx)
{
	size_t	i;

	i = 1;
	if (!(mlx->map[1] = map_copy(mlx)) || !(mlx->map[2] = map_copy(mlx)) || !(mlx->map[3] = map_copy(mlx)) || !(mlx->map[4] = map_copy(mlx)))
		exit (2);
	mlx->map[i]->origin = mat4_trans((float[3]){(mlx->map[i]->pos.vec[2] + mlx->map[i]->pos.vec[0]) / 4, (mlx->map[i]->pos.vec[3] + mlx->map[i]->pos.vec[1]) / 4, 1});
	mlx->map[i]->mode = 2;
	mlx->map[i]->cam.loc = vec4_ini((float[4]){(int)(mlx->map[i]->pos.vec[2] + mlx->map[i]->pos.vec[0] / 2), (int)(mlx->map[i]->pos.vec[3] + mlx->map[1]->pos.vec[1] / 2), 0, 1});
	mlx->map[i]->cam.rot = vec4_ini((float[4]){40, 85, 25, 1});
	mlx->map[i]->cam.plan.vec[2] = 55;
	zoom_check(mlx->map[i]);
	i++;

	mlx->map[i]->pos.vec[2] += mlx->width / 2 + 1;
	if (mlx->width % 2 == 0)
		mlx->map[i]->pos.vec[0] -= 1;
	mlx->map[i]->origin = mat4_trans((float[3]){(mlx->map[i]->pos.vec[2] + mlx->map[i]->pos.vec[0] * 2) / 4, (mlx->map[i]->pos.vec[3] + mlx->map[i]->pos.vec[1]) / 4, 1}); // ???
	mlx->map[i]->rot = vec4_ini((float[4]){-180, 0, -90,ROTA_W});
	zoom_check(mlx->map[i]);
	i++;

	if (mlx->height % 2 == 0)
		mlx->map[i]->pos.vec[1] -= 1;
	mlx->map[i]->pos.vec[3] += mlx->height / 2 + 1;
	mlx->map[i]->origin = mat4_trans((float[3]){(mlx->map[i]->pos.vec[2] + mlx->map[i]->pos.vec[0]) / 4, (mlx->map[i]->pos.vec[3] + mlx->map[i]->pos.vec[1] * 2) / 4, 1});
	mlx->map[i]->rot = vec4_ini((float[4]){-180, -90, 180,ROTA_W});
	zoom_check(mlx->map[i]);
	i++;

	if (mlx->width % 2 == 0)
		mlx->map[i]->pos.vec[0] -= 1;
	if (mlx->height % 2 == 0)
		mlx->map[i]->pos.vec[1] -= 1;
	mlx->map[i]->pos.vec[2] += mlx->width / 2 + 1;
	mlx->map[i]->pos.vec[3] += mlx->height / 2 + 1;
	mlx->map[i]->origin = mat4_trans((float[3]){(mlx->map[i]->pos.vec[2] + mlx->map[i]->pos.vec[0] * 2) / 4, (mlx->map[i]->pos.vec[3] + mlx->map[i]->pos.vec[1] * 2) / 4, 1});
	mlx->map[i]->rot = vec4_ini((float[4]){-90, -90, -180,ROTA_W});
	zoom_check(mlx->map[i]);
}

void	settings_reset(t_map *map, t_mlx *mlx)
{
	mlx->mode = 1;
	mlx->smap = mlx->map[0];
	map->rot = vec4_ini((float[4]){ROTA_X, ROTA_Y, ROTA_Z, ROTA_W});
	map->mode = MODE_DEF;
	map->color = MODE_COLOR;
	map->h_mod = H_MOD;
	map->pos = vec4_ini((float[4]){mlx->width, mlx->height, 0, 0});
	map->zoom = ZOOM_DEF;
	zoom_check(map);
	map->cam.loc = vec4_ini((float[4]){(int)(map->pos.vec[0] / 2), (int)(map->pos.vec[1] / 2), 0, 1});
	map->cam.plan = vec4_ini((float[4]){0, 100, FOV_DEF, -1});
	map->cam.rot = vec4_ini((float[4]){90, 90, 0, 1});
	map->origin = mat4_trans((float[3]){mlx->width / 4, mlx->height / 4, 1});
	map->limit = 1;
	//mat4_trans((float[3]){START_X + map->size.x * WIDTH, START_Y + map->size.y * WIDTH, 1});
}

// mode 1 map_matrix, mode 2/3 camera_matrix
void	draw(t_map *map, t_mlx *mlx, t_mat4 matrix, t_loca (*loca)(t_point*, t_map*, t_mat4))
{
	t_point	*row;
	t_point	*curr;
	t_loca	this;
	t_loca	next;

	row = map->start;
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
	// rotation cube HOW TO MAKE A T_POINT?? 
	//this = (*loca)(map_point(vec4_ini((float[4]){0, 0, 0, 1}), 0xffffff), map, matrix);
	//next = map_point(vec4_ini((float[4]){0, -1, 0, 1}), 0xffffff);
	//draw_linez1(mlx, map, this, (*loca)(curr->bottm, map, matrix));
}

void	draw_selected(t_mlx *mlx, t_map *map)
{
	if (map->mode == 1)
		draw(map, mlx, map_matrix(map), point_loca);
	else if (map->mode == 2)
		draw(map, mlx, camera_matrix(map->cam), point_loca_orth);
	else if (map->mode == 3)
		draw(mlx->smap, mlx, camera_matrix(map->cam), point_loca_pin);
}

void	draw_map(t_mlx *mlx)
{
	int	i;

	mlx_clear_window(mlx->mlx_ptr, mlx->mlx_win);
	if (mlx->mode == 2)
	{
		i = 0;
		while (++i < 5)
			draw_selected(mlx, mlx->map[i]);
		draw_linez1(mlx, mlx->map[0], map_point(vec4_ini((float[4]){0, mlx->height / 2, 0, 1}), 0xffffff), map_point(vec4_ini((float[4]){mlx->width, mlx->height / 2, 0, 1}), 0xffffff));

		draw_linez1(mlx, mlx->map[0], map_point(vec4_ini((float[4]){mlx->width / 2, 0, 0, 1}), 0xffffff), map_point(vec4_ini((float[4]){mlx->width / 2, mlx->height, 0, 1}), 0xffffff));

		draw_linez1(mlx, mlx->map[0], map_point(vec4_ini((float[4]){mlx->smap->pos.vec[2], mlx->smap->pos.vec[3], 0, 1}), 0xffffff), 
			map_point(vec4_ini((float[4]){mlx->smap->pos.vec[2] + mlx->smap->pos.vec[0], mlx->smap->pos.vec[3], 0, 1}), 0xffffff)); // left top -> right top

		draw_linez1(mlx, mlx->map[0], map_point(vec4_ini((float[4]){mlx->smap->pos.vec[2], mlx->smap->pos.vec[3], 0, 1}), 0xffffff), 
			map_point(vec4_ini((float[4]){mlx->smap->pos.vec[2], mlx->smap->pos.vec[3] + mlx->smap->pos.vec[1], 0, 1}), 0xffffff)); // left top -> left bottom

		draw_linez1(mlx, mlx->map[0], map_point(vec4_ini((float[4]){mlx->smap->pos.vec[2], mlx->smap->pos.vec[3] + mlx->smap->pos.vec[1], 0, 1}), 0xffffff), 
			map_point(vec4_ini((float[4]){mlx->smap->pos.vec[2] + mlx->smap->pos.vec[0], mlx->smap->pos.vec[3] + mlx->smap->pos.vec[1], 0, 1}), 0xffffff)); // left bottom -> right bottom

		draw_linez1(mlx, mlx->map[0], map_point(vec4_ini((float[4]){mlx->smap->pos.vec[2] + mlx->smap->pos.vec[0], mlx->smap->pos.vec[3], 0, 1}), 0xffffff), 
			map_point(vec4_ini((float[4]){mlx->smap->pos.vec[2] + mlx->smap->pos.vec[0], mlx->smap->pos.vec[3] + mlx->smap->pos.vec[1], 0, 1}), 0xffffff)); // right top -> right bottom
	}
	else {
		draw_selected(mlx, mlx->smap);
	}
}
