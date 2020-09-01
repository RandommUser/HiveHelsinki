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

# define NUM_1 83
# define NUM_2 84
# define NUM_4 86
# define NUM_6 88
# define NUM_8 91
# define NUM_9 92
# define NUM_P 69
# define NUM_M 78
# define NUM_A 67

# define K_W 13
# define K_A 0
# define K_S 1
# define K_D 2
# define K_B 11
# define K_LCN 256
# define K_1 18
# define K_2 19
# define K_3 20
# define K_4 21
# define K_5 23
# define K_MI 27
# define K_PL 24
# define K_P 35
# define K_T 17
# define K_R 15
# define K_ENT 36
# define K_COM 43
# define K_DOT 47
# define K_COL 41
# define K_QUO 39
# define K_SBS 33
# define K_SBC 30
# define K_TAB 48

# define MOU_L 1
# define MOU_R 2
# define MOU_S_U 5
# define MOU_S_D 4

# define COLOR_SPLIT ','
# define WIDTH 10
# define START_X 150
# define START_Y 150
# define FOV_DEF 70
# define FOV_STEP 5
# define ZOOM_DEF 1
# define ZOOM_STEP 10
# define MODE_DEF 1
# define DEF_COLOR 0x888888
# define HEIGHT 20
# define MAX_COLOR 0xff0000
# define MIN_COLOR 0x0000ff
# define H_MOD 0.2
# define W_MOD 1
# define ROTA_X -100
# define ROTA_Y -90
# define ROTA_Z -170
# define ROTA_W 1
# define ROTA_STEP 10
# define ANIM_STEP 100
# define ANIM_TIME 500000
# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define MIN_WIDTH 200
# define MIN_HEIGHT 100
# define MAX_WIDTH 2560
# define MAX_HEIGHT 1440

# define ERR_MEMORY 4
# define ERR_MAP 5
# define ERR_MLX 2
# define ERR_READER 3
# define ESC_EXIT 0

/*
** point in map
** loc: x, y, z, w
*/

typedef struct		s_point
{
	t_vec4			loc;
	struct s_point	*top;
	struct s_point	*left;
	struct s_point	*right;
	struct s_point	*bottm;
	long			color;
}					t_point;

/*
** x,y coordinate position
*/

typedef struct		s_coord
{
	float	x;
	float	y;
	float	z;
}					t_coord;

/*
** pixel position
** color: r, g, b
** loc: x, y, z, w
*/

typedef struct		s_loca
{
	t_rgb	color;
	t_vec4	loc;
}					t_loca;

/*
** camera data
** loc: x, y, z, w
** rot: x, y, z, w;
** plan: near pain, far plain, Fov, vanishing point
*/

typedef struct		s_cam
{
	t_vec4	loc;
	t_vec4	rot;
	t_vec4	plan;
}					t_cam;

/*
** map data
** size: x / 2, z / 2 (points in input)
** start: top left corner of input map
** origin: x, y(, z, w) translation
** rot: x, y, z, w angles
** cam: camera struct
** pos: widht, height, x origin, y origin (map render area)
*/

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
	t_vec4	rot;
	t_cam	cam;
	t_vec4	pos;
	int		thick;
}					t_map;

/*
** mlx data
** map[5]: map copies for swapping
** smap: currently selected map
*/

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
	int		verbose;
}					t_mlx;

/*
** input reader
*/

int					map_reader(t_mlx *mlx, char *file, t_map **map);
t_point				*point_conv(t_point *start, char **str, int y);
t_point				*find_point(t_point *curr, int x, int y);

/*
** misc struct init
*/

t_coord				coords(int x, int y);
t_loca				map_point(t_vec4 vec, int color);

/*
** projection calculations
*/

t_loca				point_loca(t_point *point, t_map *map, t_mat4 trans);
t_loca				point_loca_orth(t_point *point, t_map *map, t_mat4 trans);
t_loca				point_loca_pin(t_point *point, t_map *map, t_mat4 rot);
t_loca				rotation_cube(t_vec4 loc, t_map *map, int color);
t_mat4				rot_matrix(float rot[4]);

/*
** drawing functions
*/

void				draw_map(t_mlx *window);
void				draw_line(t_mlx *mlx, t_map *map, t_loca start, t_loca end);
void				draw_linet(t_mlx *mlx, t_map *map, t_loca start,
						t_loca end);
void				draw_rota(t_mlx *mlx, t_map *map);
void				draw_to_image(t_mlx *mlx, t_map *map, t_loca spot);
int					pos_test(float map[4], float start[4], float end[4]);
int					height_color(float z, int min, int max, float depth);

/*
** mlx/map resetting stuff
*/

void				settings_reset(t_map *map, t_mlx *mlx);
void				map_reset(t_mlx *mlx, t_map *map);
void				map0_reset(t_mlx *mlx, t_map *map);
void				map1_reset(t_mlx *mlx, t_map *map);
void				map2_reset(t_mlx *mlx, t_map *map);
void				map3_reset(t_mlx *mlx, t_map *map);
void				map4_reset(t_mlx *mlx, t_map *map);
void				map_gen_reset(t_mlx *mlx, t_map *map);
t_map				*map_copy(t_mlx *mlx);
void				map_size(t_map **map);
void				zoom_check(t_map *map);

/*
** control actions
*/

void				actions1(int func, t_map *map);
void				actions2(int func, t_map *map, float dir);
void				actions3(int func, t_map *map, int dir, int ang);
void				actions4(int func, t_mlx *mlx, int x, int y);
void				actions5(int func, t_map *map, int x, int y);
void				view_mode(t_mlx *mlx);
void				mexit(int num);

/*
** control handling
*/

void				contra(t_mlx *mlx, int key);
void				keys(t_mlx *mlx, int key);

/*
** map transitions
*/

void				map_anim(t_mlx *mlx, t_map *start, t_map *end);
t_vec4				anim_step(float start[4], float diff[4], float i);
t_mat4				anim_step2(t_mat4 end, t_mat4 start, t_vec4 diff, float i);

#endif
