/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 14:38:31 by phakakos          #+#    #+#             */
/*   Updated: 2020/09/15 14:38:33 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void		color_show(t_mlx *mlx)
{
	t_rgb	color;
	t_dot	coord;

	color = rgb_conv(mlx->color[mlx->colort - 1]);
	coord.x = COLOR_OUTL - 1;
	while (++coord.x < COLOR_OUTL * 1 + COLOR_WID * 1)
	{
		coord.y = COLOR_OUTL - 1;
		while (++coord.y <= 255 + COLOR_OUTL)
		{
			to_color(mlx, vec4_ini((float[4]){coord.x, coord.y, 0, rgb_color(255 - coord.y + COLOR_OUTL, 0, 0)}));
			if (255 - coord.y + COLOR_OUTL == color.red)
				to_color(mlx, vec4_ini((float[4]){coord.x, coord.y, 0, rgb_color(255 - color.red, 0, 0)}));
		}	
	}
	coord.x += COLOR_OUTL - 1;
	while (++coord.x < COLOR_OUTL * 2 + COLOR_WID * 2)
	{
		coord.y = COLOR_OUTL - 1;
		while (++coord.y <= 255 + COLOR_OUTL)
		{
			to_color(mlx, vec4_ini((float[4]){coord.x, coord.y, 0, rgb_color(0, 255 - coord.y + COLOR_OUTL, 0)}));
			if (255 - coord.y + COLOR_OUTL == color.green)
				to_color(mlx, vec4_ini((float[4]){coord.x, coord.y, 0, rgb_color(0, 255 - color.green, 0)}));
		}
	}
	coord.x += COLOR_OUTL - 1;
	while (++coord.x < COLOR_OUTL * 3 + COLOR_WID * 3)
	{
		coord.y = COLOR_OUTL - 1;
		while (++coord.y <= 255 + COLOR_OUTL)
		{
			to_color(mlx, vec4_ini((float[4]){coord.x, coord.y, 0, rgb_color(0, 0, 255 - coord.y + COLOR_OUTL)}));
			if (255 - coord.y + COLOR_OUTL == color.blue)
				to_color(mlx, vec4_ini((float[4]){coord.x, coord.y, 0, rgb_color(0, 0, 255 - color.blue)}));
		}
	}
}

// julia, base		x(s), y(s), r, cx, cy, (n)
static double	julia(int iter, double val[6], int width, int height) //double xs, double ys, double r)
{
	double	xte;
	int		i;
	double	last[2];

	i = -1;
	val[0] = normalize(val[0], (double[4]){0, width, -(val[2]), val[2]});
	val[1] = normalize(val[1], (double[4]){0, height, -(val[2]), val[2]});
	while (val[0] * val[0]  + val[1] * val[1] < val[2] * val[2] &&  ++i < iter)
	{
		last[0] = val[0];
		last[1] = val[1];
		xte = val[0]  * val[0]  - val[1] * val[1];
		val[1] = 2 * val[0] * val[1] + val[4];
		val[0]  = xte + val[3];
		if (last[0] == val[0] && last[1] == val[1]) // check for looping // add "too close to 0?"
			return (iter);
	}
	return (i == -1 ? 0 : i);
}


// julia flex		x(s), y(s), r, cx, cy, n
static double	julia_flex(int iter, double val[6], int width, int height) //double xs, double ys, double r)
{
	double	xte;
	int		i;
	double	last[2];

	if (val[5] == 0)
		return (julia(iter, val, width, height));
	i = -1;
	val[0] = normalize(val[0], (double[4]){0, width, -(val[2]), val[2]});
	val[1] = normalize(val[1], (double[4]){0, height, -(val[2]), val[2]});
	while (val[0] * val[0]  + val[1] * val[1] < val[2] * val[2] &&  ++i < iter)
	{
		last[0] = val[0];
		last[1] = val[1];
		xte = pow(val[0]  * val[0]  - val[1] * val[1], val[5] / 2) * cos(val[5] * atan2(val[1], val[0])) + val[3];
		val[1] = pow(2 * val[0] * val[1] + val[4], val[5] / 2) * sin(val[5] * atan2(val[1], val[0])) + val[4];
		val[0]  = xte;// + val[3];
		if (last[0] == val[0] && last[1] == val[1]) // check for looping // add "too close to 0?"
			return (iter);
	}
	return (i == -1 ? 0 : i);
}

static double	mandel(int iter, double xs, double ys)
{
	double	x; 
	double	y;
	double	xte;
	int		i;
	double	last[2];

	i = -1;
	x = 0;
	y = 0;
	while (x * x + y * y <= 4 &&  ++i < iter)
	{
		last[0] = x;
		last[1] = y;
		xte = x * x - y * y + xs;
		y = 2 * x * y + ys;
		x = xte;
		if (last[0] == x && last[1] == y) // check for looping // add "too close to 0?"
			return (iter);
	}
	return (i == -1 ? 0 : i);
}

void	barnsley(float *val)
{
	float	x;
	float	y;
	float	r;

	r = (float)rand()/(float)(RAND_MAX);
	if (r < 0.01)
	{
		x = 0;
		y = 0.16 * val[1];
	}
	else if (r < 0.86)
	{
		x = 0.85 * val[0] + 0.04 * val[1];
		y = -0.04 * val[0] + 0.85 * val[1] + 1.6;
	}
	else if (r < 0.93)
	{
		x = 0.20 * val[0] - 0.26 * val[1];
		y = 0.23 * val[0] + 0.22 * val[1] + 1.6;
	}
	else
	{
		x = -0.15 * val[0] + 0.28 * val[1];
		y = 0.26 * val[0] + 0.24 * val[1] + 0.44;
	}
	val[0] = x;
	val[1] = y;
}
/*
void	fractal31(void *para)
{
	float	val[2]; // x, y
	int		i, y;
	t_frac	*frac;
	t_vec4	point;

	frac = para;
	frac->off[0] += frac->width / 2 * frac->zoom - frac->width / 2;
	frac->off[1] += frac->height / 2 * frac->zoom - frac->height / 2;
	if (frac->thread == 1)
		printf("offx = %f offy = %f\n", frac->off[0], frac->off[1]);
	i = -1;
	y = 0;
	val[0] = 0;
	val[1] = 0;
	while (++i < frac->iter * 100)// && y < frac->iter)//frac->iter)
	{
		//if (frac->thread == 1)
		//	printf("offx %f zoom %f x %f\nx_min %f x_max %f\n", 
		//		frac->off[0], frac->zoom, val[0], BARN_X_MIN + (((BARN_X_MAX - BARN_X_MIN) * (frac->off[0] / frac->width)) * frac->zoom), BARN_X_MAX  + (((BARN_X_MAX - BARN_X_MIN) * (frac->off[0] / frac->width)) * frac->zoom));
		point = vec4_ini((float[4]){normalize(val[0], (double[4])
		{BARN_X_MIN - (((BARN_X_MAX - BARN_X_MIN) * (frac->off[0] / frac->width)) * frac->zoom), 
		BARN_X_MAX  - (((BARN_X_MAX - BARN_X_MIN) * (frac->off[0] / frac->width)) * frac->zoom), 0, frac->width}) * frac->zoom,
		normalize(val[1], (double[4])
		{BARN_Y_MIN - (((BARN_Y_MAX - BARN_Y_MIN) * (frac->off[1] / frac->height)) * frac->zoom), 
		BARN_Y_MAX - (((BARN_Y_MAX - BARN_Y_MIN) * (frac->off[1] / frac->height)) * frac->zoom), 0, frac->height}) * frac->zoom, 0, 1}); // not good with zoom
		point.vec[0] -= frac->width / 2;
		point.vec[1] -= frac->width / 2;
		point = mat4_vec4(rot_matrix(frac->mlx->rot), point);
		point.vec[0] += frac->width / 2;// + frac->off[0] * 2;
		point.vec[1] += frac->height / 2;//  + frac->off[1] * 2;
		point.vec[3] = 0x00ff00;
		to_image(frac->mlx, point);
		barnsley(val);

	}
}

//julia
void	fractal22(void *para)
{
	int		val[2]; // x, y
	int		i;
	t_frac	*frac;
	t_vec4	point;

	frac = para;
	frac->off[0] += frac->width / 2 * frac->zoom - frac->width / 2;
	frac->off[1] += frac->height / 2 * frac->zoom - frac->height / 2;
	if (frac->thread == 1)
		printf("offx = %f offy = %f\n", frac->off[0], frac->off[1]);
	val[1] = frac->y;
	i = 0;
	while (--frac->lines >= 0)
	{
		val[0] = -1;
		while (++val[0] < frac->width)
		{
			point =  vec4_ini((float[4]){val[0] * frac->zoom - frac->off[0],
			 val[1] * frac->zoom - frac->off[1], 0, 1});
			point.vec[0] -= frac->width / 2;
			point.vec[1] -= frac->width / 2;
			point = mat4_vec4(rot_matrix(frac->mlx->rot), point);
			point.vec[0] += frac->width / 2;
			point.vec[1] += frac->height / 2;
			frac->num[i++] = julia_flex(frac->iter, (double[6]){val[0], val[1], frac->mlx->jul[2], frac->mlx->jul[0], frac->mlx->jul[1], frac->mlx->jul[3]}, frac->width, frac->height);
			if (frac->mlx->rot[0] != ROT_X || frac->mlx->rot[1] != ROT_Y || frac->mlx->rot[2] != ROT_Z)
				three_d(frac->mlx, vec4_ini((float[4]){val[0], val[1], frac->num[i - 1], 1}));
		}
		val[1]++;
	}
	frac->lines = frac->size / frac->width;
	if (frac->mlx->rot[0] == ROT_X && frac->mlx->rot[1] == ROT_Y && frac->mlx->rot[2] == ROT_Z)
		fractal_norm(frac);
	else
	{
	//	three_d_two(frac->mlx, frac);
	}
}

// mandel
void	fractal11(void *para)
{
	int		val[2]; // x, y
	int		i;
	t_frac	*frac;
	t_vec4	orig;
	t_mat4	rot;

	frac = para;
	frac->off[0] += frac->width / 2 * frac->zoom - frac->width / 2;
	frac->off[1] += frac->height / 2 * frac->zoom - frac->height / 2;
	val[1] = frac->y;
	i = 0;
	rot = mat4_rot_inverse(rot_matrix(frac->mlx->rot));
	while (--frac->lines >= 0)
	{
		val[0] = -1;
		while (++val[0] < frac->width)
		{
			orig = mat4_vec4(rot, vec4_ini((float[4]){val[0] - frac->mlx->width / 2, val[1] - frac->mlx->height / 2, 0, 1}));
			orig.vec[0] += frac->mlx->width / 2;
			orig.vec[1] += frac->mlx->height / 2;
			frac->num[i] = mandel(frac->iter, normalize((orig.vec[0] + frac->off[0]) / frac->zoom, (double[4]){0, frac->width, MAN_MINX,
			MAN_MAXX}), normalize((orig.vec[1] + frac->off[1]) / frac->zoom, (double[4]){0, frac->height, MAN_MINY, MAN_MAXY}));
			//frac->num[i++] = mandel(frac->iter, normalize(val[0] * frac->zoom - frac->off[0], (double[4]){0, frac->width, MAN_MINX,
			//MAN_MAXX}), normalize(val[1] * frac->zoom - frac->off[1], (double[4]){0, frac->height, MAN_MINY, MAN_MAXY}));
			if (frac->mlx->rot[0] != ROT_X || frac->mlx->rot[1] != ROT_Y || frac->mlx->rot[2] != ROT_Z) // why removing this segfaults??
				three_d(frac->mlx, vec4_ini((float[4]){val[0], val[1], frac->num[i++], 1}));
		}
		val[1]++;
	}
	frac->lines = frac->size / frac->width;
	if (frac->mlx->rot[0] == ROT_X && frac->mlx->rot[1] == ROT_Y && frac->mlx->rot[2] == ROT_Z)
		fractal_norm(frac);
	else
	{
	//	three_d_two(frac->mlx, frac);
	}
}
void	fractal2(void *para)
{
	int		val[2]; // x, y
	int		i;
	t_frac	*frac;
	t_vec4	point;

	frac = para;
	frac->off[0] += frac->width / 2 * frac->zoom - frac->width / 2;
	frac->off[1] += frac->height / 2 * frac->zoom - frac->height / 2;
	if (frac->thread == 1)
		printf("offx = %f offy = %f\n", frac->off[0], frac->off[1]);
	val[1] = frac->y;
	i = 0;
	while (--frac->lines >= 0)
	{
		val[0] = -1;
		while (++val[0] < frac->width)
		{
			point =  vec4_ini((float[4]){val[0] * frac->zoom - frac->off[0],
			 val[1] * frac->zoom - frac->off[1], 0, 1});
			point.vec[0] -= frac->width / 2;
			point.vec[1] -= frac->width / 2;
			point = mat4_vec4(rot_matrix(frac->mlx->rot), point);
			point.vec[0] += frac->width / 2;
			point.vec[1] += frac->height / 2;
			frac->num[i++] = mandel(frac->iter, normalize(point.vec[0], (double[4]){0, frac->width, MAN_MINX,
			MAN_MAXX}), normalize(point.vec[1], (double[4]){0, frac->height, MAN_MINY, MAN_MAXY}));
			if (frac->mlx->rot[0] != ROT_X || frac->mlx->rot[1] != ROT_Y || frac->mlx->rot[2] != ROT_Z)
				three_d(frac->mlx, vec4_ini((float[4]){val[0], val[1], frac->num[i - 1], 1}));
		}
		val[1]++;
	}
	frac->lines = frac->size / frac->width;
	if (frac->mlx->rot[0] == ROT_X && frac->mlx->rot[1] == ROT_Y && frac->mlx->rot[2] == ROT_Z)
		fractal_norm(frac);
	else
	{
	//	three_d_two(frac->mlx, frac);
	}
}

void	fractal1(void *para)
{
	int		val[2]; // x, y
	int		i;
	t_frac	*frac;



	frac = para;
//	ft_putstr("thread start ");
//	ft_putnbr(frac->thread);
//	ft_putchar('\n');
//	ft_putpointer(frac->num);
//	ft_putchar('\n');
	frac->off[0] += frac->width / 2 * frac->zoom - frac->width / 2;
	frac->off[1] += frac->height / 2 * frac->zoom - frac->height / 2;
	if (frac->thread == 1)
		printf("offx = %f offy = %f\n", frac->off[0], frac->off[1]);
	val[1] = frac->y;
	i = 0;
	while (--frac->lines >= 0)
	{
		val[0] = -1;
		while (++val[0] < frac->width)
		{
			frac->num[i++] = mandel(frac->iter, normalize(val[0] * frac->zoom - frac->off[0], (double[4]){0, frac->width, MAN_MINX,
			MAN_MAXX}), normalize(val[1] * frac->zoom - frac->off[1], (double[4]){0, frac->height, MAN_MINY, MAN_MAXY}));
			if (frac->mlx->rot[0] != ROT_X || frac->mlx->rot[1] != ROT_Y || frac->mlx->rot[2] != ROT_Z)
				three_d(frac->mlx, vec4_ini((float[4]){val[0], val[1], frac->num[i - 1], 1}));
		}
		val[1]++;
	}
	frac->lines = frac->size / frac->width;
	if (frac->mlx->rot[0] == ROT_X && frac->mlx->rot[1] == ROT_Y && frac->mlx->rot[2] == ROT_Z)
		fractal_norm(frac);
	else
	{
	//	three_d_two(frac->mlx, frac);
	}
	
//	mlx_put_image_to_window(frac->mlx->mlx_ptr, frac->mlx->mlx_win, frac->mlx->mlx_img[frac->thread], 0, frac->y);
//	ft_putstr("thread end ");
//	ft_putnbr(frac->thread);
//	ft_putchar('\n');
//	printf("[0] = %d\n", frac->num[0]);
	//pthread_exit(NULL);
}

*/
// barnsley
void	fractal_barn(void *para)
{
	float	val[2]; // x, y
	int		i, y;
	t_frac	*frac;
	t_vec4	point;

	frac = para;
	if (frac->thread == 1)
		printf("offx = %f offy = %f\n", frac->off[0], frac->off[1]);
	i = -1;
	y = 0;
	val[0] = 0;
	val[1] = 0;
	while (++i < frac->iter * 100)
	{
		point = vec4_ini((float[4]){normalize(val[0], (double[4]){BARN_X_MIN, BARN_X_MAX , -(frac->width / 2), frac->width / 2}),
		normalize(val[1], (double[4]){BARN_Y_MIN, BARN_Y_MAX, -(frac->height / 2), frac->height / 2}), 0, 1});
		point = mat4_vec4(rot_matrix(frac->mlx->rot), point);
		point.vec[0] = (point.vec[0] + frac->off[0]) / frac->zoom + frac->width / 2;
		point.vec[1] = (point.vec[1] + frac->off[1]) / frac->zoom + frac->height / 2;
		point.vec[3] = BARN_COLOR;
		to_image(frac->mlx, point);
		barnsley(val);
	}
}

