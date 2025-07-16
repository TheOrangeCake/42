/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:40:30 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/08 09:45:39 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat() : name("Default"), grade(150) {
	
}

Bureaucrat::Bureaucrat(int grade) : name("Default") {
	try {
		if (grade > 150)
			throw Bureaucrat::GradeTooLowException();
		else if (grade < 1)
			throw Bureaucrat::GradeTooHighException();
		else
			this->grade = grade;
	} catch (Bureaucrat::GradeTooLowException& e) {
		std::cout << "Exception: " << e.what() << std::endl;
		this->grade = 150;
	} catch (Bureaucrat::GradeTooHighException& e) {
		std::cout << "Exception: " << e.what() << std::endl;
		this->grade = 1;
	}
}

Bureaucrat::Bureaucrat(std::string name, int grade) : name(name) {
	try {
		if (grade > 150)
			throw Bureaucrat::GradeTooLowException();
		else if (grade < 1)
			throw Bureaucrat::GradeTooHighException();
		else
			this->grade = grade;
	} catch (Bureaucrat::GradeTooLowException& e) {
		std::cout << "Exception: " << e.what() << std::endl;
		this->grade = 150;
	} catch (Bureaucrat::GradeTooHighException& e) {
		std::cout << "Exception: " << e.what() << std::endl;
		this->grade = 1;
	}
}

Bureaucrat::Bureaucrat(const Bureaucrat& copy) : name(copy.name), grade(copy.grade) {
	(void)copy;
}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& assign) {
	if (this != &assign)
		this->grade = assign.grade;
	return (*this);
}

Bureaucrat::~Bureaucrat() {
	
}

std::string Bureaucrat::getName() const {
	return (this->name);
}

int	Bureaucrat::getGrade() const {
	return (this->grade);
}

void Bureaucrat::promote() {
	try {
		this->grade -= 1;
		std::cout << "Promoting 1 grade" << std::endl;
		if (this->grade < 1)
			throw Bureaucrat::GradeTooHighException();
	} catch (Bureaucrat::GradeTooHighException& e) {
		std::cout << "Exception: " << e.what() << std::endl;
		this->grade = 1;
	}
}

void Bureaucrat::promote(int grade) {
	if (grade < 0) {
		std::cout << "Fail! Can not set negative grade" << std::endl;
		return;
	}
	try {
		this->grade -= grade;
		std::cout << "Promoting " << grade << " grade" << std::endl;
		if (this->grade < 1)
			throw Bureaucrat::GradeTooHighException();
	} catch (Bureaucrat::GradeTooHighException& e) {
		std::cout << "Exception: " << e.what() << std::endl;
		this->grade = 1;
	}
}

void Bureaucrat::demote() {
	try {
		this->grade += 1;
		std::cout << "Demoting 1 grade" << std::endl;
		if (this->grade > 150)
			throw Bureaucrat::GradeTooLowException();
	} catch (Bureaucrat::GradeTooLowException& e) {
		std::cout << "Exception: " << e.what() << std::endl;
		this->grade = 150;
	}
}

void Bureaucrat::demote(int grade) {
	if (grade < 0) {
		std::cout << "Fail! Can not set negative grade" << std::endl;
		return;
	}
	try {
		this->grade += grade;
		std::cout << "Demoting " << grade << " grade" << std::endl;
		if (this->grade > 150)
			throw Bureaucrat::GradeTooLowException();
	} catch (Bureaucrat::GradeTooLowException& e) {
		std::cout << "Exception: " << e.what() << std::endl;
		this->grade = 150;
	}
}
		
const char* Bureaucrat::GradeTooHighException::what() const throw() {
	return ("GradeTooHighException. Grade was set to 1 instead");
}
const char* Bureaucrat::GradeTooLowException::what() const throw() {
	return ("GradeTooLowException. Grade was set to 150 instead");
}

std::ostream& operator<<(std::ostream& o, const Bureaucrat& person) {
	o << person.getName() << ", bureaucrat grade " << person.getGrade() << ".";
	return (o);
}