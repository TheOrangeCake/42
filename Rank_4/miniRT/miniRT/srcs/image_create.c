/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 11:48:26 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/17 17:13:54 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

// Ray equation: R(t) = O + t·D
// Origin, Direction, t disrance, R(t) point on the ray at t
void	intersection(t_params *params, t_ray *ray)
{
	intersection_sphere(params, ray);
	intersection_plane(params, ray);
	intersection_cylinder(params, ray);
	intersection_cone(params, ray);
	calculate_ambient_light(params, ray);
	calculate_diffuse_light(params, ray);
	calculate_specular_light(params, ray);
	if (params->quantity.camera == 1 && params->quantity.light != 0)
	{
		if (ray->hit_plane)
			ray->color = color_add(ray->ambient, ray->diffuse);
		else
			ray->color = color_add(ray->specular,
					color_add(ray->ambient, ray->diffuse));
	}
	else if (params->quantity.light == 0 && (ray->hit_sphere != NULL
			|| ray->hit_plane != NULL || ray->hit_cylinder != NULL
			|| ray->hit_cone != NULL))
		ray->color = ray->ambient;
	else
	{
		ray->color.r = 0;
		ray->color.g = 0;
		ray->color.b = 0;
	}
}

// Setup camera direction based on camera vector.
// world_up is the world orientation vector.
// forward is axe z, right is axe x and up is axe y for camera vector.
void	initialise_values(t_params *params, t_world *world)
{
	world->world_up.a = 0;
	world->world_up.b = 1;
	world->world_up.c = 0;
	world->forward = params->camera.vector;
	vector_normalize(&world->forward);
	world->right = vector_cross(world->world_up, world->forward);
	vector_normalize(&world->right);
	world->up = vector_cross(world->forward, world->right);
	world->aspect_ratio = (double)WIDTH / HEIGHT;
	world->fov_rad = tan((params->camera.fov * M_PI / 180.0) / 2.0);
}

void	initialise_ray(t_params *params, t_ray *ray)
{
	ray->origin = pos_to_vector(params->camera.pos);
	ray->color.r = 0;
	ray->color.g = 0;
	ray->color.b = 0;
	ray->t = 3.402823466e+38f;
	ray->hit_plane = NULL;
	ray->hit_cylinder = NULL;
	ray->hit_sphere = NULL;
	ray->hit_cone = NULL;
	ray->diffuse.r = 0;
	ray->diffuse.g = 0;
	ray->diffuse.b = 0;
	ray->hit_inside = false;
	ray->normal = ray->direction;
	ray->hit_point = vector_add(ray->origin,
			vector_multi(ray->t, ray->direction));
}

// pixel.horiz shifts the ray horizontally
// pixel.vert shifts the ray vetically
void	render_object(t_params *params)
{
	t_pixel	pixel;
	t_world	world;
	t_ray	ray;

	initialise_values(params, &world);
	pixel.i = -1;
	while (++pixel.i < HEIGHT)
	{
		pixel.j = -1;
		printf("Rendering row %d/%d\n", pixel.i + 1, HEIGHT);
		while (++pixel.j < WIDTH)
		{
			pixel.horiz = vector_multi((2 * ((pixel.j + 0.5f) / WIDTH) - 1)
					* world.aspect_ratio * world.fov_rad, world.right);
			pixel.vert = vector_multi((1 - 2 * ((pixel.i + 0.5) / HEIGHT))
					* world.fov_rad, world.up);
			ray.direction = vector_add(world.forward,
					vector_add(pixel.horiz, pixel.vert));
			vector_normalize(&ray.direction);
			initialise_ray(params, &ray);
			intersection(params, &ray);
			my_mlx_pixel_put(params, pixel.i, pixel.j, ray.color);
		}
	}
}
