/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 18:30:55 by phakakos          #+#    #+#             */
/*   Updated: 2019/11/12 17:53:56 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*dstt;
	char	*srcc;

	i = 0;
	dstt = (char *)dst;
	srcc = (char *)src;
	if (dst == src)
		return (dst);
	while (i < n)
	{
		dstt[i] = srcc[i];
		i++;
	}
	return (dst);
}
