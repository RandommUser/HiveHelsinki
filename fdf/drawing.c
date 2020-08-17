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

void	draw_spot(t_mlx *mlx, t_loca curr)
{
	double	pi;
	int		z;
	double	i;
	int		x;
	int		y;
   
	pi = 3.1415926535;
	z = 1;
	while (z++ < mlx->map->zoom)
	{
		i = 0;
		while (i < 360)
		{
			x = z * cos(i * pi / 180);
			y = z * sin(i * pi / 180);
			if (x % 1 == 0 && y % 1 == 0)
				mlx_pixel_put(mlx->mlx_ptr, mlx->mlx_win, curr.loc.vec[0] + x, curr.loc.vec[1] + y, trgb_conv(curr.color));
		//	i += 0.1;
			i += 30;
		}
	}
	mlx_pixel_put(mlx->mlx_ptr, mlx->mlx_win, curr.loc.vec[0], curr.loc.vec[1], trgb_conv(curr.color));
}

void	draw_line1(t_mlx *mlx, t_loca start, t_loca end)
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
			curr.color = color_flow(start, diff, curr, end);
			//if (curr.x + mlx->zoom >= 0 && curr.x - mlx->zoom <= mlx->width && 
			//		curr.y + mlx->zoom >= 0 && curr.y - mlx->zoom <= mlx->height)
			//	draw_spot(mlx, curr);
			mlx_pixel_put(mlx->mlx_ptr, mlx->mlx_win, curr.loc.vec[0], curr.loc.vec[1], trgb_conv(curr.color));
			curr.loc.vec[0] = curr.loc.vec[0] < end.loc.vec[0] ? curr.loc.vec[0] + 1 : curr.loc.vec[0] - 1;
		}
	}
	else
	{
		while (curr.loc.vec[1] != end.loc.vec[1])
		{
			curr.loc.vec[0] = start.loc.vec[0] + diff.loc.vec[0] * (curr.loc.vec[1] - start.loc.vec[1]) / diff.loc.vec[1];
			curr.color = color_flow(start, diff, curr, end);
			//if (curr.x + mlx->zoom >= 0 && curr.x - mlx->zoom <= mlx->width &&
			//		curr.y + mlx->zoom >= 0 && curr.y - mlx->zoom <= mlx->height)
			//	draw_spot(mlx, curr);
			mlx_pixel_put(mlx->mlx_ptr, mlx->mlx_win, curr.loc.vec[0], curr.loc.vec[1], trgb_conv(curr.color));
			curr.loc.vec[1] = curr.loc.vec[1] < end.loc.vec[1] ? curr.loc.vec[1] + 1 : curr.loc.vec[1] - 1;
		}
	}
//printf("drew a line from x:%d y:%d z:%d to x:%d y:%d z:%d\n", start.x, start.y, start.z, end.x, end.y, end.z);
//printf("starting colors | red: %d green: %d blue: %d\n", start.color.red, start.color.green, start.color.blue);
//printf("final colors | red: %d green: %d blue: %d\n", curr.color.red, curr.color.green, curr.color.blue);
//printf("goal colors | red: %d green: %d blue: %d\n", end.color.red, end.color.green, end.color.blue);
}

void	draw_linez1(t_mlx *mlx, t_loca start, t_loca end)
{
	double	pi;
	double	i;
	t_loca	nstart;
	t_loca	nend;
	double	angle;

	pi = 3.14159265;
	draw_line1(mlx, start, end);
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


void	settings_reset(t_map *map, t_mlx *mlx)
{
	mlx->fov = FOV_DEF;
	map->rot = vec4_ini((float[4]){ROTA_X, ROTA_Y, ROTA_Z, ROTA_W});
	map->origin = mat4_trans((float[3]){START_X + map->size.x * WIDTH, START_Y + map->size.y * WIDTH, 1});
	map->zoom = ZOOM_DEF;
	map->mode = MODE_DEF;
	map->color = MODE_COLOR;
	map->h_mod = H_MOD;
	map->cam.loc = vec4_ini((float[4]){(int)(map->pos.vec[0] / 2), (int)(map->pos.vec[1] / 2), 0, 1});
	map->cam.plan = vec4_ini((float[4]){110, 120, FOV_DEF, 1});
	map->cam.rot = vec4_ini((float[4]){90, 90, 0, 1});
	map->pos = vec4_ini((float[4]){mlx->width, mlx->height, 0, 0});
}

void	draw1(t_map *map, t_mlx *mlx)
{
	t_point	*row;
	t_point	*curr;
	t_loca	this;
	t_loca	next;
	t_mat4	matrix;

	matrix = map_matrix(map);
	row = map->start;
	while (row && (curr = row))
	{
		while (curr)
		{
			this = point_loca(curr, map, matrix);
			if (curr->right)
				draw_linez1(mlx, this, point_loca(curr->right, map, matrix));
			if (curr->bottm)
				draw_linez1(mlx, this, point_loca(curr->bottm, map, matrix));
			curr = curr->right;
		}
		row = row->bottm;
	}
}

void	draw2(t_map *map, t_mlx *mlx)
{
	t_point	*row;
	t_point	*curr;
	t_loca	this;
	t_loca	next;
	t_mat4	matrix;

	matrix = camera_matrix(map->cam);
	row = map->start;
	while (row && (curr = row))
	{
		while (curr)
		{
			this = point_loca_p(curr, map, matrix);
			if (curr->right)
				draw_linez1(mlx, this, point_loca_p(curr->right, map, matrix));
			if (curr->bottm)
				draw_linez1(mlx, this, point_loca_p(curr->bottm, map, matrix));
			curr = curr->right;
		}
		row = row->bottm;
	}
}

void	draw_map(t_map *map, t_mlx *mlx)
{
	mlx_clear_window(mlx->mlx_ptr, mlx->mlx_win);
	if (map->mode == 1)
		draw1(map, mlx);
	else if (map->mode == 2)
		draw2(map, mlx);
//	map = map;
//	mlx = mlx;
}
