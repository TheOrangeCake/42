/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 21:57:11 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/14 22:18:47 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_HPP
#define POINT_HPP
#include "Fixed.hpp"

class Point {
	private:
		Fixed const _x;
		Fixed const _y;

	public:
		Point();
		Point(float const a, float const b);
		Point(const Point& copy);
		Point& operator=(const Point& assign);
		~Point();

		Fixed getPoint_x() const;
		Fixed getPoint_y() const;
		
};

#endif