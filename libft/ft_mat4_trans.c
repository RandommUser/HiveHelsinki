/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mat4_trans.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 13:18:20 by phakakos          #+#    #+#             */
/*   Updated: 2020/08/31 13:18:21 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

t_mat4	mat4_scales(long double s[4])
{
	t_mat4	ret;
	size_t	i;
	size_t	n;

	i = -1;
	n = 4;
	ret = mat4_ini();
	while (++i < n)
		ret.mat[i][i] = s[i];
	return (ret);
}

t_mat4	mat4_rotx(double theta)
{
	t_mat4	rota;
	double	sint;
	double	cost;

	rota = mat4_ini();
	rota.mat[3][3] = 1;
	sint = sin(theta * (3.14159265 / 180));
	cost = cos(theta * (3.14159265 / 180));
	rota.mat[0][2] = 1;
	rota.mat[1][0] = cost;
	rota.mat[1][1] = sint;
	rota.mat[2][0] = sint * -1;
	rota.mat[2][1] = cost;
	return (rota);
}

t_mat4	mat4_roty(double theta)
{
	t_mat4	rota;
	double	sint;
	double	cost;

	rota = mat4_iden();
	sint = sin(theta * (3.14159265 / 180));
	cost = cos(theta * (3.14159265 / 180));
	rota.mat[0][0] = cost;
	rota.mat[0][2] = -(sint);
	rota.mat[2][0] = sint;
	rota.mat[2][2] = cost;
	return (rota);
}

t_mat4	mat4_rotz(double theta)
{
	t_mat4	rota;
	double	sint;
	double	cost;

	rota = mat4_ini();
	rota.mat[3][3] = 1;
	sint = sin(theta * (3.14159265 / 180));
	cost = cos(theta * (3.14159265 / 180));
	rota.mat[0][0] = cost;
	rota.mat[0][1] = sint;
	rota.mat[1][0] = sint * -1;
	rota.mat[1][1] = cost;
	rota.mat[2][2] = 1;
	return (rota);
}

t_mat4	mat4_trans(long double s[3])
{
	t_mat4	tran;

	tran = mat4_scales((long double[4]){1, 1, 1, 1});
	tran.mat[0][3] = s[0];
	tran.mat[1][3] = s[1];
	tran.mat[2][3] = s[2];
	return (tran);
}
