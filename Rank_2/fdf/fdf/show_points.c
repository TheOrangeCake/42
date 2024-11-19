/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_points.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:20:02 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/19 12:04:11 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// put pixel to screen
void	my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	char	*dest;

	dest = img->addr + (x * img->line_length + y * (img->bits_per_pixel / 8));
	*(unsigned int*)dest = color;
}

void	bresenham(t_data *img, int x0, int y0, int x1, int y1)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
    int	e2;

	dx = ABS(x1 - x0);
	dy = -ABS(y1 - y0);
	if (x0 < x1)
		sx = 1;
	else
		sx = -1;
	if (y0 < y1)
		sy = 1;
	else
		sy = -1;
	err = dx + dy;
	e2 = 2 * err;
	while(x0 != x1 || y0 != y1)
	{
		my_mlx_pixel_put(img, x0, y0, 0x0000FF);
		if (e2 >= dy) 
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

// circle through points
void	create_image(t_data *img, t_point **map, int *row, int *column)
{
	int x;
	int y;

	x = 0;
	while (x < *row)
	{
 		y = 0;
		while (y < *column)
		{
			my_mlx_pixel_put(img, map[x][y].x, map[x][y].y, map[x][y].color);
			y++;
		}
		x++;
	}
	x = 0;
	// while (x < *row)
	// {
	// 	y = 0;
	// 	while (y < *column)
	// 	{
	// 		bresenham(img, map[x][y].x, map[x][y].y, map[x + 1][y].x, map[x + 1][y].y);
	// 		bresenham(img, map[x][y].x, map[x][y].y, map[x][y + 1].x, map[x][y + 1].y);
	// 		y++;
	// 	}
	// 	x++;
	// }
		// y = 0;
		// x = 0;
		// while (x < *row - 1)
		// {
		// 	bresenham(img, map[x][y].x, map[x][y].y, map[x + 1][y].x, map[x + 1][y].y);
		// 	// bresenham(img, map[x][y].x, map[x][y].y, map[x][y + 1].x, map[x][y + 1].y);
		// 	x++;
		// }

		// y = 0;
		// x = 0;
		// while (y < *column)
		// {
		// 	// bresenham(img, map[x][y].x, map[x][y].y, map[x + 1][y].x, map[x + 1][y].y);
		// 	bresenham(img, map[x][y].x, map[x][y].y, map[x][y + 1].x, map[x][y + 1].y);
		// 	y++;
		// }
		
		// y = 0;
		// x = 1;
		// while (y < *column)
		// {
		// 	// bresenham(img, map[x][y].x, map[x][y].y, map[x + 1][y].x, map[x + 1][y].y);
		// 	bresenham(img, map[x][y].x, map[x][y].y, map[x][y + 1].x, map[x][y + 1].y);
		// 	y++;
		// }
}
