/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chrcount.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 12:12:03 by phakakos          #+#    #+#             */
/*   Updated: 2020/02/11 12:14:01 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_chrcount(char *str, char c)
{
	long	i;
	long	rtn;

	i = -1;
	rtn = 0;
	while (str[++i])
		rtn = str[i] == c ? rtn + 1 : rtn;
	return (rtn);
}
