/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:05:40 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/17 13:31:21 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

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

// fill the map with points
t_point	**fill_map(t_point **map, int fd, int *row)
{
	char	*line;
	char	**array;
	int		x;
	int		y;
	t_point point;

	x = 0;
	while (x < (*row))
	{
		line = get_next_line(fd);
		array = ft_split(line, ' ');
		free(line);
		if (array == NULL)
			return (NULL);
		y = 0;
		while (array[y] != NULL)
		{
			point.z = ft_atoi(array[y]);
			map[x][y] = point;
			y++;
		}
		free_split(array);
		x++;
	}
    return (map);
}
