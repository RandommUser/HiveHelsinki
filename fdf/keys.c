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

void	contra(t_mlx *mlx, int key)
{
	static char	contra;

	if (key == 126 && (contra == 0 || contra == 1))
		contra++;
	else if (key == 125 && (contra == 2 || contra == 3))
		contra++;
	else if (key == 123 && (contra == 4 || contra == 6))
		contra++;
	else if (key == 124 && (contra == 5 || contra == 7))
		contra++;
	else if (key == 11 && contra == 8)
		contra++;
	else if (key == 0 && contra == 9)
		contra++;
	else if (key == 36 && contra == 10)
	{
		contra = 0;
		actions1(1, mlx->smap);
		draw_map(mlx);
	}
}

static void	keys3(t_mlx *mlx, int key)
{
	if (key == 20) // map 3
		actions4(1, mlx, 3, 0);
	else if (key == 21) // map 4
		actions4(1, mlx, 4, 0);
	else if (key == 256) // map (fov) limitor
		actions1(2, mlx->smap);
	else if (key == 27) // vanishing point --
		actions2(0, mlx->smap, -1);
	else if (key == 24) // vanishing point ++;
		actions2(0 ,mlx->smap, 1);
	else if (key == 17) // thicc
		actions1(0, mlx->smap);
	else if (key == 2 && mlx->smap->mode != 0)
		mlx->smap->mode = 0;
	else if (key == 2 && mlx->smap->mode == 0)
		mlx->smap->mode = 1;
	else
		return ;
	draw_map(mlx);
}

static void	keys2(t_mlx *mlx, int key)
{
	if (key == 41) // nearP --
		actions5(1, mlx->smap, 0, -1);
	else if (key == 39) // nearP ++
		actions5(1, mlx->smap, 0, 1);
	else if (key == 33) // farP --
		actions5(1, mlx->smap, 1, -1);
	else if (key == 30) // farP ++
		actions5(1, mlx->smap, 1, 1);
	else if (key == 75) // camera plain flip
		actions1(4, mlx->smap);
	else if (key == 15) // reset map
		mlx->mode == 1 ? map0_reset(mlx, mlx->smap) : 
			map_reset(mlx, mlx->smap);
	else if (key == 23) // view mode swap
		view_mode(mlx);
	else if (key == 18) // map 1
		actions4(1, mlx, 1, 0);
	else if (key == 19) // map 2
		actions4(1, mlx, 2, 0);
	else
	{
		keys3(mlx, key);
		return ;
	}
	draw_map(mlx);
}

static void	keys1(t_mlx *mlx, int key)
{
	if (key == 86) // right
		actions3(0, mlx->smap, 1, -1);
	else if (key == 91) // top
		actions3(0, mlx->smap, 0, -1);
	else if (key == 84) // bottom
		actions3(0, mlx->smap, 0, 1);
	else if (key == 92) // c-clockwise
		actions3(0, mlx->smap, 2, 1);
	else if (key == 83) // clockwise
		actions3(0, mlx->smap, 2, -1);
	else if (key == 69) // height +
		actions2(3, mlx->smap, 1.1);
	else if (key == 67) // height flip
		actions2(3, mlx->smap, -1);
	else if (key == 78) // height --
		actions2(3, mlx->smap, 0.9);
	else if (key == 43) // fov ++
		actions2(2, mlx->smap, -1);
	else if (key == 47) // fov --
		actions2(2, mlx->smap, 1);
	else
	{
		keys2(mlx, key);
		return ;
	}
	draw_map(mlx);
}

void	keys(t_mlx *mlx, int key)
{
	if (key == PG_UP) // zoom
		actions2(1, mlx->smap, -1);
	else if (key == PG_DW) // zoom
		actions2(1, mlx->smap, 1);
	else if (key == AR_UP) // move
		actions3(1, mlx->smap, 1, -1);
	else if (key == AR_DW) // move
		actions3(1, mlx->smap, 1, 1);
	else if (key == AR_LF) // move
		actions3(1, mlx->smap, 0, -1);
	else if (key == AR_RG) // move
		actions3(1, mlx->smap, 0, 1);
	else if (key == K_W) // skew or something
		actions3(1, mlx->smap, 2, 1);
	else if (key == K_S) // skew or something
		actions3(1, mlx->smap, 2, -1);
	else if (key == 35) // projection change
		actions1(3, mlx->smap);
	else if (key == 88) // left
		actions3(0, mlx->smap, 1, 1);
	else
	{
		keys1(mlx, key);
		return ;
	}
	draw_map(mlx);
}
