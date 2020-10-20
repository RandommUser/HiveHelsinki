/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formula.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 13:41:36 by phakakos          #+#    #+#             */
/*   Updated: 2020/10/20 13:41:38 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/*
** Default Julia fractal formula
*/

static double	julia(int iter, t_box box)
{
	box.i = -1;
	box.x = map(box.x, (long double[4]){0, box.width,
		-(box.jul.r), box.jul.r});
	box.y = map(box.y, (long double[4]){0, box.height,
		-(box.jul.r), box.jul.r});
	while (box.x * box.x + box.y * box.y <=
		box.jul.r * box.jul.r && ++box.i < iter)
	{
		box.last.x = box.x;
		box.last.y = box.y;
		box.xte = box.x * box.x - box.y * box.y;
		box.y = 2 * box.x * box.y + box.jul.cy;
		box.x = box.xte + box.jul.cx;
		if (box.last.x == box.x && box.last.y == box.y)
			return (iter);
	}
	return (box.i == -1 ? 0 : box.i);
}

/*
** Flexible Julia fractal formula
*/

double			julia_flex(int iter, t_box box)
{
	if (box.jul.n == 0)
		return (julia(iter, box));
	box.i = -1;
	box.x = map(box.x, (long double[4]){0, box.width,
		-(box.jul.r), box.jul.r});
	box.y = map(box.y, (long double[4]){0, box.height,
		-(box.jul.r), box.jul.r});
	while (box.x * box.x + box.y * box.y <=
		box.jul.r * box.jul.r && ++box.i < iter)
	{
		box.last.x = box.x;
		box.last.y = box.y;
		box.xte = pow(box.x * box.x - box.y * box.y, box.jul.n / 2) *
			cos(box.jul.n * atan2(box.y, box.x)) + box.jul.cx;
		box.y = pow(2 * box.x * box.y + box.jul.cy, box.jul.n / 2) *
			sin(box.jul.n * atan2(box.y, box.x)) + box.jul.cy;
		box.x = box.xte;
		if (box.last.x == box.x && box.last.y == box.y)
			return (iter);
	}
	return (box.i == -1 ? 0 : box.i);
}

/*
** Mandelbrot fractal formula
*/

double			mandel(int iter, t_box box)
{
	box.xs = map(box.x, (long double[4]){0, box.width, MAN_MINX, MAN_MAXX});
	box.ys = map(box.y, (long double[4]){0, box.height, MAN_MINY, MAN_MAXY});
	box.i = -1;
	box.x = 0;
	box.y = 0;
	while (box.x * box.x + box.y * box.y <= 4 && ++box.i < iter)
	{
		box.last.x = box.x;
		box.last.y = box.y;
		box.xte = box.x * box.x - box.y * box.y + box.xs;
		box.y = 2 * box.x * box.y + box.ys;
		box.x = box.xte;
		if (box.last.x == box.x && box.last.y == box.y)
			return (iter);
	}
	return (box.i == -1 ? 0 : box.i);
}
