/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mat2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 13:46:46 by phakakos          #+#    #+#             */
/*   Updated: 2020/08/11 13:46:48 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

//counter-clockwise
t_mat2  *mat2_rota(double theta)
{
    t_mat2  *rota;
    float   sint;
    float   cost;

    if (!(rota = (t_mat2*)matn_ini(2)))
        return (NULL);
    sint = sin(theta * (3.14159265 / 180));
    cost = cos(theta * (3.14159265 / 180));
    rota->mat[0][0] = cost;
    rota->mat[0][1] = -(sint);
    rota->mat[1][0] = sint;
    rota->mat[1][1] = cost;
    return (rota);
}

t_mat2  *mat2_flip(void)
{
    t_mat2   *flip;

    if (!(flip = (t_mat2*)matn_ini(2)))
        return (NULL);
    flip->mat[0][0] = 1;
    flip->mat[0][1] = 0;
    flip->mat[1][0] = 0;
    flip->mat[1][1] = -1;
    return (flip);
}

t_vec2  *mat2_vec(t_mat2 *mat2, t_vec2 *vec2)
{
    float   ret[2];

    ret[0] = mat2->mat[0][0] * vec2->vec[0] + mat2->mat[0][1] * vec2->vec[1];
    ret[1] = mat2->mat[1][0] * vec2->vec[0] + mat2->mat[1][1] * vec2->vec[1];
    return ((t_vec2*)vecn_cpy((float*)ret, 2));
}