// julia
void	fractal_jul(void *para)
{
	int		val[2]; // x, y
	t_frac	*frac;
	t_vec4	point;

	frac = para;
	if (frac->thread == 1)
		printf("offx = %f offy = %f\n", frac->off[0], frac->off[1]);
	val[1] = frac->y;
	while (--frac->lines >= 0)
	{
		val[0] = -1;
		while (++val[0] < frac->width)
		{
			point = mat4_vec4(rot_matrix(frac->mlx->rot), vec4_ini((float[4]){(val[0] - frac->mlx->width / 2), (val[1] - frac->mlx->height / 2), 0, 1}));
			point.vec[0] = point.vec[0] * frac->zoom + frac->width / 2 - frac->off[0] * 2;
			point.vec[1] = point.vec[1] * frac->zoom + frac->height / 2 - frac->off[1] * 2;
			point.vec[3] = julia_flex(frac->iter, (double[6]){point.vec[0], point.vec[1], frac->mlx->jul[2], frac->mlx->jul[0], frac->mlx->jul[1], frac->mlx->jul[3]}, frac->width, frac->height);
			point.vec[3] = mlx_get_color_value(frac->mlx->mlx_ptr, map_color(frac->iter - point.vec[3], (double[4]){0, frac->iter, frac->mlx->color[0], frac->mlx->color[1]}));
			//(int)normalize(frac->iter - point.vec[3], (double[4]){0, frac->iter, frac->mlx->color[0], frac->mlx->color[1]}));
			point.vec[0] = val[0];
			point.vec[1] = val[1];
			to_image(frac->mlx, point);
		}
		val[1]++;
	}
	frac->lines = frac->size / frac->width;
}

