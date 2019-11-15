/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 16:21:45 by phakakos          #+#    #+#             */
/*   Updated: 2019/11/12 18:09:27 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static void	convert_int(int n, char type, size_t len)
{
	char	inta[12];
	int		i;

	i = len - 1;
	ft_memset(inta, '\0', 12);
	inta[0] = type;
	if (n == 0)
		inta[1] = '0';
	while (n > 0)
	{
		inta[i] = (n % 10) + '0';
		i--;
		n = n / 10;
	}
	if (type == '+')
		write(1, &inta[1], len - 1);
	else
		write(1, inta, len);
}

void		ft_putnbr(int n)
{
	char	type;
	size_t	len;

	type = '+';
	if (n == -2147483648)
	{
		ft_putstr("-2147483648");
		return ;
	}
	else if (n == 2147483647)
	{
		ft_putstr("2147483647");
		return ;
	}
	if (n < 0)
	{
		len = ft_nbrlen(n);
		type = '-';
	}
	else
		len = ft_nbrlen(n) + 1;
	convert_int(ft_abs(n), type, len);
}
