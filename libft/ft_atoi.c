/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 13:14:55 by phakakos          #+#    #+#             */
/*   Updated: 2020/02/12 17:27:01 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_side(const char *str, int *i)
{
	if (str[*i] == '+')
	{
		*i = *i + 1;
		return (1);
	}
	else if (str[*i] == '-')
	{
		*i = *i + 1;
		return (-1);
	}
	else
		return (0);
}

int			ft_atoi(const char *str)
{
	int i;
	int side;
	int total;

	i = ft_skipempty((char *)str);
	side = find_side(str, &i);
	total = 0;
	while (ft_isdigit(str[i]))
	{
		total = (total * 10) + (str[i] - '0');
		i++;
	}
	if (side != 0)
		return (total * side);
	else
		return (total);
}
