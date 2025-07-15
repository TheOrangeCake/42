/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:40:12 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/15 12:16:47 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"

int	main(void)
{
	{
		// Unsigned
		Bureaucrat personA = Bureaucrat("Frimousse", 135);
		ShrubberyCreationForm  formA = ShrubberyCreationForm();
		formA.execute(personA);
		std::cout << "-----" << std::endl;

		// Low grade
		Bureaucrat personB = Bureaucrat("Pookie", 140);
		formA.execute(personB);
		std::cout << "-----" << std::endl;

		// All ok
		formA.beSigned(personA);
		std::cout << formA << std::endl;
		formA.execute(personA);
		std::cout << "-----" << std::endl;
	}
}