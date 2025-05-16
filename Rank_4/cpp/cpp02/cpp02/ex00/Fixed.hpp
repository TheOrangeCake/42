/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:13:37 by hoannguy          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/05/14 17:35:10 by hoannguy         ###   ########.fr       */
=======
/*   Updated: 2025/05/13 23:27:53 by hoannguy         ###   ########.fr       */
>>>>>>> 0a3deaf (test)
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

#include <iostream>
<<<<<<< HEAD
#include <cmath>
=======
>>>>>>> 0a3deaf (test)

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
<<<<<<< HEAD

=======
>>>>>>> 0a3deaf (test)
};

#endif