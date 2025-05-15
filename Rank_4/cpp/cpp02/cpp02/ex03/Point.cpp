/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 21:58:09 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/15 15:51:43 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

Point::Point() : _x(0), _y(0) {
}

Point::Point(float const a, float const b) : _x(Fixed(a)), _y(Fixed(b)) {
}

Point::Point(const Point& copy) : _x(copy._x), _y(copy._y){
}

// not in use because const _x and const _y
Point& Point::operator=(const Point& assign) {
	(void)assign;
	return (*this);
}

Point::~Point() {
}

Fixed Point::getPoint_x() const {
	return (this->_x);
}

Fixed Point::getPoint_y() const{
	return (this->_y);
}