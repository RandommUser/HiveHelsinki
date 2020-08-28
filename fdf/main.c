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
// map_anim helper
t_vec4	anim_step(float start[4], float diff[4], float i)
{
	t_vec4	end;

	end.vec[0] = start[0] + diff[0] * (i / ANIM_STEP);
	end.vec[1] = start[1] + diff[1] * (i / ANIM_STEP);
	end.vec[2] = start[2] + diff[2] * (i / ANIM_STEP);
	end.vec[3] = start[3] + diff[3] * (i / ANIM_STEP);
	return (end);
}
// map_anim helper
t_mat4	anim_step2(t_mat4 end, t_mat4 start, float diff[4], float i)
{
	end.mat[0][3] = start.mat[0][3] + diff[0] * (i / ANIM_STEP);
	end.mat[1][3] = start.mat[1][3] + diff[1] * (i / ANIM_STEP);
	end.mat[2][3] = start.mat[2][3] + diff[2] * (i / ANIM_STEP);
	end.mat[3][3] = start.mat[3][3] + diff[3] * (i / ANIM_STEP);
	return (end);
}
// map_anim helper
t_vec4	diff_ini(float start[4], float end[4])
{
	t_vec4	diff;

	diff = vec4_ini((float[4]){end[0] - start[0], end[1] - start[1], 
		end[2] - start[2], end[3] - start[3]});
	return (diff);
}
// map_anim helper
t_vec4	diff_ini2(t_mat4 start, t_mat4 end)
{
	t_vec4	diff;

	diff = vec4_ini((float[4]){end.mat[0][3] - start.mat[0][3], 
		end.mat[1][3] - start.mat[1][3], end.mat[2][3] - start.mat[2][3], 
		end.mat[3][3] - start.mat[3][3]});
	return (diff);
}
// map_anim helper
void	play_anim(t_mlx *mlx, t_map *start, t_map *end, t_vec4 diff[4])
{
	float	i;

	i = -1;
	while (++i <= ANIM_STEP)
	{
		if (start->mode == 1)
		{
			end->origin = anim_step2(end->origin, start->origin, diff[0].vec, i);
			end->rot = anim_step(start->rot.vec, diff[1].vec, i);
		}
		else
		{
			end->cam.loc = anim_step(start->cam.loc.vec, diff[0].vec, i);
			end->cam.rot = anim_step(start->cam.rot.vec, diff[1].vec, i);
			end->cam.plan = anim_step(start->cam.plan.vec, diff[2].vec, i);
		}
		end->h_mod = start->h_mod + diff[3].vec[0] * (i / ANIM_STEP);
		end->zoom = start->zoom + diff[3].vec[1] * (i / ANIM_STEP); 
		draw_map(mlx);
		mlx_do_sync(mlx->mlx_ptr);
		usleep(ANIM_TIME / ANIM_STEP);
	}
	end->thick = diff[3].vec[2];
	draw_map(mlx);
}
// map_anim helper
int		anim_diff_check(t_vec4 diff[4])
{
	if (!diff[0].vec[0] && !diff[0].vec[1] && 
		!diff[0].vec[2] && !diff[0].vec[3] &&
		!diff[1].vec[0] && !diff[1].vec[1] && 
		!diff[1].vec[2] && !diff[1].vec[3] &&
		!diff[2].vec[0] && !diff[2].vec[1] && 
		!diff[2].vec[2] && !diff[2].vec[3] &&
		!diff[3].vec[0] && !diff[3].vec[1])
		return (0);
	return (1);
}

/*
** diff = 1) location 2) rotation 3) view plain 4) misc 
*/
void	map_anim(t_mlx *mlx, t_map *start, t_map *end)
{
	t_vec4	diff[4];

	mlx->smap = end;
	if (start->mode != end->mode)
		return ;
	if (!(end->thick = 0))
		diff[3] = vec4_ini((float[4]){end->h_mod - start->h_mod, 
			end->zoom - start->zoom, end->thick, 0});
	if (start->mode == 1)
	{
		diff[0] = diff_ini2(start->origin, end->origin);
		diff[1] = diff_ini(start->rot.vec, end->rot.vec);
		diff[2] = vec4_ini((float[4]){0, 0, 0, 0});
		if (!anim_diff_check(diff))
			return ;
	}
	else
	{
		diff[0] = diff_ini(start->cam.loc.vec, end->cam.loc.vec);
		diff[1] = diff_ini(start->cam.rot.vec, end->cam.rot.vec);
		diff[2] = diff_ini(start->cam.plan.vec, end->cam.plan.vec);
		if (!anim_diff_check(diff))
			return ;
	}
	play_anim(mlx, start, end, diff);
}

