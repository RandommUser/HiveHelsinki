/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:20:20 by phakakos          #+#    #+#             */
/*   Updated: 2020/06/02 15:10:20 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_loca	map_point(t_vec4 vec, int color)
{
	t_loca	rtn;

	rtn.loc.vec[0] = (int)vec.vec[0];
	rtn.loc.vec[1] = (int)vec.vec[1];
	rtn.loc.vec[2] = (int)vec.vec[2];
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

void	map_size(t_map **map)
{
	t_point	*start;
	float		x;
	float		y;

	start = (*map)->start;
	x = 0;
	y = 0;
	while (start->right && (++x))
		start = start->right;
	while (start->bottm && (++y))
		start = start->bottm;
	(*map)->size.x = x / 2;
	(*map)->size.y = y / 2;
}

t_mat4	map_matrix(t_map *map)
{
	//t_mat4	zoom;
	t_mat4	trans;

	//zoom = mat4_scales((float[4]){map->zoom, map->zoom, map->zoom, 1});
	trans = mat4_iden();
	trans = mat4_mat4(trans, map->rotx);
	trans = mat4_mat4(trans, map->roty);
	trans = mat4_mat4(trans, map->rotz);
	mat4_put(trans);
	//trans = mat4_mat4(trans, zoom);
	//mat4_put(trans);
	//trans = mat4_mat4(trans, map->origin);
	//mat4_put(trans);
	return (trans);
}

t_loca	point_loca(t_point *point, t_map *map, t_mat4 trans)
{
	t_vec4	vec;
	t_mat4	zoom;

	point->color = point->color == -1 ? DEF_COLOR : point->color;
	
	//vec = vec4_ini((float[4]){point->loc.vec[0],point->loc.vec[1],point->loc.vec[2],point->loc.vec[3]});
	vec = vec4_ini((float[4]){(point->loc.vec[0] - map->size.x) * WIDTH,
		(point->loc.vec[1] - map->size.y) * WIDTH, point->loc.vec[2] * WIDTH * map->h_mod, point->loc.vec[3]});
	//vec4_put(vec);
	//write(1, "\n", 1);
	//mat4_put(trans);
	//trans = mat4_trans((float[3]){(point->loc.vec[0] - map->size.x) * WIDTH,
	//	(point->loc.vec[1] - map->size.y) * WIDTH, 1});
	//vec = mat4_vec4(trans, vec);
	zoom = mat4_scales((float[4]){map->zoom, map->zoom, map->zoom, 1});
	//zoom = mat4_mat4(zoom, map->origin);
	//mat4_put(zoom);

	
	vec = mat4_vec4(trans, vec);
	vec = mat4_vec4(map->origin, vec);
	vec = mat4_vec4(zoom, vec);
	zoom = mat4_pro();
	vec = mat4_vec4(zoom, vec);
	
	
	
	//vec = mat4_vec4(zoom, vec);
	//vec4_put(vec);
//	vec.vec[0] = map->pos.x * map->w_mod + point->loc.vec[0] * WIDTH * map->w_mod * mlx->zoom;
//	vec.vec[1] = map->pos.y * map->w_mod + point->loc.vec[1] * WIDTH * map->w_mod * mlx->zoom;
//	vec.vec[2] = point->loc.vec[2] * WIDTH * map->h_mod * mlx->zoom;
	return (map_point(vec, point->color));
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
//		map->w_mod = map->w_mod * 0.9;
//		printf("%f\n", map->zoom / 1.2);
		map->zoom = map->zoom / 1.2;
		draw_map(map, mlx);
	}
	else if (key == PG_DW)
	{
//		map->w_mod = map->w_mod * 1.1;
		map->zoom = map->zoom * 1.2;
		draw_map(map, mlx);
	}
	else if (key == AR_UP)
	{
//		map->pos.y -= WIDTH * map->w_mod * mlx->zoom / 2;
//printf("start pos is x: %f y: %f\n", map->pos.x, map->pos.y);
		draw_map(map, mlx);
	}
	else if (key == AR_DW)
	{
//		map->pos.y += WIDTH * map->w_mod * mlx->zoom/ 2;
//printf("start pos is x: %f y: %f\n", map->pos.x, map->pos.y);
		draw_map(map, mlx);
	}
	else if (key == AR_LF)
	{
//		map->pos.x -= WIDTH * map->w_mod * mlx->zoom / 2;
//printf("start pos is x: %f y: %f\n", map->pos.x, map->pos.y);
		draw_map(map, mlx);
	}
	else if (key == AR_RG)
	{
//		map->pos.x += WIDTH * map->w_mod * mlx->zoom / 2;
//printf("start pos is x: %f y: %f\n", map->pos.x, map->pos.y);
		draw_map(map, mlx);
	}
	else if (key == K_W)
	{
//		map->pos.y -= WIDTH * map->w_mod / 4;
//printf("start pos is x: %f y: %f\n", map->pos.x, map->pos.y);
		draw_map(map, mlx);
	}
	else if (key == K_S)
	{
//		map->pos.y += WIDTH * map->w_mod / 4;
//printf("start pos is x: %f y: %f\n", map->pos.x, map->pos.y);
		draw_map(map, mlx);
	}
	else if (key == K_A)
	{
//		map->pos.x -= WIDTH * map->w_mod / 4;
//printf("start pos is x: %f y: %f\n", map->pos.x, map->pos.y);
		draw_map(map, mlx);
	}
	else if (key == K_D)
	{
//		map->pos.x += WIDTH * map->w_mod / 4;
//printf("start pos is x: %f y: %f\n", map->pos.x, map->pos.y);
		draw_map(map, mlx);
	}
	else if (key == 88) // left
	{
		map->rot.vec[1] = map->rot.vec[1] + ROTA_STEP;
		map->rot.vec[1] = map->rot.vec[1] >= 360 ? map->rot.vec[1] - 360 : map->rot.vec[1];
		map->roty = mat4_roty(map->rot.vec[1]);
		draw_map(map, mlx);
	}
	else if (key == 86) // right
	{
		map->rot.vec[1] = map->rot.vec[1] - ROTA_STEP;
		map->rot.vec[1] = map->rot.vec[1] <= -360 ? map->rot.vec[1] + 360 : map->rot.vec[1];
		map->roty = mat4_roty(map->rot.vec[1]);
		draw_map(map, mlx);
	}
	else if (key == 91) // top
	{
		map->rot.vec[0] = map->rot.vec[0] - ROTA_STEP;
		map->rot.vec[0] = map->rot.vec[0] <= -360 ? map->rot.vec[0] + 360 : map->rot.vec[0];
		map->rotx = mat4_rotx(map->rot.vec[0]);
		draw_map(map, mlx);
	}
	else if (key == 84) // bottom
	{
		map->rot.vec[0] = map->rot.vec[0] + ROTA_STEP;
		map->rot.vec[0] = map->rot.vec[0] >= 360 ? map->rot.vec[0] - 360 : map->rot.vec[0];
		map->rotx = mat4_rotx(map->rot.vec[0]);
		draw_map(map, mlx);
	}
	else if (key == 92) // c-clockwise
	{
		map->rot.vec[2] = map->rot.vec[2] + ROTA_STEP;
		map->rot.vec[2] = map->rot.vec[2] >= 360 ? map->rot.vec[2] - 360 : map->rot.vec[2];
		map->rotz = mat4_rotz(map->rot.vec[2]);
		draw_map(map, mlx);
	}
	else if (key == 83) // clockwise
	{
		map->rot.vec[2] = map->rot.vec[2] - ROTA_STEP;
		map->rot.vec[2] = map->rot.vec[2] <= -360 ? map->rot.vec[2] + 360 : map->rot.vec[2];
		map->rotz = mat4_rotz(map->rot.vec[2]);
		draw_map(map, mlx);
	}
	else if (key == 69)
	{
		map->h_mod *= 1.1;
		draw_map(map, mlx);
	}
	else if (key == 67)
	{
		map->h_mod *= -1;
		draw_map(map, mlx);
	}
	else if (key == 78)
	{
		map->h_mod /= 1.1;
		draw_map(map, mlx);
	}
	else if (key == 15)
	{
		settings_reset(map, mlx);
		draw_map(map, mlx);
	}
	else if (key == 2 && map->mode != 0)
		map->mode = 0;
	else if (key == 2 && map->mode == 0)
		map->mode = 1;
	else
		contra = 0;
	ft_putnbr(key);
	ft_putstr("\n");
printf("current rota | x: %f y: %f z: %f zoom: %f\nheight mod %f\n", map->rot.vec[0], map->rot.vec[1], map->rot.vec[2], map->zoom, map->h_mod);
	return (0);
}
/*
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
*/
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
	//rtn->zoom = ZOOM_DEF;
	//rtn->mode = MODE_DEF;
	//rtn->color = MODE_COLOR;
	rtn->map = NULL;
	//rtn->rot = vec4_ini((float[4]){0, 0, 0, 1});
	//rtn->rotx = mat4_rotx(0);
	//rtn->roty = mat4_roty(0);
	//rtn->rotz = mat4_rotz(0);
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
	//mlx_mouse_hook(mlx->mlx_win, mouse_testing, mlx);
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
