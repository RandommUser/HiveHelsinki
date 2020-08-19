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

void	rota(t_map *map, int angle, int dir)
{

	if (map->mode == 2)
	{
		map->cam.rot.vec[angle] += ROTA_STEP / 2 * dir;
		if (map->cam.rot.vec[angle] <= -360 || map->cam.rot.vec[angle] >= 360)
			map->cam.rot.vec[angle] = (ft_abs(map->cam.rot.vec[angle]) - 360) * dir;
	}
	else
	{
		map->rot.vec[angle] += (ROTA_STEP * dir);
		if (map->rot.vec[angle] <= -360 || map->rot.vec[angle] >= 360)
			map->rot.vec[angle] = (ft_abs(map->rot.vec[angle]) - 360) * dir;
	}
}

void	map_select(t_mlx *mlx, int n)
{
	if (mlx->mode == 2 && n > 0 && n < 5)
		mlx->smap = mlx->map[n];
}

void	view_mode(t_mlx *mlx)
{
	if (mlx->mode == 2)
	{
		mlx->mode = 1;
		mlx->smap = mlx->map[0];
	}
	else
	{
		mlx->mode = 2;
		mlx->smap = mlx->map[1];
	}
}

void	mode(t_map *map)
{
	map->mode = map->mode == 2 ? 1 : 2;
}

void	move(t_map *map, int angle, int dir)
{
	if (map->mode == 2)
		map->cam.loc.vec[angle] += WIDTH * dir;
	else
		map->origin.mat[angle][3] += WIDTH * dir;
}

void	zoom(t_map *map, int dir)
{
	map->zoom = dir > 0 ? map->zoom * 1.2 : map->zoom / 1.2;
}

void	fov(t_map *map, int dir)
{
	if (map->mode == 2)
	{
		map->cam.plan.vec[2] += FOV_STEP * dir;
		if (map->cam.plan.vec[2] >= 180 || map->cam.plan.vec[2] <= 0)
			map->cam.plan.vec[2] -= FOV_STEP * dir;
	}
}

void	plain_flip(t_map *map)
{
	if (map->mode == 2)
	{
		map->cam.plan.vec[0] *= -1;
		map->cam.plan.vec[1] *= -1;
	}
}

void	cam_plain(t_map *map, int coord, int dir)
{
	if (map->mode == 2)
	{
		map->cam.plan.vec[coord] += WIDTH / 2 * dir;
		if (map->cam.plan.vec[0] == map->cam.plan.vec[1])
			map->cam.plan.vec[coord] -= WIDTH / 2 * dir;
	}
}

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

t_mat4	camera_matrix(t_cam cam)
{
	t_mat4	ret;

	ret = mat4_iden();
	ret = mat4_mat4(ret, mat4_rotx(cam.rot.vec[0]));
	ret = mat4_mat4(ret, mat4_roty(cam.rot.vec[1]));
	ret = mat4_mat4(ret, mat4_rotz(cam.rot.vec[2]));
	return (ret);
}

t_mat4	map_matrix(t_map *map)
{
	t_mat4	trans;

	trans = mat4_iden();
	trans = mat4_mat4(trans, mat4_rotx(map->rot.vec[0]));
	trans = mat4_mat4(trans, mat4_roty(map->rot.vec[1]));
	trans = mat4_mat4(trans, mat4_rotz(map->rot.vec[2]));
//	mat4_put(trans);
	return (trans);
}


// scale -> rotate -> translate -> projection

