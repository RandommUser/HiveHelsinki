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

static int		mouse_live(int x, int y, void *param)
{
	t_mlx	*mlx;

	mlx = param;

	if (!(x >= 0 && x < mlx->width && y >= 0 && y < mlx->height))
		return (-1);
	if (mlx->jupt)
	{
		printf("x %d y %d\n", x, y);
		if (!mlx->jur)
		{
			mlx->mouse_pos[0] = x;
			mlx->mouse_pos[1] = y;
		}
		else
		{
			mlx->jul[2] = normalize(x, (double[4]){0, mlx->width, 1, sqrt(JULIA_MAX_R)});
			mlx->jul[2] *= normalize(y, (double[4]){0, mlx->height, 1, sqrt(JULIA_MAX_R)});
		}

		mlx->jul[0] = normalize(mlx->mouse_pos[0] - mlx->width / 2, (double[4]){-(mlx->width / 2), mlx->width / 2, -(mlx->jul[2]), mlx->jul[2]});
		mlx->jul[1] = normalize(mlx->mouse_pos[1] - mlx->height / 2, (double[4]){-(mlx->height / 2), mlx->height / 2, -(mlx->jul[2]), mlx->jul[2]});
		draw(mlx);
		printf("n %f r %f cx %f cy %f\n", mlx->jul[3], mlx->jul[2], mlx->jul[0], mlx->jul[1]);
	}
	else
	{
		draw(mlx);
	}
	
	return (0);
}

static int		mouse(int button, int x, int y, void *param)
{
	t_mlx		*mlx;

	mlx = param;
	mlx_image_wipe(mlx, 0, mlx->width, mlx->height);
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
	{
		mlx->offx += (int)(mlx->width / 2 - x) * mlx->zoom;
		mlx->offy += (int)(mlx->height / 2 - y) * mlx->zoom;
		draw(mlx);
		printf("offx %f offy %f\n", mlx->offx, mlx->offy);
	}
	if (button == MOU_R)
	{
		mlx->offx = (x - mlx->width / 2) * mlx->zoom;
		mlx->offy = (y - mlx->height / 2) * mlx->zoom;
		draw(mlx);
		printf("offx %f offy %f\n", mlx->offx, mlx->offy);
	}
	if (button == MOU_S_U)
	{
		mlx->offx += (mlx->width / 2 - x) * mlx->zoom;
		mlx->offy += (mlx->height / 2 - y) * mlx->zoom;
		mlx->zoom = mlx->zoom < 0.1 ? mlx->zoom * 10 : mlx->zoom + 0.1;
		draw(mlx);
		printf("zoom %f offx %f off y %f\n", mlx->zoom, mlx->offx, mlx->offy);
	}
	if (button == MOU_S_D)
	{
		mlx->offx += (mlx->width / 2 - x) * mlx->zoom;
		mlx->offy += (mlx->height / 2 - y) * mlx->zoom;
		mlx->zoom = mlx->zoom < 0.2 ? mlx->zoom / 10 : mlx->zoom - 0.1;
		draw(mlx);
		printf("zoom %f offx %f off y %f\n", mlx->zoom, mlx->offx, mlx->offy);
	}

	mlx_pixel_put(mlx->mlx_ptr, mlx->mlx_win, mlx->width / 2 - 2, mlx->height /2, 0xffffff);
	mlx_pixel_put(mlx->mlx_ptr, mlx->mlx_win, mlx->width / 2 - 1, mlx->height /2, 0xffffff);
	mlx_pixel_put(mlx->mlx_ptr, mlx->mlx_win, mlx->width / 2, mlx->height /2, 0xffffff);
	mlx_pixel_put(mlx->mlx_ptr, mlx->mlx_win, mlx->width / 2 + 1, mlx->height /2, 0xffffff);
	mlx_pixel_put(mlx->mlx_ptr, mlx->mlx_win, mlx->width / 2 + 2, mlx->height /2, 0xffffff);
	mlx_pixel_put(mlx->mlx_ptr, mlx->mlx_win, mlx->width / 2, mlx->height /2 - 2, 0xffffff);
	mlx_pixel_put(mlx->mlx_ptr, mlx->mlx_win, mlx->width / 2, mlx->height /2 - 1, 0xffffff);
	mlx_pixel_put(mlx->mlx_ptr, mlx->mlx_win, mlx->width / 2, mlx->height /2 + 1, 0xffffff);
	mlx_pixel_put(mlx->mlx_ptr, mlx->mlx_win, mlx->width / 2, mlx->height /2 + 2, 0xffffff);
	return (0);
}

