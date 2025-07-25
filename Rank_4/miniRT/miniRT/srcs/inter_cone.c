/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 21:38:09 by maw               #+#    #+#             */
/*   Updated: 2025/07/10 18:23:12 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

bool	height_projection_cone(t_ray *ray, t_cone *cone, float t)
{
	float		height_projection;
	t_vector	base;
	t_vector	from_base;
	t_vector	axis;
	t_vector	hit_point;

	axis = cone->vector;
	vector_normalize (&axis);
	hit_point = vector_add(ray->origin,
			vector_multi(t, ray->direction));
	base = vector_sub(pos_to_vector(cone->pos), vector_multi(cone->h, axis));
	from_base = vector_sub(hit_point, base);
	height_projection = vector_dot(from_base, axis);
	if (height_projection < 0 || height_projection > cone->h)
	{
		ray->hit_cone = NULL;
		return (false);
	}
	return (true);
}

void	set_t2_cone(t_cone *cone, t_ray *ray, float t2)
{
	t_vector	temp;
	t_vector	axis;

	if (t2 >= ray->t || t2 < 0)
		return ;
	axis = cone->vector;
	vector_normalize (&axis);
	ray->hit_point = vector_add(ray->origin,
			vector_multi(t2, ray->direction));
	ray->t = t2;
	ray->color = cone->color;
	ray->hit_sphere = NULL;
	ray->hit_cylinder = NULL;
	ray->hit_cone = cone;
	ray->hit_plane = NULL;
	temp = vector_sub(ray->hit_point, pos_to_vector(cone->pos));
	ray->normal = vector_sub(temp, vector_multi(vector_dot(temp, axis), axis));
	vector_normalize(&ray->normal);
	if (vector_dot(ray->normal, ray->direction) > 0)
		ray->hit_inside = true;
	else
		ray->hit_inside = false;
	ray->hit_point = vector_add(ray->hit_point,
			vector_multi(0.0001, ray->normal));
}

void	calculate_lateral_t_cone_2(t_cone *cone, t_ray *ray, t_inter_cone *t)
{
	t->axis = cone->vector;
	vector_normalize(&t->axis);
	t->oc = vector_sub(ray->origin, pos_to_vector(cone->pos));
	t->k = cone->d / (2 * cone->h);
	t->k2 = powf(t->k, 2);
	t->dv = vector_dot(ray->direction, t->axis);
	t->oc_v = vector_dot(t->oc, t->axis);
	t->d_perp = vector_sub(ray->direction, vector_multi(t->dv, t->axis));
	t->oc_perp = vector_sub(t->oc,
			vector_multi(vector_dot(t->oc, t->axis), t->axis));
	t->a = vector_dot(t->d_perp, t->d_perp) - t->k2 * t->dv * t->dv;
	t->c = vector_dot(t->oc_perp, t->oc_perp) - t->k2 * t->oc_v * t->oc_v;
	t->b = 2 * (vector_dot(t->d_perp, t->oc_perp) - t->k2 * t->dv * t->oc_v);
}

float	calculate_lateral_t_cone(t_cone *cone, t_ray *ray)
{
	t_inter_cone	t;
	float			t1;
	float			t2;	

	calculate_lateral_t_cone_2(cone, ray, &t);
	t.disc = t.b * t.b - 4 * t.a * t.c;
	if (t.disc < 0)
		return (-1);
	t1 = (-t.b - sqrtf(t.disc)) / (2 * t.a);
	t2 = (-t.b + sqrtf(t.disc)) / (2 * t.a);
	if (t2 < 0)
		return (-1);
	if (t1 > 0 && height_projection_cone(ray, cone, t1))
		return (t1);
	if (t2 > 0 && height_projection_cone(ray, cone, t2))
		return (t2);
	return (-1);
}

void	intersection_cone(t_params *params, t_ray *ray)
{
	int			i;
	float		t_lateral;
	float		t_cap;
	t_vector	normal_cap;

	if (!params->cone)
		return ;
	i = -1;
	while (params->cone[++i])
	{
		t_lateral = calculate_lateral_t_cone(params->cone[i], ray);
		t_cap = calculate_cap_t_cone(params->cone[i], ray, &normal_cap);
		if (t_cap > 0 && t_cap < ray->t)
			set_t_cap_cone(ray, t_cap, params->cone[i], normal_cap);
		if (t_lateral > 0 && t_lateral < ray->t)
			set_t2_cone(params->cone[i], ray, t_lateral);
	}
}
