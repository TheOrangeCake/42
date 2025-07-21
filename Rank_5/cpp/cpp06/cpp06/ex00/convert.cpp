/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:27:31 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/21 19:11:55 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

void convertSpecial(std::string input) {
	int	i;
	std::string f;
	std::string d;
	
	i = -1;
	std::string type[6] = {
		"-inff", "+inff", "nanf",
		"-inf", "+inf", "nan"
	};
	while (++i < 6) {
		if (type[i] == input)
			break;
	}
	switch (i % 3) {
		case 0:
			f = "-inff";
			d = "-inf";
			break;
		case 1:
			f = "+inff";
			d = "+inf";
			break;
		case 2:
			f = "nanf";
			d = "nan";
			break;
		default:
			std::cout << "Nani????" <<std::endl;
			return;
	}
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;
	std::cout << "float: " << f << std::endl;
	std::cout << "double: " << d << std::endl;
}

void convertChar(std::string input) {
	(void)input;
	std::cout << "this is a char" << std::endl;
}

void convertInt(std::string input) {
	(void)input;
	std::cout << "this is an int" << std::endl;
}

void convertFloat(std::string input) {
	(void)input;
	std::cout << "this is a float" << std::endl;
}

void convertDouble(std::string input) {
	(void)input;
	std::cout << "this is a double" << std::endl;
}