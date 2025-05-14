/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:13:37 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/14 21:54:23 by hoannguy         ###   ########.fr       */
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


		bool operator>(const Fixed& bigger) const;
		bool operator<(const Fixed& smaller) const;
		bool operator>=(const Fixed& bigger_equal) const;
		bool operator<=(const Fixed& smaller_equal) const;
		bool operator==(const Fixed& equal) const;
		bool operator!=(const Fixed& not_equal) const;
		
		Fixed operator+(const Fixed& plus) const;
		Fixed operator-(const Fixed& minus) const;
		Fixed operator*(const Fixed& multiply) const;
		Fixed operator/(const Fixed& divide) const;

		Fixed& operator++();
		Fixed operator++(int);
		Fixed& operator--();
		Fixed operator--(int);
		
		~Fixed();

		int		getRawBits(void) const;
		void	setRawBits(int const raw);
		float 	toFloat(void) const;
		int		toInt(void) const;

		static Fixed& min(Fixed& a, Fixed& b);
		static const Fixed& min(const Fixed& a, const Fixed& b);
		static Fixed& max(Fixed& a, Fixed& b);
		static const Fixed& max(const Fixed& a, const Fixed& b);
};

std::ostream& operator<<(std::ostream& o, const Fixed& number);

#endif