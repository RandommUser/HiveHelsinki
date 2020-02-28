/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 16:44:27 by phakakos          #+#    #+#             */
/*   Updated: 2020/02/28 19:57:08 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static char	*final_fix(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == -1)
			str[i] = '\0';
		i++;
	}
	return (str);
}

static void	strnrep(char *str, char c, int n, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (str[i] == c)
			str[i] = n;
		i++;
	}
}

static int	return_handle(int exit, char **line, char **files)
{
	char	*temp;
	char	*rtn;

	*line = NULL;
	if (exit != 1)
		return (exit);
	if (!ft_strchr(*files, '\n'))
		rtn = *files;
	else if (!(rtn = ft_strsub(*files, 0, ft_strclen(*files, '\n'))))
		exit = -1;
	if (!rtn || (ft_strclen(*files, '\0') - ft_strclen(*files, '\n')) < 2)
		temp = NULL;
	else if (!(temp = ft_strcreate((ft_strchr(*files, '\n') + 1), \
					ft_strclen(*files, '\0') + 1)))
		exit = -1;
	if (exit == 1)
	{
		if (*files != rtn)
			free(*files);
		*files = temp;
		*line = final_fix(rtn);
	}
	else
		free(rtn);
	return (exit);
}

int			get_next_line(const int fd, char **line)
{
	char		*temp;
	char		text[BUFF_SIZE + 1];
	static char	*files[FD_LIMIT + 1];
	long		len;

	if (!line)
		return (-1);
	len = 0;
	while (fd >= 0 && fd <= FD_LIMIT && !ft_strchr(files[fd], '\n') && \
			(len = read(fd, &text, BUFF_SIZE)) > 0)
	{
		strnrep(text, '\0', -1, len - 1);
		text[len] = '\0';
		if (!(temp = ft_strjoin(files[fd], text)))
			return (return_handle(-1, line, NULL));
		free(files[fd]);
		files[fd] = temp;
		temp = NULL;
	}
	if (len < 0 || fd < 0 || fd > FD_LIMIT)
		return (return_handle(-1, line, NULL));
	if (files[fd] && files[fd][0] != '\0')
		return (return_handle(1, line, &files[fd]));
	return (return_handle(0, line, NULL));
}
