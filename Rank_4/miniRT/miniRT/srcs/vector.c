/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 15:07:17 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/10 17:39:34 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

t_vector	vector_add(t_vector v1, t_vector v2)
{
	t_vector	v3;

	v3.a = v1.a + v2.a;
	v3.b = v1.b + v2.b;
	v3.c = v1.c + v2.c;
	return (v3);
}

t_vector	vector_sub(t_vector v1, t_vector v2)
{
	t_vector	v3;

	v3.a = v1.a - v2.a;
	v3.b = v1.b - v2.b;
	v3.c = v1.c - v2.c;
	return (v3);
}

t_vector	vector_multi(float x, t_vector v1)
{
	t_vector	v2;

	v2.a = x * v1.a;
	v2.b = x * v1.b;
	v2.c = x * v1.c;
	return (v2);
}

t_vector	vector_divi(t_vector v1, float x)
{
	t_vector	v2;

	v2.a = v1.a / x;
	v2.b = v1.b / x;
	v2.c = v1.c / x;
	return (v2);
}

float	vector_dot(t_vector v1, t_vector v2)
{
	float	x;

	x = v1.a * v2.a + v1.b * v2.b + v1.c * v2.c;
	return (x);
}
