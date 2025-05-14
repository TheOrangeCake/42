/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:13:31 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/14 22:32:57 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include "Point.hpp"

int	main(void)
{
	Point	a(2.5f, 5);
	Point	b(a);

	std::cout << a.getPoint_x() << std::endl;
	std::cout << a.getPoint_y() << std::endl;
	std::cout << b.getPoint_x() << std::endl;
	std::cout << b.getPoint_y() << std::endl;
	
	return (0);
}

// Note: The second assignment operator call is because of compiler optimisation.
// To illustrate simply: 
// Fixed temp = Fixed(1234.4321f);
// a = temp;
// So the first assignment is temp, second is a. The destructor call is for temp.