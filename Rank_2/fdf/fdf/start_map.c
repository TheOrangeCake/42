/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:09:05 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/18 15:06:18 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


t_point	**initiate_map(t_point **map, int *row, int column)
{
	int	x;

	x = 0;
	map = calloc(sizeof(t_point *), (*row));
	if (map == NULL)
		return (NULL);
	while (x < *row)
	{
		map[x] = calloc(sizeof(t_point), column);
		if (map[x] == NULL)
		{
			while (--x >= 0)
				free(map[x]);
			free(map);
			return (NULL);
		}
		x++;
	}
	return (map);
}

t_point	**start_map(int fd, int *row)
{
	int		i;
	int		column;
	char	*line;
	t_point	**map;

	line = get_next_line(fd);
	if (line == NULL)
		return (NULL);
	column = ft_strlen(line);
	*row = 1;
	while (1)
	{
		free(line);
		line = get_next_line(fd);
		if (line == NULL)
		{
			map = initiate_map(map, row, column);
			return (map);
		}
		i = ft_strlen(line);
		if (column < i)
			column = i;
		(*row)++;
	}
	return (NULL);
}

