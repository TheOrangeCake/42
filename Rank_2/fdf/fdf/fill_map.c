/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:05:40 by hoannguy          #+#    #+#             */
/*   Updated: 2025/03/04 17:00:03 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

t_point	**initiate_new_map(int *row, int *column)
{
	int		x;
	t_point	**map;

	x = 0;
	map = ft_calloc((*row), sizeof(t_point *));
	if (map == NULL)
		return (NULL);
	while (x < *row)
	{
		map[x] = ft_calloc(*column, sizeof(t_point));
		if (map[x] == NULL)
		{
			while (x-- > 0)
				free(map[x]);
			return (free(map), NULL);
		}
		x++;
	}
	return (map);
}

// fill points with meta data
t_point	fill_point(char *array, t_point point, t_params *params)
{
	point.x = (params -> x) * 60;
	point.y = (params -> y) * 50;
	point.z = ft_atoi(array) * 5;
	point.color = get_color(array) * params -> color_change;
	return (point);
}

// fill the map with points
t_point	**fill_map(t_params *params)
{
	t_point	point;

	params -> fd = open(params -> file_name, O_RDONLY);
	params -> x = 0;
	while (params -> x < params -> row)
	{
		params -> line = get_next_line(params -> fd);
		params -> array = ft_split(params -> line, ' ');
		if (params -> array == NULL)
			return (NULL);
		free(params -> line);
		params -> y = 0;
		while (params -> y < params -> column)
		{
			point = fill_point(params -> array[params -> y], point, params);
			params -> map[params -> x][params -> y] = point;
			params -> y++;
		}
		free_split(params -> array);
		params -> x++;
	}
	params -> line = get_next_line(params -> fd);
	close(params -> fd);
	return (params -> map);
}
