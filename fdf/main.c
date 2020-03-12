/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:20:20 by phakakos          #+#    #+#             */
/*   Updated: 2020/02/21 16:18:09 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_loca	map_point(int x, int y, int z, int color)
{
	t_loca	rtn;

	rtn.x = x;
	rtn.y = y;
	rtn.z = z;
	rtn.color = rgb_conv(color);
	return (rtn);
}

t_coord	coords(int x, int y)
{
	t_coord	rtn;

	rtn.x = x;
	rtn.y = y;
	return (rtn);
}

t_coord	center_point(t_map *map)
{
	t_point	*start;
	int		x;
	int		y;

	start = map->start;
	while (start->right)
		start = start->right;
	while (start->bottm)
		start = start->bottm;
	x = start->x * 10 / 2;
	x = /*(float)(x / 10) * map->w_mod + */(float)(x / 10) * WIDTH * map->w_mod + map->pos.x * map->w_mod;
	y = start->y * 10 / 2;
	y = /*(float)(y / 10) * map->w_mod + */(float)(y / 10) * WIDTH * map->w_mod + map->pos.y * map->w_mod;
	return (coords(x, y));
}

t_loca	rota_x(t_loca point, t_mlx *mlx)
{
	t_coord	center;
	int		rota;
	float	prog;

	rota = mlx->rota.y;
	prog = (float)(rota) / 90;
	if (point.x == -1 || rota == 0)
		return (point);
	center = center_point(mlx->map);
	if (prog == 1 || prog == 3 || prog == -1 || prog == -3)
	{
		if (prog == 1 || prog == -3)
			point.x = center.x + point.z;
		else
			point.x = center.x - point.z;
	}
	else if (prog == 2 || prog == -2)
		point.x = center.x - (point.x - center.x);
	else
	{
		prog = prog < 0 ? prog * -1 : prog;
		prog = prog > 1 ? (int)(prog) + 1 - prog : prog;
		if ((rota < 90 && rota >= 0) || (rota > -360 && rota < -270))
			point.x += point.z * prog + (center.x - point.x - WIDTH * mlx->map->w_mod) * prog;
		else if ((rota < 0 && rota > -90) || (rota > 270 && rota < 360))
			point.x += (center.x - point.x - WIDTH * mlx->map->w_mod) * prog - point.z * prog;
		else
			point.x = center.x +  point.z * prog - (point.x - center.x - WIDTH *mlx->map->w_mod) * prog;
	}
	return (point);
}

t_loca	point_loca(t_point *point, t_map *map)
{
	int x;
	int y;
	int z;

	if (!point)
		return (map_point(-1, -1, -1, -1));
	x = map->pos.x * map->w_mod + point->x * WIDTH * map->w_mod;
	y = map->pos.y * map->w_mod + point->y * WIDTH * map->w_mod;
	z = point->z * WIDTH * map->h_mod;
	point->color = point->color == -1 ? DEF_COLOR : point->color;
	return (map_point(x, y, z, point->color));
}

/*
void	draw_line(t_mlx *mlx, t_coord start, t_coord end, int color)
{
	int dx;
	int dy;
	int x;
	int y;

	x = start.x;
	y = start.y;
	dx = end.x - start.x;
	dy = end.y - start.y;
	if ((ft_abs(dx) > ft_abs(dy) && dx != 0) || dy == 0)
	{
		while (x != end.x)
		{
			y = start.y + dy * (x - start.x) / dx;
			mlx_pixel_put(mlx->mlx_ptr, mlx->mlx_win, x, y, color);
			x = x < end.x ? x + 1 : x - 1;
		}
	}
	else
	{
		while (y != end.y)
		{
			x = start.x + dx * (y - start.y) / dy;
			mlx_pixel_put(mlx->mlx_ptr, mlx->mlx_win, x, y, color);
			y = y < end.y ? y + 1 : y - 1;
		}
	}
}

void	draw_box(t_mlx *mlx, t_coord start, t_coord end)
{
	int x;
	int y;
	int i;

	x = mlx->width;
	y = mlx->height;
	i = start.x;
	while (i <= end.y)
	{
		draw_line(mlx, coords(0, i), coords(x, i), 0x000000);
		i++;
	}
}
*/

