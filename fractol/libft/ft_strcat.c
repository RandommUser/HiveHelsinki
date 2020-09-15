/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 18:57:33 by phakakos          #+#    #+#             */
/*   Updated: 2019/10/17 19:11:07 by phakakos         ###   ########.fr       */
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

char		*ft_strcat(char *s1, const char *s2)
{
	int i;
	int	y;

	if (!s1[0])
		i = 0;
	else
		i = cat_end(s1);
	y = 0;
	while (s2[y])
	{
		s1[i + y] = s2[y];
		y++;
	}
	s1[i + y] = '\0';
	return (s1);
}
