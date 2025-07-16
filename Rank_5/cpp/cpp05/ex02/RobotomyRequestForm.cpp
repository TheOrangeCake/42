/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:36:59 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/16 15:37:53 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm() : 
	AForm("RobotomyRequestForm", 72, 45) {
		this->target = "Goofy";
}

RobotomyRequestForm::RobotomyRequestForm(std::string target) : 
	AForm("RobotomyRequestForm", 72, 45) {
		this->target = target;
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& copy) :
	AForm("RobotomyRequestForm", 72, 45) {
	this->setIsSigned(copy.getIsSigned());
	this->target = copy.target;
}
RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm& assign) {
	if (this != &assign){
		this->setIsSigned(assign.getIsSigned());
		this->target = assign.target;
	}
	return (*this);
}
RobotomyRequestForm::~RobotomyRequestForm() {
}

bool RobotomyRequestForm::execute(Bureaucrat const & executor) const {
	int	random;

	if (this->requirementsCheck(executor) == true) {
		std::cout << "Drilling... Brrrrrrrr... Brrrrrrrr" << std::endl;
		random = rand()  % 2;
		if (random % 2 == 0)
			std::cout << "-> " << this->target << " has been robotomized successfully" << std::endl;
		else
			std::cout << "-> The robotomy has failed!" << std::endl;
		return (true);
	} else {
		return (false);
	}
}