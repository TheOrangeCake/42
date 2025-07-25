/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_specular.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:43:09 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/11 16:46:44 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

t_vector	reflect(t_vector in, t_vector normal)
{
	float		dot;
	t_vector	reflect;

	dot = vector_dot(in, normal);
	reflect = vector_sub(in, vector_multi(2 * dot, normal));
	return (reflect);
}

void	initialise_specular_default(t_ray *ray)
{
	ray->specular.r = 0;
	ray->specular.g = 0;
	ray->specular.b = 0;
}

void	set_specular(float dot, t_light *light, t_ray *ray)
{
	float	shine;

	if (ray->hit_sphere)
		shine = ray->hit_sphere->shine;
	else if (ray->hit_cylinder)
		shine = ray->hit_cylinder->shine;
	else if (ray->hit_cone)
		shine = ray->hit_cone->shine;
	else
		return ;
	dot = pow(dot, shine);
	ray->specular.r += light->color.r * dot;
	ray->specular.g += light->color.g * dot;
	ray->specular.b += light->color.b * dot;
	if (ray->specular.r > 255)
		ray->specular.r = 255;
	if (ray->specular.g > 255)
		ray->specular.g = 255;
	if (ray->specular.b > 255)
		ray->specular.b = 255;
}

void	calculate_specular_light(t_params *params, t_ray *ray)
{
	int			i;
	t_vector	hit_light;
	t_vector	hit_camera;
	t_vector	in;
	float		dot;

	if (!params->light)
		return ;
	hit_camera = vector_sub(pos_to_vector(params->camera.pos), ray->hit_point);
	vector_normalize(&hit_camera);
	initialise_specular_default(ray);
	i = -1;
	while (params->light[++i])
	{
		hit_light = vector_sub(pos_to_vector(params->light[i]->pos),
				ray->hit_point);
		vector_normalize(&hit_light);
		if (shadow_check(params, ray, i))
			continue ;
		in = vector_multi(-1.0f, hit_light);
		ray->reflect = reflect(in, ray->normal);
		dot = vector_dot(ray->reflect, hit_camera);
		if (dot > 0)
			set_specular(dot, params->light[i], ray);
	}
}
