/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mat4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 16:05:20 by phakakos          #+#    #+#             */
/*   Updated: 2020/08/12 16:05:21 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

t_mat4  *mat4_rotz(double theta)
{
    t_mat4  *rota;
    double   sint;
    double   cost;

    if (!(rota = (t_mat4*)matn_scale_sini((float[4]){0, 0, 0, 1}, 4)))
        return (NULL);
    sint = sin(theta * (3.14159265 / 180));
    cost = cos(theta * (3.14159265 / 180));
    rota->mat[0][0] = cost;
    rota->mat[0][1] = sint;
    rota->mat[1][0] = -(sint);
    rota->mat[1][1] = cost;
    return (rota);
}

t_mat4  *mat4_roty(double theta)
{
    t_mat4  *rota;
    double   sint;
    double   cost;

    if (!(rota = (t_mat4*)matn_scale_sini((float[4]){0, 0, 0, 1}, 4)))
        return (NULL);
    sint = sin(theta * (3.14159265 / 180));
    cost = cos(theta * (3.14159265 / 180));
    rota->mat[0][0] = -(sint);
    rota->mat[0][1] = cost;
    rota->mat[1][2] = 1;
    rota->mat[2][0] = cost;
    rota->mat[2][1] = sint;
    return (rota);
}

t_mat4  *mat4_rotx(double theta)
{
    t_mat4  *rota;
    double   sint;
    double   cost;

    if (!(rota = (t_mat4*)matn_scale_sini((float[4]){0, 0, 0, 1}, 4)))
        return (NULL);
    sint = sin(theta * (3.14159265 / 180));
    cost = cos(theta * (3.14159265 / 180));
    rota->mat[0][2] = 1;
    rota->mat[1][0] = cost;
    rota->mat[1][1] = sint;
    rota->mat[2][0] = -(sint);
    rota->mat[2][1] = cost;
    return (rota);
}

t_mat4  *mat4_trans(float *s)
{
    t_mat4  *tran;

    if (!(tran = (t_mat4*)matn_iden(4)))
        return (NULL);
    tran->mat[0][3] = s[0];
    tran->mat[1][3] = s[1];
    tran->mat[2][3] = s[2];
    return (tran);
}