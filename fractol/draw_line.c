/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 11:28:25 by phakakos          #+#    #+#             */
/*   Updated: 2020/08/31 11:28:27 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/*
** "drawing" to image
** draw_line1 helper -> (draw_linez1 helper ->) draw helper -> draw_selected ->
**		draw_map
*/

void			draw_to_image(t_mlx *mlx, int *image, t_vec4 spot)
{
	long	writer;

	writer = ((mlx->size_line / 4) * (int)spot.vec[1]) + (int)spot.vec[0];
	if (spot.vec[0] >= 0 && spot.vec[0] < mlx->width && spot.vec[1] >= 0 &&
		spot.vec[1] < mlx->height)
	{
		if (mlx->height_map[writer] < spot.vec[2])
		{
			image[writer] = mlx_get_color_value(mlx->mlx_ptr, (int)spot.vec[3]);
			mlx->height_map[writer] = spot.vec[2];
		}
	}
}

/*
** calculate the color change between points
** draw_line1 helper -> (draw_linez1 helper ->) draw helper -> draw_selected ->
** 		draw_map
*/

static int	color_flow(t_vec4 start, t_vec4 diff, t_vec4 curr, t_vec4 end)
{
	int		color;
	float	prog;

	if (ft_fabs(diff.vec[0]) > ft_fabs(diff.vec[1]))
	{
		prog = ft_fabs(curr.vec[0] - end.vec[0]);
		prog = prog == 0 ? 0 : 1 - prog / ft_fabs(diff.vec[0]);
	}
	else
	{
		prog = ft_fabs(curr.vec[1] - end.vec[1]);
		prog = prog == 0 ? 0 : 1 - prog / ft_fabs(diff.vec[1]);
	}
	color = (1 - prog) * start.vec[3] + end.vec[3] * prog;
	return (color);
}

/*
** move x/y position while drawing
** draw_line1 helper -> (draw_linez1 helper ->) draw helper -> draw_selected ->
**		draw_map
*/

static float	move_line(t_vec4 start, t_vec4 diff, float curr, int i)
{
	int		y;
	float	rtn;

	y = i == 1 ? 0 : 1;
	rtn = start.vec[y];
	rtn += diff.vec[y] * (curr - start.vec[i]) / diff.vec[i];
	return (rtn);
}

/*
** move Z position while drawing
** draw_line1 helper -> (draw_linez1 helper ->) draw helper -> draw_selected ->
**		 draw_map
*/

static float	move_height(t_vec4 start, t_vec4 diff, float curr, int i)
{
	float	rtn;

	rtn = start.vec[2];
	rtn += diff.vec[2] * (curr - start.vec[i]) / diff.vec[i];
	return (rtn);
}

/*
** just draw line
** (draw_linez1 helper ->) draw helper -> draw_selected -> draw_map
*/

void			draw_line(t_mlx *mlx, t_vec4 start, t_vec4 end)
{
	t_vec4	diff;
	t_vec4	curr;
	int		i;
	int		y;
//printf("starting %f %f %f to %f %f %f\n", start.vec[0], start.vec[1], start.vec[2], end.vec[0], end.vec[1], end.vec[2]);
	curr = start;
	diff.vec[0] = (float)(end.vec[0] - start.vec[0]);
	diff.vec[1] = (float)(end.vec[1] - start.vec[1]);
	diff.vec[2] = (float)(end.vec[2] - start.vec[2]);
	if (!(i = 1) || diff.vec[1] == 0 || (diff.vec[0] != 0 &&
	ft_fabs(diff.vec[0]) > ft_fabs(diff.vec[1])))
		i = 0;
	y = i == 0 ? 1 : 0;
	while ((int)curr.vec[i] != (int)end.vec[i])
	{
		//printf("calculating %f %f %f to %f %f %f\n curr %f %f %f\n", start.vec[0], start.vec[1], start.vec[2], end.vec[0], end.vec[1], end.vec[2], curr.vec[0], curr.vec[1], curr.vec[2]);
		curr.vec[y] = move_line(start, diff, curr.vec[i], i);
		curr.vec[2] = move_height(start, diff, curr.vec[i], i);
		curr.vec[3] = color_flow(start, diff, curr, end);
		draw_to_image(mlx, mlx->img_dat[0], curr);
		curr.vec[i] = curr.vec[i] < end.vec[i] ? curr.vec[i]
			+ 1 : curr.vec[i] - 1;
	}
	draw_to_image(mlx, mlx->img_dat[0], curr);
}
