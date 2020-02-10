/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcreate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 13:56:55 by phakakos          #+#    #+#             */
/*   Updated: 2019/10/28 15:47:13 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcreate(char const *s, size_t len)
{
	char	*rtn;

	if (!(rtn = ft_strnew(len)))
		return (NULL);
	ft_strncpy(rtn, s, len);
	return (rtn);
}
