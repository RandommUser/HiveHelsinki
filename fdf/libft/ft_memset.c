/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 18:25:27 by phakakos          #+#    #+#             */
/*   Updated: 2019/10/22 14:47:34 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	char			*bb;
	unsigned char	cc;

	cc = (unsigned char)c;
	bb = (char *)b;
	i = 0;
	while (i < len)
	{
		bb[i] = cc;
		i++;
	}
	return (b);
}
