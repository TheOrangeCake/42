/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:13:37 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/14 01:11:08 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

#include <iostream>
#include <cmath>

class Fixed {
	private:
		int	_value;
		static int const _fraction = 8;
	
	public:
		Fixed(int const number);
		Fixed(float const number);

		Fixed();
		Fixed(const Fixed& copy);
		Fixed& operator=(const Fixed& assign);
		~Fixed();

		int		getRawBits(void) const;
		void	setRawBits(int const raw);
		float 	toFloat(void) const;
		int		toInt(void) const;

};

std::ostream& operator<<(std::ostream& o, const Fixed& number);

#endif