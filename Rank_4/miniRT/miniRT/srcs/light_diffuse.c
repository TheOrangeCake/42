/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   light_diffuse.c									:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: hoannguy <hoannguy@student.42lausanne.c	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/06/15 17:34:59 by hoannguy		  #+#	#+#			 */
/*   Updated: 2025/06/15 19:36:21 by hoannguy		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../inc/minirt.h"

// Dot product of normal and hit_light vector:
// if > 0, then light hits the surface, else the surface is in other side.
// Light hit at 90o if == 0. 
void	all_diffuse(t_params *params, t_ray *ray,
	t_color *diffuse_total, t_color *object_color)
{
	int			i;
	t_vector	hit_light;

	if (!params->light)
		return ;
	i = -1;
	while (params->light[++i])
	{
		hit_light = vector_sub(pos_to_vector(params->light[i]->pos),
				ray->hit_point);
		vector_normalize(&hit_light);
		if ((ray->hit_sphere || ray->hit_cylinder || ray->hit_cone)
			&& ray->hit_inside == true)
			hit_light = vector_multi(-1.0f, hit_light);
		if (shadow_check(params, ray, i))
			continue ;
		if (vector_dot(ray->normal, hit_light) <= 0)
			continue ;
		diffuse_total->r += object_color->r * params->light[i]->color.r / 255.0f
			* vector_dot(ray->normal, hit_light) * params->light[i]->ratio;
		diffuse_total->g += object_color->g * params->light[i]->color.g / 255.0f
			* vector_dot(ray->normal, hit_light) * params->light[i]->ratio;
		diffuse_total->b += object_color->b * params->light[i]->color.b / 255.0f
			* vector_dot(ray->normal, hit_light) * params->light[i]->ratio;
	}
}

void	ray_color_above_255(t_ray *ray)
{
	if (ray->diffuse.r > 255)
		ray->diffuse.r = 255;
	if (ray->diffuse.g > 255)
		ray->diffuse.g = 255;
	if (ray->diffuse.b > 255)
		ray->diffuse.b = 255;
}

// formula is 
// object color * light color * light ratio
// * (surface normal . hitToLight vector)
void	calculate_diffuse_light(t_params *params, t_ray *ray)
{
	t_color	color;
	t_color	diffuse_total;

	if (!ray->hit_sphere && !ray->hit_cylinder
		&& !ray->hit_plane && !ray->hit_cone)
		return ;
	if (ray->hit_sphere)
		get_sphere_color(params, ray, &color);
	else if (ray->hit_cylinder)
		get_cylinder_color(params, ray, &color);
	else if (ray->hit_plane)
		get_plane_color(params, ray, &color);
	else if (ray->hit_cone)
		get_cone_color(params, ray, &color);
	diffuse_total.r = 0;
	diffuse_total.g = 0;
	diffuse_total.b = 0;
	all_diffuse(params, ray, &diffuse_total, &color);
	ray->diffuse.r = (int)diffuse_total.r;
	ray->diffuse.g = (int)diffuse_total.g;
	ray->diffuse.b = (int)diffuse_total.b;
	ray_color_above_255(ray);
}
