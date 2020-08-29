/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 16:29:20 by phakakos          #+#    #+#             */
/*   Updated: 2020/08/29 16:29:22 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/*
** map_anim helper
*/

t_vec4	anim_step(float start[4], float diff[4], float i)
{
	t_vec4	end;

	end.vec[0] = start[0] + diff[0] * (i / ANIM_STEP);
	end.vec[1] = start[1] + diff[1] * (i / ANIM_STEP);
	end.vec[2] = start[2] + diff[2] * (i / ANIM_STEP);
	end.vec[3] = start[3] + diff[3] * (i / ANIM_STEP);
	return (end);
}

/*
** map_anim helper
*/

t_mat4	anim_step2(t_mat4 end, t_mat4 start, t_vec4 diff, float i)
{
	end.mat[0][3] = start.mat[0][3] + diff.vec[0] * (i / ANIM_STEP);
	end.mat[1][3] = start.mat[1][3] + diff.vec[1] * (i / ANIM_STEP);
	end.mat[2][3] = start.mat[2][3] + diff.vec[2] * (i / ANIM_STEP);
	end.mat[3][3] = start.mat[3][3] + diff.vec[3] * (i / ANIM_STEP);
	return (end);
}
