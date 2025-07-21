/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typeCheck.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:26:44 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/21 19:15:07 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

bool checkSpecial(std::string input) {
	if (input == "-inff" || input == "+inff" || input == "nanf")
		return (true);
	if (input == "-inf" || input == "+inf" || input == "nan")
		return (true);
	return (false);
}

bool checkChar(std::string input) {
	(void)input;
	return (false);
}

bool checkInt(std::string input) {
	(void)input;
	return (false);
}

bool checkFloat(std::string input) {
	(void)input;
	return (false);
}

bool checkDouble(std::string input) {
	(void)input;
	return (false);
}

int typeCheck(std::string input) {
	size_t	decimal;
	size_t	f;
	size_t	F;
	
	decimal = input.find('.');
	if (decimal == std::string::npos) {
		if (checkSpecial(input))
			return (5);
		if (checkChar(input))
			return (1);
		if (checkInt(input))
			return (2);
	} else {
		f = input.find('f');
		F = input.find('F');
		if (f != std::string::npos || F != std::sting::npos) {
			if (checkFloat(input))
				return (3);
		} else {
			if (checkDouble(input))
				return (4);
		}
	}
	return (-1);
}