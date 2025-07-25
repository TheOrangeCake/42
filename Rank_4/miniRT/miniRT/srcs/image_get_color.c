/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_get_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:03:01 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/11 16:13:04 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	get_sphere_color(t_params *params, t_ray *ray, t_color *color)
{
	t_color	temp;

	if (ray->hit_sphere->texture_type == CHECKER)
		temp = checkerboard_sphere(params, ray->hit_point, ray->hit_sphere);
	else if (ray->hit_sphere->texture_type == STRIPE)
		temp = stripe_sphere(params, ray->hit_point, ray->hit_sphere);
	else if (ray->hit_sphere->texture_type == EARTH)
		temp = planet_sphere(params, ray->hit_point, ray->hit_sphere, EARTH);
	else if (ray->hit_sphere->texture_type == MARS)
		temp = planet_sphere(params, ray->hit_point, ray->hit_sphere, MARS);
	else if (ray->hit_sphere->texture_type == MERCU)
		temp = planet_sphere(params, ray->hit_point, ray->hit_sphere, MERCU);
	else if (ray->hit_sphere->texture_type == PLUTO)
		temp = planet_sphere(params, ray->hit_point, ray->hit_sphere, PLUTO);
	else if (ray->hit_sphere->texture_type == VENUS)
		temp = planet_sphere(params, ray->hit_point, ray->hit_sphere, VENUS);
	else
		temp = ray->hit_sphere->color;
	color->r = temp.r;
	color->g = temp.g;
	color->b = temp.b;
	return ;
}

void	get_cylinder_color(t_params *params, t_ray *ray, t_color *color)
{
	t_color	temp;

	if (ray->hit_cylinder->texture_type == CHECKER)
		temp = checkerboard_cylinder(params,
				ray->hit_point, ray->hit_cylinder);
	else
		temp = ray->hit_cylinder->color;
	color->r = temp.r;
	color->g = temp.g;
	color->b = temp.b;
	return ;
}

void	get_cone_color(t_params *params, t_ray *ray, t_color *color)
{
	t_color	temp;

	(void)params;
	temp = ray->hit_cone->color;
	color->r = temp.r;
	color->g = temp.g;
	color->b = temp.b;
	return ;
}

void	get_plane_color(t_params *params, t_ray *ray, t_color *color)
{
	t_color	temp;

	if (ray->hit_plane->texture_type == CHECKER)
		temp = checkerboard_plane(params, ray);
	else if (ray->hit_plane->texture_type == STRIPE)
		temp = stripe_plane(params, ray->hit_point);
	else
		temp = ray->hit_plane->color;
	color->r = temp.r;
	color->g = temp.g;
	color->b = temp.b;
	return ;
}
