/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 16:53:24 by phakakos          #+#    #+#             */
/*   Updated: 2019/11/01 20:53:25 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char		*create_num(char *s)
{
	char	*rtn;

	if (!(rtn = ft_strcreate(s, ft_strlen(s) + 1)))
		return (NULL);
	else
		return (rtn);
}

static char		*convert_int(int n, char type, size_t len)
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
		return (create_num(&inta[1]));
	else
		return (create_num(inta));
}

char			*ft_itoa(int n)
{
	char	type;
	size_t	len;

	type = '+';
	if (n == -2147483648)
		return (create_num("-2147483648"));
	else if (n == 2147483647)
		return (create_num("2147483647"));
	if (n < 0)
	{
		len = ft_nbrlen(n);
		type = '-';
	}
	else
		len = ft_nbrlen(n) + 1;
	return (convert_int(ft_abs(n), type, len));
}
