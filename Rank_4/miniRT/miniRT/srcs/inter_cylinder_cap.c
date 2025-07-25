/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_cylinder_cap.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 16:03:24 by maw               #+#    #+#             */
/*   Updated: 2025/07/12 15:57:21 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	set_t_cap(t_ray *ray, float t, t_cylinder *cylinder, t_vector normal)
{
	ray->t = t;
	ray->hit_cylinder = cylinder;
	ray->hit_plane = NULL;
	ray->hit_sphere = NULL;
	ray->hit_cone = NULL;
	ray->color = cylinder->color;
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

float	touch_under_cap(t_vector axis, t_ray *ray, t_cylinder *cylinder)
{
	float		denom;
	float		t;
	t_vector	base;
	t_vector	hit_point;

	base = vector_sub(pos_to_vector(cylinder->pos),
			vector_multi(cylinder->h / 2, axis));
	denom = vector_dot(ray->direction, axis);
	if (fabs(denom) < 0.000001)
		return (-1);
	t = vector_dot(vector_sub(base, ray->origin), axis) / denom;
	if (t < 0 || t >= ray->t)
		return (-1);
	hit_point = vector_add(ray->origin, vector_multi(t, ray->direction));
	if (vector_lenght(vector_sub(hit_point, base)) > cylinder->d / 2)
		return (-1);
	return (t);
}

float	touch_top_cap(t_vector axis, t_ray *ray, t_cylinder *cylinder)
{
	float		denom;
	float		t;
	t_vector	base;
	t_vector	hit_point;	

	base = vector_add(pos_to_vector(cylinder->pos),
			vector_multi(cylinder->h / 2, axis));
	denom = vector_dot(ray->direction, axis);
	if (fabs(denom) < 0.000001)
		return (-1);
	t = vector_dot(vector_sub(base, ray->origin), axis) / denom;
	if (t < 0 || t >= ray->t)
		return (-1);
	hit_point = vector_add(ray->origin, vector_multi(t, ray->direction));
	if (vector_lenght(vector_sub(hit_point, base)) > cylinder->d / 2)
		return (-1);
	return (t);
}

float	calculate_cap_t(t_cylinder *cylinder, t_ray *ray, t_vector *normal)
{
	t_vector	axis;
	float		t_top;
	float		t_under;
	float		best;

	best = -1;
	axis = cylinder->vector;
	vector_normalize(&axis);
	*normal = axis;
	t_under = touch_under_cap(axis, ray, cylinder);
	t_top = touch_top_cap(axis, ray, cylinder);
	if (t_under >= 0)
	{
		best = t_under;
		*normal = vector_multi(-1, axis);
	}
	if (t_top >= 0 && (best == -1 || t_top < best))
	{
		best = t_top;
		*normal = axis;
	}
	return (best);
}
