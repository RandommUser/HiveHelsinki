/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 13:32:33 by phakakos          #+#    #+#             */
/*   Updated: 2020/02/19 16:24:58 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	print_point(t_point	*start, int x, int y)
{
	t_point	*point;
//printf("\nPrint_point\nStart->x = %d Start->y = %d\n Finding %d : %d\n", start->x, start->y, x, y);
	if (start->x == x && start->y == y)
	{ }
	else if (!(point = find_point(start, x, y)))
	{
		ft_putstr("Could not find @ ");
		ft_putnbr(x);
		ft_putchar(':');
		ft_putnbr(y);
		ft_putchar('\n');
		return ;
	}
	ft_putstr("---\nPoint\nX:");
	ft_putnbr(point->x);
	ft_putstr("\nY: ");
	ft_putnbr(point->y);
	ft_putstr("\nZ: ");
	ft_putnbr(point->z);
	ft_putstr("\nColor: ");
	ft_putnbr(point->color);
	ft_putstr("\nThis: ");
	ft_putpointer(point);
	ft_putstr("\nTop: ");
	ft_putpointer(point->top);
	ft_putstr("\nLeft: ");
	ft_putpointer(point->left);
	ft_putstr("\nBottom: ");
	ft_putpointer(point->bottm);
	ft_putstr("\nRight: ");
	ft_putpointer(point->right);
	ft_putchar('\n');
}

t_point	*find_point(t_point *curr, int x, int y)
{
//printf("finding %d : %d\n", x, y);
//if (curr)
//printf("currently %d : %d\n", curr->x, curr->y);
	if (curr == NULL)
		return (NULL);
	if (curr->x == x && curr->y == y)
		return (curr);
	if (curr->x < x && curr->right)
		return (find_point(curr->right, x, y));
	if (curr->x > x && curr->left)
		return (find_point(curr->left, x, y));
	if (curr->y < y && curr->bottm)
		return (find_point(curr->bottm, x, y));
	if (curr->y > y && curr->top)
		return (find_point(curr->top, x, y));
	return (NULL);
}

void	point_conn(t_point *start, t_point *add, t_coord spot)
{
	t_point	*left;
	t_point	*right;
	t_point	*top;
	t_point	*bottom;
//ft_putstr("\nfinding left connection\n");
	left = find_point(start, spot.x - 1, spot.y);
//ft_putstr("left checked\n");
	if (left)
		left->right = add;
	add->left = left;
//ft_putstr("finding right connection\n");
	right = find_point(start, spot.x + 1, spot.y);
//ft_putstr("right checked\n");
	if (right)
		right->left = add;
	add->right = right;
//ft_putstr("finding top connection\n");
	top = find_point(start, spot.x, spot.y - 1);
//ft_putstr("top checked\n");
	if (top)
		top->bottm = add;
	add->top = top;
//ft_putstr("finding bottom connection\n");
	bottom = find_point(start, spot.x, spot.y + 1);
//ft_putstr("bottom checked\n");
	if (bottom)	
		bottom->top = add;
	add->bottm = bottom;
}

t_point	*point_init(t_point *start, t_coord spot, int height, int color)
{
	t_point	*rtn;
//printf("making a point at x:%d, y:%d\n", spot.x, spot.y);
	if (!(rtn = (t_point *)malloc(sizeof(t_point))))
		return (NULL);
	rtn->x = spot.x;
	rtn->y = spot.y;
	rtn->top = NULL;
	rtn->bottm = NULL;
	rtn->left = NULL;
	rtn->right = NULL;
	if (start)
		point_conn(start, rtn, spot);
	rtn->z = height;
	rtn->color = color;
//ft_putstr("printing current\n");
//printf("point at x:%d, y:%d\n", spot.x, spot.y);
//printf("%d x %d\n", rtn->x, rtn->y);
//	print_point(rtn, spot.x, spot.y);
	return (rtn);
}

t_point	*point_conv(t_point *start, char **str, int y)
{
	int	x;
	int	height;
	int	color;
//ft_putstr("point conv starting\n");
	x = 0;
	if (!start)
	{
printf("making a new starting point: %s\n", str[x]);
		height = ft_atoi(str[x]);
		if (ft_strchr(str[x], COLOR_SPLIT))
			color = ft_atoi_base(str[x] + ft_strclen(str[x], COLOR_SPLIT) + 1, 16);
		else
			color = -1;
//printf("new starting point | x:%d, y:%d, z:%d | color:%d\n", x, y, height, color);
		start = point_init(start, coords(x, y), height, color);
ft_putstr("made a new start point\n");
		x++;
	}
	while (start && str[x])
	{
//ft_putstr("conv loop @");
//ft_putnbr(x);
//ft_putchar('\n');
		height = ft_atoi(str[x]);
		if (ft_strchr(str[x], COLOR_SPLIT))
		{
//printf("str: %s | color at :'%s'\n", str[x], (char *)(str[x] + ft_strclen(str[x], COLOR_SPLIT) + 1));
			color = ft_atoi_base(str[x] + ft_strclen(str[x], COLOR_SPLIT) + 1, 16);
		}
		else
			color = -1;
//printf("new point | x:%d, y:%d, z:%d | color:%d\n", x, y, height, color);
		if (!(point_init(start, coords(x, y), height, color)))
			return (NULL);
ft_putstr("point added\n");
		x++;
	}
	ft_strarrdel(str);
	return (start);
}
