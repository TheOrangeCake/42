/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:49:37 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/27 15:32:51 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	shift_coordinates(t_point **map, t_save_line save, int row, int column)
{
	int	x;
	int	y;

	x = 0;
	while (x < row)
	{
		y = 0;
		while (y < column)
		{
			map[x][y].x -= save.min_x - 50;
			map[x][y].y -= save.min_y - 50;
			y++;
		}
		x++;
	}
}

void	find_coordinates(t_point **map, int row, int column)
{
	int			x;
	int			y;
	t_save_line	save;

	x = 0;
	save.min_x = 0;
	save.min_y = 0;
	while (x < row)
	{
		y = 0;
		while (y < column)
		{
			if (map[x][y].x < save.min_x)
				save.min_x = map[x][y].x;
			if (map[x][y].y < save.min_y)
				save.min_y = map[x][y].y;
			y++;
		}
		x++;
	}
	shift_coordinates(map, save, row, column);
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
			map[x][y].x = (tempy - tempx) * sin(M_PI / -6) - map[x][y].z;
			map[x][y].y = (tempy + tempx) * cos(M_PI / 4);
			y++;
		}
		x++;
	}
	find_coordinates(map, row, column);
}

void	military(t_point **map, int row, int column, float d)
{
	int		x;
	int		y;
	float	cos_d;
	float	sin_d;

	cos_d = cos(d);
	sin_d = sin(d);
	x = 0;
	while (x < row)
	{
		y = 0;
		while (y < column)
		{
			map[x][y].x = map[x][y].x + map[x][y].z * cos_d;
			map[x][y].y = map[x][y].y + map[x][y].z * sin_d;
			y++;
		}
		x++;
	}
	find_coordinates(map, row, column);
}


// rotate the map 90o
// tempx = map[x][y].x;
// tempy = map[x][y].y;
// map[x][y].x = (tempy - tempx) * sin(M_PI / -6);
// map[x][y].y = (tempy + tempx) * cos(M_PI / -4) - map[x][y].z;
