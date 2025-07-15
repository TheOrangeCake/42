/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:35:01 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/15 12:37:55 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm() : 
	AForm("ShrubberyCreationForm", 145, 137) {
		this->target = "home";
}

ShrubberyCreationForm::ShrubberyCreationForm(std::string target) : 
	AForm("ShrubberyCreationForm", 145, 137) {
		this->target = target;
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& copy) :
	AForm("ShrubberyCreationForm", 145, 137) {
	this->setIsSigned(copy.getIsSigned());
	this->target = copy.target;
}
ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& assign) {
	if (this != &assign){
		this->setIsSigned(assign.getIsSigned());
		this->target = assign.target;
	}
	return (*this);
}
ShrubberyCreationForm::~ShrubberyCreationForm() {
}

bool ShrubberyCreationForm::execute(Bureaucrat const & executor) const {
	std::ofstream file;
	
	if (this->requirementsCheck(executor) == true) {
		file.open((this->target + "_shrubbery").c_str());
		if (!file.is_open()) {
			std::cerr << "ofstream failed!" << std::endl;
			return (false);
		}
		file.close();
		return (true);
	} else {
		std::cout << "Do nothing" << std::endl;
		return (false);
	}
}