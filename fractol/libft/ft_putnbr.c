/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 16:21:45 by phakakos          #+#    #+#             */
/*   Updated: 2019/11/17 14:15:05 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static void	convert(long n, char type, size_t len)
{
	char	output[len];
	size_t	i;
	long	ten;

	ten = 10;
	i = len - 1;
	ft_memset(output, '\0', len);
	output[0] = type;
	if (n == 0)
		output[1] = '0';
	while (n > 0)
	{
		output[i] = (n % ten) + '0';
		i--;
		n = n / ten;
	}
	if (type == '+')
		write(1, &output[1], len - 1);
	else
		write(1, output, len);
}

void		ft_putnbr(long n)
{
	char	type;
	size_t	len;
	long	max;

	type = '+';
	max = -9223372036854775807 - 1;
	if (n == max)
	{
		ft_putstr("-9223372036854775808");
		return ;
	}
	if (n < 0)
	{
		len = ft_nbrlen(n);
		type = '-';
	}
	else
		len = ft_nbrlen(n) + 1;
	convert(ft_abs(n), type, len);
}
