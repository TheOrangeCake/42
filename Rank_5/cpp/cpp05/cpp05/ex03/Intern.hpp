/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:39:26 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/23 23:09:42 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERN_HPP
# define INTERN_HPP
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include <string>
#include <cctype>

class Intern {
	public:
		Intern();
		Intern(Intern& copy);
		Intern& operator=(Intern& assign);
		~Intern();
	
		AForm* makeForm(std::string formName, std::string target);
	
	private:
		AForm* makeRobotomy(std::string target);
		AForm* makePardon(std::string target);
		AForm* makeShrubbery(std::string target);
};

#endif