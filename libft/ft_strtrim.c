/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 12:39:16 by phakakos          #+#    #+#             */
/*   Updated: 2019/11/08 18:44:01 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*check_start(char const *s)
{
	size_t	i;

	i = 0;
	while (s[i] && ft_isspace(s[i]))
		i++;
	return ((char *)&s[i]);
}

static size_t	check_len(char *s)
{
	size_t	len;

	len = ft_strlen(s);
	if (len == 0)
		return (0);
	while (s[len - 1] && ft_isspace(s[len - 1]))
		len--;
	return (len);
}

char			*ft_strtrim(char const *s)
{
	char	*start;
	char	*rtn;
	size_t	i;
	size_t	len;

	if (!s)
		return (NULL);
	start = check_start(s);
	len = check_len(start);
	if (!(rtn = ft_strnew(len + 1)))
		return (NULL);
	ft_bzero(rtn, len + 1);
	i = 0;
	while (i < len)
	{
		rtn[i] = start[i];
		i++;
	}
	return (rtn);
}
