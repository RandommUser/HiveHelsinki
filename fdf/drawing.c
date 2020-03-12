/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 15:53:04 by phakakos          #+#    #+#             */
/*   Updated: 2020/02/20 19:49:34 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_rgb	color_flow(t_loca start, t_loca diff, t_loca curr, t_loca end)
{
	t_rgb	rtn;
	float	prog;

	if (ft_abs(diff.x) > ft_abs(diff.y))
	{
		prog = ft_abs(curr.x - end.x);
		prog = prog == 0 ? 0 : 1 - prog / ft_abs(diff.x);
	}
	else
	{
		prog = ft_abs(curr.y - end.y);
		prog = prog == 0 ? 0 : 1 - prog / ft_abs(diff.y);;
	}
	rtn.red = (1 - prog) * start.color.red + end.color.red * prog;
	rtn.green = (1 - prog) * start.color.green + end.color.green * prog;
	rtn.blue = (1 - prog) * start.color.blue + end.color.blue * prog;
//printf("curr|x:%d y:%d |end|x:%d y:%d\n", curr.x, curr.y, end.x, end.y);
//printf("prog|red:%d|green:%d|blue%d|prog:%f\n", rtn.red, rtn.green, rtn.blue,prog);
	return (rtn);
}

void	draw_line1(t_mlx *mlx, t_loca start, t_loca end)
{
	t_loca	diff;
	t_loca	curr;

	if (start.x == -1 || end.x == -1)
		return ;
	curr.x = start.x;
	curr.y = start.y;
	curr.z = start.z;
	curr.color = start.color;
//	diff.color = rgb_calc(end.color, start.color, '-');
	diff.x = end.x - start.x;
	diff.y = end.y - start.y;
	diff.z = end.z - start.z;
	if ((ft_abs(diff.x) > ft_abs(diff.y) && diff.x != 0) || diff.y == 0)
	{
		while (curr.x != end.x)
		{
			curr.y = start.y + diff.y * (curr.x - start.x) / diff.x;
			curr.color = color_flow(start, diff, curr, end);
			mlx_pixel_put(mlx->mlx_ptr, mlx->mlx_win, curr.x, curr.y,
					trgb_conv(curr.color));
			curr.x = curr.x < end.x ? curr.x + 1 : curr.x - 1;
		}
	}
	else
	{
		while (curr.y != end.y)
		{
			curr.x = start.x + diff.x * (curr.y - start.y) / diff.y;
			curr.color = color_flow(start, diff, curr, end);
			mlx_pixel_put(mlx->mlx_ptr, mlx->mlx_win, curr.x, curr.y,
					trgb_conv(curr.color));
			curr.y = curr.y < end.y ? curr.y + 1 : curr.y - 1;
		}
	}
//printf("drew a line from x:%d y:%d z:%d to x:%d y:%d z:%d\n", start.x, start.y, start.z, end.x, end.y, end.z);
//printf("starting colors | red: %d green: %d blue: %d\n", start.color.red, start.color.green, start.color.blue);
//printf("final colors | red: %d green: %d blue: %d\n", curr.color.red, curr.color.green, curr.color.blue);
//printf("goal colors | red: %d green: %d blue: %d\n", end.color.red, end.color.green, end.color.blue);
}

void	settings_reset(t_map *map, t_mlx *mlx)
{
	mlx->fov = FOV_DEF;
	mlx->rota = map_point(ROTA_X, ROTA_Y, ROTA_Z, 0);
	mlx->zoom = ZOOM_DEF;
	mlx->mode = MODE_DEF;
	mlx->color = MODE_COLOR;
	map->w_mod = W_MOD;
	map->h_mod = H_MOD;
	map->pos = coords(START_X, START_Y);
}

void	draw1(t_map *map, t_mlx *mlx)
{
	t_point	*row;
	t_point	*curr;
	t_loca	this;
	t_loca	next;

	row = map->start;
	while (row)
	{
		curr = row;
		while (curr)
		{
			this = point_loca(curr, map);
			this = rota_x(this, mlx);
			next = point_loca(curr->right, map);
			next = rota_x(next, mlx);
			draw_line1(mlx, this, next);
			next = point_loca(curr->bottm, map);
			next = rota_x(next, mlx);
			draw_line1(mlx, this, next);
			curr = curr->right;
		}
		row = row->bottm;
	}
}

void	draw_map(t_map *map, t_mlx *mlx)
{
	mlx_clear_window(mlx->mlx_ptr, mlx->mlx_win);
	if (mlx->mode == 1)
		draw1(map, mlx);
//	map = map;
//	mlx = mlx;
}
