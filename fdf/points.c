/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 13:32:33 by phakakos          #+#    #+#             */
/*   Updated: 2020/06/02 14:59:05 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_point		*find_point(t_point *curr, int x, int y)
{
	if (curr == NULL)
		return (NULL);
	if (curr->loc.vec[0] == x && curr->loc.vec[1] == y)
		return (curr);
	if (curr->loc.vec[0] < x && curr->right)
		return (find_point(curr->right, x, y));
	if (curr->loc.vec[0] > x && curr->left)
		return (find_point(curr->left, x, y));
	if (curr->loc.vec[1] < y && curr->bottm)
		return (find_point(curr->bottm, x, y));
	if (curr->loc.vec[1] > y && curr->top)
		return (find_point(curr->top, x, y));
	return (NULL);
}

void		point_conn(t_point *start, t_point *add, t_coord spot)
{
	t_point	*left;
	t_point	*right;
	t_point	*top;
	t_point	*bottom;

	if ((left = find_point(start, spot.x - 1, spot.y)))
		left->right = add;
	add->left = left;
	if ((right = find_point(start, spot.x + 1, spot.y)))
		right->left = add;
	add->right = right;
	if ((top = find_point(start, spot.x, spot.y - 1)))
		top->bottm = add;
	add->top = top;
	if ((bottom = find_point(start, spot.x, spot.y + 1)))
		bottom->top = add;
	add->bottm = bottom;
}

t_point		*point_init(t_point *start, t_coord spot, int height, int color)
{
	t_point	*rtn;

	if (!(rtn = (t_point *)malloc(sizeof(t_point))))
		return (NULL);
	rtn->loc.vec[0] = spot.x;
	rtn->loc.vec[1] = spot.y;
	rtn->loc.vec[2] = height;
	rtn->loc.vec[3] = 1;
	rtn->color = color;
	rtn->top = NULL;
	rtn->bottm = NULL;
	rtn->left = NULL;
	rtn->right = NULL;
	if (start)
		point_conn(start, rtn, spot);
	return (rtn);
}

static void	map_valid(char **str)
{
	size_t	i;
	size_t	y;
	int		hex;

	y = -1;
	while (str[++y] && (i = -1))
	{
		hex = -1;
		while (str[y][++i])
		{
			if ((hex == 0 && str[y][i] != '0') || (hex == 1 && str[y][i]
				!= 'x' && str[y][i] != 'X'))
				mexit(ERR_MAP);
			else if ((i > 0 && str[y][i] == COLOR_SPLIT && hex == -1) ||
				hex == 0 || hex == 1)
				hex++;
			else if (hex >= 2 && hex < 8 && (ft_isdigit(str[y][i]) ||
				((str[y][i] >= 'a' && str[y][i] <= 'f') ||
				(str[y][i] >= 'A' && str[y][i] <= 'F'))))
				hex++;
			else if (hex == 8 || !(ft_isdigit(str[y][i])) || str[y][i] ==
				COLOR_SPLIT)
				mexit(ERR_MAP);
		}
	}
}

t_point		*point_conv(t_point *start, char **str, int y)
{
	int		x;
	long	height;
	int		color;

	map_valid(str);
	x = -1;
	if (!start && !(++x))
	{
		height = ft_atoi_base(str[x], 10);
		color = ft_strchr(str[x], COLOR_SPLIT) ? ft_atoi_base(str[x] +
		ft_strclen(str[x], COLOR_SPLIT) + 1, 16) : -1;
		if (!(start = point_init(start, coords(x, y), height, color)))
			mexit(ERR_MEMORY);
	}
	while (start && str[++x])
	{
		height = ft_atoi(str[x]);
		color = ft_strchr(str[x], COLOR_SPLIT) ? ft_atoi_base(str[x] +
		ft_strclen(str[x], COLOR_SPLIT) + 1, 16) : -1;
		if (!(point_init(start, coords(x, y), height, color)))
			mexit(ERR_MEMORY);
	}
	ft_strarrdel(str);
	return (start);
}
