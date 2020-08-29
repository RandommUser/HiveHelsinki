/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:20:20 by phakakos          #+#    #+#             */
/*   Updated: 2020/06/02 15:10:20 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/*
** key loop
*/

int	input(int key, void *param)
{
	t_mlx		*mlx;

	mlx = param;
	if (key == ESC_KEY)
		exit(0);
	contra(mlx, key);
	keys(mlx, key);
	// TO REMOVE
	ft_putnbr(key);
	ft_putstr("\n");
	if (mlx->smap->mode > 1)
	{
		printf("current rota | x: %f y: %f z: %f zoom: %f\n", mlx->smap->cam.rot.vec[0], mlx->smap->cam.rot.vec[1], mlx->smap->cam.rot.vec[2], mlx->smap->zoom);
		printf("cam x %f y %f z %f\n", mlx->smap->cam.loc.vec[0], mlx->smap->cam.loc.vec[1], mlx->smap->cam.loc.vec[2]);
		printf("nP %f fP %f fov %f\n", mlx->smap->cam.plan.vec[0], mlx->smap->cam.plan.vec[1], mlx->smap->cam.plan.vec[2]);
	}
	else
	{
		printf("current rota | x: %f y: %f z: %f zoom: %f\nheight mod %f\n", mlx->smap->rot.vec[0], mlx->smap->rot.vec[1], mlx->smap->rot.vec[2], mlx->smap->zoom, mlx->smap->h_mod);
		printf("x %f y %f\n", mlx->smap->origin.mat[0][3], mlx->smap->origin.mat[1][3]);
		printf("w %f h %f x %f y %f\n", mlx->smap->pos.vec[0], mlx->smap->pos.vec[1], mlx->smap->pos.vec[2], mlx->smap->pos.vec[3]);
		printf("stuff %f %f %f %f\n",mlx->smap->pos.vec[2] + mlx->smap->pos.vec[0], (mlx->smap->pos.vec[2] + mlx->smap->pos.vec[0]) / 4, mlx->smap->pos.vec[3] + mlx->smap->pos.vec[1], mlx->smap->pos.vec[3] + mlx->smap->pos.vec[1] / 4);
	}
	printf("view mode %d vanishing point %f\n", mlx->mode, mlx->smap->cam.plan.vec[3]);
	if (mlx->mode == 2)
	{
		printf("map 1 %p map 2 %p map 3 %p map 4 %p\n", mlx->map[1], mlx->map[2], mlx->map[3], mlx->map[4]);
		printf("smap %p\n", mlx->smap);
	}
	return (0);
}

/*
** mouse loop
** map select | map origin move | zoom++ | zoom--
*/

int	mouse(int button, int x, int y, void *param)
{
	t_mlx		*mlx;

	mlx = param;
	printf("\npressed %d at x %d y %d\n", button, x, y);
	if (button == MOU_L)
		actions4(0, mlx, x, y);
	else if (button == MOU_R)
		actions5(0, mlx->smap, x, y);
	else if (button == MOU_S_U)
		actions2(1, mlx->smap, 1);
	else if (button == MOU_S_D)
		actions2(1, mlx->smap, -1);
	else
		return (0);
	draw_map(mlx);
	// TO REMOVE
	if (mlx->smap->mode > 1)
	{
		printf("current rota | x: %f y: %f z: %f zoom: %f\n", mlx->smap->cam.rot.vec[0], mlx->smap->cam.rot.vec[1], mlx->smap->cam.rot.vec[2], mlx->smap->zoom);
		printf("cam x %f y %f z %f\n", mlx->smap->cam.loc.vec[0], mlx->smap->cam.loc.vec[1], mlx->smap->cam.loc.vec[2]);
		printf("nP %f fP %f fov %f\n", mlx->smap->cam.plan.vec[0], mlx->smap->cam.plan.vec[1], mlx->smap->cam.plan.vec[2]);
	}
	else
	{
		printf("current rota | x: %f y: %f z: %f zoom: %f\nheight mod %f\n", mlx->smap->rot.vec[0], mlx->smap->rot.vec[1], mlx->smap->rot.vec[2], mlx->smap->zoom, mlx->smap->h_mod);
		printf("x %f y %f\n", mlx->smap->origin.mat[0][3], mlx->smap->origin.mat[1][3]);
		printf("w %f h %f x %f y %f\n", mlx->smap->pos.vec[0], mlx->smap->pos.vec[1], mlx->smap->pos.vec[2], mlx->smap->pos.vec[3]);
		printf("stuff %f %f %f %f\n",mlx->smap->pos.vec[2] + mlx->smap->pos.vec[0], (mlx->smap->pos.vec[2] + mlx->smap->pos.vec[0]) / 4, mlx->smap->pos.vec[3] + mlx->smap->pos.vec[1], mlx->smap->pos.vec[3] + mlx->smap->pos.vec[1] / 4);
	}
	printf("view mode %d vanishing point %f\n", mlx->mode, mlx->smap->cam.plan.vec[3]);
	if (mlx->mode == 2)
	{
		printf("map 1 %p map 2 %p map 3 %p map 4 %p\n", mlx->map[1], mlx->map[2], mlx->map[3], mlx->map[4]);
		printf("smap %p\n", mlx->smap);
	}
	return (0);
}

