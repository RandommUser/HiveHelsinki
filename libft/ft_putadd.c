/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 15:41:07 by phakakos          #+#    #+#             */
/*   Updated: 2019/11/17 16:17:56 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static char	convert(long n)
{
	int	c;

	c = n % 16;
	if (c > 9)
		return ('a' + (c - 10));
	else
		return ('0' + c);
}

static void	putadd(long n, size_t len)
{
	char	rtn[len + 2];
	size_t	i;

	len += 2;
	i = len - 1;
	ft_memset(rtn, '0', len);
	rtn[0] = '0';
	rtn[1] = 'x';
	while (n > 0)
	{
		rtn[i] = convert(n);
		n = n / 16;
		i--;
	}
	write(1, rtn, len);
}

void		ft_putadd(void *p)
{
	void	*start;
	long	place;

	start = NULL;
	place = p - start;
	putadd(place, ft_hxdlen(place));
}
