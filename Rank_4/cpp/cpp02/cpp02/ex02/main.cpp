/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:13:31 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/14 18:29:56 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

int	main(void)
{
	Fixed 		a(3.5f);
	Fixed 		b(2.5f);

	if (a != b)
		std::cout << "true" << std::endl;
	else
		std::cout << "false" << std::endl;
	
	return (0);
}

// Note: The second assignment operator call is because of compiler optimisation.
// To illustrate simply: 
// Fixed temp = Fixed(1234.4321f);
// a = temp;
// So the first assignment is temp, second is a. The destructor call is for temp.