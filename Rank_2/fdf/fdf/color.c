/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:28:25 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/26 15:26:12 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	interpolating_color(int color1, int color0, int step, int current_step)
{
	t_color	color;
	float	fraction;

	color.red0 = color0 >> 16 & 0xFF;
	color.green0 = color0 >> 8 & 0xFF;
	color.blue0 = color0 & 0xFF;
	color.red1 = color1 >> 16 & 0xFF;
	color.green1 = color1 >> 8 & 0xFF;
	color.blue1 = color1 & 0xFF;
	fraction = (float)current_step / (float)step;
	color.red_new = (int)(color.red0 + ((color.red1 - color.red0) * fraction));
	color.green_new = (int)(color.green0 + ((color.green1 - color.green0) * fraction));
	color.blue_new = (int)(color.blue0 + ((color.blue1 - color.blue0) * fraction));
	color.color = ((color.red_new << 16) | (color.green_new << 8) | (color.blue_new));

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