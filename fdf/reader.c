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
ft_putstr("parsing a line\n");
	if (!file || !file[0])
		return (NULL);
	if (!new_map)
	{
		if (!(new_map = (t_map *)malloc(sizeof(t_map))) ||
		!(new_map->start = point_conv((void *)0, file, y)))
			return (NULL);
		new_map->h_mod = H_MOD;
		new_map->size = coords(1, 1);
		new_map->origin = mat4_trans((float[3]){START_X, START_Y, 1});
	}
	else
		if (!new_map->start || !(point_conv(new_map->start, file, y)))
			return (NULL);
	return (new_map);
}

int		map_reader(t_mlx *mlx, char *file, t_map **map)
{
	int 	fd;
	long	len;
	char	*line;
	t_map	*new_map;
	int		y;

	new_map = NULL;
	y = -1;
	if ((fd = open(file, O_RDONLY)) < 3)
		return (0);
	while (get_next_line(fd, &line) > -1 && line && ++y >= 0)
		if (!(new_map = map_parse(new_map, ft_strsplit(line, ' '), y)))
			return (0);
	if (new_map)
		*map = new_map;
	else
		ft_putstr("skipped map making\n");
	map_size(map);
	settings_reset(*map, mlx);
	close(fd);
	return (1);
}
