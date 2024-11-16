/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:09:05 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/16 14:01:57 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_strlen_no_color(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		i++;
		if(line[i] == ',')
			count++;
	}
	i = i - (count *9);
	return (i);
}

int	**initiate_2D_map(int *x, int y)
{
	int	**map;
	int	i;

	map = malloc(sizeof(int *) * (*x));
	if (map == NULL)
		return (NULL);
	i = 0;
	while (i < (*x))
	{
		map[i] = malloc(sizeof(int) * y);
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

int	**check_map(int fd, int *x)
{
	char	*line;
	int		i;
	int		j;

	line = get_next_line(fd);
	if (line == NULL)
	{
		ft_printf("File is empty or error");
		exit(EXIT_FAILURE);
	}
	i = ft_strlen_no_color(line);
	*x = 1;
	while (line != NULL)
	{
		line = get_next_line(fd);
		if (line == NULL)
			return(initiate_2D_map(x, i));
		j = ft_strlen_no_color(line);
		if (j != i)
		{
            free(line); // potential leak here, to free all previous get_next_line
			ft_printf("Map error");
			exit(EXIT_FAILURE);
		}
		(*x)++;
	}
	return(initiate_2D_map(x, i));
}
