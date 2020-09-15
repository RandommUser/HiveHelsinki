/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 10:53:33 by phakakos          #+#    #+#             */
/*   Updated: 2019/11/19 18:44:06 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*ss;

	if (!s)
		return (NULL);
	i = 0;
	ss = (char *)s;
	while (s[i])
	{
		if (s[i] == c)
			return (ss + ft_sizeofchar(i));
		i++;
	}
	if (c == '\0')
		return (ss + ft_sizeofchar(i));
	else
		return (NULL);
}
