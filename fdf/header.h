/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:18:35 by phakakos          #+#    #+#             */
/*   Updated: 2020/02/20 19:04:50 by phakakos         ###   ########.fr       */
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

# define COLOR_SPLIT ','
# define WIDTH 50
# define START_X 150
# define START_Y 150
# define FOV_DEF 100
# define ZOOM_DEF 50
# define MODE_DEF 1
# define MODE_COLOR 1
# define DEF_COLOR 0x888888
# define H_MOD 0.2
# define W_MOD 1
# define ROTA_X 0
# define ROTA_Y 0
# define ROTA_Z 0
# define ROTA_STEP 10

typedef struct		s_point
{
	int				x;
	int				y;
	int				z;
	struct s_point	*top;
	struct s_point	*left;
	struct s_point	*right;
	struct s_point	*bottm;
	int				color;
}					t_point;

 typedef struct		s_coord
{
	int	x;
	int y;
}					t_coord;

typedef struct		s_loca
{
	t_rgb	color;
	int		x;
	int		y;
	int		z;
}					t_loca;

typedef	struct		s_map
{
	t_point	*start;
	float	w_mod;
	float	h_mod;
	t_coord	pos;
}					t_map;

typedef struct		s_mlx
{
	void	*mlx_ptr;
	void	*mlx_win;
	char	*title;
	int		height;
	int		width;
	int		fov;
	float	zoom;
	int		mode;
	int		color;
	t_loca	rota;
	t_map	*map;
}					t_mlx;

int					map_reader(t_mlx *mlx, char *file, t_map **map);

t_coord				coords(int x, int y);

t_loca				map_point(int x, int y, int z, int color);
t_loca				point_loca(t_point *point, t_map *map);
t_loca				rota_x(t_loca point, t_mlx *mlx);

t_point				*point_conv(t_point *start, char **str, int y);
t_point				*find_point(t_point *curr, int x, int y);

void				print_point(t_point *start, int x, int y);
void				draw_map(t_map *map, t_mlx *window);
void				draw_line1(t_mlx *mlx, t_loca start, t_loca end);
void				settings_reset(t_map *map, t_mlx *mlx);

#endif
