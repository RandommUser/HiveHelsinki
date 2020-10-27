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

# include <math.h>
# include <stdlib.h>
# include <pthread.h>

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
# define K_V 9
# define K_LCN 256
# define K_1 18
# define K_2 19
# define K_3 20
# define K_4 21
# define K_5 23
# define K_O 31
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

# define ROT_X -90
# define ROT_Y 270
# define ROT_Z -180
# define ROTA_STEP 5

# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define MIN_WIDTH 200
# define MIN_HEIGHT 100
# define MAX_WIDTH 2560
# define MAX_HEIGHT 1440

# define THREADS 8
# define ITER 50
# define ITER_STEP 50
# define MIN_ITER 10
# define MAX_ITER 20000
# define WINDOWS 10
# define DEF_BG 0xffffff
# define EXTRA 100
# define OFF_STEP 5
# define ZOOM_STEP 0.2

# define NAME_MAN "mandelbrot"
# define NAME_JULIA "julia"
# define NAME_BARN "barnsley"
# define NAME_MULT "multibrot"
# define NAMES NAME_MAN "|" NAME_JULIA "|" NAME_BARN "|" NAME_MULT

# define MAN_MINX -2.5
# define MAN_MAXX 1
# define MAN_MINY 1
# define MAN_MAXY -1
# define MAN_HEIGHT 400

# define JULIA_MAX_R 4
# define JULIA_STEP 2
# define JULIA_HEIGHT 400

# define BARN_X_MIN -2.1820
# define BARN_X_MAX 2.6558
# define BARN_Y_MIN 9.9983
# define BARN_Y_MAX 0
# define BARN_COLOR 0x00ff00
# define BARN_HEIGHT 400

# define MULT_HEIGHT 400
# define MULT_STEP 0.1
# define MULT_MIN -4
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
# define X_EXIT 6

typedef struct		s_julia
{
	double	cx;
	double	cy;
	double	r;
	double	n;
}					t_julia;

typedef struct		s_dot
{
	int	x;
	int	y;
}					t_dot;

typedef struct		s_ddot
{
	long double	x;
	long double	y;
}					t_ddot;

typedef struct		s_mlx t_mlx;

typedef struct		s_mlx
{
	t_mlx		**mlxs;
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
	int			extra;
	int			verbose;
	int			iter;
	int			anim_iter;
	long double	zoom;
	int			zo;
	t_ddot		off;
	long double	rot[3];
	char		jupt;
	char		jur;
	t_dot		mouse_pos;
	t_julia		jul;
	void		(*func)(void*);
	int			*windows;
	int			color[2];
	char		colort;
	void		*clr_swat;
	int			clr_line;
	int			*clr_dat;
	long double	(*clr_func)(long double, long double[4]);
}					t_mlx;

typedef struct		s_box
{
	long double	x;
	long double	y;
	long double xs;
	long double	ys;
	long double xte;
	long double r;
	long double d;
	long double pr;
	long double	w;
	long double	h;
	double		i;
	int			j;
	int			k;
	int			width;
	int			height;
	t_julia		jul;
	t_ddot		last;
}					t_box;

typedef struct		s_frac
{
	long double	zoom;
	int			iter;
	int			width;
	int			height;
	long double	w;
	long double	h;
	int			y;
	int			lines;
	t_ddot		off;
	t_mlx		*mlx;
}					t_frac;

void				run_exit(int code, char *spot);
int					draw(t_mlx *mlx);
void				draw_line(t_mlx *mlx, t_vec4 start, t_vec4 end);
void				height_reset(long double *arr, long double val, int w,
						int h);
void				to_image(t_mlx *mlx, t_vec4 spot);
void				mlx_image_set(int *img_dat, int width, int height,
						int color);
void				color_show(t_mlx *mlx);
void				color_pick(t_mlx *mlx, int x, int y);

void				fractal_man(void *para);
void				fractal_jul(void *para);
void				fractal_barn(void *para);
void				fractal_mult(void *para);

t_ddot				barnsley(t_ddot val);
double				multibrot(int iter, t_box box);
double				mandel(int iter, t_box box);
double				julia_flex(int iter, t_box box);

t_mlx				*mlx_start(int arr[2], char **argv, void *mlx_ptr,
						int *windows);
void				mlx_def_value(t_mlx *mlx);

t_mat4				rot_matrix(long double rot[3]);

long double			map(long double p, long double arr[4]);
long double			map_color(long double p, long double arr[4]);
int					iter_color(t_frac *frac, t_vec4 point);

int					iter_anim(void *param);
int					window_close(void *param);
int					input(int key, void *param);
int					mouse(int button, int x, int y, void *param);
int					mouse_live(int x, int y, void *param);

void				zoom(t_mlx *mlx, char c);
void				iter(t_mlx *mlx, char c);
t_mlx				*loop_start(void *param, int key, int x, int y);
void				julia_manual(t_mlx *mlx, char a, char c);

#endif
