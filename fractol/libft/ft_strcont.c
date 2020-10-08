/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcont.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 12:19:57 by phakakos          #+#    #+#             */
/*   Updated: 2020/10/07 12:20:00 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcont(const char *str1, const char *str2)
{
	size_t	i;
	size_t	y;

	if (!str1 || !str2)
		return (0);
	i = -1;
	while (str1[++i])
	{
		y = -1;
		while (str2[++y])
		{
			if (str1[i] == str2[y])
			{
				y = 0;
				break ;
			}
		}
		if (y)
			return (0);
	}
	return (1);
}
