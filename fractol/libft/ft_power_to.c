/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power_to.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:21:01 by phakakos          #+#    #+#             */
/*   Updated: 2020/02/12 17:23:48 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_power_to(long num, int power)
{
	int base;

	base = num;
	while (power > 1)
	{
		num = num * base;
		power--;
	}
	return (num);
}

long	ft_power_base(long num, int power, int base)
{
	int	start;

	start = num;
	num = ft_power_to(base, power);
	num = num * start;
	return (num);
}
