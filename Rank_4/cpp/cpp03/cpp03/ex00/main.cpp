/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:03:13 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/15 17:18:16 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int	main(void)
{
	ClapTrap	crab;

	crab.printClapTrap();
	crab.attack("Shrimp");
	crab.printClapTrap();
	crab.takeDamage(2);
	crab.printClapTrap();
	crab.beRepaired(1);
	crab.printClapTrap();
	return (0);
}
