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
** mode 1 map_matrix, mode 2/3 camera_matrix
** draw_selected helper -> draw_map helper
*/

static void	draw(t_map *map, t_mlx *mlx, t_mat4 matrix, void *fu_ptr)
{
	t_point	*row;
	t_point	*curr;
	t_loca	this;
	t_loca	(*loca)(t_point*, t_map*, t_mat4);

	row = map->start;
	loca = fu_ptr;
	while (row && (curr = row))
	{
		while (curr)
		{
			this = (*loca)(curr, map, matrix);
			draw_linet(mlx, map, this, this);
			if (curr->right)
				draw_linet(mlx, map, this, (*loca)(curr->right, map, matrix));
			if (curr->bottm)
				draw_linet(mlx, map, this, (*loca)(curr->bottm, map, matrix));
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

static void	draw_selected(t_mlx *mlx, t_map *map)
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

static void	fview_border(t_mlx *mlx, float map[4])
{
	draw_line(mlx, mlx->map[0], map_point(vec4_ini((float[4]){0, mlx->height
		/ 2, 0, 1}), 0xffffff), map_point(vec4_ini((float[4]){mlx->width,
		mlx->height / 2, 0, 1}), 0xffffff));
	draw_line(mlx, mlx->map[0], map_point(vec4_ini((float[4]){mlx->width / 2,
		0, 0, 1}), 0xffffff), map_point(vec4_ini((float[4]){mlx->width / 2,
		mlx->height, 0, 1}), 0xffffff));
	draw_line(mlx, mlx->map[0], map_point(vec4_ini((float[4]){map[2], map[3],
		0, 1}), 0xffffff), map_point(vec4_ini((float[4]){map[2] + map[0],
		map[3], 0, 1}), 0xffffff));
	draw_line(mlx, mlx->map[0], map_point(vec4_ini((float[4]){map[2], map[3],
		0, 1}), 0xffffff), map_point(vec4_ini((float[4]){map[2], map[3]
		+ map[1], 0, 1}), 0xffffff));
	draw_line(mlx, mlx->map[0], map_point(vec4_ini((float[4]){map[2], map[3]
		+ map[1], 0, 1}), 0xffffff), map_point(vec4_ini((float[4]){map[2] +
		map[0], map[3] + map[1], 0, 1}), 0xffffff));
	draw_line(mlx, mlx->map[0], map_point(vec4_ini((float[4]){map[2] + map[0]
		, map[3], 0, 1}), 0xffffff), map_point(vec4_ini((float[4]){map[2] +
		map[0], map[3] + map[1], 0, 1}), 0xffffff));
}

void		draw_map(t_mlx *mlx)
{
	mlx_clear_window(mlx->mlx_ptr, mlx->mlx_win);
	if (mlx->mlx_img)
		mlx_destroy_image(mlx->mlx_ptr, mlx->mlx_img);
	mlx->mlx_img = mlx_new_image(mlx->mlx_ptr, mlx->width, mlx->height);
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
	else
		draw_selected(mlx, mlx->smap);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->mlx_win, mlx->mlx_img, 0, 0);
}
