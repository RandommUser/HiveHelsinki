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

static double	mandel(double xs, double ys)
{
	double	x, y, xte;
	int		i;

	i = -1;
	x = 0;
	y = 0;
	while (x * x + y * y <= 4 &&  ++i < ITER)
	{
		xte = x * x - y * y + xs;
		y = 2 * x * y + ys;
		x = xte;
	}
	return (i);
}

// mandel
void	fractal1(void *arr)//double **arr)
{
	int	val[4]; // x, y, width, height
	//int	x;
	//int	y;
	int	size, i, thread;
	//int	width;
	int		*num;

	//ft_putpointer(arr);
	//ft_putchar('\n');
	num = (int*)arr;
	ft_putstr("thread start ");
	thread = num[6];
	ft_putnbr(thread);
	ft_putchar('\n');
	val[2] = num[0];
	val[3] = num[1];
	size = num[3];
	val[1] = num[2];
	i = 0;
	while (--size >= 0)
	{
		val[0] = -1;
		while (++val[0] < val[2])
		{
			num[i++] = mandel(normalize(val[0], (double[4]){0, val[2], MAN_MINX,
			MAN_MAXX}), normalize(val[1], (double[4]){0, val[3], MAN_MINY, MAN_MAXY}));
		}
		val[1]++;
	}
	ft_putstr("thread end ");
	ft_putnbr(thread);
	ft_putchar('\n');
	printf("[0] = %d\n", num[0]);
	//pthread_exit(NULL);
}

void	draw(t_mlx *mlx)
{
	pthread_t		threads[THREADS + 1];
	int				i;
	int				parts[THREADS + 1][(int)(mlx->height / THREADS) *
		mlx->width + THREADS];

	i = 0;
	parts[0][0] = 0;
	printf("width %d height %d threads %d\n", mlx->width, mlx->height, THREADS);
	printf("split sizes %d\n", (int)(mlx->height / THREADS) * mlx->width + THREADS);
	while (i++ < THREADS)
	{
		parts[i][0] = mlx->height % THREADS - i > 0 ? 1 : 0; // need padding
		parts[i][3] = ((int)(mlx->height / THREADS) + parts[i][0]); // this block y size
		parts[i][0] = mlx->width;
		parts[i][1] = mlx->height;
		parts[0][i] = parts[i][3] * mlx->width; // save the size
		parts[i][2] = parts[0][0]; // add to total Y done so far
		parts[0][0] += parts[i][3];
		parts[i][6] = i;
		ft_putendl("creating a thread");
		ft_putpointer(parts[i]);
		ft_putchar('\n');
		printf("%d\n", parts[i][0]);
		pthread_create(&threads[i], NULL, (void*)fractal1, &parts[i]);
	}
	printf("final i = %d\n", i);
	parts[0][0] = i;

	i = 0;
	while (i++ < THREADS)
		pthread_join(threads[i], NULL);
	printf("joined\n");
	printf("testing %d\n", parts[1][0]);
	i = 0;
	int y;
	while (++i < parts[0][0])
	{
		y = -1;
		printf("split %d, size %d\n", i, parts[0][i]);
		while (++y < parts[0][i])
		{
			//printf("[%d]", parts[i][y]);
			//if (y % mlx->width == mlx->width - 1)
			//	printf("\n");
		}
	}
	i = -1;
	y = 0;
	mlx_clear_window(mlx->mlx_ptr, mlx->mlx_win);
	while (++i < THREADS)
	{
		printf("y size %d size %d\n", parts[0][i + 1] / mlx->width, parts[0][i + 1]);
		if (!mlx->mlx_img[i])
		{
			mlx->mlx_img[i] = mlx_new_image(mlx->mlx_ptr, mlx->width, parts[0][i + 1] / mlx->width);
			mlx->img_dat[i] = (int*)mlx_get_data_addr(mlx->mlx_img[i], &mlx->bpp, &mlx->size_line,
				&mlx->endian);
		}
		fractal_cpy(mlx, mlx->img_dat[i], parts[i + 1], parts[0][i + 1]);
		printf("last %d y %d\n", mlx->img_dat[i][parts[0][i + 1] - 1], y);
		mlx_string_put(mlx->mlx_ptr, mlx->mlx_win, y, y, 0xff0000, "first");
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->mlx_win, mlx->mlx_img[i], 0, y);
		mlx_string_put(mlx->mlx_ptr, mlx->mlx_win, 50, y, 0xff0000, "test");
		y += parts[0][i + 1] / mlx->width;
	}
	
	
	//pthread_exit(NULL);
}
