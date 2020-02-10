/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 18:43:54 by phakakos          #+#    #+#             */
/*   Updated: 2019/10/29 13:15:51 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	copy_rev(char *dstt, const char *srcc, size_t len)
{
	while (len > 0)
	{
		dstt[len - 1] = srcc[len - 1];
		len--;
	}
}

void		*ft_memmove(void *dst, const void *src, size_t len)
{
	const char	*srcc;
	char		*dstt;
	size_t		i;

	i = 0;
	dstt = (char *)dst;
	srcc = (const char *)src;
	if (dst < src)
	{
		while (i < len)
		{
			dstt[i] = srcc[i];
			i++;
		}
	}
	else if (dst == src)
		return (dst);
	else
		copy_rev(dstt, srcc, len);
	return (dst);
}
