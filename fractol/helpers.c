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

void	fractal_cpy(t_mlx *mlx, int *img_dat, int *arr, size_t n)
{
	size_t	i;

	i = -1;
	while (++i < n)
	{
		img_dat[i] = mlx_get_color_value(mlx->mlx_ptr, (int)normalize(ITER - arr[i], (double[4]){0, ITER, 0x000000, 0xff0000}));
	//printf("[%d]", img_dat[i]);
	}
	//printf("\n");
}

double	normalize(double p, double arr[4])
{
	p = (p - arr[0])/(arr[1] - arr[0]);
	p = (arr[3] - arr[2]) * p + arr[2];
	return (p);
}
