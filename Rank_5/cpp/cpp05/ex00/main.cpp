/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:40:12 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/07 22:01:47 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int	main(void)
{
	Bureaucrat a = Bureaucrat(3);
	std::cout << a.getName() << std::endl;
	std::cout << a.getGrade() << std::endl;
	a.promote();
	std::cout << a << std::endl;
	a.promote(20);
	std::cout << a << std::endl;
	a.demote();
	std::cout << a << std::endl;
	a.demote(150);
	std::cout << a << std::endl;
}