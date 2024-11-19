/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:05:40 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/19 11:29:43 by hoannguy         ###   ########.fr       */
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

// fill the map with points
t_point	**fill_map(t_point **map, int fd, int *row)
{
	char			*line;
	char			**array;
	int				x;
	int				y;
	t_point 		point;

	x = 0;
	while (x < (*row))
	{
		line = get_next_line(fd);
		array = ft_split(line, ' ');
		if (array == NULL)
			return (NULL);
		free(line);
		y = 0;
		while (array[y] != NULL)
		{
			point.x = x * 20;
			point.y = y * 20;
			point.z = ft_atoi(array[y]);
			point.color = get_color(array[y]);
			point.end = 0;
			map[x][y] = point;
			y++;
		}
		map[x][y - 1].end = 1;
		free_split(array);
		x++;
	}
    return (map);
}
