/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 12:26:49 by phakakos          #+#    #+#             */
/*   Updated: 2019/11/12 17:54:36 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*goal;
	char	*rtn;
	size_t	i;

	if (!s)
		return (NULL);
	goal = (char *)&s[start];
	if (!(rtn = ft_strnew(ft_sizeofchar(len) + 1)))
		return (NULL);
	i = 0;
	while (i < len)
	{
		rtn[i] = goal[i];
		i++;
	}
	return (rtn);
}
