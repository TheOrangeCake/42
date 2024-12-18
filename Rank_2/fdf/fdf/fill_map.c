/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:05:40 by hoannguy          #+#    #+#             */
/*   Updated: 2024/12/18 11:11:36 by hoannguy         ###   ########.fr       */
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
t_point	fill_point(char *array, t_point point, t_params *params)
{
	point.x = (params -> x) * 60;
	point.y = (params -> y) * 50;
	point.z = ft_atoi(array) * 5;
	point.color = get_color(array);
	return (point);
}

// fill the map with points
t_point	**fill_map(t_params *params)
{
	t_point	point;

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
	return (params -> map);
}
