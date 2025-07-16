/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:38:05 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/16 22:07:22 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm() : 
	AForm("PresidentialPardonForm", 25, 5) {
		this->target = "Goofy";
}

PresidentialPardonForm::PresidentialPardonForm(std::string target) : 
	AForm("PresidentialPardonForm", 25, 5) {
		this->target = target;
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& copy) :
	AForm("PresidentialPardonForm", 25, 5) {
	this->setIsSigned(copy.getIsSigned());
	this->target = copy.target;
}
PresidentialPardonForm& PresidentialPardonForm::operator=(const PresidentialPardonForm& assign) {
	if (this != &assign){
		this->setIsSigned(assign.getIsSigned());
		this->target = assign.target;
	}
	return (*this);
}
PresidentialPardonForm::~PresidentialPardonForm() {
}

bool PresidentialPardonForm::requirementsCheck(Bureaucrat const & executor) const {
	if (this->execute(executor) == true) {
		std::cout << this->target << " has been pardoned by Zaphod Beeblebrox" << std::endl;
		return (true);
	} else {
		return (false);
	}
}