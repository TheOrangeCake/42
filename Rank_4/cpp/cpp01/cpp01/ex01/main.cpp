/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:50:52 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/08 19:15:07 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
#include <limits>

std::string get_input_name()
{
	std::string name;

	std::cout << "Enter zombie name: " << std::endl;
	while (true)
	{
		std::getline(std::cin, name);
		if (name.empty())
		{
			std::cout << "Must enter a name" << std::endl;
		}
		else
			break;
	}
	return (name);
}

int	get_input_number()
{
	int	number;

	std::cout << "Enter number of Zombie: ";
	while (true)
	{
		std::cin >> number;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input" << std::endl;
		}
		else
			break;
	}
	return (number);
}

int main(void)
{
	std::string name;
	int	number;

	name = get_input_name();
	number = get_input_number();
	Zombie *the_horde;
	the_horde = zombieHorde(number, name);
	if (the_horde == NULL)
	{
		std::cerr << "Memory allocation error" << std::endl;
		return (1);
	}
	for (int i = 0; i < number; i++) {
		the_horde[i].announce();
	}
	delete[] the_horde;
	return (0);
}