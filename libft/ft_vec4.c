/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 14:26:10 by phakakos          #+#    #+#             */
/*   Updated: 2020/08/13 14:26:12 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** #include <stdio.h>
** void    vec4_put(t_vec4 vec)
**
**     size_t  i;
**     size_t  n;
**
**     n = 4;
**     i = -1;
**     while (++i < n)
**         printf("[%f]", vec.vec[i]);
** 	printf("\n");
** }
*/

long double	vec4_ccw(t_vec4 vec1, t_vec4 vec2, t_vec4 vec3)
{
	long double	ret;

	ret = (vec2.vec[0] - vec1.vec[0]) * (vec3.vec[1] - vec1.vec[1]);
	ret = ret - (vec2.vec[1] - vec1.vec[1]) * (vec3.vec[0] - vec1.vec[0]);
	return (ret);
}

t_vec4		vec4_ini(long double in[4])
{
	t_vec4	ret;
	size_t	i;
	size_t	n;

	i = -1;
	n = 4;
	while (++i < n)
		ret.vec[i] = in[i];
	return (ret);
}

t_vec4		vec4m_vec4(t_vec4 vec1, t_vec4 vec2)
{
	t_vec4	ret;
	size_t	i;

	ret = vec4_ini((long double[4]){0, 0, 0, 1});
	i = -1;
	while (++i < 3)
		ret.vec[i] = vec1.vec[i] - vec2.vec[i];
	return (ret);
}
