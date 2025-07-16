/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:40:12 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/08 19:25:24 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"

int	main(void)
{
	Bureaucrat a = Bureaucrat("Person A", 3);
	std::cout << a << std::endl;
	Form formular = Form();
	std::cout << formular << std::endl;

	std::cout << "-----" << std::endl;

	Form formularA = Form("A", 0, 10);
	std::cout << formularA << std::endl;

	std::cout << "-----" << std::endl;

	Form formularB = Form("B", 151, 10);
	std::cout << formularB << std::endl;

	std::cout << "-----" << std::endl;

	Form formularC = Form("C", 40, 10);
	std::cout << formularC << std::endl;
	a.signForm(formularC);
	std::cout << formularC << std::endl;

	std::cout << "-----" << std::endl;

	Bureaucrat b = Bureaucrat("Person B", 50);
	std::cout << b << std::endl;
	b.signForm(formularC);
	std::cout << formularC << std::endl;
}