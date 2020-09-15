/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarrdel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 13:22:28 by phakakos          #+#    #+#             */
/*   Updated: 2019/12/09 13:26:12 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_strarrdel(char **strarr)
{
	int i;

	i = -1;
	if (strarr)
	{
		while (strarr[++i])
			ft_strdel(&strarr[i]);
		ft_strdel(&strarr[i]);
	}
	free(strarr);
}
