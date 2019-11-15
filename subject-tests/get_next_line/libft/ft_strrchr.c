/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 11:30:22 by phakakos          #+#    #+#             */
/*   Updated: 2019/10/22 14:56:44 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*ss;

	i = ft_strlen(s);
	ss = (char *)s;
	while (i >= 0)
	{
		if (s[i] == c)
			return (ss + ft_sizeofchar(i));
		i--;
	}
	return (NULL);
}
