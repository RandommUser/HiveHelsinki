/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 11:59:22 by phakakos          #+#    #+#             */
/*   Updated: 2020/02/20 17:03:26 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_map	*map_parse(t_map *new_map, char **file, int y)
{
	if (!file || !file[0])
		return (NULL);
	if (!new_map)
	{
		if (!(new_map = (t_map *)malloc(sizeof(t_map))) ||
		!(new_map->start = point_conv((void *)0, file, y)))
			mexit(ERR_MEMORY);
	}
	else
	{
		if (!new_map->start || !(point_conv(new_map->start, file, y)))
			mexit(ERR_MEMORY);
	}
	return (new_map);
}

int		map_reader(t_mlx *mlx, char *file, t_map **map)
{
	int		fd;
	char	*line;
	t_map	*new_map;
	int		y;

	new_map = NULL;
	y = 0;
	if ((fd = open(file, O_RDONLY)) < 3 || read(fd, NULL, 0) == -1)
		mexit(ERR_READER);
	while (get_next_line(fd, &line) > -1 && line)
	{
		if (line[0] && !(new_map = map_parse(new_map,
			ft_strsplit(line, ' '), y)))
			mexit(ERR_MEMORY);
		y += !line[0] ? 0 : 1;
		free(line);
	}
	if (!new_map)
		mexit(ERR_MAP);
	*map = new_map;
	map_size(map);
	settings_reset(*map, mlx);
	close(fd);
	return (1);
}
