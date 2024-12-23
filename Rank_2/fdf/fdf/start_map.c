/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:09:05 by hoannguy          #+#    #+#             */
/*   Updated: 2024/12/23 17:15:05 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*replace_return(char **line)
{
	int	i;

	i = 0;
	while ((*line)[i] != '\0')
	{
		if ((*line)[i] == '\n')
			(*line)[i] = ' ';
		i++;
	}
	return (*line);
}

int	map_check(char *line, int column)
{
	int		i;
	char	**array;

	replace_return(&line);
	i = 0;
	array = ft_split(line, ' ');
	if (array == NULL)
		return (0);
	while (array[i] != NULL)
		i++;
	if (i != column)
		return (free_split(array), 0);
	else
	{
		free_split(array);
		return (1);
	}
}

t_point	**initiate_map(int *row, int *column)
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

// count row and column
t_point	**start_map(int fd, int *row, int *column)
{
	char	*line;
	char	**temp;

	line = get_next_line(fd);
	if (line == NULL)
		return (NULL);
	replace_return(&line);
	temp = ft_split(line, ' ');
	if (temp == NULL)
		return (free(line), NULL);
	while (temp[*column] != NULL)
		(*column)++;
	free_split(temp);
	while (1)
	{
		free(line);
		line = get_next_line(fd);
		if (line == NULL)
			return (free(line), initiate_map(row, column));
		if (map_check(line, *column) == 0)
			return (free(line), NULL);
		(*row)++;
	}
	return (NULL);
}

t_params	file_check(t_params params)
{
	params.fd = open(params.file_name, O_RDONLY);
	if (params.fd < 0)
	{
		ft_printf("Can't open file");
		close(params.fd);
		exit(EXIT_FAILURE);
	}
	params.map = start_map(params.fd, &(params.row), &(params.column));
	if (params.map == NULL)
	{
		ft_printf("Map error");
		close(params.fd);
		exit(EXIT_FAILURE);
	}
	close (params.fd);
	params.new_map = initiate_new_map(&(params.row), &(params.column));
	return (params);
}
