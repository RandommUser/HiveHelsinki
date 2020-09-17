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

static double	mandel(int iter, double xs, double ys)
{
	double	x, y, xte;
	int		i;

	i = -1;
	x = 0;
	y = 0;
	while (x * x + y * y <= 4 &&  ++i < iter)
	{
		xte = x * x - y * y + xs;
		y = 2 * x * y + ys;
		x = xte;
	}
	return (i);
}

// mandel
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
	val[1] = frac->y;
	i = 0;
	while (--frac->lines >= 0)
	{
		val[0] = -1;
		while (++val[0] < frac->width)
		{
			frac->num[i++] = mandel(frac->iter, normalize((val[0] - frac->off[0]) * frac->zoom , (double[4]){0, frac->width, MAN_MINX,
			MAN_MAXX}), normalize((val[1] - frac->off[1]) * frac->zoom  , (double[4]){0, frac->height, MAN_MINY, MAN_MAXY}));
		}
		val[1]++;
	}
	frac->lines = frac->size / frac->width;
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
	int				parts[THREADS + 1][(int)(mlx->height / THREADS) *
		mlx->width + THREADS];

	i = 0;
	slice[0].y = 0;
//	printf("width %d height %d threads %d\n", mlx->width, mlx->height, THREADS);
//	printf("split sizes %d\n", (int)(mlx->height / THREADS) * mlx->width + THREADS);
	while (i++ < THREADS)
	{
		parts[i][0] = mlx->height % THREADS - i > 0 ? 1 : 0; // need padding
		slice[i].lines  = ((int)(mlx->height / THREADS) + parts[i][0]);// this block y size
		slice[i].width = mlx->width;
		slice[i].height = mlx->height;
		slice[i].size = slice[i].lines * mlx->width;// save the size
		slice[i].y = slice[0].y; // add to total Y done so far
		slice[0].y += slice[i].lines;
		slice[i].iter = mlx->iter;
		slice[i].thread = i;
		slice[i].zoom = mlx->zoom;
		slice[i].num = parts[i];
		slice[i].off[0] = mlx->offx;
		slice[i].off[1] = mlx->offy;
//		ft_putstr("creating a thread ");
//		ft_putnbr(i);
//		ft_putchar('\n');
//		ft_putpointer(parts[i]);
//		ft_putchar('\n');
//		printf("lines %d\n", slice[i].lines);
		pthread_create(&threads[i], NULL, (void*)fractal1, &slice[i]);
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
	i = 0;
	y = 0;
	mlx_clear_window(mlx->mlx_ptr, mlx->mlx_win);
	while (++i <= THREADS)
	{
		printf("i %d | lines %d size %d\n", i, slice[i].lines, slice[i].size);
		if (!mlx->mlx_img[i])
		{
			mlx->mlx_img[i] = mlx_new_image(mlx->mlx_ptr, mlx->width, slice[i].lines);
			mlx->img_dat[i] = (int*)mlx_get_data_addr(mlx->mlx_img[i], &mlx->bpp, &mlx->size_line,
				&mlx->endian);
		}
		fractal_cpy(mlx, mlx->img_dat[i], slice[i].num, slice[i].size);
//		printf("last %d y %d\n", mlx->img_dat[i][slice[i +1].size - 1], y);
		//mlx_string_put(mlx->mlx_ptr, mlx->mlx_win, y, y, 0xff0000, "first");
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->mlx_win, mlx->mlx_img[i], 0, y);
		//mlx_string_put(mlx->mlx_ptr, mlx->mlx_win, 50, y, 0xff0000, "test");
		y += slice[i].lines;
	}
t = clock() - t;
printf("draw() took %f seconds\n", ((double)t)/CLOCKS_PER_SEC);
	mlx_string_put(mlx->mlx_ptr, mlx->mlx_win, 10, 0, 0x00ff00, "Threads");
	mlx_string_put(mlx->mlx_ptr, mlx->mlx_win, 120, 0, 0x00ff00, ft_itoa_base(THREADS, 10));
	mlx_string_put(mlx->mlx_ptr, mlx->mlx_win, 10, 20, 0x0000ff, "Iter");
	mlx_string_put(mlx->mlx_ptr, mlx->mlx_win, 120, 20, 0x0000ff, ft_itoa_base(mlx->iter, 10));
	//pthread_exit(NULL);
}
