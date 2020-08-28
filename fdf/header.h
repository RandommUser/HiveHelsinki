/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:18:35 by phakakos          #+#    #+#             */
/*   Updated: 2020/06/02 15:02:38 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "mlx.h"
# include "libft.h"

# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>

# define ESC_KEY 53
# define PG_UP 116
# define PG_DW 121
# define AR_UP 126
# define AR_DW 125
# define AR_LF 123
# define AR_RG 124
# define K_W 13
# define K_A 0
# define K_S 1
# define K_D 2

# define COLOR_SPLIT ','
# define WIDTH 10
# define START_X 150
# define START_Y 150
# define FOV_DEF 70
# define FOV_STEP 5
# define ZOOM_DEF 1
# define ZOOM_STEP 10
# define MODE_DEF 1
# define MODE_COLOR 1
# define DEF_COLOR 0x888888
# define H_MOD 0.2
# define W_MOD 1
# define ROTA_X -100
# define ROTA_Y -90
# define ROTA_Z -170
# define ROTA_W 1
# define ROTA_STEP 10
# define ANIM_STEP 100
# define ANIM_TIME 500000

# define ERR_MEMORY 4

typedef struct		s_point
{
	// x, y, z, w
	t_vec4			loc;
	struct s_point	*top;
	struct s_point	*left;
	struct s_point	*right;
	struct s_point	*bottm;
	int				color;
}					t_point;

 typedef struct		s_coord
{
	float	x;
	float	y;
	float	z;
}					t_coord;

typedef struct		s_loca
{
	t_rgb	color;
	// x, y, z, w
	t_vec4	loc;
}					t_loca;

typedef struct		s_cam
{
	// x, y, z, w
	t_vec4	loc;
	// x, y, z, w
	t_vec4	rot;
	// nearZ, farZ, fov, vanishing point
	t_vec4	plan;
}					t_cam;

typedef	struct		s_map
{
	t_coord	size;
	t_point	*start;
	float	h_mod;
	t_mat4	origin;
	float	zoom;
	int		mode;
	int		limit;
	int		color;
	// x, y, z, w angles
	t_vec4	rot;
	t_cam	cam;
	//width, height, xpos, ypos
	t_vec4	pos;
	int		thick;
}					t_map;

typedef struct		s_mlx
{
	void	*mlx_ptr;
	void	*mlx_win;
	void	*mlx_img;
	char	*img_dat;
	char	*title;
	int		bpp;
	int		size_line;
	int		endian;
	int		height;
	int		width;
	t_map	*map[5];
	t_map	*smap;
	int		mode;
}					t_mlx;

int					map_reader(t_mlx *mlx, char *file, t_map **map);

t_coord				coords(int x, int y);

t_loca				map_point(t_vec4 vec, int color);
t_loca				point_loca(t_point *point, t_map *map, t_mat4 trans);
t_loca				point_loca_orth(t_point *point, t_map *map, t_mat4 trans);
t_loca				point_loca_pin(t_point *point, t_map *map, t_mat4 rot);
t_loca				rotation_cube(t_vec4 loc, t_map *map, int color);

t_point				*point_conv(t_point *start, char **str, int y);
t_point				*find_point(t_point *curr, int x, int y);

t_mat4				map_matrix(t_map *map);
t_mat4				camera_matrix(t_cam cam);

void				draw_map(t_mlx *window);
void				draw_line1(t_mlx *mlx, t_map *map, t_loca start, t_loca end);
void				settings_reset(t_map *map, t_mlx *mlx);
void				map_reset(t_mlx *mlx, t_map *map);
void				map_size(t_map **map);
void				map0_reset(t_mlx *mlx, t_map *map);

void				actions1(int func, t_map *map);
void				actions2(int func, t_map *map, float dir);
void				actions3(int func, t_map *map, int dir, int ang);
void				actions4(int func, t_mlx *mlx, int x, int y);
void				actions5(int func, t_map *map, int x, int y);
void				view_mode(t_mlx *mlx);

void				contra(t_mlx *mlx, int key);
void				keys(t_mlx *mlx, int key);

#endif
