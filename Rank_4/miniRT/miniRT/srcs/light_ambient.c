/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:26:07 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/11 17:00:51 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

// formula is object color * ambient ratio * (ambient color / 255)
void	calculate_ambient_light(t_params *params, t_ray *ray)
{
	t_color		color;
	t_vector	view;
	float		fade;

	view = vector_sub(ray->origin, ray->hit_point);
	vector_normalize(&view);
	fade = fmaxf(vector_dot(ray->normal, view), 0.0f);
	if (ray->hit_sphere != NULL)
		get_sphere_color(params, ray, &color);
	else if (ray->hit_cylinder != NULL)
		get_cylinder_color(params, ray, &color);
	else if (ray->hit_plane != NULL)
		get_plane_color(params, ray, &color);
	else if (ray->hit_cone != NULL)
		get_cone_color(params, ray, &color);
	else
		color = (t_color){0, 0, 0};
	ray->ambient.r = color.r * params->ambient.ratio
		* (params->ambient.color.r / 255.0f) * fade;
	ray->ambient.g = color.g * params->ambient.ratio
		* (params->ambient.color.g / 255.0f) * fade;
	ray->ambient.b = color.b * params->ambient.ratio
		* (params->ambient.color.b / 255.0f) * fade;
}
