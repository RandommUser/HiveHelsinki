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

void	map_print(t_map *map)
{
	int x;
	int y;

	y = 0;
	while (y <= 10)
	{
		x = 0;
		while (x <= 18)
		{
			print_point(map->start, x, y);
			x++;
		}
		y++;
	}
	exit(0);
}

t_map	*map_parse(t_map *new_map, char **file, int y)
{
ft_putstr("parsing a line\n");
	if (!file || !file[0])
		return (NULL);
	if (!new_map)
	{
//ft_putstr("making a new map\n");
		if (!(new_map = (t_map *)malloc(sizeof(t_map))))
			return (NULL);
//ft_putstr("putting scales\n");
		new_map->w_mod = W_MOD;
		new_map->h_mod = H_MOD;
		new_map->pos = coords(START_X, START_Y);
//ft_putstr("making points\n");
		if (!(new_map->start = point_conv((void *)0, file, y)))
			return (NULL);
//ft_putstr("made a new map object\n");
	}
	else
	{
//ft_putstr("adding to current map\n");
		if (!new_map->start || !(point_conv(new_map->start, file, y)))
			return (NULL);
//ft_putstr("added to current map\n");
	}
//	ft_putstr("\nCurrent point is ");
//	ft_putpointer(new_map->start);
//	ft_putchar('\n');
	return (new_map);
}

int		map_reader(t_mlx *mlx, char *file, t_map **map)
{
	int 	fd;
	long	len;
	char	*line;
	t_map	*new_map;
	int		y;
//ft_putstr("starting map reading\n");
	new_map = NULL;
	y = 0;
	if ((fd = open(file, O_RDONLY)) < 3)
		return (0);
	while (get_next_line(fd, &line) > -1 && line)
	{
//printf("this line:'%s'\n", line);
		if (!(new_map = map_parse(new_map, ft_strsplit(line, ' '), y)))
			return (0);
		y++;
	}
	if (new_map)
	{
		*map = new_map;
//ft_putstr("created a new map\n");
		//map_print(new_map);
	}
	else
		ft_putstr("skipped map making\n");
//	len = ft_chrcount(line, ' ') + 1;
	close(fd);
//file++;
//map++;
	return (1);
}
