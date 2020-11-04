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

/*
** Exit function
*/

void		run_exit(int code, char *spot)
{
	if (!code)
		exit(0);
	if (code == USAGE)
		ft_putstr("usage: ./fractol "
			NAMES" (height)\n");
	else if (code == ERR_THREAD_VAL)
		ft_putstr("Invalid THREAD value. Min 1, max 8, int only\n");
	else if (code == ERR_PARA)
	{
		ft_putstr("Too many parameters, max is ");
		ft_putnbr(WINDOWS);
		ft_putchar('\n');
	}
	else
		ft_putstr(spot);
	exit(code);
}

/*
** Validate args
*/

static int	valid_params(int argc, char **argv)
{
	int	i;
	int	frac;
	int	name;

	i = 0;
	name = 0;
	frac = 0;
	while (++i < argc)
	{
		if (!ft_strcmp(argv[i], NAME_MAN) || !ft_strcmp(argv[i], NAME_JULIA) ||
			!ft_strcmp(argv[i], NAME_BARN) || !ft_strcmp(argv[i], NAME_MULT))
		{
			name = 1;
			frac++;
		}
		else if (name && ft_strcont(argv[i], "0123456789"))
			name = 0;
		else
			run_exit(USAGE, "main.c valid_params\n");
	}
	return (frac);
}

/*
** Initiate mlx loops
*/

static void	mlx_tloops(t_mlx *mlx)
{
	mlx_key_hook(mlx->mlx_win, input, mlx);
	mlx_mouse_hook(mlx->mlx_win, mouse, mlx);
	mlx_hook(mlx->mlx_win, 6, 0, mouse_live, mlx);
	mlx_hook(mlx->mlx_win, 17, 0, window_close, mlx);
	mlx_loop_hook(mlx->mlx_ptr, iter_anim, mlx->mlxs);
	draw(mlx);
}

/*
** Main func
** Test args, create windows
*/

int			main(int argc, char **argv)
{
	int			windows;
	int			i;
	t_mlx		*mlxs[WINDOWS + 1];
	void		*mlx_ptr;

	if (argc < 2)
		run_exit(USAGE, "main.c main() arg amount\n");
	else if (THREADS < 0 || THREADS > 8 || THREADS != (int)THREADS)
		run_exit(ERR_THREAD_VAL, "main main() THREAD check\n");
	if ((windows = valid_params(argc, argv)) > WINDOWS)
		run_exit(ERR_PARA, "main.c main() too many fractals\n");
	if (!(mlx_ptr = mlx_init()))
		run_exit(ERR_MLX, "main main() mlx_init failed\n");
	i = 0;
	while (i + 1 < argc)
	{
		mlxs[i] = mlx_start((int[2]){argc, i + 1}, argv, mlx_ptr, &windows);
		mlxs[i]->mlxs = mlxs;
		mlx_tloops(mlxs[i]);
		i += i + 2 < argc && ft_strcont(argv[i + 2], "0123456789") ? 2 : 1;
	}
	mlxs[i] = NULL;
	mlx_loop(mlx_ptr);
	return (0);
}
