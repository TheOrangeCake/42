/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 06:02:01 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/10 17:52:06 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	set_t_plane(t_plane *plane, t_ray *ray, float t, float denom)
{
	ray->t = t;
	ray->hit_plane = plane;
	ray->hit_sphere = NULL;
	ray->hit_cylinder = NULL;
	ray->hit_cone = NULL;
	ray->hit_point = vector_add(ray->origin, vector_multi(t, ray->direction));
	ray->normal = plane->vector;
	ray->color = plane->color;
	if (denom > 0)
		ray->normal = vector_multi(-1.0f, ray->normal);
	ray->hit_point = vector_add(ray->hit_point,
			vector_multi(0.0001f, ray->normal));
	ray->hit_inside = false;
}

// Linear equation: (P - O) · N = t * (D · N)
// Position, Origin, Normal, Direction
// Plugin: t = ((P0 - O) · N) / (D · N)
void	intersection_plane(t_params *params, t_ray *ray)
{
	int			i;
	float		denom;
	float		t;
	t_vector	op;

	if (!params->plane)
		return ;
	i = -1;
	while (params->plane[++i])
	{
		denom = vector_dot(ray->direction, params->plane[i]->vector);
		if (fabsf(denom) < 0.000001f)
			continue ;
		op = vector_sub(pos_to_vector(params->plane[i]->pos), ray->origin);
		t = vector_dot(op, params->plane[i]->vector) / denom;
		if ((t > 0.0001f && t < ray->t))
			set_t_plane(params->plane[i], ray, t, denom);
	}
}
