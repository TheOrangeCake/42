/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 09:33:34 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/08 19:10:52 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

Form::Form() :
	name("Default"),
	isSigned(false),
	signGrade(150),
	exeGrade(150) {
}
Form::Form(std::string name, int signGrade, int exeGrade) :
	name(name),
	isSigned(false),
	signGrade(signGrade),
	exeGrade(exeGrade) {
	try {
		if (this->signGrade > 150 || this->exeGrade > 150)
			throw Form::GradeTooLowException();
		else if (this->signGrade < 1 || this->exeGrade < 1)
			throw Form::GradeTooHighException();
	} catch (Form::GradeTooHighException& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	} catch (Form::GradeTooLowException& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}
}
Form::Form(const Form& copy) : 
	name(copy.name),
	isSigned(copy.isSigned),
	signGrade(copy.signGrade),
	exeGrade(copy.exeGrade) {
	(void)copy;
}
Form& Form::operator=(const Form& assign) {
	if (this != &assign)
		this->isSigned = assign.isSigned;
	return (*this);
}
Form::~Form() {

}

std::string Form::getName() const {
	return (this->name);
}
bool Form::getIsSigned() const {
	return (this->isSigned);
}
int Form::getSignGrade() const {
	return (this->signGrade);
}
int Form::getExeGrade() const {
	return (this->exeGrade);
}

bool Form::beSigned(Bureaucrat& person) {
	try {
		if (person.getGrade() <= this->signGrade) {
			this->isSigned = true;
			return (true);
		} else {
			throw Form::GradeTooLowException();
		}
	} catch (Form::GradeTooLowException& e) {
		std::cout << "Exception: " << e.what() << std::endl;
		this->isSigned = false;
		return (false);
	}
}

const char* Form::GradeTooHighException::what() const throw() {
	return ("GradeTooHighException.");
}
const char* Form::GradeTooLowException::what() const throw() {
	return ("GradeTooLowException.");
}

std::ostream& operator<<(std::ostream& o, const Form& form) {
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