/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:40:43 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/14 12:09:41 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP
# include <string>
# include <iostream>
# include "AForm.hpp"

class AForm;

class Bureaucrat {
	private:
		const std::string	name;
		int					grade;

	public:
		Bureaucrat();
		Bureaucrat(int grade);
		Bureaucrat(std::string name, int grade);
		Bureaucrat(const Bureaucrat& copy);
		Bureaucrat& operator=(const Bureaucrat& assign);
		~Bureaucrat();

		std::string getName() const;
		int			getGrade() const;
		void		promote();
		void		promote(int grade);
		void		demote();
		void		demote(int grade);
		void		signForm(AForm& form);
		
		
	class GradeTooHighException : public std::exception {
		public:
			virtual const char* what() const throw();
	};
	class GradeTooLowException : public std::exception {
		public:
			virtual const char* what() const throw();
	};
};

std::ostream& operator<<(std::ostream& o, const Bureaucrat& person);

#endif