/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 14:42:16 by phakakos          #+#    #+#             */
/*   Updated: 2020/02/12 14:50:08 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static void	writepoint(long n, size_t len)
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
		rtn[i] = base_conv(n, 16);
		n = n / 16;
		i--;
	}
	write(1, rtn, len);
}

void		ft_putpointer(void *p)
{
	void	*start;
	long	place;

	start = NULL;
	place = p - start;
	writepoint(place, ft_baselen(place, 16));
}
