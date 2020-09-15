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

static void	mlx_cast(t_mlx **mlx, char *name, int width, int height)
{
	if (!(*mlx = (t_mlx *)malloc(sizeof(t_mlx))))
		run_exit(ERR_MEMORY, "mlx.c mlx_init malloc(mlx)\n");
	if (!((*mlx)->mlx_ptr = mlx_init()))
		run_exit(ERR_MLX, "mlx.c mlx mlx_init()\n");
	if (!((*mlx)->mlx_win = mlx_new_window((*mlx)->mlx_ptr, width, height, name)))
		run_exit(ERR_MLX, "mlx.c mlx line mlx_new_window()\n");
}

t_mlx	*mlx_start(int argc, char **argv)
{
	int		width;
	int		height;
	t_mlx	*mlx;

	width = argc >= 4 ? ft_atoi_base(argv[2], 10) : WIN_WIDTH;
	height = argc >= 4 ? ft_atoi_base(argv[3], 10): WIN_HEIGHT;
	width = width > MAX_WIDTH ? MAX_WIDTH : width;
	width = width < MIN_WIDTH ? MIN_WIDTH : width;
	height = height > MAX_HEIGHT ? MAX_HEIGHT : height;
	height = height < MIN_HEIGHT ? MIN_HEIGHT : height;
	mlx_cast(&mlx, argv[1], width, height);
	mlx->width = width;
	mlx->height = height;
	mlx->mlx_img = NULL;
	return (mlx);
}
