/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 15:44:53 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/10 18:25:02 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

t_vector	vector_cross(t_vector v1, t_vector v2)
{
	t_vector	v3;

	v3.a = v1.b * v2.c - v1.c * v2.b;
	v3.b = v1.c * v2.a - v1.a * v2.c;
	v3.c = v1.a * v2.b - v1.b * v2.a;
	return (v3);
}

float	vector_norm2(t_vector v1)
{
	float	x;

	x = v1.a * v1.a + v1.b * v1.b + v1.c * v1.c;
	return (x);
}

void	vector_normalize(t_vector *v1)
{
	float	norm;

	norm = sqrtf(vector_norm2(*v1));
	if (norm == 0.0)
		return ;
	v1->a /= norm;
	v1->b /= norm;
	v1->c /= norm;
}

t_vector	pos_to_vector(t_pos pos)
{
	t_vector	v;

	v.a = pos.x;
	v.b = pos.y;
	v.c = pos.z;
	return (v);
}

t_color	color_add(t_color c1, t_color c2)
{
	t_color	c3;

	c3.r = c1.r + c2.r;
	c3.g = c1.g + c2.g;
	c3.b = c1.b + c2.b;
	if (c3.r > 255)
		c3.r = 255;
	if (c3.g > 255)
		c3.g = 255;
	if (c3.b > 255)
		c3.b = 255;
	return (c3);
}
