/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 11:07:16 by phakakos          #+#    #+#             */
/*   Updated: 2020/09/16 11:07:17 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	aim_rec(t_mlx *mlx)
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

void	height_reset(double *arr, double val, int width, int height)
{
	int	i;

	width--;
	height--;
	i = -1;
	while (++i <= width * height)
		arr[i] = val;
}

void	fractal_cpy(t_mlx *mlx, int *img_dat, int *arr, size_t n)
{
	size_t	i;

	i = -1;
	while (++i < n)
	{
		img_dat[i] = mlx_get_color_value(mlx->mlx_ptr, (int)normalize(mlx->iter - arr[i], (double[4]){0, mlx->iter, 0x000000, 0xff0000}));
	//printf("[%d]", img_dat[i]);
	}
	//printf("\n");
}
/*
void	fractal_norm(void *param)
{
	int		i;
	t_frac	*frac;

	i = -1;
	frac = param;
	while (++i < frac->size)
	{
		frac->num[i] = mlx_get_color_value(frac->mlx->mlx_ptr, (int)normalize(frac->mlx->iter - frac->num[i], (double[4]){0, frac->mlx->iter, 0x000000, 0xff0000}));
	}
}
*/
double	normalize(double p, double arr[4])
{
	p = (p - arr[0])/(arr[1] - arr[0]);
	p = (arr[3] - arr[2]) * p + arr[2];
	return (p);
}
