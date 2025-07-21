/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:40:50 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/21 19:09:13 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(ScalarConverter& copy) {
	(void)copy;
}
ScalarConverter& ScalarConverter::operator =(ScalarConverter& assign) {
	(void)assign;
	return (*this);
}
ScalarConverter::~ScalarConverter() {}

void ScalarConverter::convert(std::string input) {
	int type = -1;

	if (input.empty()) {
		std::cerr << "String is empty" << std::endl;
		return;
	}
	type = typeCheck(input);
	switch (type) {
		case 1:
			convertChar(input);
			break;
		case 2:
			convertInt(input);
			break;
		case 3:
			convertFloat(input);
			break;
		case 4:
			convertDouble(input);
			break;
		case 5:
			convertSpecial(input);
			break;
		default:
			std::cerr << "Invalid input!" << std::endl;
			break;
	}
}