// mandel
void	fractal_man(void *para)
{
	int		val[2]; // x, y
	t_frac	*frac;
	t_vec4	point;
	t_mat4	rot;

	frac = para;
	val[1] = frac->y;
	rot = rot_matrix(frac->mlx->rot);
	while (--frac->lines >= 0)
	{
		val[0] = -1;
		while (++val[0] < frac->width)
		{
			point = mat4_vec4(rot, vec4_ini((float[4]){val[0] - frac->mlx->width / 2, val[1] - frac->mlx->height / 2, 0, 1}));
				//point.vec[0] = (point.vec[0]) - frac->off[0] * 2 + frac->width / 2;
				//point.vec[1] = (point.vec[1]) - frac->off[1] * 2 + frac->height / 2;
					//point.vec[0] = (point.vec[0]) / frac->zoom - frac->off[0] * 2 + frac->width / 2;
					//point.vec[1] = (point.vec[1]) / frac->zoom - frac->off[1] * 2 + frac->height / 2;
			point.vec[0] = point.vec[0] * frac->zoom + frac->width / 2 - frac->off[0] * 2;
			point.vec[1] = point.vec[1] * frac->zoom + frac->height / 2 - frac->off[1] * 2;
			point.vec[3] = mandel(frac->iter, normalize(/*val[0]*/point.vec[0], (double[4]){0, frac->width, MAN_MINX,
			MAN_MAXX}), normalize(/*val[1]*/point.vec[1], (double[4]){0, frac->height, MAN_MINY, MAN_MAXY}));
			point.vec[3] = mlx_get_color_value(frac->mlx->mlx_ptr, map_color(frac->iter - point.vec[3], (double[4]){0, frac->iter, frac->mlx->color[0], frac->mlx->color[1]}));
			//(int)normalize(frac->iter - point.vec[3], (double[4]){0, frac->iter, frac->mlx->color[0], frac->mlx->color[1]}));
			point.vec[0] = val[0];
			point.vec[1] = val[1];
			to_image(frac->mlx, point);
		}
		val[1]++;
	}
	frac->lines = frac->size / frac->width;
}

