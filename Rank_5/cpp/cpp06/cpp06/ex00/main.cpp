/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:39:59 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/21 11:57:38 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <iostream>

int main(int ac, char **av)
{
	std::string str;

	if (ac != 2)
	{
		std::cerr << "Wrong number of argument!" << std::endl;
		return (1);
	}
	else
	{
		str = av[1];
		ScalarConverter::convert(str);
	}
	return (0);
}