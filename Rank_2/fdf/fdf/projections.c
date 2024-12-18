/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:49:37 by hoannguy          #+#    #+#             */
/*   Updated: 2024/12/18 19:33:38 by hoannguy         ###   ########.fr       */
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

void	isometric(t_params *params)
{
	int	x;
	int	y;
	int	tempx;
	int	tempy;

	x = 0;
	params -> projection = 1;
	while (x < (params -> row))
	{
		y = 0;
		while (y < (params -> column))
		{
			tempx = params -> map[x][y].y;
			tempy = -params -> map[x][y].x;
			params -> map[x][y].x = ((tempy - tempx) * sin(M_PI / -6)
					- params -> map[x][y].z) * params -> s_x;
			params -> map[x][y].y = ((tempy + tempx) * cos(M_PI / 4))
				* params -> s_y;
			y++;
		}
		x++;
	}
	find_coordinates(params -> map, params -> row, params -> column);
}

void	military(t_params *params, float d)
{
	int		x;
	int		y;
	float	cos_d;
	float	sin_d;

	cos_d = cos(d);
	sin_d = sin(d);
	x = 0;
	params -> projection = 0;
	while (x < params -> row)
	{
		y = 0;
		while (y < params -> column)
		{
			params -> map[x][y].x = (params -> map[x][y].x
					+ params -> map[x][y].z * cos_d) * params -> s_x;
			params -> map[x][y].y = (params -> map[x][y].y
					+ params -> map[x][y].z * sin_d) * params -> s_y;
			y++;
		}
		x++;
	}
	find_coordinates(params -> map, params -> row, params -> column);
}

void	flat(t_params *params)
{
	int	x;
	int	y;

	x = 0;
	params -> projection = 2;
	fill_map_helper(params);
	while (x < params -> row)
	{
		y = 0;
		while (y < params -> column)
		{
			params -> map[x][y].x *= params -> s_x;
			params -> map[x][y].y *= params -> s_y;
			y++;
		}
		x++;
	}
	find_coordinates(params -> map, params -> row, params -> column);
}
