/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 19:06:56 by phakakos          #+#    #+#             */
/*   Updated: 2019/11/05 14:58:10 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cat_end(char *s1)
{
	int i;

	i = 0;
	while (s1[i])
		i++;
	return (i);
}

char		*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	y;

	if (!s1[0])
		i = 0;
	else
		i = cat_end(s1);
	y = 0;
	while (y < n && s2[y])
	{
		s1[i + y] = s2[y];
		y++;
	}
	s1[i + y] = '\0';
	return (s1);
}
