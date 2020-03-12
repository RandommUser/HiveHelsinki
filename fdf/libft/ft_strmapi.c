/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 12:09:36 by phakakos          #+#    #+#             */
/*   Updated: 2019/11/08 18:46:58 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*rtn;

	if (!s || !f)
		return (NULL);
	if (!(rtn = ft_strnew(ft_sizeofchar(ft_strlen(s) + 1))))
		return (NULL);
	i = 0;
	while (s[i])
	{
		rtn[i] = f(i, s[i]);
		i++;
	}
	return (rtn);
}
