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

int				iter_color(t_frac *frac, t_vec4 point)
{
	return (mlx_get_color_value(frac->mlx->mlx_ptr, (int)frac->mlx->clr_func(
		frac->iter - point.vec[2], (long double[4]){0, frac->iter,
		frac->mlx->color[0], frac->mlx->color[1]})));
}

static void		color_spot(t_mlx *mlx, t_dot coord, t_rgb color, char c)
{
	if (c == 1)
	{
		to_color(mlx, vec4_ini((long double[4]){coord.x, coord.y, 0,
			rgb_color(255 - coord.y + COLOR_OUTL, 0, 0)}));
		if (255 - coord.y + COLOR_OUTL == color.red)
			to_color(mlx, vec4_ini((long double[4]){coord.x, coord.y, 0,
				rgb_color(255 - color.red, 0, 0)}));
	}
	else if (c == 2)
	{
		to_color(mlx, vec4_ini((long double[4]){coord.x, coord.y, 0,
			rgb_color(0, 255 - coord.y + COLOR_OUTL, 0)}));
		if (255 - coord.y + COLOR_OUTL == color.green)
			to_color(mlx, vec4_ini((long double[4]){coord.x, coord.y, 0,
				rgb_color(0, 255 - color.green, 0)}));
	}
	else if (c == 3)
	{
		to_color(mlx, vec4_ini((long double[4]){coord.x, coord.y, 0,
			rgb_color(0, 0, 255 - coord.y + COLOR_OUTL)}));
		if (255 - coord.y + COLOR_OUTL == color.blue)
			to_color(mlx, vec4_ini((long double[4]){coord.x, coord.y, 0,
				rgb_color(0, 0, 255 - color.blue)}));
	}
}

static void		color_show(t_mlx *mlx)
{
	t_rgb	color;
	t_dot	coord;
	int		loop;

	color = rgb_conv(mlx->color[mlx->colort - 1]);
	loop = 0;
	coord.x = 0;
	while (++loop <= 3)
	{
		coord.x += COLOR_OUTL - 1;
		while (++coord.x < COLOR_OUTL * loop + COLOR_WID * loop)
		{
			coord.y = COLOR_OUTL - 1;
			while (++coord.y <= 255 + COLOR_OUTL)
				color_spot(mlx, coord, color, loop);
		}
	}
}


//					0		1			2	3	4	5
// julia, base		x(s)	y(s)	||	r	cx	cy	(n)
static double	julia(int iter, t_box box)//long double val[6], int width, int height)
{
	box.i = -1;
	box.x = map(box.x, (long double[4]){0, box.width,
		-(box.jul.r), box.jul.r});
	box.y = map(box.y, (long double[4]){0, box.height,
		-(box.jul.r), box.jul.r});
	while (box.x * box.x  + box.y * box.y <=
		box.jul.r * box.jul.r &&  ++box.i < iter)
	{
		box.last.x = box.x;
		box.last.y = box.y;
		box.xte = box.x  * box.x  - box.y * box.y;
		box.y = 2 * box.x * box.y + box.jul.cy;
		box.x  = box.xte + box.jul.cx;
		if (box.last.x == box.x && box.last.y == box.y) // check for looping // add "too close to 0?"
			return (iter);
	}
	return (box.i == -1 ? 0 : box.i);
}
//					0		1			2	3	4	5
// julia flex		x(s)	y(s)	||	r	cx	cy	n
static double	julia_flex(int iter, t_box box)//long double val[6], t_julia jul, int width, int height)
{
	if (box.jul.n == 0)
		return (julia(iter, box));
	box.i = -1;
	box.x = map(box.x, (long double[4]){0, box.width,
		-(box.jul.r), box.jul.r});
	box.y = map(box.y, (long double[4]){0, box.height,
		-(box.jul.r), box.jul.r});
	while (box.x * box.x + box.y * box.y <=
		box.jul.r * box.jul.r &&  ++box.i < iter)
	{
		box.last.x = box.x;
		box.last.y = box.y;
		box.xte = pow(box.x * box.x - box.y * box.y, box.jul.n / 2) *
			cos(box.jul.n * atan2(box.y, box.x)) + box.jul.cx;
		box.y = pow(2 * box.x * box.y + box.jul.cy, box.jul.n / 2) *
			sin(box.jul.n * atan2(box.y, box.x)) + box.jul.cy;
		box.x  = box.xte;
		if (box.last.x == box.x && box.last.y == box.y) // check for looping // add "too close to 0?"
			return (iter);
	}
	return (box.i == -1 ? 0 : box.i);
}

