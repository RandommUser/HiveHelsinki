/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 12:12:40 by phakakos          #+#    #+#             */
/*   Updated: 2019/11/08 18:52:16 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strequ(char const *s1, char const *s2)
{
	if (s1 == s2)
		return (1);
	if (s1 == NULL || s2 == NULL)
		return (0);
	if (ft_strcmp(s1, s2) != 0)
		return (0);
	return (1);
}
