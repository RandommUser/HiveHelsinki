/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 19:39:08 by phakakos          #+#    #+#             */
/*   Updated: 2020/02/28 19:41:59 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strnrep(char **str, char c, char n, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (*str[i] == c)
			*str[i] = n;
		i++;
	}
}

void	ft_strrep(char **str, char c, char n)
{
	size_t	i;

	i = 0;
	if (!str)
		return ;
	while (*str[i])
	{
		if (*str[i] == c)
			*str[i] = n;
		i++;
	}
}
