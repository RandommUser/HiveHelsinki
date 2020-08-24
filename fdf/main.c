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

void	rota_cube(t_map *map)
{
	map->rot.vec[3] = map->rot.vec[3] == 1 ? 2 : 1;
}

void	vanishing_point(t_map *map, int dir)
{
	map->cam.plan.vec[3] += dir > 0 ? 0.1 : -0.1;
}

void	limitor(t_map *map)
{
	map->limit = map->limit == 1 ? 0 : 1;
}

void	rota(t_map *map, int angle, int dir)
{

	if (map->mode > 1)
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

void	map_mouse(t_mlx *mlx, int x, int y)
{
	size_t	i;

	if (mlx->mode == 2)
	{
		i = 0;
		while (++i < 5)
		{
			if (x >= mlx->map[i]->pos.vec[2] && x <= (mlx->map[i]->pos.vec[2] + mlx->map[i]->pos.vec[0]))
				if (y >= mlx->map[i]->pos.vec[3] && y <= (mlx->map[i]->pos.vec[3] + mlx->map[i]->pos.vec[1]))
				{
					mlx->smap = mlx->map[i];
					return ;
				}
		}
	}
}

void	mouse_move(t_map *map, int x, int y)
{
	if (map->mode > 1)
	{
		map->cam.loc.vec[0] = x;
		map->cam.loc.vec[1] = y;
	}
	else
	{
		map->origin.mat[0][3] = x;
		map->origin.mat[1][3] = y;
	}
}

void	mouse_zoom(t_map *map, int dir)
{
	map->zoom = dir > 0 ? map->zoom * 1.2 : map->zoom / 1.2;
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
	map->mode++;
	map->mode = map->mode > 3 ? 1 : map->mode;
}

void	move(t_map *map, int angle, int dir)
{
	if (map->mode > 1)
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
	if (map->mode > 1)
	{
		map->cam.plan.vec[2] += FOV_STEP * dir;
		if ((map->limit  && map->cam.plan.vec[2] >= 180) || (map->limit && map->cam.plan.vec[2] <= 0))
			map->cam.plan.vec[2] -= FOV_STEP * dir;
	}
}

void	plain_flip(t_map *map)
{
	if (map->mode > 1)
	{
		map->cam.plan.vec[0] *= -1;
		map->cam.plan.vec[1] *= -1;
	}
}

void	cam_plain(t_map *map, int coord, int dir)
{
	if (map->mode > 1)
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
	(*map)->size.z = 0;
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
	return (trans);
}

t_loca	rotation_cube(t_vec4 loc, t_map *map, int color)
{
	int	dir;

	loc.vec[0] *= WIDTH;
	loc.vec[1] *= WIDTH;
	loc.vec[2] *= WIDTH;
	if (map->mode == 1)
	{
		loc = mat4_vec4(map_matrix(map), loc);
		loc = mat4_vec4(map->origin, loc);
	}
	else
	{
		loc = mat4_vec4(camera_matrix(map->cam), loc);
		dir = map->mode == 2 ? 1 : 1;
		loc.vec[0] += (map->cam.loc.vec[0] * dir);
		loc.vec[1] += (map->cam.loc.vec[1] * dir);
	}
	loc = mat4_vec4(mat4_pro(), loc);
	color = color == -1 ? DEF_COLOR : color;
	return (map_point(loc, color));
}

t_loca	point_loca_orth(t_point *point, t_map *map, t_mat4 rot)
{
	t_vec4	vec;
	t_mat4	trans;

	point->color = point->color == -1 ? DEF_COLOR : point->color;
	vec = vec4_ini((float[4]){(point->loc.vec[0] - map->size.x) * WIDTH,
		(point->loc.vec[1] - map->size.y) * WIDTH, (point->loc.vec[2] * map->h_mod - map->size.z) * WIDTH, point->loc.vec[3]});
	trans = mat4_mat4(mat4_scales((float[4]){map->zoom * 2, map->zoom * 2, map->zoom * 2, 1}), rot);
	trans = mat4_mat4(trans, mat4_perps2(map->cam.plan, map->pos.vec[0] / map->pos.vec[1]));
	vec = mat4_vec4(trans, vec);
	vec.vec[0] += map->cam.loc.vec[0];
	vec.vec[1] += map->cam.loc.vec[1];
	return (map_point(vec, point->color));
}

t_loca	point_loca_pin(t_point *point, t_map *map, t_mat4 rot)
{
	t_vec4	vec;
	t_mat4	trans;

	point->color = point->color == -1 ? DEF_COLOR : point->color;
	vec = vec4_ini((float[4]){(point->loc.vec[0] - map->size.x) * WIDTH,
		(point->loc.vec[1] - map->size.y) * WIDTH, (point->loc.vec[2] * map->h_mod - map->size.z) * WIDTH, point->loc.vec[3]});
	vec = mat4_vec4(rot, vec);
	vec.vec[0] -= map->cam.loc.vec[0] - map->pos.vec[0] / 2;
	vec.vec[1] -= map->cam.loc.vec[1] - map->pos.vec[1] / 2;
	trans = mat4_pinhole(vec4_ini((float[4]){map->cam.plan.vec[2], map->cam.loc.vec[2], vec.vec[0], vec.vec[1]}), map->pos.vec[0] / map->pos.vec[1]);
	trans = mat4_mat4(trans, mat4_scales((float[4]){map->zoom / 10, map->zoom / 10, map->zoom / 10, 1}));
	vec = mat4_vec4(trans, vec);
	vec.vec[0] += map->cam.loc.vec[0];
	vec.vec[1] += map->cam.loc.vec[1];
	return (map_point(vec, point->color));
}

t_loca	point_loca(t_point *point, t_map *map, t_mat4 trans)
{
	t_vec4	vec;
	t_mat4	zoom;

	point->color = point->color == -1 ? DEF_COLOR : point->color;
	vec = vec4_ini((float[4]){(point->loc.vec[0] - map->size.x) * WIDTH,
		(point->loc.vec[1] - map->size.y) * WIDTH, point->loc.vec[2] * WIDTH * map->h_mod, point->loc.vec[3]});
	//vec4_put(vec);
	zoom = mat4_scales((float[4]){map->zoom, map->zoom, map->zoom, 1});
	//mat4_put(zoom);
	//printf("\n");
	//mat4_put(trans);
	vec = mat4_vec4(trans, vec); // map rotation matrix
	vec = mat4_vec4(zoom, vec); // zoom
	vec.vec[0] += map->origin.mat[0][3]; // translate
	vec.vec[1] += map->origin.mat[1][3];
	//vec4_put(vec);

	return (map_point(vec, point->color));
	/*
	t_vec4	vec;
	t_mat4	zoom;

	point->color = point->color == -1 ? DEF_COLOR : point->color;
	vec = vec4_ini((float[4]){(point->loc.vec[0] - map->size.x) * WIDTH,
		(point->loc.vec[1] - map->size.y) * WIDTH, point->loc.vec[2] * WIDTH * map->h_mod, point->loc.vec[3]});
	zoom = mat4_scales((float[4]){map->zoom, map->zoom, map->zoom, 1});
	mat4_put(zoom);
	
	vec = mat4_vec4(trans, vec); // map rotation matrix
	vec = mat4_vec4(zoom, vec); // zoom
	//vec = mat4_vec4(trans, vec);
	vec.vec[0] += map->origin.mat[0][3]; // translate
	vec.vec[1] += map->origin.mat[1][3];
	//vec = mat4_vec4(mat4_scales((float[4]){map->zoom, map->zoom, map->zoom, 1}), vec); // zoom
	//vec = mat4_vec4(map->origin, vec);
	//vec = mat4_vec4(mat4_pro(), vec);
	vec4_put(vec);
	return (map_point(vec, point->color));
	*/
}

int	input(int key, void *param)
{
	static int	contra;
	t_mlx		*mlx;

	mlx = param;
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
		printf("SECRET FOUND! %p\n", mlx->smap->start);
		contra = 0;
		rota_cube(mlx->smap);
		draw_map(mlx);
	}
	else
		contra = 0;
	if (key == PG_UP)
	{
		zoom(mlx->smap, -1);
		draw_map(mlx);
	}
	else if (key == PG_DW)
	{
		zoom(mlx->smap, 1);
		draw_map(mlx);
	}
	else if (key == AR_UP)
	{
		move(mlx->smap, 1, -1);
		draw_map(mlx);
	}
	else if (key == AR_DW)
	{
		move(mlx->smap, 1, 1);
		draw_map(mlx);
	}
	else if (key == AR_LF)
	{
		move(mlx->smap, 0, -1);
		draw_map(mlx);
	}
	else if (key == AR_RG)
	{
		move(mlx->smap, 0, 1);
		draw_map(mlx);
	}
	else if (key == K_W)
	{
		move(mlx->smap, 2, 1);
		draw_map(mlx);
	}
	else if (key == K_S)
	{
		move(mlx->smap, 2, -1);
		draw_map(mlx);
	}
	else if (key == K_A)
	{
		draw_map(mlx);
	}
	else if (key == K_D)
	{
		draw_map(mlx);
	}
	else if (key == 35) // projection change
	{
		mode(mlx->smap);
		draw_map(mlx);
	}
	else if (key == 88) // left
	{
		rota(mlx->smap, 1, 1);
		draw_map(mlx);
	}
	else if (key == 86) // right
	{
		rota(mlx->smap, 1, -1);
		draw_map(mlx);
	}
	else if (key == 91) // top
	{
		rota(mlx->smap, 0, -1);
		draw_map(mlx);
	}
	else if (key == 84) // bottom
	{
		rota(mlx->smap, 0, 1);
		draw_map(mlx);
	}
	else if (key == 92) // c-clockwise
	{
		rota(mlx->smap, 2, 1);
		draw_map(mlx);
	}
	else if (key == 83) // clockwise
	{
		rota(mlx->smap, 2, -1);
		draw_map(mlx);
	}
	else if (key == 69) // height +
	{
		mlx->smap->h_mod *= 1.1;
		draw_map(mlx);
	}
	else if (key == 67) // height flip
	{
		mlx->smap->h_mod *= -1;
		draw_map(mlx);
	}
	else if (key == 78) // height --
	{
		mlx->smap->h_mod /= 1.1;
		draw_map(mlx);
	}
	else if (key == 43) // fov ++
	{
		fov(mlx->smap, -1);
		draw_map(mlx);
	}
	else if (key == 47) // fov --
	{
		fov(mlx->smap, 1);
		draw_map(mlx);
	}
	else if (key == 41) // nearP --
	{
		cam_plain(mlx->smap, 0, -1);
		draw_map(mlx);
	}
	else if (key == 39) // nearP ++
	{
		cam_plain(mlx->smap, 0, 1);
		draw_map(mlx);
	}
	else if (key == 33) // farP --
	{
		cam_plain(mlx->smap, 1, -1);
		draw_map(mlx);
	}
	else if (key == 30) // farP ++
	{
		cam_plain(mlx->smap, 1, 1);
		draw_map(mlx);
	}
	else if (key == 75) // camera plain flip
	{
		plain_flip(mlx->smap);
		draw_map(mlx);
	}
	else if (key == 15) // reset map
	{
		settings_reset(mlx->smap, mlx);
		draw_map(mlx);
	}
	else if (key == 23) // view mode swap
	{
		view_mode(mlx);
		draw_map(mlx);
	}
	else if (key == 18) // map 1
	{
		map_select(mlx, 1);
		draw_map(mlx);
	}
	else if (key == 19) // map 2
	{
		map_select(mlx, 2);
		draw_map(mlx);
	}
	else if (key == 20) // map 3
	{
		map_select(mlx, 3);
		draw_map(mlx);
	}
	else if (key == 21) // map 4
	{
		map_select(mlx, 4);
		draw_map(mlx);
	}
	else if (key == 256) // map (fov) limitor
	{
		limitor(mlx->smap);
		draw_map(mlx);
	}
	else if (key == 27) // vanishing point --
	{
		vanishing_point(mlx->smap, -1);
		draw_map(mlx);
	}
	else if (key == 24) // vanishing point ++;
	{
		vanishing_point(mlx->smap, 1);
		draw_map(mlx);
	}
	else if (key == 2 && mlx->smap->mode != 0)
		mlx->smap->mode = 0;
	else if (key == 2 && mlx->smap->mode == 0)
		mlx->smap->mode = 1;

	ft_putnbr(key);
	ft_putstr("\n");
	if (mlx->smap->mode > 1)
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
		printf("stuff %f %f %f %f\n",mlx->smap->pos.vec[2] + mlx->smap->pos.vec[0], (mlx->smap->pos.vec[2] + mlx->smap->pos.vec[0]) / 4, mlx->smap->pos.vec[3] + mlx->smap->pos.vec[1], mlx->smap->pos.vec[3] + mlx->smap->pos.vec[1] / 4);
	}
	printf("view mode %d vanishing point %f\n", mlx->mode, mlx->smap->cam.plan.vec[3]);
	if (mlx->mode == 2)
	{
		printf("map 1 %p map 2 %p map 3 %p map 4 %p\n", mlx->map[1], mlx->map[2], mlx->map[3], mlx->map[4]);
		printf("smap %p\n", mlx->smap);
	}
	return (0);
}

