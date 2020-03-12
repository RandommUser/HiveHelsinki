/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 11:55:56 by phakakos          #+#    #+#             */
/*   Updated: 2019/11/01 20:53:31 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strnew(size_t size)
{
	char	*rtn;

	if (!(rtn = (char *)malloc(ft_sizeofchar(size))))
		return (NULL);
	ft_memset(rtn, '\0', size);
	return (rtn);
}