static double	mandel(int iter, long double xs, long double ys)
{
	t_box	box;

	box.i = -1;
	box.x = 0;
	box.y = 0;
	while (box.x * box.x + box.y * box.y <= 4 &&  ++box.i < iter)
	{
		box.last.x = box.x;
		box.last.y = box.y;
		box.xte = box.x * box.x - box.y * box.y + xs;
		box.y = 2 * box.x * box.y + ys;
		box.x = box.xte;
		if (box.last.x == box.x && box.last.y == box.y) // check for looping // add "too close to 0?"
			return (iter);
	}
	return (box.i == -1 ? 0 : box.i);
}

// 			(0	1)	2	3
// val =	x	y	xs	 ys
static double	multibrot_neg(int iter, t_box box)//long double val[4], long double n)
{
	box.xs = map(box.x, (long double[4]){0, box.width, MAN_MINX, MAN_MAXX});
	box.ys = map(box.y, (long double[4]){0, box.height, MAN_MINY, MAN_MAXY});
	box.x = 0;
	box.y = 0;
	box.i = -1;
	box.nn = -(box.jul.n);
	box.d = pow(pow(box.xs, 2) + pow(box.ys, 2), box.nn);
	while (box.x * box.x + box.y * box.y <= box.jul.n * box.jul.n &&
		++box.i < iter)
	{
		if (!box.d)
			return (box.i);
		box.xte = pow((box.x * box.x + box.y * box.y), (box.nn / 2)) *
			cos(box.nn * atan2(box.y, box.x)) / box.d + box.xs;
		box.y = -(pow((box.x * box.x + box.y * box.y), (box.nn / 2))) *
			sin(box.nn * atan2(box.y, box.x)) / box.d + box.ys;
		box.x = box.xte;
		if ((box.last.x == box.x && box.last.y == box.y))
			return (iter);
		box.d = pow(pow(box.x, 2) + pow(box.y, 2), box.nn);
	}
	return (box.i == -1 ? 0 : box.i);
}
// 			(0	1)	2	3
// val =	x	y	xs	 ys
static double	multibrot(int iter, t_box box)//long double val[4], long double n)
{
	if (box.jul.n < 0)
		return (multibrot_neg(iter, box));//val, n));
	box.xs = map(box.x, (long double[4]){0, box.width, MAN_MINX, MAN_MAXX});
	box.ys = map(box.y, (long double[4]){0, box.height, MAN_MINY, MAN_MAXY});
	box.x = 0;
	box.y = 0;
	box.i = -1;
	while (box.x * box.x + box.y * box.y <= box.jul.n * box.jul.n 
		&& ++box.i < iter)
	{
		box.xte = pow((box.x * box.x + box.y * box.y), (box.jul.n / 2)) *
			cos(box.jul.n * atan2(box.y, box.x)) + box.xs;
		box.y = pow((box.x * box.x + box.y * box.y), (box.jul.n / 2)) *
			sin(box.jul.n * atan2(box.y, box.x)) + box.ys;
		box.x = box.xte;
		if ((box.last.x == box.x && box.last.y == box.y))
			return (iter);
	}
	return (box.i == -1 ? 0 : box.i);
}

