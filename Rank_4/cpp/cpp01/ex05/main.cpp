/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:36:05 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/09 14:54:41 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include "Harl.hpp"

int main()
{
	std::string line;
	Harl harl;

	while (true)
	{
		std::cout << "Level: ";
		if (std::getline(std::cin, line))
		{
			if (line == "EXIT")
				break;
			else
				harl.complain(line);
		}
	}
	return (0);
}