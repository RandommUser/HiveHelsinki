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

void	fractal31(void *para)
{
	float	val[2]; // x, y
	int		i;
	t_frac	*frac;
	t_vec4	point;

	frac = para;
	//frac->off[0] += frac->width / 2 * frac->zoom - frac->width / 2;
	//frac->off[1] += frac->height / 2 * frac->zoom - frac->height / 2;
	if (frac->thread == 1)
		printf("offx = %f offy = %f\n", frac->off[0], frac->off[1]);
	else
		return ;
	i = -1;
	val[0] = 0;
	val[1] = 0;
	while (++i < frac->iter * 100)//frac->iter)
	{
		//if (frac->mlx->rot[0] != ROT_X || frac->mlx->rot[1] != ROT_Y || frac->mlx->rot[2] != ROT_Z)
		point = vec4_ini((float[4]){normalize(val[0], (double[4]){-2.1820, 2.6558, 0, frac->width}) * frac->zoom + frac->off[0],
		normalize(val[1], (double[4]){0, 9.9983, 0, frac->height}) * frac->zoom + frac->off[1], 0, 1}); // not good with zoom
		point.vec[0] -= frac->width / 2;
		point.vec[1] -= frac->width / 2;
		point = mat4_vec4(rot_matrix(frac->mlx->rot), point);
		point.vec[0] += frac->width / 2;
		point.vec[1] += frac->height / 2;
		point.vec[3] = 0x00ff00;
		to_image(frac->mlx, point);
		barnsley(val);
		//printf("x %f y %f\n", val[0], val[1]);
		/*
		point =  vec4_ini((float[4]){val[0] * frac->zoom - frac->off[0],
		 val[1] * frac->zoom - frac->off[1], 0, 1});
		point.vec[0] -= frac->width / 2;
		point.vec[1] -= frac->width / 2;
		point = mat4_vec4(rot_matrix(frac->mlx->rot), point);
		point.vec[0] += frac->width / 2;
		point.vec[1] += frac->height / 2;*/
	}
}


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
	{ // (val[0] - frac->off[0])/* * frac->zoom*/   (val[1] - frac->off[1])/* * frac->zoom*/
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
#include <time.h>
void	draw(t_mlx *mlx)
{
clock_t t = clock();
	pthread_t		threads[THREADS + 1];
	t_frac			slice[THREADS + 1];
	int				i;
	//int				parts[THREADS + 1][(int)(mlx->height / THREADS) *
	//	mlx->width + THREADS];

	mlx_clear_window(mlx->mlx_ptr, mlx->mlx_win);
	/*if (mlx->rot[0] != ROT_X || mlx->rot[1] != ROT_Y || mlx->rot[2] != ROT_Z)
	{*/
		mlx_image_wipe(mlx, 0, mlx->width, mlx->height);
		if (!(mlx->height_map = (double*)malloc((sizeof(double) * mlx->width * mlx->height))))
			run_exit(ERR_MEMORY, "draw.c draw() height_map alloc\n");
		height_reset(mlx->height_map, -21474863647, mlx->width, mlx->height); // good default height
	/*}*/
	i = 0;
	slice[0].y = 0;
//	printf("width %d height %d threads %d\n", mlx->width, mlx->height, THREADS);
//	printf("split sizes %d\n", (int)(mlx->height / THREADS) * mlx->width + THREADS);
	while (i++ < THREADS)
	{
		slice[i].mlx = mlx;
		slice[i].y = mlx->height % THREADS - i > 0 ? 1 : 0;
		//parts[i][0] = mlx->height % THREADS - i > 0 ? 1 : 0; // need padding
		slice[i].lines  = ((int)(mlx->height / THREADS) + slice[i].y);// this block y size
		mlx_image_create(mlx, i, mlx->width, slice[i].lines);
		/*if (!mlx->mlx_img[i])
		{
			mlx->mlx_img[i] = mlx_new_image(mlx->mlx_ptr, mlx->width, slice[i].lines);
			mlx->img_dat[i] = (int*)mlx_get_data_addr(mlx->mlx_img[i], &mlx->bpp, &mlx->size_line,
			&mlx->endian);
		}*/
		slice[i].width = mlx->width;
		slice[i].height = mlx->height;
		slice[i].size = slice[i].lines * mlx->width;// save the size
		slice[i].y = slice[0].y; // add to total Y done so far
		slice[0].y += slice[i].lines;
		slice[i].iter = mlx->iter;
		slice[i].thread = i;
		slice[i].zoom = mlx->zoom;
		//slice[i].num = parts[i];
		slice[i].off[0] = mlx->offx;
		slice[i].off[1] = mlx->offy;
		slice[i].num = mlx->img_dat[i];
//		ft_putstr("creating a thread ");
//		ft_putnbr(i);
//		ft_putchar('\n');
//		ft_putpointer(parts[i]);
//		ft_putchar('\n');
//		printf("lines %d\n", slice[i].lines);
		pthread_create(&threads[i], NULL, (void*)fractal31, &slice[i]);
	}
//	printf("final i = %d\n", i);
	slice[0].y = i;

	i = 0;
	while (i++ < THREADS)
		pthread_join(threads[i], NULL);
//	printf("joined\n");
//	printf("testing %d\n", parts[1][0]);
	i = 0;
	int y;
	while (++i < slice[0].y)
	{
		y = -1;
//		printf("split %d, size %d\n", i, slice[i].lines);
//		while (++y < slice[i].lines)
//		{
//			printf("[%d]", parts[i][y]);
//			if (y % mlx->width == mlx->width - 1)
//				printf("\n");
//		}
	}
//	i = 0;
	
//	while (++i <= THREADS)
//	{
		/*
		printf("i %d | lines %d size %d\n", i, slice[i].lines, slice[i].size);
		if (!mlx->mlx_img[i])
		{
			mlx->mlx_img[i] = mlx_new_image(mlx->mlx_ptr, mlx->width, slice[i].lines);
			mlx->img_dat[i] = (int*)mlx_get_data_addr(mlx->mlx_img[i], &mlx->bpp, &mlx->size_line,
				&mlx->endian);
		}
	//	fractal_cpy(mlx, mlx->img_dat[i], slice[i].num, slice[i].size);
//		printf("last %d y %d\n", mlx->img_dat[i][slice[i +1].size - 1], y);
		//mlx_string_put(mlx->mlx_ptr, mlx->mlx_win, y, y, 0xff0000, "first");
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->mlx_win, mlx->mlx_img[i], 0, y);
		//mlx_string_put(mlx->mlx_ptr, mlx->mlx_win, 50, y, 0xff0000, "test");
		*/
//		pthread_create(&threads[i], NULL, (void*)fractal_norm, &slice[i]);
//	}
//	i = 0;
//	while (i++ < THREADS)
//		pthread_join(threads[i], NULL);
	
	/*
	if (mlx->rot[0] != ROT_X || mlx->rot[1] != ROT_Y || mlx->rot[2] != ROT_Z)
	{*/
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->mlx_win, mlx->mlx_img[0], 0, 0);
		ft_memdel((void*)&mlx->height_map);
	/*}
	else
	{
		i = 0;
		y = 0;
		while (++i <= THREADS)
		{
			mlx_put_image_to_window(mlx->mlx_ptr, mlx->mlx_win, mlx->mlx_img[i], 0, y);
			y += slice[i].lines;
		}
	}
	*/
	
	
t = clock() - t;
printf("draw() took %f seconds\n", ((double)t)/CLOCKS_PER_SEC);
	mlx_string_put(mlx->mlx_ptr, mlx->mlx_win, 10, 0, 0x00ff00, "Threads");
	mlx_string_put(mlx->mlx_ptr, mlx->mlx_win, 120, 0, 0x00ff00, ft_itoa_base(THREADS, 10));
	mlx_string_put(mlx->mlx_ptr, mlx->mlx_win, 10, 20, 0x0000ff, "Iter");
	mlx_string_put(mlx->mlx_ptr, mlx->mlx_win, 120, 20, 0x0000ff, ft_itoa_base(mlx->iter, 10));
	//pthread_exit(NULL);
}
