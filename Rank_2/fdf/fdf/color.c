/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:28:25 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/26 18:48:54 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	interpolating_color(t_point point1, t_point point0, t_bresenham line)
{
	t_color	color;
	float	fraction;

	color.red0 = (point0.color >> 16) & 0xFF;
	color.green0 = (point0.color >> 8) & 0xFF;
	color.blue0 = point0.color & 0xFF;
	color.red1 = (point1.color >> 16) & 0xFF;
	color.green1 = (point1.color >> 8) & 0xFF;
	color.blue1 = point1.color & 0xFF;
	fraction = (float)line.current_step / (float)line.step;
	color.red_new = (int)(color.red0
			+ ((color.red1 - color.red0) * fraction));
	color.green_new = (int)(color.green0
			+ ((color.green1 - color.green0) * fraction));
	color.blue_new = (int)(color.blue0
			+ ((color.blue1 - color.blue0) * fraction));
	color.color = ((color.red_new << 16)
			| (color.green_new << 8) | (color.blue_new));
	return (color.color);
}

int	step(t_bresenham line)
{
	if (line.dx >= line.dy)
		line.step = line.dx;
	else
		line.step = line.dy;
	return (line.step);
}
