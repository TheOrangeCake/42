/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_cone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:44:27 by masase            #+#    #+#             */
/*   Updated: 2025/07/12 16:05:05 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

bool	height_check_cone(t_ray *shadow, float t, t_vector axis, t_cone *cone)
{
	t_vector	hit;
	t_vector	base;
	t_vector	hit_to_base;
	float		projection;

	hit = vector_add(shadow->origin, vector_multi(t, shadow->direction));
	base = vector_sub(pos_to_vector(cone->pos), vector_multi(cone->h, axis));
	hit_to_base = vector_sub(hit, base);
	projection = vector_dot(hit_to_base, axis);
	if (projection >= 0 && projection <= cone->h)
		return (true);
	return (false);
}

bool	shadow_cone_check(t_params *params, t_ray *shadow, float light_dist)
{
	int			i;
	float		t_lateral;
	float		t_cap;
	t_vector	normal_cap;
	t_vector	axis;

	if (!params->cone)
		return (false);
	i = -1;
	while (params->cone[++i])
	{
		axis = params->cone[i]->vector;
		vector_normalize(&axis);
		t_lateral = calculate_lateral_t_cone(params->cone[i], shadow);
		t_cap = calculate_cap_t_cone(params->cone[i], shadow, &normal_cap);
		if (t_lateral > 0 && t_lateral * t_lateral < light_dist)
		{
			if (height_check_cone(shadow, t_lateral, axis, params->cone[i]))
				return (true);
		}
		if (t_cap > 0 && t_cap * t_cap < light_dist)
			return (true);
	}
	return (false);
}
