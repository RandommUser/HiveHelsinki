/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 12:00:14 by phakakos          #+#    #+#             */
/*   Updated: 2019/11/08 18:40:57 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	searching(const char *hay, const char *needl, size_t i, size_t len)
{
	size_t y;

	y = 0;
	while (hay[i + y] == needl[y] && (i + y) < len)
	{
		if (needl[y] == '\0')
			return (i);
		y++;
	}
	if (!needl[y])
		return (i);
	else
		return (-1);
}

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	char	*hay;

	i = 0;
	hay = (char *)haystack;
	if (!needle[0])
		return (hay);
	while (haystack[i] && i < len)
	{
		if (haystack[i] == needle[0])
			if (searching(haystack, needle, i, len) != -1)
				return (hay + ft_sizeofchar(i));
		i++;
	}
	return (NULL);
}