#include <time.h>
static t_frac	slice_ini(t_mlx *mlx, int i, int y)
{
	t_frac	ret;

	ret.mlx = mlx;
	ret.y = mlx->height % THREADS - i > 0 ? 1 : 0;
	ret.lines  = ((int)(mlx->height / THREADS) + ret.y);// this block y size
	ret.width = mlx->width;
	ret.height = mlx->height;
	ret.size = ret.lines * mlx->width;// save the size
	ret.y = y; // add to total Y done so far
	ret.iter = mlx->iter;
	ret.thread = i;
	ret.zoom = mlx->zoom;
	ret.off[0] = mlx->offx;
	ret.off[1] = mlx->offy;
	return (ret);
}
// new draw
void	draw(t_mlx *mlx)
{
clock_t t = clock();
	pthread_t		threads[THREADS];
	t_frac			slice[THREADS];
	int				i;
	int				y;

	mlx_clear_window(mlx->mlx_ptr, mlx->mlx_win);
	//mlx_image_wipe(mlx, 0, mlx->width, mlx->height);
	i = -1;
	y = 0;
	while (++i < THREADS)
	{
		slice[i] = slice_ini(mlx, i + 1 ,y);
		y += slice[i].lines;
		pthread_create(&threads[i], NULL, (void*)mlx->func, &slice[i]);
	}
	i = -1;
	while (++i < THREADS)
		pthread_join(threads[i], NULL);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->mlx_win, mlx->mlx_img, 0, 0);
	if (mlx->colort)
	{
		color_show(mlx);
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->mlx_win, mlx->clr_swat,
			mlx->width / 2 - (3 * COLOR_WID + 4 * COLOR_OUTL) / 2,
			mlx->height / 2 - (255 + 2 * COLOR_OUTL) / 2);
	}
t = clock() - t;
printf("draw_uni() took %f seconds\n", ((double)t)/CLOCKS_PER_SEC);
mlx_string_put(mlx->mlx_ptr, mlx->mlx_win, 10, 0, 0x00ff00, "Threads");
mlx_string_put(mlx->mlx_ptr, mlx->mlx_win, 120, 0, 0x00ff00, ft_itoa_base(THREADS, 10));
mlx_string_put(mlx->mlx_ptr, mlx->mlx_win, 10, 20, 0x0000ff, "Iter");
mlx_string_put(mlx->mlx_ptr, mlx->mlx_win, 120, 20, 0x0000ff, ft_itoa_base(mlx->iter, 10));
}