/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:05:40 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/20 16:18:02 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// free split
void	free_split(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

// get color
int	get_color(const char *line)
{
	char	*ptr;
	int		color;

	ptr = ft_strchr(line, ',');
	if (ptr == NULL)
		color = 0xffffff;
	else
		color = ft_atoi_hex(line);
	return (color);
}

// fill points with meta data
t_point	fill_point(char *array, t_point point, int x, int y)
{
	point.x = x * 40;
	point.y = y * 60;
	point.z = ft_atoi(array) * 10;
	point.color = get_color(array);
	return (point);
}

// fill the map with points
t_point	**fill_map(t_point **map, int fd, int *row, int *column)
{
	char	*line;
	char	**array;
	int		x;
	int		y;
	t_point	point;

	x = 0;
	while (x < (*row))
	{
		line = get_next_line(fd);
		array = ft_split(line, ' ');
		if (array == NULL)
			return (NULL);
		free(line);
		y = 0;
		while (y < *column)
		{
			point = fill_point(array[y], point, x, y);
			map[x][y] = point;
			y++;
		}
		free_split(array);
		x++;
	}
	return (map);
}
