/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed_arithmetic.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:18:43 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/14 18:20:40 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed Fixed::operator+(const Fixed& plus) const {
	Fixed result;
	result._value = this->getRawBits() + plus.getRawBits();
	return (result);
}

Fixed Fixed::operator-(const Fixed& minus) const {
	Fixed result;
	result._value = this->getRawBits() - minus.getRawBits();
	return (result);
}

Fixed Fixed::operator*(const Fixed& multiply) const {
	Fixed result(this->toFloat() * multiply.toFloat());
	return (result);
}

Fixed Fixed::operator/(const Fixed& divide) const {
	Fixed result(this->toFloat() / divide.toFloat());
	return (result);
}