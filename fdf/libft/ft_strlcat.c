/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 19:13:47 by phakakos          #+#    #+#             */
/*   Updated: 2019/11/04 17:34:06 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	y;
	size_t	dsts;
	size_t	srcs;

	i = ft_strlen(dst);
	y = 0;
	dsts = ft_strlen(dst);
	srcs = ft_strlen(src);
	while ((i + y + 1) < dstsize && src[y])
	{
		dst[i + y] = src[y];
		y++;
	}
	dst[i + y] = '\0';
	if ((dstsize + srcs) >= (dsts + srcs))
		return (dsts + srcs);
	return (dstsize + srcs);
}
