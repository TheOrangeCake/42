/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:49:37 by hoannguy          #+#    #+#             */
/*   Updated: 2024/12/19 15:50:23 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	shift_coordinates(t_point **new_map, t_save_line save, int row, int column)
{
	int	x;
	int	y;

	x = 0;
	while (x < row)
	{
		y = 0;
		while (y < column)
		{
			new_map[x][y].x -= save.min_x - 50;
			new_map[x][y].y -= save.min_y - 50;
			y++;
		}
		x++;
	}
}

void	find_coordinates(t_point **new_map, int row, int column)
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
			if (new_map[x][y].x < save.min_x)
				save.min_x = new_map[x][y].x;
			if (new_map[x][y].y < save.min_y)
				save.min_y = new_map[x][y].y;
			y++;
		}
		x++;
	}
	shift_coordinates(new_map, save, row, column);
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
			tempx = params -> new_map[x][y].y;
			tempy = -params -> new_map[x][y].x;
			params -> new_map[x][y].x = ((tempy - tempx) * sin(M_PI / -6)
					- params -> new_map[x][y].z) * params -> s_x;
			params -> new_map[x][y].y = ((tempy + tempx) * cos(M_PI / 4))
				* params -> s_y;
			y++;
		}
		x++;
	}
	find_coordinates(params -> new_map, params -> row, params -> column);
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
			params -> new_map[x][y].x = (params -> new_map[x][y].x
					+ params -> new_map[x][y].z * cos_d) * params -> s_x;
			params -> new_map[x][y].y = (params -> new_map[x][y].y
					+ params -> new_map[x][y].z * sin_d) * params -> s_y;
			y++;
		}
		x++;
	}
	find_coordinates(params -> new_map, params -> row, params -> column);
}

void	flat(t_params *params)
{
	int	x;
	int	y;

	x = 0;
	params -> projection = 2;
	while (x < params -> row)
	{
		y = 0;
		while (y < params -> column)
		{
			params -> new_map[x][y].x *= params -> s_x;
			params -> new_map[x][y].y *= params -> s_y;
			y++;
		}
		x++;
	}
	find_coordinates(params -> new_map, params -> row, params -> column);
}
