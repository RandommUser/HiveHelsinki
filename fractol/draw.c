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

void	*fractal1(float **arr)
{

}

void	draw(t_mlx *mlx)
{
	pthread_t		threads[THREADS + 1];
	int				i;
	float			parts[THREADS + 1][(int)(mlx->height / THREADS) *
		mlx->width + THREADS];

	i = 0;
	parts[0][0] = 0;
	while (i++ < THREADS)
	{
		parts[i][0] = mlx->height % THREADS - i > 0 ? 1 : 0; // need padding
		parts[i][0] = ((int)(mlx->height / THREADS) + parts[0][3]); // this block y size
		parts[0][i] = parts[i][0] * mlx->width; // save the size
		parts[i][0] += parts[0][0]; // add to total Y done
		parts[0][0] += parts[i][0];
		pthread_create(&threads[i], NULL, fractal1, parts[i]);
	}
}
