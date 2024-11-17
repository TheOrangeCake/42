/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:05:40 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/17 19:57:48 by hoannguy         ###   ########.fr       */
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

unsigned long	str_to_hex(char *ptr)
{
	int		i;
	char	temp[8];

	i = 0;
	while (i < 8)
	{
		temp[i] = ptr[i];
		i++;
	}
	temp[i] = '\0';
	printf("%s\n", temp); // finish with converting str to hex
	i = 0xff0000;
	return (i);
}

// get color
unsigned long	*get_color(char *line)
{
	int				i;
	int				j;
	unsigned long	*color;
	
	j = 0;
	i = 0;
	color = malloc(sizeof(unsigned long) * 150); //fix with proper size
	if (color == NULL)
		return (NULL);
	while (line[i] != '\0')
	{
		if(line[i] >= '0' && line[i] <= '9') //fix the condition
		{
			i++;
			if(line[i] == ',')
			{
				i++;
				color[j] = str_to_hex(&(line[i]));
				j++;
			}
			else if(line[i] == ' ')
			{
				color[j] = 0xffffff;
				j++;
			}
		}
		i++;
	}
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
	unsigned long 	*color;

	x = 0;
	while (x < (*row))
	{
		line = get_next_line(fd);
		color = get_color(line);
		array = ft_split(line, ' ');
		if (array == NULL || color == NULL)
			return (NULL);
		free(line);
		y = 0;
		while (array[y] != NULL)
		{
			point.z = ft_atoi(array[y]);
			point.color = color[y];
			point.end = 0;
			map[x][y] = point;
			y++;
		}
		map[x][y].end = 1;
		free_split(array);
		x++;
	}
    return (map);
}
