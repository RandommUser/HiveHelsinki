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


#include <stdio.h>
void	mat4_put(t_mat4 mat4)
{
	size_t	row;
	size_t	col;
	size_t	n;

	row = -1;
	n = 4;
	while (++row < n && (col = -1))
	{
		while (++col < n)
			printf("[%f]", mat4.mat[row][col]);
		printf("\n");
	}
	printf("\n");
}

t_mat4	mat4_ini(void)
{
	t_mat4	ret;
	size_t	row;
	size_t	col;
	size_t	n;

	row = -1;
	n = 4;
	while (++row < n && (col = -1))
		while (++col < n)
			ret.mat[row][col] = 0;
	return (ret);
}

t_mat4	mat4_iden(void)
{
	t_mat4	ret;
	size_t	i;
	size_t	n;

	i = -1;
	n = 4;
	ret = mat4_ini();
	while (++i < n)
		ret.mat[i][i] = 1;
	return (ret);
}

t_mat4	mat4_scales(float s[4])
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
	//rota = mat4_iden();
	sint = sin(theta * (3.14159265 / 180));
	cost = cos(theta * (3.14159265 / 180));
	rota.mat[0][2] = 1;
	rota.mat[1][0] = cost;
	rota.mat[1][1] = sint;
	rota.mat[2][0] = sint * -1;
	rota.mat[2][1] = cost;

	//rota.mat[1][1] = cost;
	//rota.mat[1][2] = sint;
	//rota.mat[2][1] = -(sint);
	//rota.mat[2][2] = cost;
	return (rota);
}

t_mat4	mat4_roty(double theta)
{
	t_mat4	rota;
	double	sint;
	double	cost;

	rota = mat4_iden();
//	rota = mat4_ini();
//	rota.mat[3][3] = 1;
	sint = sin(theta * (3.14159265 / 180));
	cost = cos(theta * (3.14159265 / 180));
/*
	rota.mat[0][0] = sint * -1;
	rota.mat[0][1] = cost;
	rota.mat[1][2] = 1;
	rota.mat[2][0] = cost;
	rota.mat[2][1] = sint;
*/
//	/*
	rota.mat[0][0] = cost;
	rota.mat[0][2] = -(sint);
	rota.mat[2][0] = sint;
	rota.mat[2][2] = cost;
//	*/
	return (rota);
}

t_mat4	mat4_rotz(double theta)
{
	t_mat4	rota;
	double	sint;
	double	cost;

	//rota = mat4_iden();
	rota = mat4_ini();
	rota.mat[3][3] = 1;
	sint = sin(theta * (3.14159265 / 180));
	cost = cos(theta * (3.14159265 / 180));

	rota.mat[0][0] = cost;
	rota.mat[0][1] = sint;
	rota.mat[1][0] = sint * -1;
	rota.mat[1][1] = cost;
	rota.mat[2][2] = 1;

	/*
	rota.mat[0][0] = cost;
	rota.mat[0][1] = sint;
	rota.mat[1][0] = -(sint);
	rota.mat[1][1] = cost;
	*/
	return (rota);
}

t_mat4	mat4_pro(void)
{
	t_mat4	proj;

	proj = mat4_scales((float[4]){1,1,1,0});
	proj.mat[3][2] = 1;
	return (proj);
}

t_mat4	mat4_perps(t_vec4 vec)
{
	t_mat4	proj;

	proj = mat4_scales((float[4]){1,1,0,1});
	proj.mat[0][2] = vec.vec[0] / vec.vec[1];
	proj.mat[1][2] = vec.vec[1] / vec.vec[2];
	proj.mat[2][2] = 1 / vec.vec[2];
	return (proj);
}

// near, far, fov, ? || width / height
t_mat4	mat4_perps2(t_vec4 vec, float ar)
{
	t_mat4	proj;
	float	tant;
	float	range;

	tant = tan((double)vec.vec[2] * (3.14159265 / 180) / 2 );
	range = vec.vec[0] - vec.vec[1];
	proj = mat4_ini();
	proj.mat[2][3] = 1;
	proj.mat[0][0] = 1 / (tant * ar);
	proj.mat[1][1] = 1 / tant;
	proj.mat[2][2] = (-(vec.vec[0]) - vec.vec[1]) / range;
	proj.mat[3][2] = 2 * vec.vec[1] * vec.vec[0] / range;
	return (proj);
}

// focal, skew, cam x, cam y
t_mat4	mat4_pinhole(t_vec4 vec, float ar)
{
	t_mat4	proj;

	proj = mat4_iden();
	proj.mat[0][0] = vec.vec[0];
	proj.mat[0][1] = vec.vec[1];
	proj.mat[0][2] = vec.vec[2];
	proj.mat[1][1] = vec.vec[0] * ar;
	proj.mat[1][2] = vec.vec[3];
	return (proj);
}

t_mat4	mat4_trans(float s[3])
{
	t_mat4	tran;

	tran = mat4_scales((float[4]){1, 1, 1, 1});
	tran.mat[0][3] = s[0];
	tran.mat[1][3] = s[1];
	tran.mat[2][3] = s[2];
	return (tran);
}

t_mat4	mat4_mat4(t_mat4 mat1, t_mat4 mat2)
{
	t_mat4	ret;
	size_t	row;
	size_t	col;
	size_t	i;
	size_t	n;

	ret = mat4_ini();
	row = -1;
	n = 4;
	while (++row < n && (col = -1))
	{
		while (++col < n && (i = -1))
			while (++i < n)
				ret.mat[row][col] += mat1.mat[row][i] * mat2.mat[i][col];
	}
	return (ret);
}

t_vec4	mat4_vec4(t_mat4 mat4, t_vec4 vec4)
{
	t_vec4	ret;
	size_t	row;
	size_t	col;
	size_t	n;

	n = 4;
	row = -1;
	while (++row < n && (col = -1))
	{
		while (++col < n)
			ret.vec[row] += mat4.mat[row][col] * vec4.vec[col];
	}
	return (ret);
}
