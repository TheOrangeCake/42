/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:05:40 by hoannguy          #+#    #+#             */
/*   Updated: 2024/12/18 18:24:34 by hoannguy         ###   ########.fr       */
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
void	apply_rotation(t_params *params, t_point *point)
{
	double	temp_x;
	double	temp_y;
	double	temp_z;

	if (params -> switch_z == 0 && params -> switch_y == 0 && params -> switch_x == 1)
	{
		temp_y = point->y * cos(params->rotate_x) - point->z * sin(params->rotate_x);
		temp_z = point->y * sin(params->rotate_x) + point->z * cos(params->rotate_x);
		point->y = temp_y;
		point->z = temp_z;
	}
	if (params -> switch_z == 0 && params -> switch_y == 1 && params -> switch_x == 0)
	{
		temp_x = point->x * cos(params->rotate_y) + point->z * sin(params->rotate_y);
		temp_z = -point->x * sin(params->rotate_y) + point->z * cos(params->rotate_y);
		point->x = temp_x;
		point->z = temp_z;
	}
	if (params -> switch_z == 1 && params -> switch_y == 0 && params -> switch_x == 0)
	{
		temp_x = point->x * cos(params->rotate_z) - point->y * sin(params->rotate_z);
		temp_y = point->x * sin(params->rotate_z) + point->y * cos(params->rotate_z);
		point->x = temp_x;
		point->y = temp_y;
	}
	if (params -> switch_z == 0 && params -> switch_y == 0 && params -> switch_x == 2)
	{
		temp_y = point->y * cos(params->rotate_x) - point->z * sin(params->rotate_x);
		temp_z = point->y * sin(params->rotate_x) + point->z * cos(params->rotate_x);
		point->y = temp_y;
		point->z = temp_z;
	}
	if (params -> switch_z == 0 && params -> switch_y == 2 && params -> switch_x == 0)
	{
		temp_x = point->x * cos(params->rotate_y) + point->z * sin(params->rotate_y);
		temp_z = -point->x * sin(params->rotate_y) + point->z * cos(params->rotate_y);
		point->x = temp_x;
		point->z = temp_z;
	}
	if (params -> switch_z == 2 && params -> switch_y == 0 && params -> switch_x == 0)
	{
		temp_x = point->x * cos(params->rotate_z) - point->y * sin(params->rotate_z);
		temp_y = point->x * sin(params->rotate_z) + point->y * cos(params->rotate_z);
		point->x = temp_x;
		point->y = temp_y;
	}
}

// fill points with meta data
t_point	fill_point(char *array, t_point point, t_params *params)
{
	point.x = (params -> x) * 60;
	point.y = (params -> y) * 50;
	point.z = ft_atoi(array) * 5;
	point.color = get_color(array) * params -> color_change;
	apply_rotation(params, &point);
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
