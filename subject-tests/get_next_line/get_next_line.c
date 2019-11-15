/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 16:44:27 by phakakos          #+#    #+#             */
/*   Updated: 2019/11/15 17:07:52 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static long	ft_strclen(const char *s, char c)
{
	long	i;

	i = 0;
	while (s[i] && s[i] != c)
	{
		i += 1;
	}
	return (i);
}

static int	return_handle(int i, char **line, char **files)
{
	char	*temp;
	char	*rtn;

	if (i == -1)
	{
		*line = NULL;
		return (i);
	}
	if (files == NULL)
	{
		*line = NULL;
		return (0);
	}
	if (!(rtn = ft_strsub(*files, 0, ft_strclen(*files, '\n'))))
		i = -1;
	if (!ft_strchr(*files, '\n'))
		temp = NULL;
	else if (!(temp = ft_strcreate((ft_strchr(*files, '\n') + 1), \
					ft_strclen(*files, '\0') + 1)))
		i = -1;
	free(*files);
	*files = temp;
	*line = rtn;
	return (i);
}

static char	*handle_read(const char *dst, char *src, long slen)
{
	char	*rtn;

	src[slen] = '\0';
	if (!(rtn = ft_strnew(ft_strclen(dst, '\0') + slen + 1)))
		return (NULL);
	ft_strncat(rtn, dst, ft_strclen(dst, '\0'));
	ft_strncat(rtn, src, slen);
	return (rtn);
}

int			get_next_line(const int fd, char **line)
{
	char		*temp;
	char		text[BUFF_SIZE + 1];
	static char	*files[FD_LIMIT];
	long		len;

	while (fd >= 0 && (len = read(fd, &text, BUFF_SIZE)) > 0)
	{
		if (!files[fd])
			if (!(files[fd] = ft_strnew(BUFF_SIZE + 1)))
				return (return_handle(-1, line, NULL));
		if (!(temp = handle_read(files[fd], text, len)))
			return (return_handle(-1, line, NULL));
		free(files[fd]);
		files[fd] = temp;
		temp = NULL;
		if (ft_strchr(files[fd], '\n'))
			return (return_handle(1, line, &files[fd]));
	}
	if (len < 0 || fd < 0)
		return (return_handle(-1, line, NULL));
	if (files[fd] && files[fd][0] != '\0')
		return (return_handle(1, line, &files[fd]));
	return (return_handle(0, line, NULL));
}
