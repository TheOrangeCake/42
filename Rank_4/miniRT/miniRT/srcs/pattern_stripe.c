/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   pattern_stripe.c								   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: hoannguy <hoannguy@student.42lausanne.c	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/06/23 23:35:49 by hoannguy		  #+#	#+#			 */
/*   Updated: 2025/06/24 00:20:14 by hoannguy		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../inc/minirt.h"

t_color	stripe_sphere(t_params *params, t_vector hit_point, t_sphere *sphere)
{
	t_vector	center;
	float		angle;
	int			color;

	center = vector_sub(hit_point, pos_to_vector(sphere->pos));
	angle = atan2(center.c, center.a);
	color = (int)((angle / (2 * M_PI)) * params->stripe.size) % 2;
	if (color < 0)
		color += 2;
	if (color == 0)
		return (params->stripe.color1);
	return (params->stripe.color2);
}

t_color	stripe_plane(t_params *params, t_vector hit_point)
{
	int	color;

	color = (int)(hit_point.a / ((params->stripe.size / 5) + 1)) % 2;
	if (color == 0)
		return (params->stripe.color1);
	return (params->stripe.color2);
}