int	input_testing(int key, void *param)
{
	static int	contra;
	t_mlx		*mlx;
	t_map		*map;

	mlx = param;
	map = mlx->map;
	if (key == ESC_KEY)
		exit(1);
	else if (key == 117)
		mlx_clear_window(mlx->mlx_ptr, mlx->mlx_win);
	else if (key == 126 && (contra == 0 || contra == 1))
		contra++;
	else if (key == 125 && (contra == 2 || contra == 3))
		contra++;
	else if (key == 123 && (contra == 4 || contra == 6))
		contra++;
	else if (key == 124 && (contra == 5 || contra == 7))
		contra++;
	else if (key == 11 && contra == 8)
		contra++;
	else if (key == 0 && contra == 9)
		contra++;
	else if (key == 36 && contra == 10)
	{
		ft_putstr("SECRET FOUND!\n");
		contra = 0;
	}
	if (key == PG_UP)
	{
		map->w_mod = map->w_mod * 0.9;
		draw_map(map, mlx);
	}
	else if (key == PG_DW)
	{
		map->w_mod = map->w_mod * 1.1;
		draw_map(map, mlx);
	}
	else if (key == AR_UP)
	{
		map->pos.y -= WIDTH * map->w_mod / 2;
printf("start pos is x: %d y: %d\n", map->pos.x, map->pos.y);
		draw_map(map, mlx);
	}
	else if (key == AR_DW)
	{
		map->pos.y += WIDTH * map->w_mod / 2;
printf("start pos is x: %d y: %d\n", map->pos.x, map->pos.y);
		draw_map(map, mlx);
	}
	else if (key == AR_LF)
	{
		map->pos.x -= WIDTH * map->w_mod / 2;
printf("start pos is x: %d y: %d\n", map->pos.x, map->pos.y);
		draw_map(map, mlx);
	}
	else if (key == AR_RG)
	{
		map->pos.x += WIDTH * map->w_mod / 2;
printf("start pos is x: %d y: %d\n", map->pos.x, map->pos.y);
		draw_map(map, mlx);
	}
	else if (key == 88)
	{
		mlx->rota.y = mlx->rota.y + ROTA_STEP;
		mlx->rota.y = mlx->rota.y / 360 > 0 ? mlx->rota.y - 360 : mlx->rota.y;
		draw_map(map, mlx);
	}
	else if (key == 86)
	{
		mlx->rota.y = mlx->rota.y - ROTA_STEP;
		mlx->rota.y = mlx->rota.y / -360 > 0 ? mlx->rota.y + 360 : mlx->rota.y;
		draw_map(map, mlx);
	}
	else if (key == 15)
	{
		settings_reset(map, mlx);
		draw_map(map, mlx);
	}
	else if (key == 2 && mlx->mode != 0)
		mlx->mode = 0;
	else if (key == 2 && mlx->mode == 0)
		mlx->mode = 1;
	else
		contra = 0;
	ft_putnbr(key);
	ft_putstr("\n");
printf("current rota | x: %d y: %d z: %d\n", mlx->rota.x, mlx->rota.y, mlx->rota.z);
	return (0);
}

int	mouse_testing(int button, int x, int y, void *container)
{
	t_mlx		*mlx;
	static int	xx = -1;
	static int	yy = -1;
	static int	color = 0x000000;
	static int	color2 = 0x000000;
	double		freq = 0.3;
	static int	i;

	mlx = container;
	color = rgb_color((sin(freq * i + 0) * 127 + 128), (sin(freq * i + 2) * 127 + 128), (sin(freq * i + 4) * 127 + 128));
	i += 2;
	color2 = rgb_color((sin(freq * i + 0) * 127 + 128), (sin(freq * i + 2) * 127 + 128), (sin(freq * i + 4) * 127 + 128));
	i++;
	if ((xx == -1 && button == 1 )|| button == 3)
	{
		xx = x;
		yy = y;
	}
	else if (button == 1 && mlx->mode == 0)
	{
		draw_line1(mlx, map_point(xx, yy, 0, color), map_point(x, y, 0, color2));
		xx = -1;
		yy = -1;
	}
	else if (button == 2 && mlx->mode == 0)
	{
		draw_line1(mlx, map_point(xx, yy, 0, 0xffffff), map_point(x, y, 0, color));
		xx = x;
		yy = y;
	}
	else if (button == 4 && mlx->mode == 0)
	{
		color = rgb_color((sin(freq * i + 0) * 127 + 128), (sin(freq * i + 2) * 127 + 128), (sin(freq * i + 4) * 127 + 128));
		i++;
		color2 = rgb_color((sin(freq * i + 0) * 127 + 128), (sin(freq * i + 2) * 127 + 128), (sin(freq * i + 4) * 127 + 128));
		draw_line1(mlx, map_point(xx, yy, 0, color), map_point(x, y, 0, color2));
		i++;
	}
	ft_putnbr(button);
	ft_putstr(" | ");
	ft_putnbr(x);
	ft_putchar('x');
	ft_putnbr(y);
	ft_putchar('\n');
	return (0);
}

t_mlx	*cont_init(int width, int height, char *title)
{
	t_mlx	*rtn;

	if (!(rtn = (t_mlx *)malloc(sizeof(t_mlx))))
		return (NULL);
	rtn->width = width;
	rtn->height = height;
	rtn->title = title;
	rtn->mlx_ptr = mlx_init();
	rtn->mlx_win = mlx_new_window(rtn->mlx_ptr, width, height, title);
	rtn->fov = FOV_DEF;
	rtn->zoom = ZOOM_DEF;
	rtn->mode = MODE_DEF;
	rtn->color = MODE_COLOR;
	rtn->map = NULL;
	rtn->rota = map_point(ROTA_X, ROTA_Y, ROTA_Z, 0);
	return (rtn);
}

int	main(int argc, char **argv)
{
	t_mlx	*mlx;
	t_map		*map;

	mlx = NULL;
	if (argc == 4)
		mlx = cont_init(ft_atoi(argv[2]), ft_atoi(argv[3]), "Hello World");
	else
		mlx = cont_init(800, 600, "Hello World");
	mlx_key_hook(mlx->mlx_win, input_testing, mlx);
	mlx_mouse_hook(mlx->mlx_win, mouse_testing, mlx);
	if (argc > 1)
	{
		if (!map_reader(mlx, argv[1], &map))
			exit(0);
		mlx->map = map;
		draw_map(map, mlx);
	}
	mlx_loop(mlx->mlx_ptr);
	return (0);
}
