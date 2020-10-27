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

/*
** Render + to the middle of the screen to show middle
*/

static void		aim_rec(t_mlx *mlx)
{
	int	w;
	int h;

	w = mlx->width / 2;
	h = mlx->height / 2;
	mlx_pixel_put(mlx->mlx_ptr, mlx->mlx_win, w - 2, h, 0xffffff);
	mlx_pixel_put(mlx->mlx_ptr, mlx->mlx_win, w - 1, h, 0xffffff);
	mlx_pixel_put(mlx->mlx_ptr, mlx->mlx_win, w, h, 0xffffff);
	mlx_pixel_put(mlx->mlx_ptr, mlx->mlx_win, w + 1, h, 0xffffff);
	mlx_pixel_put(mlx->mlx_ptr, mlx->mlx_win, w + 2, h, 0xffffff);
	mlx_pixel_put(mlx->mlx_ptr, mlx->mlx_win, w, h - 2, 0xffffff);
	mlx_pixel_put(mlx->mlx_ptr, mlx->mlx_win, w, h - 1, 0xffffff);
	mlx_pixel_put(mlx->mlx_ptr, mlx->mlx_win, w, h + 1, 0xffffff);
	mlx_pixel_put(mlx->mlx_ptr, mlx->mlx_win, w, h + 2, 0xffffff);
}

/*
** Write more debug info on the screen
** Render + to the middle of the screen to show middle
*/

static void		draw_debug2(t_mlx *mlx)
{
	char	*print;

	mlx_string_put(mlx->mlx_ptr, mlx->mlx_win, 10, 100, 0xff80ff, "height");
	mlx_string_put(mlx->mlx_ptr, mlx->mlx_win, 120, 100, 0xff80ff,
		(print = ft_itoa_base(mlx->width + mlx->extra * EXTRA * 2, 10)) ?
		print : "ERR");
	free(print);
	mlx_string_put(mlx->mlx_ptr, mlx->mlx_win, 10, 120, 0xff80ff, "width");
	mlx_string_put(mlx->mlx_ptr, mlx->mlx_win, 120, 120, 0xff80ff,
		(print = ft_itoa_base(mlx->height + mlx->extra * EXTRA * 2, 10)) ?
		print : "ERR");
	free(print);
	aim_rec(mlx);
}

/*
** Write debug info on the screen
*/

static void		draw_debug(t_mlx *mlx)
{
	char	*print;

	if (!mlx->verbose)
		return ;
	mlx_string_put(mlx->mlx_ptr, mlx->mlx_win, 10, 0, 0x00ff00, "Threads");
	mlx_string_put(mlx->mlx_ptr, mlx->mlx_win, 120, 0, 0x00ff00,
		(print = ft_itoa_base(THREADS, 10)) ? print : "ERR");
	free(print);
	mlx_string_put(mlx->mlx_ptr, mlx->mlx_win, 10, 20, 0x0000ff, "Iter");
	mlx_string_put(mlx->mlx_ptr, mlx->mlx_win, 120, 20, 0x0000ff,
		(print = ft_itoa_base(mlx->iter, 10)) ? print : "ERR");
	free(print);
	mlx_string_put(mlx->mlx_ptr, mlx->mlx_win, 10, 40, 0x00ffff, "Rot X");
	mlx_string_put(mlx->mlx_ptr, mlx->mlx_win, 120, 40, 0x00ffff,
		(print = ft_itoa_base((int)mlx->rot[0], 10)) ? print : "ERR");
	free(print);
	mlx_string_put(mlx->mlx_ptr, mlx->mlx_win, 10, 60, 0x00ffff, "Rot Y");
	mlx_string_put(mlx->mlx_ptr, mlx->mlx_win, 120, 60, 0x00ffff,
		(print = ft_itoa_base((int)mlx->rot[1], 10)) ? print : "ERR");
	free(print);
	mlx_string_put(mlx->mlx_ptr, mlx->mlx_win, 10, 80, 0x00ffff, "Rot Z");
	mlx_string_put(mlx->mlx_ptr, mlx->mlx_win, 120, 80, 0x00ffff,
		(print = ft_itoa_base((int)mlx->rot[2], 10)) ? print : "ERR");
	free(print);
	draw_debug2(mlx);
}

/*
** Draw() helper
** Set slice variables
*/

static t_frac	slice_ini(t_mlx *mlx, int i, int y)
{
	t_frac	ret;

	ret.mlx = mlx;
	ret.y = ((mlx->height + mlx->extra * EXTRA * 2) % THREADS) - i >= 0 ? 1 : 0;
	ret.lines = ((int)((mlx->height + mlx->extra * EXTRA * 2)
		/ THREADS) + ret.y);
	ret.width = mlx->width;
	ret.height = mlx->height;
	ret.w = mlx->width / 2;
	ret.h = mlx->height / 2;
	ret.y = y;
	ret.iter = mlx->iter;
	ret.zoom = mlx->zoom;
	ret.off = mlx->off;
	return (ret);
}

/*
** Main draw call
** Split into threads
** Screen split into slices horizontally based on the number of threads
** Wait for threads to finish before printing the image
** Call color_show to render color picker, if enabled
** Call draw_debug to render debug stuff
*/

int				draw(t_mlx *mlx)
{
	pthread_t		threads[THREADS];
	t_frac			slice[THREADS];
	int				i;
	int				y;

	mlx_clear_window(mlx->mlx_ptr, mlx->mlx_win);
	if (mlx->height_map)
		height_reset(mlx->height_map, -1000000000000, mlx->width, mlx->height);
	i = -1;
	y = -(mlx->extra) * EXTRA;
	while (++i < THREADS)
	{
		slice[i] = slice_ini(mlx, i + 1, y);
		y += slice[i].lines;
		pthread_create(&threads[i], NULL, (void*)mlx->func, &slice[i]);
	}
	i = -1;
	while (++i < THREADS)
		pthread_join(threads[i], NULL);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->mlx_win, mlx->mlx_img, 0, 0);
	color_show(mlx);
	draw_debug(mlx);
	return (0);
}
