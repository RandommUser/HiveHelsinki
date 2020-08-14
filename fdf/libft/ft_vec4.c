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

#include <stdio.h>
void    vec4_put(t_vec4 vec)
{
    size_t  i;
    size_t  n;

    n = 4;
    i = -1;
    while (++i < n)
        printf("[%f]", vec.vec[i]);
    printf("\n");
}

t_vec4  vec4_ini(float in[4])
{
    t_vec4  ret;
    size_t  i;
    size_t  n;

    i = -1;
    n = 4;
    while (++i < n)
        ret.vec[i] = in[i];
    return (ret);
}