/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 14:11:25 by phakakos          #+#    #+#             */
/*   Updated: 2020/09/15 14:11:26 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/*
** Set variable to default values
*/

void			mlx_def_value(t_mlx *mlx)
{
	mlx->iter = ITER;
	mlx->anim_iter = ITER;
	mlx->extra = 0;
	mlx->zoom = 1;
	mlx->zo = 0;
	mlx->off.x = 0;
	mlx->off.y = 0;
	mlx->rot[0] = ROT_X;
	mlx->rot[1] = ROT_Y;
	mlx->rot[2] = ROT_Z;
	mlx->jupt = mlx->func == &fractal_jul ? 1 : 0;
	mlx->jur = 0;
	mlx->color[0] = mlx->func == &fractal_barn ? BARN_COLOR : COLOR_START;
	mlx->color[1] = COLOR_END;
	mlx->jul.cx = 0;
	mlx->jul.cy = 0;
	mlx->jul.r = JULIA_MAX_R;
	mlx->jul.n = 0;
	mlx->clr_func = &map_color;
	mlx->colort = 0;
	mlx->verbose = 0;
}

/*
** Create color picker image
*/

static void		mlx_color_create(t_mlx *mlx)
{
	int	width;
	int	height;

	width = 3 * COLOR_WID + 4 * COLOR_OUTL;
	height = 255 + 2 * COLOR_OUTL;
	if (!(mlx->clr_swat = mlx_new_image(mlx->mlx_ptr, width, height)))
		run_exit(ERR_MLX, "mlx.c mlx_color_create clr_swat alloc error\n");
	mlx->clr_dat = (int*)mlx_get_data_addr(mlx->clr_swat, &mlx->bpp,
		&mlx->clr_line, &mlx->endian);
	mlx_image_set(mlx->clr_dat, width, height, COLOR_BG);
}

/*
** Create main mlx image
*/

static void		mlx_image_create(t_mlx *mlx, int width, int height)
{
	if (!(mlx->mlx_img = mlx_new_image(mlx->mlx_ptr, width, height)))
		run_exit(ERR_MLX, "mlx.c mlx_image_create mlx_img alloc error\n");
	if (!(mlx->img_dat = (int*)mlx_get_data_addr(mlx->mlx_img, &mlx->bpp,
		&mlx->size_line, &mlx->endian)))
		run_exit(ERR_MLX, "mlx.c mlx_image_create img_dat alloc error\n");
	mlx_image_set(mlx->img_dat, mlx->width, mlx->height, DEF_BG);
}

/*
** Initiate mlx stuffs, create height_map if needed
** val = width, height, fractal
*/

static t_mlx	*mlx_cast(void *mlx_ptr, char *name, int val[3])
{
	t_mlx	*mlx;

	if (!(mlx = (t_mlx *)malloc(sizeof(t_mlx))))
		run_exit(ERR_MEMORY, "mlx.c mlx_init malloc(mlx)\n");
	mlx->mlx_ptr = mlx_ptr;
	if (!(mlx->mlx_win = mlx_new_window(mlx->mlx_ptr, val[0], val[1],
		name)))
		run_exit(ERR_MLX, "mlx.c mlx line mlx_new_window()\n");
	mlx->func = val[2] == 1 ? &fractal_man : NULL;
	mlx->func = val[2] == 2 ? &fractal_jul : mlx->func;
	mlx->func = val[2] == 3 ? &fractal_barn : mlx->func;
	mlx->func = val[2] == 4 ? &fractal_mult : mlx->func;
	mlx->height_map = NULL;
	if (val[2] != 3)
		if (!(mlx->height_map = (long double*)malloc(
			sizeof(long double) * (val[0] * val[1]))))
			run_exit(ERR_MEMORY, "mlx.c mlx_cast height_map casting failed\n");
	mlx->width = val[0];
	mlx->height = val[1];
	mlx_def_value(mlx);
	mlx_color_create(mlx);
	mlx_image_create(mlx, mlx->width, mlx->height);
	return (mlx);
}

/*
** Create t_mlx
** arr[] = argc, i
*/

t_mlx			*mlx_start(int arr[2], char **argv, void *mlx_ptr, int *windows)
{
	int		width;
	int		height;
	int		y;
	t_mlx	*mlx;

	y = !ft_strcmp(argv[arr[1]], NAME_MAN) ? 1 : 0;
	y = !ft_strcmp(argv[arr[1]], NAME_JULIA) ? 2 : y;
	y = !ft_strcmp(argv[arr[1]], NAME_BARN) ? 3 : y;
	y = !ft_strcmp(argv[arr[1]], NAME_MULT) ? 4 : y;
	if (arr[1] + 1 < arr[0] && ft_strcont(argv[arr[1] + 1], "0123456789"))
		height = ft_atoi_base(argv[arr[1] + 1], 10);
	else
	{
		height = y == 1 ? MAN_HEIGHT : 0;
		height = y == 2 ? JULIA_HEIGHT : height;
		height = y == 3 ? BARN_HEIGHT : height;
		height = y == 4 ? MULT_HEIGHT : height;
	}
	height = height > MAX_HEIGHT ? MAX_HEIGHT : height;
	height = height < MIN_HEIGHT ? MIN_HEIGHT : height;
	width = y == 1 || y == 4 ? height * 1.75 : height;
	mlx = mlx_cast(mlx_ptr, argv[arr[1]], (int[3]){width, height, y});
	mlx->windows = windows;
	return (mlx);
}
