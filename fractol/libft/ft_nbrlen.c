/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 16:19:15 by phakakos          #+#    #+#             */
/*   Updated: 2019/11/17 14:13:20 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_nbrlen(long n)
{
	if (n < 0)
	{
		return (1 + ft_nbrlen(ft_abs(n)));
	}
	else if (n < 10)
		return (1);
	else
		return (1 + ft_nbrlen(n / 10));
}
