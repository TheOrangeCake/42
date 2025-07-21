/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typeCheck.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:26:44 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/21 23:31:34 by hoannguy         ###   ########.fr       */
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

	if (input.length() == 1 && !isdigit(input[0]))
		return (true);
	if (input.length() == 3 && !isdigit(input[1])
		&& input[0] == '\'' && input[2] == '\'')
		return (true);
	return (false);
}

bool checkInt(std::string input) {
	unsigned int	i;

	i = 0;
	if (input[i] == '-' || input[i] == '+')
		i++;
	while (i < input.length()) {
		if (!isdigit(input[i]))
			return (false);
		i++;
	}
	return (true);
}

bool checkFloat(std::string input, size_t decimal) {
	unsigned int	i;

	i = 0;
	if (input[i] == '-' || input[i] == '+')
		i++;
	while (i < decimal) {
		if (!isdigit(input[i]))
			return (false);
		i++;
	}
	i++;
	while (i < input.length() - 1) {
		if (!isdigit(input[i]))
			return (false);
		i++;
	}
	return (true);
}

bool checkDouble(std::string input, size_t decimal) {
	unsigned int	i;

	i = 0;
	if (input[i] == '-' || input[i] == '+')
		i++;
	while (i < decimal) {
		if (!isdigit(input[i]))
			return (false);
		i++;
	}
	i++;
	while (i < input.length()) {
		if (!isdigit(input[i]))
			return (false);
		i++;
	}
	return (true);
}

int typeCheck(std::string input) {
	size_t	decimal;
	size_t	f;
	
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
		if (f != std::string::npos) {
			if (checkFloat(input, decimal))
				return (3);
		} else {
			if (checkDouble(input, decimal))
				return (4);
		}
	}
	return (-1);
}