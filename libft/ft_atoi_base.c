/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 15:02:55 by phakakos          #+#    #+#             */
/*   Updated: 2020/02/12 17:27:24 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long		atoi_conv(char c, int base)
{
	char	rtn;

	c = ft_tolower(c);
	if (ft_isdigit(c))
		rtn = c - '0';
	else if (c <= 'f' && c >= 'a')
		rtn = c - 'a' + 10;
	else
		rtn = -1;
	if (rtn > base)
		rtn = -1;
	return (rtn);
}

static int	atoi_base_calc(char *str, int base, long *rtn)
{
	int	times;

	times = 0;
	if (atoi_conv(str[0], base) > -1)
	{
		times = atoi_base_calc(str + 1, base, rtn);
		if (*rtn == -1)
			*rtn = atoi_conv(str[0], base);
		else
			*rtn = *rtn + ft_power_base(atoi_conv(str[0], base), times, base);
		times++;
	}
	return (times);
}

long		ft_atoi_base(char *str, int base)
{
	long	rtn;

	if (base == 10)
		return (ft_atoi(str));
	str += ft_skipempty((char *)str);
	if (ft_strlen(str) > 2 && ft_tolower(str[1]) == 'x' && str[0] == '0')
	{
		base = base == 0 ? 16 : base;
		str = base == 16 ? str + 2 : str;
	}
	else if (ft_strlen(str) > 2 && ft_tolower(str[1]) == 'b' && str[0] == '0')
	{
		base = base == 0 ? 2 : base;
		str = base == 2 ? str + 2 : str;
	}
	base = base == 0 ? 10 : base;
	base = base > 16 ? 16 : base;
	base = base < 2 ? 2 : base;
	rtn = -1;
	atoi_base_calc(str, base, &rtn);
	return (rtn);
}
