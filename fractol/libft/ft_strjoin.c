/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 12:34:29 by phakakos          #+#    #+#             */
/*   Updated: 2019/11/28 13:14:53 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*rtn;
	size_t	len;

	if (!s1 && !s2)
		return (NULL);
	len = 1;
	if (s1)
		len += ft_strlen(s1);
	if (s2)
		len += ft_strlen(s2);
	if (!(rtn = ft_strnew(len)))
		return (NULL);
	if (s1)
		ft_strcat(rtn, s1);
	if (s2)
		ft_strcat(rtn, s2);
	return (rtn);
}
