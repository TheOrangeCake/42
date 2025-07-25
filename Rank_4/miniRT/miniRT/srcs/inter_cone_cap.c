/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_cone_cap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 18:18:23 by masase            #+#    #+#             */
/*   Updated: 2025/07/12 16:00:04 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	set_t_cap_cone(t_ray *ray, float t, t_cone *cone, t_vector normal)
{
	ray->t = t;
	ray->hit_cylinder = NULL;
	ray->hit_plane = NULL;
	ray->hit_sphere = NULL;
	ray->hit_cone = cone;
	ray->color = cone->color;
	ray->normal = normal;
	if (vector_dot(ray->normal, ray->direction) > 0)
	{
		ray->hit_inside = true;
	}
	else
		ray->hit_inside = false;
	ray->hit_point = vector_add(ray->origin, vector_multi(t, ray->direction));
	ray->hit_point = vector_add(ray->hit_point, vector_multi(0.0001, normal));
}

float	touch_under_cap_cone(t_vector axis, t_ray *ray, t_cone *cone)
{
	float		denom;
	float		t;
	t_vector	base;
	t_vector	hit_point;

	base = vector_sub(pos_to_vector(cone->pos), vector_multi(cone->h, axis));
	denom = vector_dot(ray->direction, axis);
	if (fabs(denom) < 0.000001)
		return (-1);
	t = vector_dot(vector_sub(base, ray->origin), axis) / denom;
	if (t < 0 || t >= ray->t)
		return (-1);
	hit_point = vector_add(ray->origin, vector_multi(t, ray->direction));
	if (vector_lenght(vector_sub(hit_point, base)) > cone->d / 2)
		return (-1);
	return (t);
}

float	calculate_cap_t_cone(t_cone *cone, t_ray *ray, t_vector *normal)
{
	t_vector	axis;
	float		t_under;

	axis = cone->vector;
	vector_normalize(&axis);
	*normal = axis;
	t_under = touch_under_cap_cone(axis, ray, cone);
	if (t_under >= 0)
	{
		*normal = vector_multi(-1, axis);
		return (t_under);
	}
	return (-1);
}
