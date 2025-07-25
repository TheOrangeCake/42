/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:43:56 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/10 18:02:14 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

bool	point_inside_sphere(t_vector point, t_sphere *sphere)
{
	t_vector	center;
	float		radius;
	t_vector	point_to_sphere;
	float		distance;

	center = pos_to_vector(sphere->pos);
	radius = sphere->d / 2.0f;
	point_to_sphere = vector_sub(point, center);
	distance = vector_dot(point_to_sphere, point_to_sphere);
	return (distance < (radius * radius + 0.001f));
}

bool	calculate_t_values(float b, float a,
		float discriminant, float light_dist)
{
	float	t1;
	float	t2;

	t1 = (-b - sqrtf(discriminant)) / (2.0f * a);
	t2 = (-b + sqrtf(discriminant)) / (2.0f * a);
	if ((t1 > 0 && t1 * t1 < light_dist)
		|| (t2 > 0 && t2 * t2 < light_dist))
		return (true);
	return (false);
}

bool	shadow_sphere_check(t_params *params, t_ray *shadow,
		float light_dist, t_vector light_pos)
{
	int			i;
	float		a;
	float		b;
	float		c;
	t_vector	oc;

	if (!params->sphere)
		return (false);
	i = -1;
	while (params->sphere[++i] != NULL)
	{
		if (point_inside_sphere(shadow->origin, params->sphere[i])
			&& point_inside_sphere(light_pos, params->sphere[i]))
			continue ;
		oc = vector_sub(shadow->origin, pos_to_vector(params->sphere[i]->pos));
		a = vector_dot(shadow->direction, shadow->direction);
		b = 2.0f * vector_dot(oc, shadow->direction);
		c = vector_dot(oc, oc) - (params->sphere[i]->d / 2.0f)
			* (params->sphere[i]->d / 2.0f);
		if (b * b - 4 * a * c < 0)
			continue ;
		if (calculate_t_values(b, a, b * b - 4 * a * c, light_dist) == true)
			return (true);
	}
	return (false);
}
