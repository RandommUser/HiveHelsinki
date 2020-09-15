/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 14:47:54 by phakakos          #+#    #+#             */
/*   Updated: 2020/02/28 15:28:47 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_tolower(int c)
{
	if (ft_isupper(c))
		return (c + 32);
	else
		return (c);
}

void	ft_strlower(char **str)
{
	size_t	i;

	if (!str)
		return ;
	i = 0;
	while (*str[i])
	{
		if (ft_isupper(*str[i]))
			*str[i] = ft_tolower(*str[i]);
		i++;
	}
}
