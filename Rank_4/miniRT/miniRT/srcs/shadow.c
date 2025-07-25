/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:46:02 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/17 17:13:48 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	initialise_shadow_ray(t_ray *ray, t_ray *shadow)
{
	t_vector	offset;

	if (ray->hit_inside)
		offset = vector_multi(-0.1f, ray->normal);
	else
		offset = vector_multi(0.1f, ray->normal);
	shadow->origin = vector_add(ray->hit_point, offset);
	shadow->color.r = 0;
	shadow->color.g = 0;
	shadow->color.b = 0;
	shadow->t = 3.402823466e+38f;
	shadow->hit_plane = NULL;
	shadow->hit_cylinder = NULL;
	shadow->hit_sphere = NULL;
	shadow->hit_cone = NULL;
}

bool	shadow_check(t_params *params, t_ray *ray, int index)
{
	t_ray		shadow;
	t_vector	light_pos;
	t_vector	light_vec;
	float		light_dist;

	initialise_shadow_ray(ray, &shadow);
	light_pos = pos_to_vector(params->light[index]->pos);
	light_vec = vector_sub(light_pos, ray->hit_point);
	light_dist = vector_dot(light_vec, light_vec);
	vector_normalize(&light_vec);
	shadow.direction = light_vec;
	if (shadow_sphere_check(params, &shadow, light_dist,
			pos_to_vector(params->light[index]->pos)))
		return (true);
	if (shadow_plane_check(params, &shadow, ray, light_pos))
		return (true);
	if (shadow_cylinder_check(params, &shadow, light_dist))
		return (true);
	if (shadow_cylinder_cap_check(params, &shadow, light_dist))
		return (true);
	if (shadow_cone_check(params, &shadow, light_dist))
		return (true);
	return (false);
}