int	mouse(int button, int x, int y, void *param)
{
	t_mlx		*mlx;

	mlx = param;
	if (button == 1) // map select
	{
		map_mouse(mlx, x, y);
		draw_map(mlx);
	}
	else if (button == 2) // map origin move
	{
		mouse_move(mlx->smap, x, y);
		draw_map(mlx);
	}
	else if (button == 5) //  scroll up
	{
		mouse_zoom(mlx->smap, 1);
		draw_map(mlx);
	}
	else if (button == 4) //  scroll down
	{
		mouse_zoom(mlx->smap, -1);
		draw_map(mlx);
	}

	if (mlx->smap->mode > 1)
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
		printf("stuff %f %f %f %f\n",mlx->smap->pos.vec[2] + mlx->smap->pos.vec[0], (mlx->smap->pos.vec[2] + mlx->smap->pos.vec[0]) / 4, mlx->smap->pos.vec[3] + mlx->smap->pos.vec[1], mlx->smap->pos.vec[3] + mlx->smap->pos.vec[1] / 4);
	}
	printf("view mode %d vanishing point %f\n", mlx->mode, mlx->smap->cam.plan.vec[3]);
	if (mlx->mode == 2)
	{
		printf("map 1 %p map 2 %p map 3 %p map 4 %p\n", mlx->map[1], mlx->map[2], mlx->map[3], mlx->map[4]);
		printf("smap %p\n", mlx->smap);
	}


	printf("\npressed %d at x %d y %d\n", button, x, y);
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
	t_map	*map;

	mlx = NULL;
	if (argc == 4)
		mlx = cont_init(ft_atoi(argv[2]), ft_atoi(argv[3]), "Hello World");
	else
		mlx = cont_init(800, 600, "Hello World");
	mlx_key_hook(mlx->mlx_win, input, mlx); // LOOK INTO HOLD DOWN SUPPORT
	mlx_mouse_hook(mlx->mlx_win, mouse, mlx); // ADD MOUSE SUPPORT // MOUSE ROTATING?
	if (argc > 1)
	{
		if (!map_reader(mlx, argv[1], &mlx->map[0]))
			exit(0);
		settings_reset(mlx->map[0], mlx);
		map_reset(mlx);
		draw_map(mlx);
	}
	mlx_loop(mlx->mlx_ptr);
	return (0);
}
