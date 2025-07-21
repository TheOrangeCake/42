/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:40:13 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/21 18:37:17 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP
# include <string>
# include <iostream>
# include <cctype>
# include <cstdlib>

class ScalarConverter {
	private:
		ScalarConverter();
		ScalarConverter(ScalarConverter& copy);
		ScalarConverter& operator =(ScalarConverter& assign);
		~ScalarConverter();

	public:
		static void convert(std::string input);
};

int		typeCheck(std::string input);
void	convertSpecial(std::string input);
void	convertChar(std::string input);
void	convertInt(std::string input);
void	convertFloat(std::string input);
void	convertDouble(std::string input);

#endif