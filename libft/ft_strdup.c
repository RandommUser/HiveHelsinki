/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 18:28:07 by phakakos          #+#    #+#             */
/*   Updated: 2019/11/01 20:53:39 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*rtn;

	if ((rtn = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1))))
	{
		i = 0;
		while (s1[i])
		{
			rtn[i] = s1[i];
			i++;
		}
		rtn[i] = '\0';
		return (rtn);
	}
	else
		return (NULL);
}
