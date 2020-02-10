/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 12:05:22 by phakakos          #+#    #+#             */
/*   Updated: 2019/11/08 18:47:38 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*rtn;
	int		i;

	if (!s || !f)
		return (NULL);
	if (!(rtn = ft_strnew(ft_sizeofchar(ft_strlen(s) + 1))))
		return (NULL);
	i = 0;
	while (s[i])
	{
		rtn[i] = f(s[i]);
		i++;
	}
	return (rtn);
}
