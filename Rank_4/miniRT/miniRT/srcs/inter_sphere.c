/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 11:48:26 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/10 17:52:09 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	set_t2_sphere(t_params *params, t_sphere *sphere, t_ray *ray, float t2)
{
	ray->t = t2;
	ray->color = sphere->color;
	ray->hit_sphere = sphere;
	ray->hit_cylinder = NULL;
	ray->hit_plane = NULL;
	ray->hit_cone = NULL;
	ray->hit_point = vector_add(ray->origin,
			vector_multi(t2, ray->direction));
	ray->normal = vector_sub(ray->hit_point, pos_to_vector(sphere->pos));
	vector_normalize(&ray->normal);
	apply_bump(params, ray, sphere);
	ray->hit_point = vector_add(ray->hit_point,
			vector_multi(0.0001f, ray->normal));
	ray->hit_inside = true;
}

// t1 is first hit. Normal is perpendicular vector to hitpoint.
// t2 is second hit.
void	set_t_sphere(t_params *params, t_sphere *sphere,
		t_ray *ray, t_value_float value)
{
	if (value.t1 > 0 && value.t1 < ray->t)
	{
		ray->t = value.t1;
		ray->color = sphere->color;
		ray->hit_sphere = sphere;
		ray->hit_cylinder = NULL;
		ray->hit_plane = NULL;
		ray->hit_point = vector_add(ray->origin,
				vector_multi(value.t1, ray->direction));
		ray->normal = vector_sub(ray->hit_point, pos_to_vector(sphere->pos));
		vector_normalize(&ray->normal);
		apply_bump(params, ray, sphere);
		ray->hit_point = vector_add(ray->hit_point,
				vector_multi(0.0001f, ray->normal));
		ray->hit_inside = false;
	}
	else if (value.t2 > 0 && value.t2 < ray->t)
		set_t2_sphere(params, sphere, ray, value.t2);
}

// Quadratic equation: ||O + tD - C||² = r²
// Origin, Direction, Center, radius
// Plugin: t = -b ± √(b² - c)
void	intersection_sphere(t_params *params, t_ray *ray)
{
	int				i;
	float			b;
	t_value_float	value;
	t_vector		oc;

	if (!params->sphere)
		return ;
	i = -1;
	while (params->sphere[++i])
	{
		oc = vector_sub(ray->origin, pos_to_vector(params->sphere[i]->pos));
		b = 2.0f * vector_dot(ray->direction, oc);
		if ((b * b - 4 * (vector_dot(oc, oc)
					- pow((params->sphere[i]->d / 2), 2))) < 0)
			continue ;
		value.t1 = (-b - sqrtf(b * b - 4 * (vector_dot(oc, oc)
						- pow((params->sphere[i]->d / 2), 2)))) / 2;
		value.t2 = (-b + sqrtf(b * b - 4 * (vector_dot(oc, oc)
						- pow((params->sphere[i]->d / 2), 2)))) / 2;
		if (value.t2 < 0)
			continue ;
		set_t_sphere(params, params->sphere[i], ray, value);
	}
}
