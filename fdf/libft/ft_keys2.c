/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 15:48:20 by phakakos          #+#    #+#             */
/*   Updated: 2020/02/20 16:05:54 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalphakey(int key)
{
	if ((key >= 0 && key <= 9) || (key >= 11 && key <= 17))
		return (1);
	if (key == 31 || key == 32 || key == 34 || key == 35 || key == 37)
		return (1);
	if (key == 38 || key == 40 || key == 45 || key == 46)
		return (1);
	return (0);
}

int	ft_ismisckey(int key)
{
	if (key == 24 || key == 27 || key == 30 || key == 33)
		return (1);
	if (key == 39 || key == 41 || key == 43 || key == 44)
		return (1);
	if (key == 47 || key == 50)
		return (1);
	return (0);
}

int	ft_iskey(int key)
{
	if (ft_isalphakey(key))
		return (1);
	if (ft_isnumpad(key))
		return (1);
	if (ft_isfunckey(key))
		return (1);
	if (ft_isnavkey(key))
		return (1);
	if (ft_iscontkey(key))
		return (1);
	if (ft_isnumkey(key))
		return (1);
	return (ft_ismisckey(key));
}
