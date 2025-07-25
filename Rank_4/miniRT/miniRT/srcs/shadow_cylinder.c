/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:27:24 by maw               #+#    #+#             */
/*   Updated: 2025/07/12 16:04:17 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

bool	height_check(t_ray *shadow, float t, t_vector axis, t_cylinder *cy)
{
	t_vector	hit;
	t_vector	base;
	t_vector	hit_to_base;
	float		projection;

	hit = vector_add(shadow->origin, vector_multi(t, shadow->direction));
	base = vector_sub(pos_to_vector(cy->pos), vector_multi(cy->h / 2, axis));
	hit_to_base = vector_sub(hit, base);
	projection = vector_dot(hit_to_base, axis);
	if (projection >= 0 && projection <= cy->h)
		return (true);
	return (false);
}

bool	disk_check(t_vector base, t_ray *shadow,
	t_cylinder *cylinder, float light_dist)
{
	float		denom;
	float		t;
	t_vector	axis;

	axis = cylinder->vector;
	denom = vector_dot(shadow->direction, axis);
	if (fabs(denom) < 1e-6)
		return (false);
	t = vector_dot(vector_sub(base, shadow->origin), axis) / denom;
	if (t < 0 || t * t > light_dist)
		return (false);
	shadow->hit_point = vector_add(shadow->origin,
			vector_multi(t, shadow->direction));
	if (vector_lenght(vector_sub(shadow->hit_point, base)) > cylinder->d / 2)
		return (false);
	return (true);
}

bool	shadow_cylinder_cap_check(t_params *params, t_ray *shadow,
	float light_dist)
{
	int			i;
	t_vector	base;
	t_vector	top;
	t_vector	axis;

	if (!params->cylinder)
		return (false);
	i = -1;
	while (params->cylinder[++i])
	{
		axis = params->cylinder[i]->vector;
		vector_normalize(&axis);
		base = vector_sub(pos_to_vector(params->cylinder[i]->pos),
				vector_multi(params->cylinder[i]->h / 2, axis));
		top = vector_add(pos_to_vector(params->cylinder[i]->pos),
				vector_multi(params->cylinder[i]->h / 2, axis));
		if (disk_check(base, shadow, params->cylinder[i], light_dist))
			return (true);
		if (disk_check(top, shadow, params->cylinder[i], light_dist))
			return (true);
	}
	return (false);
}

void	cylinder_equation(t_params *params, t_ray *shadow, t_inter *t, int i)
{
	t->axis = params->cylinder[i]->vector;
	vector_normalize(&t->axis);
	t->d_perp = vector_sub(shadow->direction,
			vector_multi(vector_dot(shadow->direction, t->axis), t->axis));
	t->oc = vector_sub(shadow->origin, pos_to_vector(params->cylinder[i]->pos));
	t->oc_perp = vector_sub(t->oc,
			vector_multi(vector_dot(t->oc, t->axis), t->axis));
	t->a = vector_dot(t->d_perp, t->d_perp);
	t->c = vector_dot(t->oc_perp, t->oc_perp)
		- powf(params->cylinder[i]->d / 2, 2);
	t->b = 2 * vector_dot(t->d_perp, t->oc_perp);
	t->disc = t->b * t->b - 4 * t->a * t->c;
}

bool	shadow_cylinder_check(t_params *params, t_ray *shadow,
	float light_dist)
{
	int		i;
	float	t1;
	float	t2;
	t_inter	t;

	if (!params->cylinder)
		return (false);
	i = -1;
	while (params->cylinder[++i])
	{
		cylinder_equation(params, shadow, &t, i);
		if (t.disc < 0)
			continue ;
		t1 = (-t.b - sqrtf(t.disc)) / (2 * t.a);
		t2 = (-t.b + sqrtf(t.disc)) / (2 * t.a);
		if (height_check(shadow, t1, t.axis, params->cylinder[i]) == false)
			continue ;
		if (height_check(shadow, t2, t.axis, params->cylinder[i]) == false)
			continue ;
		if ((t1 > 0 && t1 * t1 < light_dist)
			|| (t2 > 0 && t2 * t2 < light_dist))
			return (true);
	}
	return (false);
}