t_ddot	barnsley(t_ddot val)
{
	t_box	box;

	box.r = (long double)rand()/(long double)(RAND_MAX);
	if (box.r < 0.01)
	{
		box.x = 0;
		val.y = 0.16 * val.y;
	}
	else if (box.r < 0.86)
	{
		box.x = 0.85 * val.x + 0.04 * val.y;
		val.y = -0.04 * val.x + 0.85 * val.y + 1.6;
	}
	else if (box.r < 0.93)
	{
		box.x = 0.20 * val.x - 0.26 * val.y;
		val.y = 0.23 * val.x + 0.22 * val.y + 1.6;
	}
	else
	{
		box.x = -0.15 * val.x + 0.28 * val.y;
		val.y = 0.26 * val.x + 0.24 * val.y + 0.44;
	}
	val.x = box.x;
	return (val);
}

// barnsley
void	fractal_barn(void *para)
{
	t_ddot	dot;//long double	val[2]; // x, y
	int		i;
	t_frac	*frac;
	t_vec4	point;

	frac = para;
	if (frac->thread == 1)
		printf("offx = %Lf offy = %Lf\n", frac->off.x, frac->off.y);
	i = -1;
	dot.x = 0;
	dot.y = 0;
	while (++i < frac->iter * 100)
	{
		point = vec4_ini((long double[4]){map(dot.x, (long double[4])
			{BARN_X_MIN, BARN_X_MAX , -(frac->w), frac->w}),
		map(dot.y, (long double[4]){BARN_Y_MIN, BARN_Y_MAX,
			-(frac->h), frac->h}), i / 100 - frac->iter * 50 / 100, 1});
		point = mat4_vec4(rot_matrix(frac->mlx->rot), point);
		point.vec[0] = (point.vec[0] + frac->off.x) / frac->zoom + frac->w;
		point.vec[1] = (point.vec[1] + frac->off.y) / frac->zoom + frac->h;
		point.vec[2] += frac->iter * 50 / 100;
		// UNDO THIS?
		//point.vec[3] = mlx_get_color_value(frac->mlx->mlx_ptr, (int)frac->mlx->clr_func(THREADS - frac->thread, (long double[4]){0, THREADS, frac->mlx->color[0], frac->mlx->color[1]}));
		point.vec[3] = mlx_get_color_value(frac->mlx->mlx_ptr, BARN_COLOR);
		to_image(frac->mlx, point);
		dot = barnsley(dot);
	}
}

// julia
void	fractal_jul(void *para)
{
	t_dot	dot;//int		val[2]; // x, y
	t_frac	*frac;
	t_vec4	point;
	t_box	box;

	frac = para;
	dot.y = frac->y;
	box.width = frac->width;
	box.height = frac->height;
	box.jul = frac->mlx->jul;
	while (--frac->lines >= 0)
	{
		dot.x = -(frac->mlx->extra) * EXTRA - 1;//-1;
		while (++dot.x < frac->width + frac->mlx->extra * EXTRA)
		{
			point = vec4_ini((long double[4]){dot.x - frac->w,
				dot.y - frac->h, 0, 1});
			box.x = point.vec[0] * frac->zoom + frac->w - frac->off.x;
			box.y = point.vec[1] * frac->zoom + frac->h - frac->off.y;
			point.vec[2] = julia_flex(frac->iter, box);
			point.vec[3] = iter_color(frac, point);
			point.vec[0] = dot.x;
			point.vec[1] = dot.y;
			to_image(frac->mlx, point);
		}
		dot.y++;
	}
	frac->lines = frac->size / frac->width;
}

