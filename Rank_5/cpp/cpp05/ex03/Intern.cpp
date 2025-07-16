/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:39:48 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/16 22:28:33 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

Intern::Intern() {}
Intern::Intern(Intern& copy) {
	(void)copy;
}
Intern& Intern::operator=(Intern& assign) {
	(void)assign;
	return (*this);
}
Intern::~Intern() {}

AForm* Intern::makeShrubbery(std::string target) {
	ShrubberyCreationForm *form = new ShrubberyCreationForm(target);
	return (form);
}
AForm* Intern::makePardon(std::string target) {
	PresidentialPardonForm *form = new PresidentialPardonForm(target);
	return (form);
}
AForm* Intern::makeRobotomy(std::string target) {
	RobotomyRequestForm *form = new RobotomyRequestForm(target);
	return (form);
}

AForm* Intern::makeForm(std::string formName, std::string target) {
	AForm *form;

	AForm* (Intern::*f[3])(std::string) = {
		&Intern::makeShrubbery,
		&Intern::makePardon,
		&Intern::makeRobotomy,
	};
	std::string list[3] = {
		"shrubbery creation",
		"presidential pardon",
		"robotomy request"
	};
	for (int i = 0; i < 3; i++) {
		if (formName == list[i]) {
			form = (this->*f[i])(target);
			std::cout << "Intern creates " << form->getName() << std::endl;
			return (form);
		}
	}
	std::cerr << "Form template doesn't exist!" << std::endl;
	return (NULL);
}