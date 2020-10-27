/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formula_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 13:44:46 by phakakos          #+#    #+#             */
/*   Updated: 2020/10/20 13:44:50 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/*
** Negative Multibrot fractal formula
** does not work properly for N > -2
*/

static double	multibrot_nega(int iter, t_box box)
{
	box.xs = map(box.x, (long double[4]){0, box.width, MAN_MINX, MAN_MAXX});
	box.ys = map(box.y, (long double[4]){0, box.height, MAN_MINY, MAN_MAXY});
	box.x = 0;
	box.y = 0;
	box.i = -1;
	box.pr = -(box.jul.r);
	box.d = pow(pow(box.xs, 2) + pow(box.ys, 2), box.pr);
	while (box.x * box.x + box.y * box.y <= box.jul.r * box.jul.r &&
		++box.i < iter)
	{
		if (!box.d)
			return (box.i);
		box.xte = pow((box.x * box.x + box.y * box.y), (box.pr / 2)) *
			cos(box.pr * atan2(box.y, box.x)) / box.d + box.xs;
		box.y = -(pow((box.x * box.x + box.y * box.y), (box.pr / 2))) *
			sin(box.pr * atan2(box.y, box.x)) / box.d + box.ys;
		box.x = box.xte;
		if ((box.last.x == box.x && box.last.y == box.y))
			return (iter);
		box.d = pow(pow(box.x, 2) + pow(box.y, 2), box.pr);
	}
	return (box.i == -1 ? 0 : box.i);
}

/*
** Multibrot fractal formula
*/

double			multibrot(int iter, t_box box)
{
	if (box.jul.r < 0)
		return (multibrot_nega(iter, box));
	box.xs = map(box.x, (long double[4]){0, box.width, MAN_MINX, MAN_MAXX});
	box.ys = map(box.y, (long double[4]){0, box.height, MAN_MINY, MAN_MAXY});
	box.x = 0;
	box.y = 0;
	box.i = -1;
	while (box.x * box.x + box.y * box.y <= box.jul.r * box.jul.r
		&& ++box.i < iter)
	{
		box.xte = pow((box.x * box.x + box.y * box.y), (box.jul.r / 2)) *
			cos(box.jul.r * atan2(box.y, box.x)) + box.xs;
		box.y = pow((box.x * box.x + box.y * box.y), (box.jul.r / 2)) *
			sin(box.jul.r * atan2(box.y, box.x)) + box.ys;
		box.x = box.xte;
		if ((box.last.x == box.x && box.last.y == box.y))
			return (iter);
	}
	return (box.i == -1 ? 0 : box.i);
}

/*
** Barnsley fractal formula
*/

t_ddot			barnsley(t_ddot val)
{
	t_box	box;

	box.r = (long double)rand() / (long double)(RAND_MAX);
	if (box.r < 0.01)
	{
		box.x = 0;
		val.y = 0.16 * val.y;
	}
	else if (box.r < 0.86)
	{
		box.x = 0.85 * val.x + 0.04 * val.y;
		val.y = -0.04 * val.x + 0.85 * val.y + 1.6;
	}
	else if (box.r < 0.93)
	{
		box.x = 0.20 * val.x - 0.26 * val.y;
		val.y = 0.23 * val.x + 0.22 * val.y + 1.6;
	}
	else
	{
		box.x = -0.15 * val.x + 0.28 * val.y;
		val.y = 0.26 * val.x + 0.24 * val.y + 0.44;
	}
	val.x = box.x;
	return (val);
}
