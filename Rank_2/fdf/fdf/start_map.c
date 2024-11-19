/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:09:05 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/19 12:03:58 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// calloc map
void	**initiate_map(t_point ***map, int *row, int *column)
{
	int	x;

	x = 0;
	*map = calloc((*row), sizeof(t_point *));
	if (*map == NULL)
		return (NULL);
	while (x < *row)
	{
		(*map)[x] = calloc(*column, sizeof(t_point));
		if ((*map)[x] == NULL)
		{
			while (x-- > 0)
				free((*map)[x]);
			return (free(*map), NULL);
		}
		x++;
	}
}

// count row and column
t_point	**start_map(int fd, int *row, int *column)
{
	char	*line;
	t_point	**map;
	char	**temp;

	map = NULL;
	line = get_next_line(fd);
	if (line == NULL)
		return (NULL);
	temp = ft_split(line, ' ');
	if (temp == NULL)
		return (free(line), NULL);
	while (temp[*column] != NULL)
		(*column)++;
	free(temp);
	while (1)
	{
		free(line);
		line = get_next_line(fd);
		if (line == NULL)
			return (initiate_map(&map, row, column), free(line), map);
		(*row)++;
	}
	return (NULL);
}
