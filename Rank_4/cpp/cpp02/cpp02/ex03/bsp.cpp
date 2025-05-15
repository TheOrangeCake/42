/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 22:03:27 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/15 15:48:09 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"
#include "Fixed.hpp"

bool same_point(Point const a, Point const d)
{
	return (a.getPoint_x() == d.getPoint_x() && a.getPoint_y() == d.getPoint_y());
}

Fixed cross(Point const a, Point const b, Point const d)
{
	Fixed	ab_x = b.getPoint_x() - a.getPoint_x();
	Fixed	ab_y = b.getPoint_y() - a.getPoint_y();
	Fixed	ap_x = d.getPoint_x() - a.getPoint_x();
	Fixed	ap_y = d.getPoint_y() - a.getPoint_y();
	Fixed	result = ab_x * ap_y - ab_y * ap_x;
	return (result);
}

// The logic here is checking if point d is on the same side as the vector.
// Check against AB, BC, CA using vector cross product.
// negative and positive to check the orientation of the vector.
bool bsp(Point const a, Point const b, Point const c, Point const d)
{
	if (same_point(a, d) || same_point(b, d) || same_point(c, d))
		return (false);

	Fixed	cross_ab = cross(a, b, d);
	Fixed	cross_bc = cross(b, c, d);
	Fixed	cross_ca = cross(c, a, d);

	if (cross_ab == 0 || cross_bc == 0 || cross_ca == 0)
		return (false);
	bool	negative = cross_ab < 0 || cross_bc < 0 || cross_ca < 0;
	bool	positive = cross_ab > 0 || cross_bc > 0 || cross_ca > 0;

	return !(negative && positive);
}