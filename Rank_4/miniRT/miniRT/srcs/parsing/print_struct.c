/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:29:38 by masase            #+#    #+#             */
/*   Updated: 2025/07/11 17:06:09 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	print_plane_as_array(t_plane *plane)
{
	printf("Plane\n");
	printf("Position: [%.2f, %.2f, %.2f]\n",
		plane->pos.x, plane->pos.y, plane->pos.z);
	printf("Orientation: [%.2f, %.2f, %.2f]\n",
		plane->vector.a, plane->vector.b, plane->vector.c);
	printf("Color: [%d, %d, %d]\n",
		plane->color.r, plane->color.g, plane->color.b);
}

void	print_sphere_as_array(t_sphere *sphere)
{
	printf("Sphere\n");
	printf("Position: [%.2f, %.2f, %.2f]\n",
		sphere->pos.x, sphere->pos.y, sphere->pos.z);
	printf("Diameter: %.2f\n", sphere->d);
	printf("Color: [%d, %d, %d]\n",
		sphere->color.r, sphere->color.g, sphere->color.b);
}

void	print_cylinder_as_array(t_cylinder *cyl)
{
	printf("Cylinder\n");
	printf("Position: [%.2f, %.2f, %.2f]\n",
		cyl->pos.x, cyl->pos.y, cyl->pos.z);
	printf("Orientation: [%.2f, %.2f, %.2f]\n",
		cyl->vector.a, cyl->vector.b, cyl->vector.c);
	printf("Color: [%d, %d, %d]\n",
		cyl->color.r, cyl->color.g, cyl->color.b);
	printf("Dimensions: [Diameter: %.2f, Height: %.2f]\n", cyl->d, cyl->h);
}

void	print_ambiance_as_array(t_ambient *amb)
{
	printf("Ambiance\n");
	printf("Color: [%d, %d, %d]\n",
		amb->color.r, amb->color.g, amb->color.b);
	printf("Ratio: %.2f\n", amb->ratio);
}

void	print_point_as_array(t_light *light)
{
	printf("Light\n");
	printf("Position: [%.2f, %.2f, %.2f]\n",
		light->pos.x, light->pos.y, light->pos.z);
	printf("Brightness Ratio: %.2f\n", light->ratio);
	printf("Color: [%d, %d, %d]\n",
		light->color.r, light->color.g, light->color.b);
}
