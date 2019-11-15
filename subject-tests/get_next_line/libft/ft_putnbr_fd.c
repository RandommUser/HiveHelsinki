/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 16:25:37 by phakakos          #+#    #+#             */
/*   Updated: 2019/11/12 18:09:46 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static void	convert_int(int n, char type, size_t len, int fd)
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
		write(fd, &inta[1], len - 1);
	else
		write(fd, inta, len);
}

void		ft_putnbr_fd(int n, int fd)
{
	char	type;
	size_t	len;

	if (fd < 0)
		return ;
	type = '+';
	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	else if (n == 2147483647)
	{
		ft_putstr_fd("2147483647", fd);
		return ;
	}
	if (n < 0)
	{
		len = ft_nbrlen(n);
		type = '-';
	}
	else
		len = ft_nbrlen(n) + 1;
	convert_int(ft_abs(n), type, len, fd);
}
