/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 13:28:31 by phakakos          #+#    #+#             */
/*   Updated: 2020/09/15 13:28:32 by phakakos         ###   ########.fr       */
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
# include <pthread.h>

	# include <stdio.h>

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
# define K_C 8
# define K_ENT 36
# define K_COM 43
# define K_DOT 47
# define K_COL 41
# define K_QUO 39
# define K_SBS 33
# define K_SBC 30
# define K_TAB 48
# define K_SPB 49

# define MOU_L 1
# define MOU_R 2
# define MOU_S_U 5
# define MOU_S_D 4

# define ROT_X -90//-180//-90
# define ROT_Y 270//180//-90
# define ROT_Z -180//-180
# define ROTA_STEP 5

# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define MIN_WIDTH 200
# define MIN_HEIGHT 100
# define MAX_WIDTH 2560
# define MAX_HEIGHT 1440

# define THREADS 16
# define ITER 100
# define MIN_ITER 10
# define MAX_ITER 20000
# define WINDOWS 10
# define DEF_BG 0xffffff

# define NAME_MAN "mandelbrot"
# define NAME_JULIA "julia"
# define NAME_BARN "barnsley"
# define NAME_MULT "multibrot"

# define MAN_MINX -2.5	// x 0
# define MAN_MAXX 1 	// x = width
# define MAN_MINY 1		// y = 0
# define MAN_MAXY -1	// y = height
# define MAN_HEIGHT 400 // width = (int)(height * 1.75)

# define JULIA_MAX_R 4
# define JULIA_STEP 2
# define JULIA_HEIGHT 400 // width = height

# define BARN_X_MIN -2.1820
# define BARN_X_MAX 2.6558
# define BARN_Y_MIN 9.9983
# define BARN_Y_MAX 0
# define BARN_COLOR 0x00ff00
# define BARN_HEIGHT 400 // width = height

# define MULT_HEIGHT 400
# define MULT_STEP 0.1
# define MULT_MIN -4//0.5
# define MULT_MAX 20

# define ANIM_IT_START 0
# define ANIM_IT_END 250

# define COLOR_BG 0xffffff
# define COLOR_OUTL 5
# define COLOR_WID 20
# define COLOR_START 0x000000
# define COLOR_END 0xff0000

# define ERR_MEMORY 4
# define ERR_PARA 5
# define ERR_MLX 3
# define USAGE 1
# define ERR_THREAD_VAL 2
# define ESC_EXIT 0

typedef struct		s_mlx
{
	void		*mlx_ptr;
	void		*mlx_win;
	void		*mlx_img;
	int			*img_dat;
	int			bpp;
	int			size_line;
	int			endian;
	long double *height_map;
	int			width;
	int			height;
	int			mode;
	int			verbose;
	int			iter;
	int			anim_iter;
	long double	zoom;
	int			cmin;
	int			cmax;
	long double	offx;
	long double	offy;
	long double	rot[3];
	char		jupt;
	char		jur;
	int			mouse_pos[2];
	double		jul[4]; // cx, cy, r, n
	void		(*func)(void*);
	int			*windows;
	int			color[2];
	char		colort; // 0 off, 1 start, 2 end
	void		*clr_swat;
	int			clr_line;
	int			*clr_dat;
	long double	(*clr_func)(long double, long double[4]);
}					t_mlx;

typedef struct		s_frac
{
	long double	zoom;
	int			iter;
	int			width;
	int			height;
	int			thread;
	int			y;
	int			lines;
	int			size;
	long double	off[2];
	t_mlx	*mlx;
}					t_frac;

typedef struct		s_params
{
	int		argc;
	char	**argv;
	int		i;
	int		*windows;
}					t_params;

typedef struct		s_dot
{
	int	x;
	int	y;
}					t_dot;


void				run_exit(int code, char *spot);
void				draw(t_mlx *mlx);
void				fractal_cpy(t_mlx *mlx, int *img_dat, int *arr, size_t n);
///void				fractal_norm(void *param);
void				mlx_image_create(t_mlx *mlx, int width, int height);
void				mlx_image_wipe(t_mlx *mlx, int width, int height);
void				three_d(t_mlx *mlx, t_vec4 spot);
void				three_d_two(t_mlx *mlx, t_frac *frac);
void				draw_line(t_mlx *mlx, t_vec4 start, t_vec4 end);
void				height_reset(long double *arr, long double val, int width,
						int height);
void				to_image(t_mlx *mlx, t_vec4 spot);
void				aim_rec(t_mlx *mlx);
void				to_color(t_mlx *mlx, t_vec4 spot);
void				mlx_image_set(int *img_dat, int width, int height, int color);

void				fractal_man(void *para);
void				fractal_jul(void *para);
void				fractal_barn(void *para);
void				fractal_mult(void *para);


t_mlx				*mlx_start(int arr[2], char **argv, void *mlx_ptr, int *windows);

t_mat4				rot_matrix(long double rot[3]);

long double			normalize(long double p, long double arr[4]);
long double			map_color(long double p, long double arr[4]);

void	mlx_print(t_mlx *mlx);//
void	mat4_put(t_mat4 mat4);//

#endif