/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:04:11 by hoannguy          #+#    #+#             */
/*   Updated: 2025/06/25 13:06:55 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

char	*get_bump_data(t_params *params, t_sphere *sphere, t_data *data)
{
	if (sphere->texture_type == EARTH)
		data->img = params->bump.earthbump;
	else if (sphere->texture_type == MARS)
		data->img = params->bump.marsbump;
	else if (sphere->texture_type == MERCU)
		data->img = params->bump.mercubump;
	else if (sphere->texture_type == PLUTO)
		data->img = params->bump.plutobump;
	else if (sphere->texture_type == VENUS)
		data->img = params->bump.venusbump;
	else
		return (NULL);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	return (data->addr);
}

void	apply_bump_normal(t_vector center, float du, float dv, t_ray *ray)
{
	t_vector		tangent;
	t_vector		bitangent;
	t_vector		bump_offset;

	tangent.a = -center.c;
	tangent.b = 0;
	tangent.c = center.a;
	vector_normalize(&tangent);
	if (vector_norm2(tangent) < 0.000001f)
	{
		tangent.a = 1;
		tangent.a = 0;
		tangent.a = 0;
	}
	bitangent = vector_cross(center, tangent);
	vector_normalize(&bitangent);
	bump_offset = vector_add(vector_multi(du * 2.0f, tangent),
			vector_multi(dv * 2.0f, bitangent));
	ray->normal = vector_add(ray->normal, bump_offset);
	vector_normalize(&ray->normal);
}

void	calculate_du_dv(t_data data, float *du,
		float *dv, t_value_float *uv)
{
	t_value_int		xy;
	int				index;
	int				index_u;
	int				index_v;
	float			base_h;

	xy.x = (int)(uv->t1 * XPM_WIDTH);
	xy.y = (int)(uv->t2 * XPM_HEIGHT);
	index = xy.y * data.line_length + xy.x * (data.bits_per_pixel / 8);
	index_u = xy.y * data.line_length + ((xy.x + 1) % XPM_WIDTH)
		* (data.bits_per_pixel / 8);
	index_v = ((xy.y + 1) % XPM_HEIGHT) * data.line_length + xy.x
		* (data.bits_per_pixel / 8);
	base_h = (unsigned char)data.addr[index + 2] / 255.0f;
	*du = base_h - ((float)(unsigned char)data.addr[index_u + 2] / 255.0f);
	*dv = base_h - ((float)(unsigned char)data.addr[index_v + 2] / 255.0f);
}

void	apply_bump(t_params *params, t_ray *ray, t_sphere *sphere)
{
	t_data			data;
	t_vector		center;
	t_value_float	uv;
	float			du;
	float			dv;

	data.addr = get_bump_data(params, sphere, &data);
	if (!data.addr)
		return ;
	center = vector_sub(ray->hit_point, pos_to_vector(sphere->pos));
	uv.t1 = 0.5f + atan2(center.c, center.a) / (2 * M_PI);
	uv.t2 = acos(center.b / (sphere->d / 2.0f)) / M_PI;
	uv.t1 = fmodf(uv.t1 + U_SCALE, 1.0f);
	uv.t2 = fmodf(uv.t2 + V_SCALE, 1.0f);
	if (uv.t1 < 0)
		uv.t1 += 1.0f;
	calculate_du_dv(data, &du, &dv, &uv);
	apply_bump_normal(center, du, dv, ray);
}
