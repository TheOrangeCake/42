/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:09:05 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/16 20:13:55 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// count y without color
int	ft_strlen_no_color(char *line)
{
	int	i;
	int	count_color;
	int	count_space;

	i = 0;
	count_color = 0;
	count_space = 0;
	while (line[i])
	{
		i++;
		if(line[i] == ',')
			count_color++;
		if(line[i] == ' ')
			count_space++;
	}
	i = i - (count_color *9) - count_space - 1;
	return (i);
}

// malloc the map
int	**initiate_2D_map(int *x, int *y)
{
	int	**map;
	int	i;

	map = malloc(sizeof(int *) * (*x));
	if (map == NULL)
		return (NULL);
	i = 0;
	while (i < (*x))
	{
		map[i] = malloc(sizeof(int) * (*y));
		if (map[i] == NULL)
		{
			while (i > 0)
				free(map[--i]);
			free(map);
			return (NULL);
		}
		i++;
	}
	return (map);
}

// check if map is rectangular and no hole
int	**check_map(int fd, int *x, int *y)
{
	char	*line;
	int		j;

	line = get_next_line(fd);
	if (line == NULL)
	{
		ft_printf("File is empty or error");
		exit(EXIT_FAILURE);
	}
	*y = ft_strlen_no_color(line);
	*x = 1;
	while (line != NULL)
	{
		line = get_next_line(fd);
		if (line == NULL)
			return(initiate_2D_map(x, y));
		j = ft_strlen_no_color(line);
		if (j != *y)
		{
            free(line);
			ft_printf("Map error");
			exit(EXIT_FAILURE);
		}
		free(line);
		(*x)++;
	}
	return(initiate_2D_map(x, y));
}