// multibrot
void	fractal_mult(void *para)
{
	t_dot	dot;
	t_frac	*frac;
	t_vec4	point;
	t_box	box;

	frac = para;
	dot.y = frac->y;
	box.jul = frac->mlx->jul;
	box.width = frac->width;
	box.height = frac->height;
	while (--frac->lines >= 0)
	{
		dot.x = -(frac->mlx->extra) * EXTRA - 1;//-1;
		while (++dot.x < frac->width + frac->mlx->extra * EXTRA)
		{
			point = vec4_ini((long double[4]){dot.x - frac->w,
				dot.y - frac->h, 0, 1});
			box.x = point.vec[0] * frac->zoom + frac->w - frac->off.x;
			box.y = point.vec[1] * frac->zoom + frac->h - frac->off.y;
			point.vec[2] = multibrot(frac->iter, box);/*(long double[4]){
				point.vec[0], point.vec[1], map(point.vec[0], (long double[4]){
				0, frac->width, MAN_MINX, MAN_MAXX}), map(point.vec[1],
				(long double[4]){0, frac->height, MAN_MINY, MAN_MAXY})},
				frac->mlx->jul.r);*/
			point.vec[3] = iter_color(frac, point);
			point.vec[0] = dot.x;
			point.vec[1] = dot.y;
			to_image(frac->mlx, point);
		}
		dot.y++;
	}
	frac->lines = frac->size / frac->width;
}

// mandel
void	fractal_man(void *para)
{
	t_dot	dot;
	t_frac	*frac;
	t_vec4	point;

	frac = para;
	dot.y = frac->y;
	while (--frac->lines >= 0)
	{
		dot.x = -(frac->mlx->extra) * EXTRA - 1;//-1;
		while (++dot.x < frac->width + frac->mlx->extra * EXTRA)
		{
			point = vec4_ini((long double[4]){dot.x - frac->w, dot.y - frac->h, 0, 1});
			point.vec[0] = point.vec[0] * frac->zoom + frac->w - frac->off.x;
			point.vec[1] = point.vec[1] * frac->zoom + frac->h - frac->off.y;
			point.vec[2] = mandel(frac->iter, map(point.vec[0], (long double[4]
				){0, frac->width, MAN_MINX, MAN_MAXX}), map(point.vec[1],
				(long double[4]){0, frac->height, MAN_MINY, MAN_MAXY}));
			point.vec[3] = iter_color(frac, point);
			point.vec[0] = dot.x;
			point.vec[1] = dot.y;
			to_image(frac->mlx, point);
		}
		dot.y++;
	}
	frac->lines = frac->size / frac->width;
}

#include <time.h>
static t_frac	slice_ini(t_mlx *mlx, int i, int y)
{
	t_frac	ret;

	ret.mlx = mlx;
	ret.y = (mlx->height + mlx->extra * EXTRA * 2) % THREADS - i > 0 ? 1 : 0;
	ret.lines  = ((int)((mlx->height + mlx->extra * EXTRA * 2) / THREADS) + ret.y);// this block y size
	ret.width = mlx->width;
	ret.height = mlx->height;
	ret.w = mlx->width / 2;
	ret.h = mlx->height / 2;
	ret.size = ret.lines * mlx->width;// save the size
	ret.y = y; // add to total Y done so far
	ret.iter = mlx->iter;
	ret.thread = i;
	ret.zoom = mlx->zoom;
	ret.off.x = mlx->offx;
	ret.off.y = mlx->offy;
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
	char			*print;

	mlx_clear_window(mlx->mlx_ptr, mlx->mlx_win);
	if (mlx->height_map)
		height_reset(mlx->height_map, -1000000000000, mlx->width, mlx->height);
	//mlx_image_wipe(mlx, 0, mlx->width, mlx->height);
	printf("'screen' size width %d height %d\n", mlx->width + mlx->extra * EXTRA * 2, mlx->height + mlx->extra * EXTRA * 2);
	i = -1;
	y = -(mlx->extra) * EXTRA;
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
mlx_string_put(mlx->mlx_ptr, mlx->mlx_win, 120, 0, 0x00ff00, (print = ft_itoa_base(THREADS, 10)));
free(print);
mlx_string_put(mlx->mlx_ptr, mlx->mlx_win, 10, 20, 0x0000ff, "Iter");
mlx_string_put(mlx->mlx_ptr, mlx->mlx_win, 120, 20, 0x0000ff, (print = ft_itoa_base(mlx->iter, 10)));
free(print);
}