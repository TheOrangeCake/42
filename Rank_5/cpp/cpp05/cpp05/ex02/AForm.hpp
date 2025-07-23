/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 09:33:28 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/23 22:58:29 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AFORM_HPP
#define AFORM_HPP
#include <string>
#include <ostream>
#include "Bureaucrat.hpp"

class Bureaucrat;

class AForm {
	private:
		const std::string	name;
		bool 				isSigned;
		const int			signGrade;
		const int			exeGrade;

	public:
		AForm();
		AForm(std::string name, int signGrade, int exeGrade);
		AForm(const AForm& copy);
		AForm& operator=(const AForm& assign);
		virtual ~AForm();

		std::string 	getName() const;
		bool 			getIsSigned() const;
		int 			getSignGrade() const;
		int 			getExeGrade() const;
		void			setIsSigned(bool value);
		bool 			beSigned(Bureaucrat& person);
		virtual bool 	execute(Bureaucrat const & executor) const = 0;

		class GradeTooHighException : public std::exception {
			public:
				virtual const char* what() const throw();
		};
		class GradeTooLowException : public std::exception {
			public:
				virtual const char* what() const throw();
		};
		class FormNotSignedException : public std::exception {
			public:
				virtual const char* what() const throw();
		};
};

std::ostream& operator<<(std::ostream& o, const AForm& form);

#endif