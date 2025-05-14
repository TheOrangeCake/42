/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed_compare.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:19:41 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/14 18:30:08 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

bool Fixed::operator>(const Fixed& bigger) const {
	if (this->toFloat() > bigger.toFloat())
		return (true);
	else
		return (false);
}

bool Fixed::operator<(const Fixed& smaller) const {
	if (this->toFloat() < smaller.toFloat())
		return (true);
	else
		return (false);
}

bool Fixed::operator>=(const Fixed& bigger_equal) const {
	if (this->toFloat() >= bigger_equal.toFloat())
		return (true);
	else
		return (false);
}

bool Fixed::operator<=(const Fixed& smaller_equal) const {
	if (this->toFloat() <= smaller_equal.toFloat())
		return (true);
	else
		return (false);
}

bool Fixed::operator==(const Fixed& equal) const {
	if (this->toFloat() == equal.toFloat())
		return (true);
	else
		return (false);
}

bool Fixed::operator!=(const Fixed& not_equal) const {
	if (this->toFloat() != not_equal.toFloat())
		return (true);
	else
		return (false);
}