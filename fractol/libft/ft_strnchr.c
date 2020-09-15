/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 15:52:35 by phakakos          #+#    #+#             */
/*   Updated: 2020/02/28 16:29:03 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnchr(const char *s, int c, size_t len)
{
	size_t	i;
	char	*ss;

	if (!s)
		return (NULL);
	i = 0;
	ss = (char *)s;
	while (i < len)
	{
		if (s[i] == c)
			return (ss + ft_sizeofchar(i));
		i++;
	}
	return (NULL);
}
