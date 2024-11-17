/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:09:05 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/17 11:46:29 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	**start_map(int fd, int *row, int *column)
{
	int		i;
	char	*line;
	t_point	**map;

	line = get_next_line(fd);
	if (line == NULL)
		return (NULL);
	*column = ft_strlen(line);
	*row = 1;
	while (true)
	{
		free(line);
		line = get_next_line(fd);
		if (line == NULL)
		{
			map = initiate_map(map, row, column);
			return (map);
		}
		i = ft_strlen(line);
		if (*column < i)
			*column = i;
		(*row)++;
	}
	return (NULL);
}

t_point	**initiate_map(t_point **map, int *row, int *column)
{
	int	x;
	int	y;

	x = 0;
	map = malloc(sizeof(t_point *) * (*row));
	if (map == NULL)
		return (NULL);
	while (x < *row)
	{
		y = 0;
		while (y < *column)
		{
			map[x][y] = malloc(sizeof(t_point) * 1);
			if (map[x][y] == NULL)
			{
				while (--y >= 0)
					free(map[x][y]);
				free(map);
				return (NULL);
			}
			y++;
		}
		x++;
	}
	return (map);
}
