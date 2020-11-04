/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 13:41:24 by phakakos          #+#    #+#             */
/*   Updated: 2020/10/20 13:41:27 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/*
** Barnsley
*/

void		fractal_barn(void *para)
{
	t_ddot	dot;
	int		i;
	t_frac	*frac;
	t_vec4	point;

	frac = para;
	i = -1;
	dot.x = 0;
	dot.y = 0;
	while (++i < frac->iter * 100)
	{
		point = vec4_ini((long double[4]){map(dot.x, (long double[4])
			{BARN_X_MIN, BARN_X_MAX, -(frac->w), frac->w}),
		map(dot.y, (long double[4]){BARN_Y_MIN, BARN_Y_MAX,
			-(frac->h), frac->h}), 0, 1});
		point = mat4_vec4(rot_matrix(frac->mlx->rot), point);
		point.vec[0] = (point.vec[0] + frac->off.x) / frac->zoom + frac->w;
		point.vec[1] = (point.vec[1] + frac->off.y) / frac->zoom + frac->h;
		point.vec[3] = mlx_get_color_value(frac->mlx->mlx_ptr,
			frac->mlx->color[0]);
		to_image(frac->mlx, point);
		dot = barnsley(dot);
	}
}

/*
** Shared fractal functionality
** Used for Mandel/Multibrot, Julia
*/

static void	fractal_base(t_frac *frac, t_box box, double (*func)(int, t_box))
{
	t_dot	dot;
	t_vec4	point;

	dot.y = frac->y;
	while (--frac->lines >= 0)
	{
		dot.x = -(frac->mlx->extra) * EXTRA - 1;
		while (++dot.x < frac->width + frac->mlx->extra * EXTRA)
		{
			point = vec4_ini((long double[4]){dot.x - frac->w,
				dot.y - frac->h, 0, 1});
			box.x = point.vec[0] * frac->zoom + frac->w - frac->off.x;
			box.y = point.vec[1] * frac->zoom + frac->h - frac->off.y;
			point.vec[2] = func(frac->iter, box);
			point.vec[3] = iter_color(frac, point);
			point.vec[0] = dot.x;
			point.vec[1] = dot.y;
			to_image(frac->mlx, point);
		}
		dot.y++;
	}
}

/*
** Julia
*/

void		fractal_jul(void *para)
{
	t_frac	*frac;
	t_box	box;

	frac = para;
	box.width = frac->width;
	box.height = frac->height;
	box.jul = frac->mlx->jul;
	fractal_base(frac, box, &julia_flex);
}

/*
** Multibrot
*/

void		fractal_mult(void *para)
{
	t_frac	*frac;
	t_box	box;

	frac = para;
	box.jul = frac->mlx->jul;
	box.width = frac->width;
	box.height = frac->height;
	fractal_base(frac, box, &multibrot);
}

/*
** Mandelbrot
*/

void		fractal_man(void *para)
{
	t_frac	*frac;
	t_box	box;

	frac = para;
	box.width = frac->width;
	box.height = frac->height;
	fractal_base(frac, box, &mandel);
}
