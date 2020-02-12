/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 14:20:50 by phakakos          #+#    #+#             */
/*   Updated: 2020/02/12 14:53:46 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_baselen(long value, int base)
{
	int rtn;

	rtn = 0;
	if ((base == 10 && value < 0) || value == 0)
		rtn++;
	value = value < 0 ? value * -1 : value;
	while (value > 0)
	{
		value = value / base;
		rtn++;
	}
	return (rtn);
}

char		base_conv(long value, int base)
{
	int	c;

	c = value % base;
	if (c > 9)
		return ('a' + (c - 10));
	return ('0' + c);
}

static void	itoa_conv(char **str, long value, int base)
{
	size_t	i;

	i = ft_baselen(value, base) - 1;
	if (value < 0 && base == 10)
		str[0][0] = '-';
	value = value < 0 ? value * -1 : value;
	while (i >= 0)
	{
		str[0][i] = base_conv(value, base);
		value = value / base;
		if (value == 0)
			break ;
		i--;
	}
}

char		*ft_itoa_base(long value, int base)
{
	char	*rtn;

	if (base > 16)
		base = 16;
	else if (base < 2)
		base = 2;
	if (!(rtn = ft_strnew(ft_baselen(value, base) + 1)))
		return (NULL);
	rtn[ft_baselen(value, base)] = '\0';
	itoa_conv(&rtn, value, base);
	return (rtn);
}
