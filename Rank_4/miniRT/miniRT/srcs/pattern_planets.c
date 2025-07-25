/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_planets.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 00:32:27 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/10 17:40:24 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	initialise_data(t_params *params, t_data *data, int type)
{
	if (type == EARTH)
		data->img = params->bump.earth;
	else if (type == MARS)
		data->img = params->bump.mars;
	else if (type == MERCU)
		data->img = params->bump.mercu;
	else if (type == PLUTO)
		data->img = params->bump.pluto;
	else if (type == VENUS)
		data->img = params->bump.venus;
	else if (type == EARTH_BUMP)
		data->img = params->bump.earthbump;
	else if (type == MARS_BUMP)
		data->img = params->bump.marsbump;
	else if (type == MERCU_BUMP)
		data->img = params->bump.mercubump;
	else if (type == PLUTO_BUMP)
		data->img = params->bump.plutobump;
	else if (type == VENUS_BUMP)
		data->img = params->bump.venusbump;
	data->addr = mlx_get_data_addr(data->img,
			&data->bits_per_pixel, &data->line_length, &data->endian);
}

// change u and v to displace the map
void	set_xy(t_vector hit_point, t_sphere *sphere, int *x, int *y)
{
	float		u;
	float		v;
	t_vector	center;

	center = vector_sub(hit_point, pos_to_vector(sphere->pos));
	u = 0.5f + atan2(center.c, center.a) / (2 * M_PI);
	v = acos(center.b / (sphere->d / 2.0f)) / M_PI;
	u = fmodf(u + U_SCALE, 1.0f);
	if (u < 0)
		u += 1.0f;
	if (u > 1)
		u = fmodf(u, 1.0f);
	v = fmodf(v + V_SCALE, 1.0f);
	if (v < 0)
		v = 0.0f;
	if (v > 1)
		v = 1.0f;
	*x = (int)(u * XPM_WIDTH);
	*y = (int)(v * XPM_HEIGHT);
}

t_color	planet_sphere(t_params *params,
		t_vector hit_point, t_sphere *sphere, int type)
{
	int			x;
	int			y;
	int			index;
	t_color		color;
	t_data		data;

	set_xy(hit_point, sphere, &x, &y);
	initialise_data(params, &data, type);
	index = y * data.line_length + x * (data.bits_per_pixel / 8);
	color.b = (unsigned char)data.addr[index + 0];
	color.g = (unsigned char)data.addr[index + 1];
	color.r = (unsigned char)data.addr[index + 2];
	return (color);
}
