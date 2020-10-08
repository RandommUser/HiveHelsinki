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
		ft_putstr("usage: ./fractol "NAME_MAN"|"NAME_JULIA"|"NAME_BARN" (height)\n");
	else if (code == ERR_THREAD_VAL)
		ft_putstr("Invalid THREAD value. Min 1, max 8, int only\n");
	ft_putstr(spot);
	exit(code);
}

void	close_window(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx_ptr, mlx->mlx_img);
	mlx_destroy_window(mlx->mlx_ptr, mlx->mlx_win);
	(*mlx->windows)--;
	if (!(*mlx->windows))
		run_exit(ESC_EXIT, "main.c close_window() last window\n");
	//ft_memdel((void**)mlx);
	free(mlx);
	mlx = NULL;
	//pthread_exit(NULL);
}

static int		window_close(void *param)
{
	t_mlx	*mlx;

	mlx = param;
	//run_exit(10, "Pressed X\n");
	close_window(mlx);
	return (0);
}

static int		draw_leaf(void *param)
{
	t_mlx	*mlx;

	mlx = param;
	if (mlx->jupt)
		draw(mlx);
	return (0);
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
		//draw(mlx);
	}
	
	return (0);
}

static int		mouse(int button, int x, int y, void *param)
{
	t_mlx		*mlx;
	

	mlx = param;
	mlx_image_wipe(mlx, mlx->width, mlx->height);
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
	/*		MOUSE CLICK COORDINATE "FIX" TESTING
	t_vec4		mous;
	mous = vec4_ini((float[4]){x, y, 0, 1});
	mous.vec[0] -= mlx->width / 2;
	mous.vec[1] -= mlx->height /2;
	mous = mat4_vec4(rot_matrix(mlx->rot), mous);
	mous.vec[0] += mlx->width / 2;
	mous.vec[1] += mlx->height / 2;
	printf("og coords x %d y %d\n", x, y);
	x = mous.vec[0];
	y = mous.vec[1];
	printf("rotated coords x %d y %d\n", x, y);
	*/
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
		mlx->zoom = mlx->zoom < 0.1 ? mlx->zoom * 10 : mlx->zoom * 1.1;//+ 0.1;
		draw(mlx);
		printf("zoom %f offx %f off y %f\n", mlx->zoom, mlx->offx, mlx->offy);
	}
	if (button == MOU_S_D)
	{
		mlx->offx += (mlx->width / 2 - x) * mlx->zoom;
		mlx->offy += (mlx->height / 2 - y) * mlx->zoom;
		mlx->zoom = mlx->zoom < 0.2 ? mlx->zoom / 10 : mlx->zoom * 0.9;//- 0.1;
		draw(mlx);
		printf("zoom %f offx %f off y %f\n", mlx->zoom, mlx->offx, mlx->offy);
	}
	aim_rec(mlx);
	return (0);
}

static int		input(int key, void *param)
{
	t_mlx	*mlx;

	printf("key %d\n", key);
	mlx = param;
	mlx_image_wipe(mlx, mlx->width, mlx->height);
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
		mlx->zoom = mlx->zoom < 0.1 ? mlx->zoom * 2 : mlx->zoom * 1.1;//+ 0.1;
		draw(mlx);
		printf("zoom++ %f\n", mlx->zoom);
	}
	if (key == PG_DW)
	{
		mlx->zoom = mlx->zoom < 0.2 ? mlx->zoom / 2 : mlx->zoom * 0.9;//- 0.1;
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
	printf("rot x %f y %f z %f\n", mlx->rot[0], mlx->rot[1], mlx->rot[2]);
	return (0);
}

