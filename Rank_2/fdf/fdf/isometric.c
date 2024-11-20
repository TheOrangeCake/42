/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:49:37 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/20 11:37:00 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void shift_coordinates(t_point **map, int row, int column) {
    int x, y;
    double min_x = 0, min_y = 0;

    // Find the minimum transformed coordinates
    for (x = 0; x < row; x++) {
        for (y = 0; y < column; y++) {
            if (map[x][y].x < min_x)
                min_x = map[x][y].x;
            if (map[x][y].y < min_y)
                min_y = map[x][y].y;
        }
    }

    //Shift all points to make them positive
    for (x = 0; x < row; x++) {
        for (y = 0; y < column; y++) {
            map[x][y].x -= min_x;
            map[x][y].y -= min_y;
        }
    }
}

void	isometric(t_point **map, int row, int column)
{
	int	x;
	int	y;
	int	tempx;
	int	tempy;

	x = 0;
	while (x < (row))
	{
		y = 0;
		while (y < (column))
		{
			tempx = map[x][y].y;
			tempy = -map[x][y].x;
			map[x][y].x = (tempy - tempx) * sin(M_PI / -6) - map[x][y].z; //change this for vertical rotation
			map[x][y].y = (tempy + tempx) * cos(M_PI / -4);
			y++;
		}
		x++;
	}
	shift_coordinates(map, row, column);
}

// rotate the map 90%
// tempx = map[x][y].x;
// tempy = map[x][y].y;
// map[x][y].x = (tempy - tempx) * sin(M_PI / -6);
// map[x][y].y = (tempy + tempx) * cos(M_PI / -4) - map[x][y].z;
