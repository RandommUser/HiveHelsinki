/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 17:20:52 by phakakos          #+#    #+#             */
/*   Updated: 2020/08/28 17:20:55 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/*
** SUPER SECRET BONUS
*/

void		contra(t_mlx *mlx, int key)
{
	static char	contra;

	if (key == AR_UP && (contra == 0 || contra == 1))
		contra++;
	else if (key == AR_DW && (contra == 2 || contra == 3))
		contra++;
	else if (key == AR_LF && (contra == 4 || contra == 6))
		contra++;
	else if (key == AR_RG && (contra == 5 || contra == 7))
		contra++;
	else if (key == K_B && contra == 8)
		contra++;
	else if (key == K_A && contra == 9)
		contra++;
	else if (key == K_ENT && contra == 10)
	{
		contra = 0;
		actions1(1, mlx->smap);
		draw_map(mlx);
	}
}

/*
**  map select (2-4) | limitor toggle | vanishing point-- | vanishing point++
**  thick lines toggle | depth coloring toggle
*/

static void	keys3(t_mlx *mlx, int key)
{
	if (key == K_2)
		actions4(1, mlx, 2, 0);
	else if (key == K_3)
		actions4(1, mlx, 3, 0);
	else if (key == K_4)
		actions4(1, mlx, 4, 0);
	else if (key == K_LCN)
		actions1(2, mlx->smap);
	else if (key == K_MI)
		actions2(0, mlx->smap, -1);
	else if (key == K_PL)
		actions2(0, mlx->smap, 1);
	else if (key == K_T)
		actions1(0, mlx->smap);
	else if (key == K_TAB)
		actions1(4, mlx->smap);
	else
		return ;
	draw_map(mlx);
}

/*
**  fov++ | fov-- | near plain-- | near plain++ | far plain++ | far plain--
**  map reset | view mode toggle | map select (1)
*/

static void	keys2(t_mlx *mlx, int key)
{
	if (key == K_DOT)
		actions2(2, mlx->smap, 1);
	else if (key == K_COM)
		actions2(2, mlx->smap, -1);
	else if (key == K_COL)
		actions5(1, mlx->smap, 0, -1);
	else if (key == K_QUO)
		actions5(1, mlx->smap, 0, 1);
	else if (key == K_SBS)
		actions5(1, mlx->smap, 1, -1);
	else if (key == K_SBC)
		actions5(1, mlx->smap, 1, 1);
	else if (key == K_R)
		mlx->mode == 1 ? map0_reset(mlx, mlx->smap) :
			map_reset(mlx, mlx->smap);
	else if (key == K_5)
		view_mode(mlx);
	else if (key == K_1)
		actions4(1, mlx, 1, 0);
	else
	{
		keys3(mlx, key);
		return ;
	}
	draw_map(mlx);
}

/*
**  rotate left (y-axis) | rotate right (y-axis) | rotate top (x-axis)
**  rotate bottom (x-axis) | rotate clockwise (z-axis)
** 	rotate cclockwise (z-axis) | height++ | height--
*/

static void	keys1(t_mlx *mlx, int key)
{
	if (key == NUM_4)
		actions3(0, mlx->smap, 1, 1);
	else if (key == NUM_6)
		actions3(0, mlx->smap, 1, -1);
	else if (key == NUM_8)
		actions3(0, mlx->smap, 0, -1);
	else if (key == NUM_2)
		actions3(0, mlx->smap, 0, 1);
	else if (key == NUM_9)
		actions3(0, mlx->smap, 2, 1);
	else if (key == NUM_1)
		actions3(0, mlx->smap, 2, -1);
	else if (key == NUM_P)
		actions2(3, mlx->smap, 1.1);
	else if (key == NUM_A)
		actions2(3, mlx->smap, -1);
	else if (key == NUM_M)
		actions2(3, mlx->smap, 0.9);
	else
	{
		keys2(mlx, key);
		return ;
	}
	draw_map(mlx);
}

/*
**  zoom-- | zoom++ | move up | move down | move left | move right
**  skew left | skew right | projection change
*/

void		keys(t_mlx *mlx, int key)
{
	if (key == PG_DW)
		actions2(1, mlx->smap, -1);
	else if (key == PG_UP)
		actions2(1, mlx->smap, 1);
	else if (key == AR_UP)
		actions3(1, mlx->smap, 1, -1);
	else if (key == AR_DW)
		actions3(1, mlx->smap, 1, 1);
	else if (key == AR_LF)
		actions3(1, mlx->smap, 0, -1);
	else if (key == AR_RG)
		actions3(1, mlx->smap, 0, 1);
	else if (key == K_W)
		actions3(1, mlx->smap, 2, 1);
	else if (key == K_S)
		actions3(1, mlx->smap, 2, -1);
	else if (key == K_P)
		actions1(3, mlx->smap);
	else
	{
		keys1(mlx, key);
		return ;
	}
	draw_map(mlx);
}