int	valid_params(int argc, char **argv)
{
	int	i;
	int	frac;
	int	name;

	i = 0;
	name = 0;
	frac = 0;
	while (++i < argc)
	{
		if (!ft_strcmp(argv[i], NAME_MAN) || !ft_strcmp(argv[i], NAME_JULIA) || !ft_strcmp(argv[i], NAME_BARN))
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
void	mlx_start_loop(void *para)
{
	t_params	*param;
	t_mlx		*mlx;

	param = para;
	printf("going into mlx_start\n");
	mlx = mlx_start(param->argc, param->argv, param->i, param->windows);
	printf("mlx made\n");
	mlx_key_hook(mlx->mlx_win, input, mlx);
	mlx_mouse_hook(mlx->mlx_win, mouse, mlx);
	mlx_hook(mlx->mlx_win, 6, 0 , mouse_live, mlx);
	mlx_hook(mlx->mlx_win, 17, 0 , window_close, mlx);
	mlx_loop(mlx->mlx_ptr);
	printf("created the window\n");
}
*/
void	mlx_tloops(void *para)
{
	t_mlx	*mlx;

	mlx = para;
printf("starting mlx hook %p\n", para);
	mlx_key_hook(mlx->mlx_win, input, mlx);
	mlx_mouse_hook(mlx->mlx_win, mouse, mlx);
	mlx_hook(mlx->mlx_win, 6, 0 , mouse_live, mlx);
	mlx_hook(mlx->mlx_win, 17, 0 , window_close, mlx);
	if (mlx->func == &fractal_barn)
		mlx_loop_hook(mlx->mlx_ptr, draw_leaf, mlx);
printf("action hooks done\n");
//	mlx_loop(mlx->mlx_ptr);
//printf("window loop done\n");
}

void	mlx_print(t_mlx *mlx)
{
	printf("mlx *p %p\n", mlx);
	printf("mlx_ptr %p\n", mlx->mlx_ptr);
	printf("mlx_win %p\n", mlx->mlx_win);
	printf("mlx_img %p\n", mlx->mlx_img);
	printf("img_dat %p\n", mlx->img_dat);
	printf("windows # %p = %d\n", mlx->windows, (*mlx->windows));
}

int	main(int argc, char **argv)
{
	//t_mlx		*mlx;
	int			windows;
	int			i;
//	pthread_t	threads[THREADS];
	t_params	param[THREADS];
	t_mlx		*mlxs[THREADS + 1];
	void		*mlx_ptr;

	if (argc < 2)
		run_exit(USAGE, "main.c main() arg amount\n");
	else if (THREADS < 0 || THREADS > 64 || THREADS != (int)THREADS)
		run_exit(ERR_THREAD_VAL, "main main() THREAD check\n");
	if ((windows = valid_params(argc, argv)) > THREADS)
		run_exit(ERR_PARA, "main.c main() too many fractals\n");
	if (!(mlx_ptr = mlx_init()))
		run_exit(ERR_MLX, "main main() mlx_init failed\n");
	i = 0;
	printf("mlx_ptr %p\n", mlx_ptr);
	while (i + 1 < argc)
	{
		param[i].argc = argc;
		param[i].argv = argv;
		param[i].windows = &windows;
		param[i].i = i + 1;
		printf("new param argc %d argv %s windows %p i %d\n", param[i].argc, param[i].argv[i + 1], param->windows, param->i);
		mlxs[i] = mlx_start((int[2]){argc, i + 1}, argv, mlx_ptr, &windows);
		printf("starting a thread for mlx %p\n", mlxs[i]);
		//mlx_print(mlxs[i]);
		mlx_tloops(mlxs[i]);
		//pthread_create(&threads[i], NULL, (void*)mlx_start_loop, &param[i]);
		//pthread_create(&threads[i], NULL, (void*)mlx_tloops, mlxs[i]);
		i += i + 2 < argc && ft_strcont(argv[i + 2], "0123456789") ? 2 : 1;
	}
	mlxs[i] = NULL;

	mlx_loop(mlx_ptr);
//pthread_join(threads[0], NULL);
	//mlx = mlx_start(argc, argv);
	//mlx_key_hook(mlx->mlx_win, input, mlx);
	//mlx_mouse_hook(mlx->mlx_win, mouse, mlx);
	//mlx_hook(mlx->mlx_win, 6, 0 , mouse_live, mlx);
	//mlx_hook(mlx->mlx_win, 17, 0 , window_close, mlx);
//mlx_loop_hook(mlx->mlx_ptr, draw_leaf, mlx);
	//mlx_loop(mlx->mlx_ptr);
	return (0);
}