/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 10:53:33 by phakakos          #+#    #+#             */
/*   Updated: 2019/10/22 15:56:59 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*ss;

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
