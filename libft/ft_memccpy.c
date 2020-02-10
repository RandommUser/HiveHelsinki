/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 18:34:29 by phakakos          #+#    #+#             */
/*   Updated: 2019/11/03 13:09:44 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	cc;
	unsigned char	*dstt;
	unsigned char	*srcc;
	size_t			i;

	i = 0;
	srcc = (unsigned char *)src;
	dstt = (unsigned char *)dst;
	cc = (unsigned char)c;
	while (i < n)
	{
		if (srcc[i] == cc)
		{
			dstt[i] = srcc[i];
			return (dst + ft_sizeofchar(i + 1));
		}
		dstt[i] = srcc[i];
		i++;
	}
	return (NULL);
}
