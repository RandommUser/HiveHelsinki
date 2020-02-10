/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hxdm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:31:12 by phakakos          #+#    #+#             */
/*   Updated: 2019/11/17 15:18:50 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	convert(long n)
{
	int	c;

	c = n % 16;
	if (c > 9)
		return ('a' + (c - 10));
	else
		return ('0' + c);
}

char		*ft_hxdm(long n)
{
	char	*rtn;
	char	*temp;
	size_t	i;
	size_t	len;

	len = ft_nbrlen(n);
	if (!(rtn = ft_strnew(len + 1)))
		return (NULL);
	i = len - 1;
	ft_memset(rtn, '0', len);
	while (n > 0)
	{
		rtn[i] = convert(n);
		n = n / 16;
		i--;
	}
	if (!(temp = ft_strdup(&rtn[ft_strrclen(rtn, '0')])))
		return (NULL);
	free(rtn);
	return (temp);
}
