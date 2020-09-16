/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 13:28:38 by phakakos          #+#    #+#             */
/*   Updated: 2020/09/15 13:28:39 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	run_exit(int code, char *spot)
{
	if (!code)
		exit(0);
	if (code == USAGE)
		ft_putstr("usage: ./fractol map (width height)\n");
	else if (code == ERR_THREAD_VAL)
		ft_putstr("Invalid THREAD value. Min 1, max 8, int only\n");
	ft_putstr(spot);
	exit(code);
}

static int		input(int key, void *param)
{
	t_mlx	*mlx;

	mlx = param;
	if (key == ESC_KEY)
		run_exit(0, "");
	if (key == NUM_1)
		draw(mlx);
	if (key == K_R)
		mlx_clear_window(mlx->mlx_ptr, mlx->mlx_win);
	return (0);
}

int	main(int argc, char ** argv)
{
	t_mlx	*mlx;

	if (argc < 2)
		run_exit(USAGE, "main.c main() arg amount\n");
	else if (THREADS < 0 || THREADS > 16 || THREADS != (int)THREADS)
		run_exit(ERR_THREAD_VAL, "main main() THREAD check\n");
	mlx = mlx_start(argc, argv);
	mlx_key_hook(mlx->mlx_win, input, mlx);
	
	mlx_loop(mlx->mlx_ptr);
	return (0);
}