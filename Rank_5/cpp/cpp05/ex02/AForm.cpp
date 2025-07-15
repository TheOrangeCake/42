/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 09:33:34 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/15 22:55:28 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"

AForm::AForm() :
	name("Default"),
	isSigned(false),
	signGrade(150),
	exeGrade(150) {
}
AForm::AForm(std::string name, int signGrade, int exeGrade) :
	name(name),
	isSigned(false),
	signGrade(signGrade),
	exeGrade(exeGrade) {
	try {
		if (this->signGrade > 150 || this->exeGrade > 150)
			throw AForm::GradeTooLowException();
		else if (this->signGrade < 1 || this->exeGrade < 1)
			throw AForm::GradeTooHighException();
	} catch (AForm::GradeTooHighException& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	} catch (AForm::GradeTooLowException& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}
}
AForm::AForm(const AForm& copy) : 
	name(copy.name),
	isSigned(copy.isSigned),
	signGrade(copy.signGrade),
	exeGrade(copy.exeGrade) {
	(void)copy;
}
AForm& AForm::operator=(const AForm& assign) {
	if (this != &assign)
		this->isSigned = assign.isSigned;
	return (*this);
}
AForm::~AForm() {
}

std::string AForm::getName() const {
	return (this->name);
}
bool AForm::getIsSigned() const {
	return (this->isSigned);
}
int AForm::getSignGrade() const {
	return (this->signGrade);
}
int AForm::getExeGrade() const {
	return (this->exeGrade);
}
void AForm::setIsSigned(bool value) {
	this->isSigned = value;
}

bool AForm::beSigned(Bureaucrat& person) {
	try {
		if (person.getGrade() <= this->signGrade) {
			this->isSigned = true;
			return (true);
		} else {
			throw AForm::GradeTooLowException();
		}
	} catch (AForm::GradeTooLowException& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
		this->isSigned = false;
		return (false);
	}
}

bool AForm::requirementsCheck(Bureaucrat const & executor) const {
	try {
		if (executor.getGrade() > this->exeGrade) {
			throw AForm::GradeTooLowException();
		}
		if (this->isSigned == false) {
			throw AForm::FormNotSignedException();
		}
		return (true);
	} catch (AForm::GradeTooLowException& e) {
		std::cerr << "Exception: " << e.what() << " Grade too low!" << std::endl;
		return (false);
	} catch (AForm::FormNotSignedException& e) {
		std::cerr << "Exception: " << e.what() << " Form isn't signed!" << std::endl;
		return (false);
	}
}

const char* AForm::GradeTooHighException::what() const throw() {
	return ("GradeTooHighException.");
}
const char* AForm::GradeTooLowException::what() const throw() {
	return ("GradeTooLowException.");
}
const char* AForm::FormNotSignedException::what() const throw() {
	return ("FormNotSignedException.");
}

std::ostream& operator<<(std::ostream& o, const AForm& form) {
	std::string temp;

	if (form.getIsSigned() == true)
		temp = "True";
	else
		temp = "False";
	o << "Form:\n" 
		<< "  Name: " << form.getName() << "\n"
		<< "  Sign Grade: " << form.getSignGrade() << "\n"
		<< "  Exec Grade: " << form.getExeGrade() << "\n"
		<< "  Signed: " << temp;
	return (o);
}