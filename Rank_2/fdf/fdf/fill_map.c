/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:05:40 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/16 18:40:25 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
// #include <stdio.h>

// fill the map with points
int	**fill_map(int **map, int fd, int *i)
{
	char	*line;
	char	**array;
	int		x;
	int		y;

	x = 0;
	while(x <= ((*i) - 1))
	{
		line = get_next_line(fd);
		array = ft_split(line, ' ');
		y = 0;
		while (array[y] != NULL)
		{
			map[x][y] = ft_atoi(array[y]);
			y++;
		}
		free(line);
		x++;
	}
	// int		a;   // test array value
	// int		b;
	// b = 0;
	// while (b < 34)
	// {
	// 	a = 0;
	// 	while (a < 27)
	// 	{
	// 		printf("%d ", map[b][a]);
	// 		a++;
	// 	}
	// 	b++;
	// 	printf("\n");
	// }
    return (map);
}
