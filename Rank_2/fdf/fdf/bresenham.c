/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:34:36 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/20 16:21:36 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	find_sx(int *x0, int *x1, int *sx)
{
	if (*x0 < *x1)
		*sx = 1;
	else
		*sx = -1;
}

void	find_sy(int *y0, int *y1, int *sy)
{
	if (*y0 < *y1)
		*sy = 1;
	else
		*sy = -1;
}

void	move_horizontally(int *err, int *dy, int *x0, int *sx)
{
	*err -= *dy;
	*x0 += *sx;
}

void	move_vertically(int *err, int *dx, int *y0, int *sy)
{
	*err += *dx;
	*y0 += *sy;
}

void	bresenham(t_data *img, t_point point0, t_point point1)
{
	t_bresenham	line;

	line.x0 = point0.x;
	line.y0 = point0.y;
	line.x1 = point1.x;
	line.y1 = point1.y;
	line.dx = abs(line.x1 - line.x0);
	line.dy = abs(line.y1 - line.y0);
	find_sx(&line.x0, &line.x1, &line.sx);
	find_sy(&line.y0, &line.y1, &line.sy);
	line.err = line.dx - line.dy;
	while (line.x0 != line.x1 || line.y0 != line.y1)
	{
		my_mlx_pixel_put(img, line.x0, line.y0, point1.color);
		line.e2 = 2 * line.err;
		if (line.e2 > -line.dy)
			move_horizontally(&line.err, &line.dy, &line.x0, &line.sx);
		if (line.e2 < line.dx)
			move_vertically(&line.err, &line.dx, &line.y0, &line.sy);
	}
}
