/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 18:39:40 by phakakos          #+#    #+#             */
/*   Updated: 2019/11/06 13:35:28 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ncpy_null(char *dst, size_t i, size_t len)
{
	while (i < len)
	{
		dst[i] = '\0';
		i++;
	}
}

char		*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if ((i + 1) == len && src[i] == '\0')
		{
			dst[i] = '\0';
			i++;
			break ;
		}
		if (!src[i])
			break ;
		dst[i] = src[i];
		i++;
	}
	if (i != len)
		ncpy_null(dst, i, len);
	return (dst);
}
