/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:40:12 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/23 23:11:01 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "Intern.hpp"

int	main(void)
{
	{
		std::cout << "----- Robotomy request -----" << std::endl;
		Bureaucrat personA = Bureaucrat("Frimousse", 5);
		Intern someRandomIntern;
		AForm* rrf;
		rrf = someRandomIntern.makeForm("robotomy request", "Bender");
		if (rrf != NULL) {
			std::cout << *rrf << std::endl;
			std::cout << personA << std::endl;

			// All ok
			std::cout << "----- All ok -----" << std::endl;
			personA.signForm(*rrf);
			personA.executeForm(*rrf);
			std::cout << std::endl;
			delete rrf;
		}
	}
	{
		std::cout << "----- Presidential pardon -----" << std::endl;
		Bureaucrat personA = Bureaucrat("Frimousse", 5);
		Intern someRandomIntern;
		AForm* rrf;
		rrf = someRandomIntern.makeForm("presidential pardon", "Olivier");
		if (rrf != NULL) {
			std::cout << *rrf << std::endl;
			std::cout << personA << std::endl;

			// All ok
			std::cout << "----- All ok -----" << std::endl;
			personA.signForm(*rrf);
			personA.executeForm(*rrf);
			std::cout << std::endl;
			delete rrf;
		}
	}
	{
		std::cout << "----- Shrubbery -----" << std::endl;
		Bureaucrat personA = Bureaucrat("Frimousse", 5);
		Intern someRandomIntern;
		AForm* rrf;
		rrf = someRandomIntern.makeForm("shrubbery creation", "Patrick");
		if (rrf != NULL) {
			std::cout << *rrf << std::endl;
			std::cout << personA << std::endl;

			// All ok
			std::cout << "----- All ok -----" << std::endl;
			personA.signForm(*rrf);
			personA.executeForm(*rrf);
			std::cout << std::endl;
			delete rrf;
		}
	}
	{
		std::cout << "----- Form not exist -----" << std::endl;
		Bureaucrat personA = Bureaucrat("Frimousse", 5);
		Intern someRandomIntern;
		AForm* rrf;
		rrf = someRandomIntern.makeForm("random form", "random name");
		if (rrf != NULL) {
			std::cout << *rrf << std::endl;
			std::cout << personA << std::endl;

			// All ok
			std::cout << "----- All ok -----" << std::endl;
			personA.signForm(*rrf);
			personA.executeForm(*rrf);
			std::cout << std::endl;
			delete rrf;
		}
	}
}