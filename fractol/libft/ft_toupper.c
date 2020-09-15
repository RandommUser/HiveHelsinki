/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 14:40:45 by phakakos          #+#    #+#             */
/*   Updated: 2020/02/28 15:28:33 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_toupper(int c)
{
	if (ft_islower(c))
		return (c - 32);
	else
		return (c);
}

void	ft_strupper(char **str)
{
	size_t	i;

	if (!str)
		return ;
	i = 0;
	while (*str[i])
	{
		if (ft_islower(*str[i]))
			*str[i] = ft_toupper(*str[i]);
		i++;
	}
}
