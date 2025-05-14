/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed_min_max.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:43:38 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/14 21:54:25 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed& Fixed::min(Fixed& a, Fixed& b) {
	if (a > b)
		return (b);
	else
		return (a);
}

const Fixed& Fixed::min(const Fixed& a, const Fixed& b) {
	if (a > b)
		return (b);
	else
		return (a);
}

Fixed& Fixed::max(Fixed& a, Fixed& b) {
	if (a < b)
		return (b);
	else
		return (a);
}

const Fixed& Fixed::max(const Fixed& a, const Fixed& b) {
	if (a < b)
		return (b);
	else
		return (a);
}
