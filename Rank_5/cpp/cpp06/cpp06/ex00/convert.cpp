/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:27:31 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/22 00:31:09 by hoannguy         ###   ########.fr       */
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
	char	c;

	if (input.length() == 1) {
		c = input[0];
	} else if (input.length() == 3) {
		c = input[1];
	}
	if (!isprint(c)) {
		std::cout << "char: Non displayable" << std::endl;
	} else {
		std::cout << "char: \'" << c << "\'"<< std::endl;
	}
	std::cout << "int: " << static_cast<int>(c) << std::endl;
	std::cout << "float: " << static_cast<float>(c) << ".0f" << std::endl;
	std::cout << "double: " << static_cast<double>(c) << ".0" <<std::endl;
}
	
void convertInt(std::string input) {
	long	l;
	int		i;

	errno = 0;
	l = strtol(input.c_str(), NULL, 10);
	if (l > INT_MAX || l < INT_MIN) {
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		if (errno == ERANGE) {
			std::cout << "float: impossible" << std::endl;
			std::cout << "double: impossible" << std::endl;
		} else {
			std::cout << "float: " << std::fixed << std::setprecision(1) << static_cast<float>(l) << "f" << std::endl;
			std::cout << "double: " << std::fixed << std::setprecision(1) << static_cast<double>(l) << std::endl;
		}
	} else {
		i = static_cast<int>(l);
		if (i < 0 || i > 127)
			std::cout << "char: impossible" << std::endl;
		else {
			if (!isprint(i)) {
				std::cout << "char: Non displayable" << std::endl;
			} else {
				std::cout << "char: \'" << static_cast<char>(i) << "\'"<< std::endl;
			}
		}
		std::cout << "int: " << i << std::endl;
		std::cout << "float: " << std::fixed << std::setprecision(1) << static_cast<float>(i) << "f" << std::endl;
		std::cout << "double: " << std::fixed << std::setprecision(1) << static_cast<double>(i) << std::endl;
	}
}

void convertFloat(std::string input) {
	double	d;
	float	f;

	errno = 0;
	d = strtod(input.c_str(), NULL);
	if (errno == ERANGE) {
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
	} else {
		f = static_cast<float>(d);
		if (f < 0 || f > 127)
			std::cout << "char: impossible" << std::endl;
		else {
			if (!isprint(f))
				std::cout << "char: Non displayable" << std::endl;
			else
				std::cout << "char: \'" << static_cast<char>(f) << "\'"<< std::endl;
		}
		if (f > INT_MAX || f < INT_MIN) {
			std::cout << "int: impossible" << std::endl;
		} else {
			std::cout << "int: " << static_cast<int>(f) << std::endl;
		}
		std::cout << "float: " << std::fixed << std::setprecision(1) << f << "f" << std::endl;
		std::cout << "double: " << std::fixed << std::setprecision(1) << static_cast<double>(f) << std::endl;
	}
}

void convertDouble(std::string input) {
	(void)input;
	std::cout << "this is a double" << std::endl;
}