void	view_mode(t_mlx *mlx)
{
	if (mlx->mode == 2)
	{
		map_reset(mlx, mlx->smap);
		map0_reset(mlx, mlx->map[1]);
		map0_reset(mlx, mlx->map[2]);
		map0_reset(mlx, mlx->map[3]);
	}
	else
	{
		map_reset(mlx, mlx->map[1]);
		map_reset(mlx, mlx->map[2]);
		map_reset(mlx, mlx->map[3]);
		map_reset(mlx, mlx->map[4]);
		mlx->map[1]->mode = 2;
		mlx->map[2]->mode = 1;
		mlx->map[3]->mode = 1;
		mlx->map[4]->mode = 1;
	}
	mlx->mode = mlx->mode == 1 ? 2 : 1;
	mlx->smap = mlx->mode == 1 ? mlx->map[0] : mlx->map[1];
}
/*
** 0) thick lines 1) rotation cube toggle 2) fov limitor 3) map mode toggle
** 4) plain_flip
*/
void	actions1(int func, t_map *map)
{
	if (func == 0)
		map->thick = map->thick ? 0 : 1;
	else if (func == 1)
		map->rot.vec[3] = map->rot.vec[3] == 1 ? 2 : 1;
	else if (func == 2)
		map->limit = map->limit == 1 ? 0 : 1;
	else if (func == 3)
	{
		map->mode++;
		map->mode = map->mode > 3 ? 1 : map->mode;
	}
	else if (func == 4 && map->mode > 1) // does nothing??
	{
		map->cam.plan.vec[0] *= -1;
		map->cam.plan.vec[1] *= -1;
	}
}
/*
** 0) moving vanishing point 1) map zoom 2) FOV change 3) height modifier
*/
void	actions2(int func, t_map *map, float dir)
{
	if (func == 0)
		map->cam.plan.vec[3] += dir > 0 ? 0.1 : -0.1;
	else if (func == 1)
		map->zoom = dir > 0 ? map->zoom * 1.2 : map->zoom / 1.2;
	else if (func == 2 && map->mode > 1)
	{
		map->cam.plan.vec[2] += FOV_STEP * dir;
		if ((map->limit  && map->cam.plan.vec[2] >= 180) || 
			(map->limit && map->cam.plan.vec[2] <= 0))
			map->cam.plan.vec[2] -= FOV_STEP * dir;
	}
	else if (func == 3)
	{
		map->h_mod *= dir;
	}
}
/*
** 0) map rotating 1) map move
*/
void	actions3(int func, t_map *map, int ang, int dir)
{
	if (func == 0)
	{
		if (map->mode > 1)
		{
			map->cam.rot.vec[ang] += ROTA_STEP / 2 * dir;
			if (map->cam.rot.vec[ang] <= -360 || map->cam.rot.vec[ang] 
				>= 360)
				map->cam.rot.vec[ang] = (ft_abs(map->cam.rot.vec[ang]) 
					- 360) * dir;
		}
		else
		{
			map->rot.vec[ang] += (ROTA_STEP * dir);
			if (map->rot.vec[ang] <= -360 || map->rot.vec[ang] >= 360)
				map->rot.vec[ang] = (ft_abs(map->rot.vec[ang]) - 360) * dir;
		}
	}
	else if (func == 1)
	{
		if (map->mode > 1)
			map->cam.loc.vec[ang] += WIDTH * dir;
		else
			map->origin.mat[ang][3] += WIDTH * dir;
	}
}
/*
** 0) map mouse select 1) key map select
*/
void	actions4(int func, t_mlx *mlx, int x, int y)
{
	size_t	i;

	if (func == 0 && mlx->mode == 2)
	{
		i = 0;
		while (++i < 5)
		{
			if (x >= mlx->map[i]->pos.vec[2] && x <= (mlx->map[i]->pos.vec[2] 
				+ mlx->map[i]->pos.vec[0]))
				if (y >= mlx->map[i]->pos.vec[3] && y <= 
					(mlx->map[i]->pos.vec[3] + mlx->map[i]->pos.vec[1]))
				{
					mlx->smap = mlx->map[i];
					return ;
				}
		}
	}
	else if (func == 1)
	{
		if (mlx->mode == 2 && x > 0 && x < 5)
			mlx->smap = mlx->map[x];
		else if (mlx->mode == 1 && mlx->smap != mlx->map[--x])
			map_anim(mlx, mlx->smap, mlx->map[x]);
	}
}
/*
** 0) mouse move 1) camera plain changes
*/
void	actions5(int func, t_map *map, int x, int y)
{
	if (func == 0)
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
	else if (func == 1 && map->mode > 1)
	{
		map->cam.plan.vec[x] += WIDTH / 2 * y;
		if (map->cam.plan.vec[0] == map->cam.plan.vec[1])
			map->cam.plan.vec[x] -= WIDTH / 2 * y;
	}
}


