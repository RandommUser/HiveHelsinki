/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 11:40:14 by phakakos          #+#    #+#             */
/*   Updated: 2019/11/08 18:41:10 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	searching(const char *haystack, const char *needle, int i)
{
	int y;

	y = 0;
	while (haystack[i + y] == needle[y])
	{
		if (needle[y] == '\0')
			return (i);
		y++;
	}
	if (!needle[y])
		return (i);
	else
		return (-1);
}

char		*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	char	*hay;

	i = 0;
	hay = (char *)haystack;
	if (!needle[0])
		return (hay);
	while (haystack[i])
	{
		if (haystack[i] == needle[0])
		{
			if (searching(haystack, needle, i) != -1)
				return (hay + ft_sizeofchar(i));
		}
		i++;
	}
	return (NULL);
}
