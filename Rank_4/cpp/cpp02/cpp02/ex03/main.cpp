/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:13:31 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/15 15:53:49 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include "Point.hpp"

int	main(void)
{
	Point const	a(1, 1);
	Point const	b(7, 4);
	Point const	c(3, 6);
	Point const	point(2.5f, 3.5f);

	if (bsp(a, b, c, point))
		std::cout << "True" << std::endl;
	else
		std::cout << "False" << std::endl;
	
	return (0);
}
