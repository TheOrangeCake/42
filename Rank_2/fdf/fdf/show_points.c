/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_points.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:20:02 by hoannguy          #+#    #+#             */
/*   Updated: 2024/12/19 14:33:10 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// put pixel to screen
void	my_mlx_pixel_put(t_params *params, int x, int y, int color)
{
	char	*dest;

	if (x >= 0 && x < HEIGHT && y >= 0 && y < WIDTH)
	{
		dest = params -> addr + (x * params -> line_length + y
				* (params -> bits_per_pixel / 8));
		*(unsigned int *)dest = color;
	}
}

void	draw_horizontal(t_params *params)
{
	int	x;
	int	y;

	x = 0;
	while (x < params -> row)
	{
		y = 0;
		while (y < params -> column - 1)
		{
			bresenham(params, params -> new_map[x][y], params -> new_map[x][y + 1]);
			y++;
		}
		x++;
	}
}

void	draw_vertical(t_params *params)
{
	int	x;
	int	y;

	y = 0;
	while (y < params -> column)
	{
		x = 0;
		while (x < params -> row - 1)
		{
			bresenham(params, params -> new_map[x][y], params -> new_map[x + 1][y]);
			x++;
		}
		y++;
	}
}

// circle through points
void	create_image(t_params *params)
{
	draw_horizontal(params);
	draw_vertical(params);
}

	// int	x;
	// int	y;

	// x = 0;
	// while (x < *row)
	// {
	// 	y = 0;
	// 	while (y < *column)
	// 	{
	// 		my_mlx_pixel_put(img, map[x][y].x, map[x][y].y, map[x][y].color);
	// 		y++;
	// 	}
	// 	x++;
	// }