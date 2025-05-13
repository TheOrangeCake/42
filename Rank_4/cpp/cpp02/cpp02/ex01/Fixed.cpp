/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:14:15 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/14 00:56:31 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed() {
	std::cout << "Default constructor called" << std::endl;
	_value = 0;
}

Fixed::Fixed(const Fixed& copy) {
	std::cout << "Copy constructor called" << std::endl;
	*this = copy;
}

Fixed& Fixed::operator=(const Fixed& assign) {
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &assign)
		this->_value = assign.getRawBits();
	return (*this);
}

Fixed::~Fixed() {
	std::cout << "Destructor called" << std::endl;
}

int Fixed::getRawBits(void) const {
	return (this->_value);
}

void Fixed::setRawBits(int const raw) {
	this->_value = raw;
}

Fixed::Fixed(int const number) {
	std::cout << "Int constructor called" << std::endl;
	this->_value = number * ( 1 << _fraction);
}

Fixed::Fixed(float const number) {
	std::cout << "Float constructor called" << std::endl;
	this->_value = roundf(number * (1 << _fraction));
}

float Fixed::toFloat(void) const {
	float i;
	
	i = (float)this->_value;
	i = i / (1 << _fraction);
	return (i);
}

int	Fixed::toInt(void) const {
	int	i;

	i = roundf(this->_value / (1 << _fraction));
	return (i);
}

std::ostream& operator<<(std::ostream& o, const Fixed& number) {
	o << number.toFloat();
	return (o);
}