/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:44:20 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/18 17:34:41 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// void	drawline(t_data **img, int dx, int dy, int sx, int sy)
// {
// 	int	err;
//     int	e2;

// 	err = dx + dy;
// 	e2 = 2 * err;
// 	while(x0 != x1 && y0 != y1)
// 	{
// 		my_mlx_pixel_put(&img, x0, y0, 0x000000FF);
// 		if (e2 >= dy) 
// 		{
// 			err += dy;
// 			x0 += sx;
// 		} /* e_xy+e_x > 0 */
// 		if (e2 <= dx)
// 		{
// 			err += dx;
// 			y0 += sy;
// 		} /* e_xy+e_y < 0 */
// 	}
// }

void	bresenham(t_data **img, int x0, int y0, int x1, int y1)
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
	// drawline(img, dx, dy, sx, sy);
	err = dx + dy;
	e2 = 2 * err;
	while(x0 != x1 || y0 != y1)
	{
		my_mlx_pixel_put(&img, x0, y0, 0x000000FF);
		if (e2 >= dy) 
		{
			err += dy;
			x0 += sx;
		} /* e_xy+e_x > 0 */
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		} /* e_xy+e_y < 0 */
	}
}
