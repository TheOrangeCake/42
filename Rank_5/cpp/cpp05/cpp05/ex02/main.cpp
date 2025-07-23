/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:40:12 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/23 23:07:50 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"

int	main(void)
{
	{
		std::cout << "----- Information -----" << std::endl;
		Bureaucrat personA = Bureaucrat("Frimousse", 135);
		Bureaucrat personB = Bureaucrat("Pookie", 149);
		ShrubberyCreationForm  formA = ShrubberyCreationForm();
		std::cout << formA << std::endl;
		std::cout << personA << std::endl;
		std::cout << personB << std::endl;
		
		// Unsigned
		std::cout << "----- Unsigned error -----" << std::endl;
		personA.executeForm(formA);

		// Low grade
		std::cout << "----- Low grade error -----" << std::endl;
		personB.signForm(formA);
		personB.executeForm(formA);

		// All ok
		std::cout << "----- All ok -----" << std::endl;
		personA.signForm(formA);
		// formA.execute(personA);
		personA.executeForm(formA);
		std::cout << std::endl;
	}
	{
		std::cout << "----- Information -----" << std::endl;
		Bureaucrat personA = Bureaucrat("Frimousse", 5);
		Bureaucrat personB = Bureaucrat("Pookie", 149);
		PresidentialPardonForm formA = PresidentialPardonForm("Mickey");
		std::cout << formA << std::endl;
		std::cout << personA << std::endl;
		std::cout << personB << std::endl;
		
		// Unsigned
		std::cout << "----- Unsigned error -----" << std::endl;
		personA.executeForm(formA);

		// Low grade
		std::cout << "----- Low grade error -----" << std::endl;
		personB.signForm(formA);
		personB.executeForm(formA);

		// All ok
		std::cout << "----- All ok -----" << std::endl;
		personA.signForm(formA);
		// formA.execute(personA);
		personA.executeForm(formA);
		std::cout << std::endl;
	}
	{
		std::cout << "----- Information -----" << std::endl;
		Bureaucrat personA = Bureaucrat("Frimousse", 5);
		Bureaucrat personB = Bureaucrat("Pookie", 149);
		RobotomyRequestForm formA = RobotomyRequestForm("Mickey");
		std::cout << formA << std::endl;
		std::cout << personA << std::endl;
		std::cout << personB << std::endl;
		
		// Unsigned
		std::cout << "----- Unsigned error -----" << std::endl;
		personA.executeForm(formA);

		// Low grade
		std::cout << "----- Low grade error -----" << std::endl;
		personB.signForm(formA);
		personB.executeForm(formA);

		// All ok
		std::cout << "----- All ok -----" << std::endl;
		personA.signForm(formA);
		personA.executeForm(formA);
		std::cout << std::endl;
	}
}