/*
void	cam_plain(t_map *map, int coord, int dir) //action5-1
{
	if (map->mode > 1)
	{
		map->cam.plan.vec[coord] += WIDTH / 2 * dir;
		if (map->cam.plan.vec[0] == map->cam.plan.vec[1])
			map->cam.plan.vec[coord] -= WIDTH / 2 * dir;
	}
}

void	mouse_move(t_map *map, int x, int y) //action5-0
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

void	move(t_map *map, int angle, int dir) //action3-1
{
	if (map->mode > 1)
		map->cam.loc.vec[angle] += WIDTH * dir;
	else
		map->origin.mat[angle][3] += WIDTH * dir;
}

void	rota(t_map *map, int angle, int dir) //action3-0
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

void	fov(t_map *map, int dir) //actions2-2 
{
	if (map->mode > 1)
	{
		map->cam.plan.vec[2] += FOV_STEP * dir;
		if ((map->limit  && map->cam.plan.vec[2] >= 180) || (map->limit && map->cam.plan.vec[2] <= 0))
			map->cam.plan.vec[2] -= FOV_STEP * dir;
	}
}

void	zoom(t_map *map, int dir) //actions2-1 COMBINE
{
	map->zoom = dir > 0 ? map->zoom * 1.2 : map->zoom / 1.2;
}

void	mouse_zoom(t_map *map, int dir) //
{
	map->zoom = dir > 0 ? map->zoom * 1.2 : map->zoom / 1.2;
}

void	plain_flip(t_map *map) // does nothing//
{
	if (map->mode > 1)
	{
		map->cam.plan.vec[0] *= -1;
		map->cam.plan.vec[1] *= -1;
	}
}

void	mode(t_map *map) //actions1-3
{
	map->mode++;
	map->mode = map->mode > 3 ? 1 : map->mode;
}

void	thicc(t_map *map) //actions1-0
{
	map->thick = map->thick ? 0 : 1;
}

void	rota_cube(t_map *map) //actions1-1
{
	map->rot.vec[3] = map->rot.vec[3] == 1 ? 2 : 1;
}

void	vanishing_point(t_map *map, int dir) //actions2-0
{
	map->cam.plan.vec[3] += dir > 0 ? 0.1 : -0.1;
}

void	limitor(t_map *map) //actions1-2
{
	map->limit = map->limit == 1 ? 0 : 1;
}

void	map_select(t_mlx *mlx, int n) //action4-1
{
	if (mlx->mode == 2 && n > 0 && n < 5)//
		mlx->smap = mlx->map[n];
	else if (mlx->mode == 1 && mlx->smap != mlx->map[--n])
		map_anim(mlx, mlx->smap, mlx->map[n]);
}

void	map_mouse(t_mlx *mlx, int x, int y)//action4-0
{
}
*/
// END OF CONTROL FUNCTIONS

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
		loc.vec[0] += map->cam.loc.vec[0];
		loc.vec[1] += map->cam.loc.vec[1];
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
		(point->loc.vec[1] - map->size.y) * WIDTH , (point->loc.vec[2] * 
		map->h_mod - map->size.z) * WIDTH, point->loc.vec[3]});
	trans = mat4_mat4(mat4_scales((float[4]){map->zoom, map->zoom, map->zoom,
		 1}), rot);
	trans = mat4_mat4(trans, mat4_perps2(map->cam.plan, 
		map->pos.vec[0] / map->pos.vec[1]));
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
	return (map_point(vec, point->color));
}

