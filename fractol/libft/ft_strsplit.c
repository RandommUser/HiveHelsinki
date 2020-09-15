/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 12:50:56 by phakakos          #+#    #+#             */
/*   Updated: 2019/11/11 14:52:23 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char		**free_fail(char **s, int i)
{
	while (i >= 0)
	{
		if (s[i])
			free(s[i]);
		i--;
	}
	free(s);
	return (NULL);
}

static size_t	split_len(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int		count_words(char const *s, char c)
{
	int i;
	int	rtn;

	if (!s || !ft_isascii(c))
		return (-1);
	i = 0;
	rtn = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			i = i + (int)split_len(&s[i], c);
			rtn++;
		}
	}
	return (rtn);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**rtn;
	int		y;
	int		i;
	int		words;

	if ((words = count_words(s, c)) < 0)
		return (NULL);
	if (!(rtn = (char **)ft_memalloc(sizeof(char *) * (words + 1))))
		return (NULL);
	i = 0;
	y = 0;
	while (s[y])
	{
		if (s[y] == c)
			y++;
		else
		{
			if (!(rtn[i] = ft_strcreate(&s[y], (split_len(&s[y], c)))))
				return (free_fail(rtn, i - 1));
			y = y + (int)split_len(&s[y], c);
			i++;
		}
	}
	rtn[i] = NULL;
	return (rtn);
}
