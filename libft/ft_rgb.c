/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rgb.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 17:26:08 by phakakos          #+#    #+#             */
/*   Updated: 2020/02/10 18:28:46 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		floor(long num)
{
	if (num > 255)
		return (num % 256);
	else
		return (num);
}

int				rgb_color(unsigned int red, unsigned int green,
		unsigned int blue)
{
	red = floor(red);
	green = floor(green);
	blue = floor(blue);
	blue += green * 256;
	blue += red * 256 * 256;
	return (blue);
}
