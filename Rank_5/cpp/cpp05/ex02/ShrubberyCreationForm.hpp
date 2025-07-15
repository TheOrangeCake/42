/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:34:51 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/15 12:16:11 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHRUBBERYCREATIONFORM_HPP
# define SHRUBBERYCREATIONFORM_HPP
# include "Bureaucrat.hpp"
# include "AForm.hpp"
# include <iostream>
# include <fstream>

class Bureaucrat;

class ShrubberyCreationForm : public AForm {
	private:
		std::string target;
	
	public:
		ShrubberyCreationForm();
		ShrubberyCreationForm(std::string target);
		ShrubberyCreationForm(const ShrubberyCreationForm& copy);
		ShrubberyCreationForm& operator=(const ShrubberyCreationForm& assign);
		~ShrubberyCreationForm();

		bool execute(Bureaucrat const & executor) const;
};

#endif