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

static int		input(int key, void *param)
{
	t_mlx		*mlx;

	mlx = param;
	if (mlx->verbose)
	{
		ft_putstr("pressed ");
		ft_putnbr(key);
		ft_putstr("\n");
	}
	if (key == ESC_KEY)
		exit(ESC_EXIT);
	contra(mlx, key);
	keys(mlx, key);
	return (0);
}

/*
** mouse loop
** map select | map origin move | zoom++ | zoom--
*/

static int		mouse(int button, int x, int y, void *param)
{
	t_mlx		*mlx;

	mlx = param;
	if (mlx->verbose)
	{
		ft_putstr("pressed ");
		ft_putnbr(button);
		ft_putstr(" at x ");
		ft_putnbr(x);
		ft_putstr(" y ");
		ft_putnbr(y);
		ft_putchar('\n');
	}
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
	return (0);
}

/*
** main helper
*/

static t_mlx	*cont_init(int width, int height, char *title)
{
	t_mlx	*rtn;

	if (!(rtn = (t_mlx *)malloc(sizeof(t_mlx))))
		mexit(ERR_MEMORY);
	rtn->width = width;
	rtn->height = height;
	rtn->title = title;
	if (!(rtn->mlx_ptr = mlx_init()))
		mexit(ERR_MLX);
	if (!(rtn->mlx_win = mlx_new_window(rtn->mlx_ptr, width, height, title)))
		mexit(ERR_MLX);
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

static void		mlx_startup(int argc, char **argv, t_mlx **mlx)
{
	int	width;
	int	height;

	width = WIN_WIDTH;
	height = WIN_HEIGHT;
	if (argc >= 4)
	{
		width = ft_atoi_base(argv[2], 10);
		height = ft_atoi_base(argv[3], 10);
		width = width > MAX_WIDTH ? MAX_WIDTH : width;
		width = width < MIN_WIDTH ? MIN_WIDTH : width;
		height = height > MAX_HEIGHT ? MAX_HEIGHT : height;
		height = height < MIN_HEIGHT ? MIN_HEIGHT : height;
	}
	mlx[0] = cont_init(width, height, argv[1]);
	mlx[0]->verbose = argc == 5 && ft_strcmp(argv[4], "true") == 0 ? 1 : 0;
	mlx_key_hook(mlx[0]->mlx_win, input, *mlx);
	mlx_mouse_hook(mlx[0]->mlx_win, mouse, *mlx);
	mlx[0]->mlx_img = NULL;
	if (!map_reader(mlx[0], argv[1], &mlx[0]->map[0]))
		mexit(ERR_MAP);
}

int				main(int argc, char **argv)
{
	t_mlx	*mlx;

	if (argc < 2 || argc > 5)
	{
		ft_putendl("usage: ./fdf [map.fdf] (width) (height) {verbose 'true'}");
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
