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

void		mlx_image_wipe(t_mlx *mlx, int width, int height)
{
	int	i;

	if (!mlx || !mlx->img_dat)
		return ;
	i = -1;
	while (++i <= width * height)
		mlx->img_dat[i] = DEF_BG;
}

void		mlx_image_set(int *img_dat, int width, int height, int color)
{
	int	i;

	if (!img_dat)
		return ;
	i = -1;
	while (++i <= width * height)
		img_dat[i] = color;
}

void		mlx_color_create(t_mlx *mlx)
{
	int	width;
	int	height;

	if (!mlx->clr_swat)
	{
		width = 3 * COLOR_WID + 4 * COLOR_OUTL;
		height = 255 + 2 * COLOR_OUTL;
		mlx->clr_swat = mlx_new_image(mlx->mlx_ptr, width, height);
		if (!mlx->clr_swat)
			run_exit(ERR_MLX, "mlx.c mlx_color_create clr_swat alloc error\n");
		mlx->clr_dat = (int*)mlx_get_data_addr(mlx->clr_swat, &mlx->bpp, &mlx->clr_line,
		&mlx->endian);
		mlx_image_set(mlx->clr_dat, width, height, COLOR_BG);
	}
}

void		mlx_image_create(t_mlx *mlx, int width, int height)
{
	if (!mlx->mlx_img)
	{
		mlx->mlx_img = mlx_new_image(mlx->mlx_ptr, width, height);
		if (!mlx->mlx_img)
			run_exit(ERR_MLX, "mlx.c mlx_image_create mlx_img alloc error\n");
		mlx->img_dat = (int*)mlx_get_data_addr(mlx->mlx_img, &mlx->bpp, &mlx->size_line,
		&mlx->endian);
		mlx_image_wipe(mlx, width, height);
	}
}
// width, height, fractal
static void	mlx_cast(t_mlx **mlx, void *mlx_ptr, char *name, int val[3])//int width, int height)
{
	if (!(*mlx = (t_mlx *)malloc(sizeof(t_mlx))))
		run_exit(ERR_MEMORY, "mlx.c mlx_init malloc(mlx)\n");
printf("mlx struct initialized for window\n");
	(*mlx)->mlx_ptr = mlx_ptr;
printf("mlx initialized for window\n");
	if (!((*mlx)->mlx_win = mlx_new_window((*mlx)->mlx_ptr, val[0], val[1],
		name)))
		run_exit(ERR_MLX, "mlx.c mlx line mlx_new_window()\n");
printf("mlx window initialized for window\n");
	(*mlx)->func = val[2] == 1 ? &fractal_man : NULL;
	(*mlx)->func = val[2] == 2 ? &fractal_jul : (*mlx)->func;
	(*mlx)->func = val[2] == 3 ? &fractal_barn : (*mlx)->func;
	(*mlx)->func = val[2] == 4 ? &fractal_mult : (*mlx)->func;
}

// argc, i
t_mlx		*mlx_start(int arr[2], char **argv, void *mlx_ptr, int *windows)
{
	int		width;
	int		height;
	int		y;
	t_mlx	*mlx;

	//width = argc >= 4 ? ft_atoi_base(argv[2], 10) : WIN_WIDTH;
	//height = argc >= 4 ? ft_atoi_base(argv[3], 10) : WIN_HEIGHT;
	//width = width > MAX_WIDTH ? MAX_WIDTH : width;
	//width = width < MIN_WIDTH ? MIN_WIDTH : width;
	//height = height > MAX_HEIGHT ? MAX_HEIGHT : height;
	//height = height < MIN_HEIGHT ? MIN_HEIGHT : height;
	y = 0;
	if (!ft_strcmp(argv[arr[1]], NAME_MAN))
		y = 1;//mlx->func = &fractal_man;
	else if (!ft_strcmp(argv[arr[1]], NAME_JULIA))
		y = 2;//mlx->func = &fractal_jul;
	else if (!ft_strcmp(argv[arr[1]], NAME_BARN))
		y = 3;//mlx->func = &fractal_barn;
	else if (!ft_strcmp(argv[arr[1]], NAME_MULT))
		y = 4;
	else
		run_exit(USAGE, "mlx.c mlx_start() invalid fractal name\n");
printf("fractal #%d\n", y);
	if (arr[1] + 1 < arr[0] && ft_strcont(argv[arr[1] + 1], "0123456789"))
		height = ft_atoi(argv[arr[1] + 1]);
	else
	{
		height = y == 1 ? MAN_HEIGHT : 0;
		height = y == 2 ? JULIA_HEIGHT : height;
		height = y == 3 ? BARN_HEIGHT : height;
		height = y == 4 ? MULT_HEIGHT : height;
	}
	height = height > MAX_HEIGHT ? MAX_HEIGHT : height;
	width = y == 1 || y == 4 ? (int)(height * 1.75) : height;
printf("window width %d height %d\n", width, height);
	mlx_cast(&mlx, mlx_ptr, argv[arr[1]], (int[3]){width, height, y});//width, height);
printf("mlx created for window %d\n", arr[1]);
	mlx->width = width;
	mlx->height = height;
printf("mlx size set window %d\n", arr[1]);
	mlx->iter = ITER;
	mlx->zoom = 1;
	mlx->offx = 0;
	mlx->offy = 0;
printf("mlx iter and off for window %d\n", arr[1]);
	mlx->rot[0] = ROT_X;
	mlx->rot[1] = ROT_Y;
	mlx->rot[2] = ROT_Z;
printf("mlx rot for window %d\n", arr[1]);
	mlx->jupt = 0;
	mlx->jur = 0;
	mlx->color[0] = COLOR_START;
	mlx->color[1] = COLOR_END;
	mlx->colort = 0;
	//mlx->jul = (double[4]){0, 0, 1, 1};
	mlx->jul[2] = JULIA_MAX_R;
	mlx->jul[3] = 0;
printf("mlx julia var for window %d\n", arr[1]);
	mlx->windows = windows;
printf("mlx windows *p for window %d\n", arr[1]);
	mlx->mlx_img = NULL;
	mlx->clr_swat = NULL;
	mlx->clr_func = &map_color;
	mlx_color_create(mlx);
	mlx_image_create(mlx, width, height);
printf("mlx_img created for window %d\n", arr[1]);
mlx_print(mlx);
	return (mlx);
}