t_loca	point_loca(t_point *point, t_map *map, t_mat4 trans)
{
	t_vec4	vec;
	t_mat4	zoom;

	point->color = point->color == -1 ? DEF_COLOR : point->color;
	vec = vec4_ini((float[4]){(point->loc.vec[0] - map->size.x) * WIDTH,
		(point->loc.vec[1] - map->size.y) * WIDTH, 
		point->loc.vec[2] * WIDTH * map->h_mod, point->loc.vec[3]});
	zoom = mat4_scales((float[4]){map->zoom, map->zoom, map->zoom, 1});
	vec = mat4_vec4(trans, vec);
	vec = mat4_vec4(zoom, vec);
	vec.vec[0] += map->origin.mat[0][3];
	vec.vec[1] += map->origin.mat[1][3];
	return (map_point(vec, point->color));
}

int	input(int key, void *param)
{
	t_mlx		*mlx;

	mlx = param;
	if (key == ESC_KEY)
		exit(0);
	contra(mlx, key);
	keys(mlx, key);
	/*else if (key == 117) // del
	{
		draw_map(mlx);
	}
	if (key == 126 && (contra == 0 || contra == 1))
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
printf("SECRET FOUND!\n");
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
		mlx->mode == 1 ? map0_reset(mlx, mlx->smap) : map_reset(mlx, mlx->smap);
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
	else if (key == 17) // thicc
	{
		thicc(mlx->smap);
		draw_map(mlx);
	}
	else if (key == 2 && mlx->smap->mode != 0)
		mlx->smap->mode = 0;
	else if (key == 2 && mlx->smap->mode == 0)
		mlx->smap->mode = 1;
*/
	// TO REMOVE
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
	printf("\npressed %d at x %d y %d\n", button, x, y);
	if (button == 1) // map select
		actions4(0, mlx, x, y);
	else if (button == 2) // map origin move
		actions5(0, mlx->smap, x, y);
	else if (button == 5) //  scroll up
		actions2(1, mlx->smap, 1);
	else if (button == 4) //  scroll down
		actions2(1, mlx->smap, -1);
	else
		return (0);
	draw_map(mlx);
	// TO REMOVE
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
	rtn->mlx_img = NULL;
	rtn->img_dat = NULL;
	rtn->map[0] = NULL;
	rtn->smap = NULL;
	return (rtn);
}

int	main(int argc, char **argv)
{
	t_mlx	*mlx;
	t_map	*map;

	mlx = NULL;
	if (argc < 2)
		return (1);
	else if (argc == 4)
		mlx = cont_init(ft_atoi(argv[2]), ft_atoi(argv[3]), argv[1]);
	else
		mlx = cont_init(800, 600, argv[1]);
	mlx_key_hook(mlx->mlx_win, input, mlx);
	mlx_mouse_hook(mlx->mlx_win, mouse, mlx);
	mlx->mlx_img = mlx_new_image(mlx->mlx_ptr, mlx->width, mlx->width);
	mlx->img_dat = mlx_get_data_addr(mlx->mlx_img, &mlx->bpp, &mlx->size_line, &mlx->endian);
//	printf("img data %s\n", mlx->img_dat);
//	printf("bpp %d size line %d endian %d\n", mlx->bpp, mlx->size_line, mlx->endian);
	if (!map_reader(mlx, argv[1], &mlx->map[0]))
		exit(0);
	settings_reset(mlx->map[0], mlx);
	map_reset(mlx, mlx->map[0]);
	map0_reset(mlx, mlx->map[1]);
	map0_reset(mlx, mlx->map[2]);
	map0_reset(mlx, mlx->map[3]);
	map_reset(mlx, mlx->map[4]);
	draw_map(mlx);
	mlx_loop(mlx->mlx_ptr);
	return (0);
}
