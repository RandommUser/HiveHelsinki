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

void			draw_to_image(t_mlx *mlx, t_map *map, t_loca spot)
{
	long	writer;
	int		*image;

	if (!mlx->mlx_img)
		return ;
	if (spot.loc.vec[0] >= map->pos.vec[2] && spot.loc.vec[0] <= map->pos.vec[2]
		+ map->pos.vec[0] - 1 && spot.loc.vec[1] >= map->pos.vec[3] &&
		spot.loc.vec[1] <= map->pos.vec[3] + map->pos.vec[1] -1 && ((map->limit
		&& map->mode > 1 && spot.loc.vec[2] >= map->cam.plan.vec[3]) ||
		(map->mode == 1 || !map->limit)))
	{
		writer = ((mlx->size_line / 4) * (int)spot.loc.vec[1]) +
			(int)spot.loc.vec[0];
		image = (int*)mlx->img_dat;
		image[writer] = mlx_get_color_value(mlx->mlx_ptr,
			trgb_conv(spot.color));
	}
}

/*
** calculate the color change between points
** draw_line1 helper -> (draw_linez1 helper ->) draw helper -> draw_selected ->
** 		draw_map
*/

static t_rgb	color_flow(t_loca start, t_loca diff, t_loca curr, t_loca end)
{
	t_rgb	rtn;
	float	prog;

	if (ft_abs(diff.loc.vec[0]) > ft_abs(diff.loc.vec[1]))
	{
		prog = ft_abs(curr.loc.vec[0] - end.loc.vec[0]);
		prog = prog == 0 ? 0 : 1 - prog / ft_abs(diff.loc.vec[0]);
	}
	else
	{
		prog = ft_abs(curr.loc.vec[1] - end.loc.vec[1]);
		prog = prog == 0 ? 0 : 1 - prog / ft_abs(diff.loc.vec[1]);
	}
	rtn.red = (1 - prog) * start.color.red + end.color.red * prog;
	rtn.green = (1 - prog) * start.color.green + end.color.green * prog;
	rtn.blue = (1 - prog) * start.color.blue + end.color.blue * prog;
	return (rtn);
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

void			draw_line(t_mlx *mlx, t_map *map, t_loca start, t_loca end)
{
	t_loca	diff;
	t_loca	curr;
	int		i;
	int		y;

	curr = start;
	diff.loc.vec[0] = end.loc.vec[0] - start.loc.vec[0];
	diff.loc.vec[1] = end.loc.vec[1] - start.loc.vec[1];
	diff.loc.vec[2] = end.loc.vec[2] - start.loc.vec[2];
	if (!(i = 1) || diff.loc.vec[1] == 0 || (diff.loc.vec[0] != 0 &&
	ft_abs(diff.loc.vec[0]) > ft_abs(diff.loc.vec[1])))
		i = 0;
	y = i == 0 ? 1 : 0;
	while (curr.loc.vec[i] != end.loc.vec[i])
	{
		curr.loc.vec[y] = move_line(start.loc, diff.loc, curr.loc.vec[i], i);
		curr.loc.vec[2] = move_height(start.loc, diff.loc, curr.loc.vec[i], i);
		curr.color = color_flow(start, diff, curr, end);
		draw_to_image(mlx, map, curr);
		curr.loc.vec[i] = curr.loc.vec[i] < end.loc.vec[i] ? curr.loc.vec[i]
			+ 1 : curr.loc.vec[i] - 1;
	}
	draw_to_image(mlx, map, curr);
}