t_loca	point_loca_p(t_point *point, t_map *map, t_mat4 rot)
{
	t_vec4	vec;
	t_mat4	proj;
	t_mat4	zoom;
	t_mat4	trans;
	t_vec4	rotn;

	point->color = point->color == -1 ? DEF_COLOR : point->color;
	zoom = mat4_scales((float[4]){map->zoom, map->zoom, map->zoom, 1});
	

	vec = vec4_ini((float[4]){(point->loc.vec[0] - map->size.x) * WIDTH,
		(point->loc.vec[1] - map->size.y) * WIDTH, point->loc.vec[2] * WIDTH * map->h_mod, point->loc.vec[3]});
//	vec4_put(vec);

	/* MORE ROTATIONS */
/*	printf("x %f y %f\n", map->rot.vec[0], map->rot.vec[1]);
	printf("x %f y %f\n", map->cam.plan.vec[2] / 2 * (point->loc.vec[0] - map->size.x) / map->size.x, map->cam.plan.vec[2] / 2 * (point->loc.vec[1] - map->size.y) / map->size.y);
	rotn = map->rot;
	rotn.vec[0] = -1 * (map->rot.vec[0] + 45 * (point->loc.vec[0] - map->size.x) / map->size.x);
	rotn.vec[1] = 1 * (map->rot.vec[1] + 45 * (point->loc.vec[1] - map->size.y) / map->size.y);
	rot = mat4_iden();
	rot = mat4_mat4(rot, mat4_rotx(rotn.vec[0]));
	rot = mat4_mat4(rot, mat4_roty(rotn.vec[1]));
	rot = mat4_mat4(rot, mat4_rotz(rotn.vec[2]));
*/

	trans = mat4_mat4(zoom, rot);
//	write(1, "\n", 1);
//	mat4_put(trans);
//	vec4_put(vec);
	trans = mat4_mat4(trans, mat4_perps2(map->cam.plan, map->pos.vec[0] / map->pos.vec[1]));
	
	
	//trans = mat4_mat4(trans, mat4_trans((float[3]){(int)(map->pos.vec[0] / 2), (int)(map->pos.vec[1] / 2), 1}));

	
	
//	write(1, "\n", 1);
//	mat4_put(trans);
	vec = mat4_vec4(trans, vec);
	vec.vec[0] += map->cam.loc.vec[0]; //(int)(map->pos.vec[0] / 2);
	vec.vec[1] += map->cam.loc.vec[1]; //(int)(map->pos.vec[1] / 2);
	
//	vec4_put(vec);

	//vec = vec4m_vec4(vec, map->cam.loc);
	//vec4_put(vec);
	//write(1, "\n", 1);
	/*
	mat4_put(rot);
	vec = mat4_vec4(rot, vec);
	vec4_put(vec);
	write(1, "\n", 1);
	proj = mat4_perps2(map->cam.plan, map->pos.vec[0] / map->pos.vec[1]);
	mat4_put(proj);
	vec = mat4_vec4(proj, vec);
	vec4_put(vec);
	//vec.vec[0] = vec.vec[0] / vec.vec[3];
	//vec.vec[1] = vec.vec[1] / vec.vec[3];
	vec4_put(vec);
	*/
	//vec = mat4_vec4(zoom, vec);
	//vec = mat4_vec4(mat4_trans((float[3]){(int)(map->pos.vec[0] / 2), (int)(map->pos.vec[1] / 2), 1}), vec);
	//vec4_put(vec);

	//vec.vec[0] = vec.vec[0] / vec.vec[3];
	//vec.vec[1] = vec.vec[1] / vec.vec[3];
	//sleep(120);
	return (map_point(vec, point->color));
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
	vec = mat4_vec4(zoom, vec);
	vec = mat4_vec4(map->origin, vec);
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
	map = mlx->smap;
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
	else
		contra = 0;
	
	if (key == PG_UP)
	{
		zoom(mlx->smap, -1);
		draw_map(map, mlx);
	}
	else if (key == PG_DW)
	{
		zoom(mlx->smap, 1);
		draw_map(map, mlx);
	}
	else if (key == AR_UP)
	{
		move(mlx->smap, 1, -1);
		draw_map(map, mlx);
	}
	else if (key == AR_DW)
	{
		move(mlx->smap, 1, 1);
		draw_map(map, mlx);
	}
	else if (key == AR_LF)
	{
		move(mlx->smap, 0, -1);
		draw_map(map, mlx);
	}
	else if (key == AR_RG)
	{
		move(mlx->smap, 0, 1);
		draw_map(map, mlx);
	}
	else if (key == K_W)
	{
		move(mlx->smap, 2, 1);
		draw_map(map, mlx);
	}
	else if (key == K_S)
	{
		move(mlx->smap, 2, -1);
		draw_map(map, mlx);
	}
	else if (key == K_A)
	{
		draw_map(map, mlx);
	}
	else if (key == K_D)
	{
		draw_map(map, mlx);
	}
	else if (key == 35) // projection change
	{
		//settings_reset(map, mlx);
		mode(mlx->smap);
		draw_map(map, mlx);
	}
	else if (key == 88) // left
	{
		rota(mlx->smap, 1, 1);
		draw_map(map, mlx);
	}
	else if (key == 86) // right
	{
		rota(mlx->smap, 1, -1);
		draw_map(map, mlx);
	}
	else if (key == 91) // top
	{
		rota(mlx->smap, 0, -1);
		draw_map(map, mlx);
	}
	else if (key == 84) // bottom
	{
		rota(mlx->smap, 0, 1);
		draw_map(map, mlx);
	}
	else if (key == 92) // c-clockwise
	{
		rota(mlx->smap, 2, 1);
		draw_map(map, mlx);
	}
	else if (key == 83) // clockwise
	{
		rota(mlx->smap, 2, -1);
		draw_map(map, mlx);
	}
	else if (key == 69) // height +
	{
		mlx->smap->h_mod *= 1.1;
		draw_map(map, mlx);
	}
	else if (key == 67) // height flip
	{
		mlx->smap->h_mod *= -1;
		draw_map(map, mlx);
	}
	else if (key == 78) // height --
	{
		mlx->smap->h_mod /= 1.1;
		draw_map(map, mlx);
	}
	else if (key == 43) // fov ++
	{
		fov(mlx->smap, -1);
		draw_map(map, mlx);
	}
	else if (key == 47) // fov --
	{
		fov(mlx->smap, 1);
		draw_map(map, mlx);
	}
	else if (key == 41) // nearP --
	{
		cam_plain(mlx->smap, 0, -1);
		draw_map(map, mlx);
	}
	else if (key == 39) // nearP ++
	{
		cam_plain(mlx->smap, 0, 1);
		draw_map(map, mlx);
	}
	else if (key == 33) // farP --
	{
		cam_plain(mlx->smap, 1, -1);
		draw_map(map, mlx);
	}
	else if (key == 30) // farP ++
	{
		cam_plain(mlx->smap, 1, 1);
		draw_map(map, mlx);
	}
	else if (key == 75) // camera plain flip
	{
		plain_flip(mlx->smap);
		draw_map(map, mlx);
	}
	else if (key == 15) // reset map
	{
		settings_reset(mlx->smap, mlx);
		draw_map(map, mlx);
	}
	else if (key == 23) // view mode swap
	{
		view_mode(mlx);
		draw_map(map, mlx);
	}
	else if (key == 18) // map 1
	{
		map_select(mlx, 1);
		draw_map(map, mlx);
	}
	else if (key == 19) // map 2
	{
		map_select(mlx, 2);
		draw_map(map, mlx);
	}
	else if (key == 20) // map 3
	{
		map_select(mlx, 3);
		draw_map(map, mlx);
	}
	else if (key == 21) // map 4
	{
		map_select(mlx, 4);
		draw_map(map, mlx);
	}
	else if (key == 2 && map->mode != 0)
		mlx->smap->mode = 0;
	else if (key == 2 && map->mode == 0)
		mlx->smap->mode = 1;

	ft_putnbr(key);
	ft_putstr("\n");
	if (mlx->smap->mode == 2)
	{
		printf("current rota | x: %f y: %f z: %f zoom: %f\n", mlx->smap->cam.rot.vec[0], mlx->smap->cam.rot.vec[1], mlx->smap->cam.rot.vec[2], mlx->smap->zoom);
		printf("cam x %f y %f z %f\n", mlx->smap->cam.loc.vec[0], mlx->smap->cam.loc.vec[1], mlx->smap->cam.loc.vec[2]);
		printf("nP %f fP %f fov %f\n", mlx->smap->cam.plan.vec[0], mlx->smap->cam.plan.vec[1], mlx->smap->cam.plan.vec[2]);
	}
	else
	{
		printf("current rota | x: %f y: %f z: %f zoom: %f\nheight mod %f\n", mlx->smap->rot.vec[0], mlx->smap->rot.vec[1], mlx->smap->rot.vec[2], mlx->smap->zoom, mlx->smap->h_mod);
		printf("x %f y %f\n", mlx->smap->origin.mat[0][3], mlx->smap->origin.mat[1][3]);
		printf("w %f h %f x %f y %f\n", mlx->smap->pos.vec[0], mlx->smap->pos.vec[1], mlx->smap->pos.vec[2], mlx->smap->pos.vec[3]);
		printf("stuff %f %f %f %f\n",mlx->map[2]->pos.vec[2] + mlx->map[2]->pos.vec[0], (mlx->map[2]->pos.vec[2] + mlx->map[2]->pos.vec[0]) / 4, mlx->map[2]->pos.vec[3] + mlx->map[2]->pos.vec[1], mlx->map[2]->pos.vec[3] + mlx->map[2]->pos.vec[1] / 4);
	}
	printf("view mode %d\n", mlx->mode);
	if (mlx->mode == 2)
	{
		printf("map 1 %p map 2 %p map 3 %p map 4 %p\n", mlx->map[1], mlx->map[2], mlx->map[3], mlx->map[4]);
		printf("smap %p\n", mlx->smap);
	}
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
	rtn->mode = 1;
	//rtn->zoom = ZOOM_DEF;
	//rtn->mode = MODE_DEF;
	//rtn->color = MODE_COLOR;
	rtn->map[0] = NULL;
	rtn->smap = NULL;
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
		mlx->map[0] = map;
		mlx->smap = mlx->map[0];
		settings_reset(map, mlx);
		map_reset(mlx);
		draw_map(map, mlx);
	}
	mlx_loop(mlx->mlx_ptr);
	return (0);
}
