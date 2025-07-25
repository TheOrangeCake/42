/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:18:10 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/07 16:34:49 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

float	d_light_plane(t_vector light_pos, t_plane *plane)
{
	float		light_to_plane;
	t_vector	temp;

	temp = vector_sub(light_pos, pos_to_vector(plane->pos));
	light_to_plane = fabsf(vector_dot(temp, plane->vector));
	return (light_to_plane);
}

bool	shadow_plane_check(t_params *params, t_ray *shadow,
		t_ray *ray, t_vector light_pos)
{
	int			i;
	float		denom;
	float		t;
	t_vector	op;
	float		light_dist;

	if (!params->plane)
		return (false);
	light_dist = vector_dot(vector_sub(light_pos, ray->hit_point),
			vector_sub(light_pos, ray->hit_point));
	i = -1;
	while (params->plane[++i])
	{
		if (params->plane[i] == ray->hit_plane
			|| d_light_plane(light_pos, params->plane[i]) < 0.01f)
			continue ;
		denom = vector_dot(shadow->direction, params->plane[i]->vector);
		if (fabsf(denom) < 0.000001f)
			continue ;
		op = vector_sub(pos_to_vector(params->plane[i]->pos), shadow->origin);
		t = vector_dot(op, params->plane[i]->vector) / denom;
		if (t > 0.0001f && t * t < light_dist)
			return (true);
	}
	return (false);
}