static int		input(int key, void *param)
{
	t_mlx	*mlx;

	printf("key %d\n", key);
	mlx = param;
	mlx_image_wipe(mlx, 0, mlx->width, mlx->height);
	if (key == ESC_KEY)
		run_exit(0, "");
	if (key == K_ENT)
		draw(mlx);
	if (key == K_R)
	{
		mlx->iter = ITER;
		mlx->offx = 0;
		mlx->offy = 0;
		mlx->zoom = 1;
		mlx->rot[0] = ROT_X;
		mlx->rot[1] = ROT_Y;
		mlx->rot[2] = ROT_Z;
		draw(mlx);
	}
	if (key == NUM_P)
	{
		mlx->iter += 50;
		mlx->iter = mlx->iter > MAX_ITER ? MAX_ITER : mlx->iter;
		draw(mlx);
		printf("iter++ %d\n", mlx->iter);
	}
	if (key == NUM_M)
	{
		mlx->iter -= 50;
		mlx->iter = mlx->iter <= 0 ? MIN_ITER : mlx->iter;
		draw(mlx);
		printf("iter-- %d\n", mlx->iter);
	}
	if (key == PG_UP)
	{
		mlx->zoom = mlx->zoom < 0.1 ? mlx->zoom * 2 : mlx->zoom + 0.1;
		draw(mlx);
		printf("zoom++ %f\n", mlx->zoom);
	}
	if (key == PG_DW)
	{
		mlx->zoom = mlx->zoom < 0.2 ? mlx->zoom / 2 : mlx->zoom - 0.1;
		//mlx->zoom = mlx->zoom < 0.000001 ? mlx->zoom = 0.000001 : mlx->zoom; // make it not reach 0 | not needed(?)
		draw(mlx);
		printf("zoom-- %f\n", mlx->zoom);
	}
	if (key == AR_DW)
	{
		mlx->offy += 5 * mlx->zoom;
		draw(mlx);
		printf("offy++ %f\n", mlx->offy);
	}
	if (key == AR_UP)
	{
		mlx->offy -= 5 * mlx->zoom;
		draw(mlx);
		printf("offy-- %f\n", mlx->offy);
	}
	if (key == AR_RG)
	{
		mlx->offx += 5 * mlx->zoom;
		draw(mlx);
		printf("offx++ %f\n", mlx->offx);
	}
	if (key == AR_LF)
	{
		mlx->offx -= 5 * mlx->zoom;
		draw(mlx);
		printf("offx-- %f\n", mlx->offx);
	}


	if (key == NUM_4)
	{
		mlx->rot[1] += ROTA_STEP;
		mlx->rot[1] -= mlx->rot[1] >= 360 ? 360 : 0;
		draw(mlx);
	}
	if (key == NUM_6)
	{
		mlx->rot[1] -= ROTA_STEP;
		mlx->rot[1] += mlx->rot[1] <= -360 ? 360 : 0;
		draw(mlx);
	}
	if (key == NUM_2)
	{
		mlx->rot[0] += ROTA_STEP;
		mlx->rot[0] -= mlx->rot[0] >= 360 ? 360 : 0;
		draw(mlx);
	}
	if (key == NUM_8)
	{
		mlx->rot[0] -= ROTA_STEP;
		mlx->rot[0] += mlx->rot[0] <= -360 ? 360 : 0;
		draw(mlx);
	}
	if (key == NUM_9)
	{
		mlx->rot[2] += ROTA_STEP;
		mlx->rot[2] -= mlx->rot[2] >= 360 ? 360 : 0;
		draw(mlx);
	}
	if (key == NUM_1)
	{
		mlx->rot[2] -= ROTA_STEP;
		mlx->rot[2] += mlx->rot[2] <= -360 ? 360 : 0;
		draw(mlx);
	}
	if (key == K_SPB)
		mlx->jupt = mlx->jupt ? 0 : 1;
	if (key == K_LCN)
		mlx->jur = mlx->jur ? 0 : 1;
	if (key == K_COM)
	{
		mlx->jul[3] -= 2;
		draw(mlx);
	}
	if (key == K_DOT)
	{
		mlx->jul[3] += 2;
		draw(mlx);
	}
	return (0);
}

int	main(int argc, char ** argv)
{
	t_mlx	*mlx;

	if (argc < 2)
		run_exit(USAGE, "main.c main() arg amount\n");
	else if (THREADS < 0 || THREADS > 64 || THREADS != (int)THREADS)
		run_exit(ERR_THREAD_VAL, "main main() THREAD check\n");
	mlx = mlx_start(argc, argv);
	mlx_key_hook(mlx->mlx_win, input, mlx);
	mlx_mouse_hook(mlx->mlx_win, mouse, mlx);
	mlx_hook(mlx->mlx_win, 6, 0 , mouse_live, mlx);
	mlx_loop(mlx->mlx_ptr);
	return (0);
}