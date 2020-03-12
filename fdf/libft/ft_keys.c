/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 15:01:32 by phakakos          #+#    #+#             */
/*   Updated: 2020/02/20 16:07:35 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** These are functions to test for different parts for the keyboards
** Key numbers represent US keyboard layout
*/

#include "libft.h"

int	ft_isnumpad(int key)
{
	if (key >= 81 && key <= 89)
		return (1);
	if (key == 91 || key == 92 || key == 71 || key == 75 || key == 76)
		return (1);
	if (key == 78 || key == 65 || key == 67 || key == 69)
		return (1);
	return (0);
}

int	ft_isfunckey(int key)
{
	if (key >= 96 && key <= 101)
		return (1);
	if (key == 105 || key == 107 || key == 109 || key == 111)
		return (1);
	if (key == 113 || key == 118 || key == 120 || key == 120)
		return (1);
	return (0);
}

int	ft_isnavkey(int key)
{
	if (key >= 115 && key <= 117)
		return (1);
	if (key >= 123 && key <= 126)
		return (1);
	if (key == 119 || key == 121 || key == 279)
		return (1);
	return (0);
}

int	ft_iscontkey(int key)
{
	if (key >= 257 && key <= 262)
		return (1);
	if (key == 53 || key == 256 || key == 269 || key == 36)
		return (1);
	if (key == 48 || key == 51)
		return (1);
	return (0);
}

int	ft_isnumkey(int key)
{
	if (key >= 18 && key <= 23)
		return (1);
	if (key == 25 || key == 26 || key == 28 || key == 29)
		return (1);
	return (0);
}
