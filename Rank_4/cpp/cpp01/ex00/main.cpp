/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:48:21 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/07 20:29:34 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main(void)
{
	Zombie *zombie1;
	zombie1 = newZombie("Zombie 1 heap");
	if (zombie1 == NULL)
	{
		std::cout << "Memory allocation error" << std::endl;
		return (1);
	}
	zombie1->announce();

	randomChump("Zombie stack");
	
	Zombie *zombie2;
	zombie2 = newZombie("Zombie 2 heap");
	if (zombie2 == NULL)
	{
		std::cout << "Memory allocation error" << std::endl;
		return (1);
	}
	zombie2->announce();

	delete zombie1;
	delete zombie2;
	
	return (0);
}