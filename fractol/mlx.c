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

void		mlx_image_wipe(t_mlx *mlx, int img, int width, int height)
{
	int	i;

	width--;
	height--;
	i = -1;
	while (++i <= width * height)
		mlx->img_dat[img][i] = 0;
}

void		mlx_image_create(t_mlx *mlx, int i, int width, int height)
{
	if (!mlx->mlx_img[i])
	{
		mlx->mlx_img[i] = mlx_new_image(mlx->mlx_ptr, width, height);
		if (!mlx->mlx_img[i])
			run_exit(ERR_MLX, "mlx.c mlx_image_create mlx_img alloc error\n");
		mlx->img_dat[i] = (int*)mlx_get_data_addr(mlx->mlx_img[i], &mlx->bpp, &mlx->size_line,
		&mlx->endian);
	}
}

static void	mlx_cast(t_mlx **mlx, char *name, int width, int height)
{
	if (!(*mlx = (t_mlx *)malloc(sizeof(t_mlx))))
		run_exit(ERR_MEMORY, "mlx.c mlx_init malloc(mlx)\n");
	if (!((*mlx)->mlx_ptr = mlx_init()))
		run_exit(ERR_MLX, "mlx.c mlx mlx_init()\n");
	if (!((*mlx)->mlx_win = mlx_new_window((*mlx)->mlx_ptr, width, height,
		name)))
		run_exit(ERR_MLX, "mlx.c mlx line mlx_new_window()\n");
}

t_mlx		*mlx_start(int argc, char **argv)
{
	int		width;
	int		height;
	int		i;
	t_mlx	*mlx;

	width = argc >= 4 ? ft_atoi_base(argv[2], 10) : WIN_WIDTH;
	height = argc >= 4 ? ft_atoi_base(argv[3], 10) : WIN_HEIGHT;
	width = width > MAX_WIDTH ? MAX_WIDTH : width;
	width = width < MIN_WIDTH ? MIN_WIDTH : width;
	height = height > MAX_HEIGHT ? MAX_HEIGHT : height;
	height = height < MIN_HEIGHT ? MIN_HEIGHT : height;
	mlx_cast(&mlx, argv[1], width, height);
	mlx->width = width;
	mlx->height = height;
	mlx->iter = ITER;
	mlx->zoom = 1;
	mlx->offx = 0;
	mlx->offy = 0;
	mlx->rot[0] = ROT_X;
	mlx->rot[1] = ROT_Y;
	mlx->rot[2] = ROT_Z;
	i = -1;
	while (++i <= THREADS)
		mlx->mlx_img[i] = NULL;
	mlx_image_create(mlx, 0, width, height);
	return (mlx);
}
