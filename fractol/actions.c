/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 16:36:02 by phakakos          #+#    #+#             */
/*   Updated: 2020/10/20 16:36:03 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	zoom(t_mlx *mlx, char c)
{
	if (c == '+')
		mlx->zoom = mlx->zoom < 0.1 ? mlx->zoom * 2 : mlx->zoom * 1.1;//FIX
	else if (c == '-')
		mlx->zoom = mlx->zoom < 0.2 ? mlx->zoom / 2 : mlx->zoom * 0.9;// FIX
	else
		return ; // remove
	printf("zoom%c%c %.30Lf\n", c, c, mlx->zoom);
}
