/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:59:56 by maw               #+#    #+#             */
/*   Updated: 2025/07/17 17:08:41 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

bool	height_projection(t_ray *ray, t_cylinder *cylinder, float t)
{
	float		height_projection;
	t_vector	base;
	t_vector	from_base;
	t_vector	axis;
	t_vector	hit_point;

	axis = cylinder->vector;
	vector_normalize (&axis);
	hit_point = vector_add(ray->origin,
			vector_multi(t, ray->direction));
	base = vector_sub(pos_to_vector(cylinder->pos),
			vector_multi(cylinder->h / 2, axis));
	from_base = vector_sub(hit_point, base);
	height_projection = vector_dot(from_base, axis);
	if (height_projection < 0 || height_projection > cylinder->h)
		return (false);
	return (true);
}

void	set_t2_cylinder(t_cylinder *cylinder, t_ray *ray, float t2)
{
	t_vector	axis;
	t_vector	temp;

	if (t2 >= ray->t || t2 < 0)
		return ;
	axis = cylinder->vector;
	vector_normalize (&axis);
	ray->hit_point = vector_add(ray->origin,
			vector_multi(t2, ray->direction));
	ray->t = t2;
	ray->color = cylinder->color;
	ray->hit_sphere = NULL;
	ray->hit_cone = NULL;
	ray->hit_cylinder = cylinder;
	ray->hit_plane = NULL;
	temp = vector_sub(ray->hit_point, pos_to_vector(cylinder->pos));
	ray->normal = vector_sub(temp, vector_multi(vector_dot(temp, axis), axis));
	vector_normalize(&ray->normal);
	if (vector_dot(ray->normal, ray->direction) > 0)
		ray->hit_inside = true;
	else
		ray->hit_inside = false;
	ray->hit_point = vector_add(ray->hit_point,
			vector_multi(0.0001, ray->normal));
}

void	equation_cylinder(t_cylinder *cylinder, t_ray *ray, t_inter *t)
{
	t->axis = cylinder->vector;
	vector_normalize(&t->axis);
	t->d_perp = vector_sub(ray->direction,
			vector_multi(vector_dot(ray->direction, t->axis), t->axis));
	t->oc = vector_sub(ray->origin, pos_to_vector(cylinder->pos));
	t->oc_perp = vector_sub(t->oc,
			vector_multi(vector_dot(t->oc, t->axis), t->axis));
	t->a = vector_dot(t->d_perp, t->d_perp);
	t->c = vector_dot(t->oc_perp, t->oc_perp) - powf(cylinder->d / 2, 2);
	t->b = 2 * vector_dot(t->d_perp, t->oc_perp);
	t->disc = t->b * t->b - 4 * t->a * t->c;
}

float	calculate_lateral_t(t_cylinder *cylinder, t_ray *ray)
{
	t_inter		t;
	float		t1;
	float		t2;	

	equation_cylinder(cylinder, ray, &t);
	if (t.disc < 0)
		return (-1);
	t1 = (-t.b - sqrtf(t.disc)) / (2 * t.a);
	t2 = (-t.b + sqrtf(t.disc)) / (2 * t.a);
	if (t2 < 0)
		return (-1);
	if (t1 > 0 && height_projection(ray, cylinder, t1))
		return (t1);
	if (t2 > 0 && height_projection(ray, cylinder, t2))
		return (t2);
	return (-1);
}

void	intersection_cylinder(t_params *params, t_ray *ray)
{
	int			i;
	float		t_lateral;
	float		t_cap;
	t_vector	normal_cap;

	if (!params->cylinder)
		return ;
	i = -1;
	while (params->cylinder[++i])
	{
		t_lateral = calculate_lateral_t(params->cylinder[i], ray);
		t_cap = calculate_cap_t(params->cylinder[i], ray, &normal_cap);
		if (t_lateral > 0.001 && t_lateral < ray->t)
			set_t2_cylinder(params->cylinder[i], ray, t_lateral);
		if (t_cap > 0.001 && t_cap < ray->t)
			set_t_cap(ray, t_cap, params->cylinder[i], normal_cap);
	}
}
