/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:13:37 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/14 17:35:10 by hoannguy         ###   ########.fr       */
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
		Fixed();
		Fixed(const Fixed& copy);
		Fixed& operator=(const Fixed& assign);
		~Fixed();

		int		getRawBits(void) const;
		void	setRawBits(int const raw);

};

#endif