/*
** main helper
*/

t_mlx	*cont_init(int width, int height, char *title)
{
	t_mlx	*rtn;

	if (!(rtn = (t_mlx *)malloc(sizeof(t_mlx))))
		exit(ERR_MEMORY);
	rtn->width = width;
	rtn->height = height;
	rtn->title = title;
	if (!(rtn->mlx_ptr = mlx_init()))
		exit (ERR_MLX);
	if (!(rtn->mlx_win = mlx_new_window(rtn->mlx_ptr, width, height, title)))
		exit(ERR_MLX);
	rtn->mode = 1;
	rtn->mlx_img = NULL;
	rtn->img_dat = NULL;
	rtn->map[0] = NULL;
	rtn->smap = NULL;
	return (rtn);
}

/*
** main helper
*/

void	mlx_startup(int argc, char **argv, t_mlx **mlx)
{
	if (argc == 4)
		mlx[0] = cont_init(ft_atoi(argv[2]) <= MAX_WIDTH ? ft_atoi(argv[2]) :
		MAX_WIDTH, ft_atoi(argv[3]) <= MAX_HEIGHT ? ft_atoi(argv[3]) :
		MAX_HEIGHT, argv[1]);
	else
		mlx[0] = cont_init(WIN_WIDTH, WIN_HEIGHT, argv[1]);
	mlx_key_hook(mlx[0]->mlx_win, input, *mlx);
	mlx_mouse_hook(mlx[0]->mlx_win, mouse, *mlx);
	if (!(mlx[0]->mlx_img = mlx_new_image(mlx[0]->mlx_ptr, mlx[0]->width, mlx[0]->width))
		|| !(mlx[0]->img_dat = mlx_get_data_addr(mlx[0]->mlx_img, &mlx[0]->bpp,
		&mlx[0]->size_line, &mlx[0]->endian)))
		exit(ERR_MLX);
//	printf("img data %s\n", mlx->img_dat);
//	printf("bpp %d size line %d endian %d\n", mlx->bpp, mlx->size_line, mlx->endian);
	if (!map_reader(mlx[0], argv[1], &mlx[0]->map[0]))
		exit(ERR_MAP);
}

int	main(int argc, char **argv)
{
	t_mlx	*mlx;

	if (argc < 2)
	{
		ft_putendl("usage: ./fdf [map.fdf] (width) (height)");
		return (1);
	}
	else
		mlx_startup(argc, argv, &mlx);
	map_reset(mlx, mlx->map[0]);
	map0_reset(mlx, mlx->map[1]);
	map0_reset(mlx, mlx->map[2]);
	map0_reset(mlx, mlx->map[3]);
	map_reset(mlx, mlx->map[4]);
	draw_map(mlx);
	mlx_loop(mlx->mlx_ptr);
	return (0);
}
