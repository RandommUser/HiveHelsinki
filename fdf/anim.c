/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 16:26:28 by phakakos          #+#    #+#             */
/*   Updated: 2020/08/29 16:26:29 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/*
** map_anim helper
*/

static t_vec4	diff_ini(float start[4], float end[4])
{
	t_vec4	diff;

	diff = vec4_ini((float[4]){end[0] - start[0], end[1] - start[1],
		end[2] - start[2], end[3] - start[3]});
	return (diff);
}

/*
** map_anim helper
*/

static t_vec4	diff_ini2(t_mat4 start, t_mat4 end)
{
	t_vec4	diff;

	diff = vec4_ini((float[4]){end.mat[0][3] - start.mat[0][3],
		end.mat[1][3] - start.mat[1][3], end.mat[2][3] - start.mat[2][3],
		end.mat[3][3] - start.mat[3][3]});
	return (diff);
}

/*
** map_anim helper
*/

static void		play_anim(t_mlx *mlx, t_map *start, t_map *end, t_vec4 diff[4])
{
	float	i;

	i = -1;
	while (++i <= ANIM_STEP)
	{
		if (start->mode == 1)
		{
			end->origin = anim_step2(end->origin, start->origin, diff[0], i);
			end->rot = anim_step(start->rot.vec, diff[1].vec, i);
		}
		else
		{
			end->cam.loc = anim_step(start->cam.loc.vec, diff[0].vec, i);
			end->cam.rot = anim_step(start->cam.rot.vec, diff[1].vec, i);
			end->cam.plan = anim_step(start->cam.plan.vec, diff[2].vec, i);
		}
		end->h_mod = start->h_mod + diff[3].vec[0] * (i / ANIM_STEP);
		end->zoom = start->zoom + diff[3].vec[1] * (i / ANIM_STEP);
		draw_map(mlx);
		mlx_do_sync(mlx->mlx_ptr);
		usleep(ANIM_TIME / ANIM_STEP);
	}
	end->thick = diff[3].vec[2];
	draw_map(mlx);
}

/*
** map_anim helper
*/

static int		anim_diff_check(t_vec4 diff[4])
{
	if (!diff[0].vec[0] && !diff[0].vec[1] &&
		!diff[0].vec[2] && !diff[0].vec[3] &&
		!diff[1].vec[0] && !diff[1].vec[1] &&
		!diff[1].vec[2] && !diff[1].vec[3] &&
		!diff[2].vec[0] && !diff[2].vec[1] &&
		!diff[2].vec[2] && !diff[2].vec[3] &&
		!diff[3].vec[0] && !diff[3].vec[1])
		return (0);
	return (1);
}

/*
** map swap animation
** diff = 1) location 2) rotation 3) view plain 4) misc
*/

void			map_anim(t_mlx *mlx, t_map *start, t_map *end)
{
	t_vec4	diff[4];

	mlx->smap = end;
	if (start->mode != end->mode)
		return ;
	diff[3] = vec4_ini((float[4]){end->h_mod - start->h_mod,
		end->zoom - start->zoom, end->thick, 0});
	if (start->mode == 1)
	{
		diff[0] = diff_ini2(start->origin, end->origin);
		diff[1] = diff_ini(start->rot.vec, end->rot.vec);
		diff[2] = vec4_ini((float[4]){0, 0, 0, 0});
		if (!anim_diff_check(diff))
			return ;
	}
	else
	{
		diff[0] = diff_ini(start->cam.loc.vec, end->cam.loc.vec);
		diff[1] = diff_ini(start->cam.rot.vec, end->cam.rot.vec);
		diff[2] = diff_ini(start->cam.plan.vec, end->cam.plan.vec);
		if (!anim_diff_check(diff))
			return ;
	}
	end->thick = 0;
	play_anim(mlx, start, end, diff);
}
