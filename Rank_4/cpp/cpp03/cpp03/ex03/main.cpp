/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:03:13 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/19 13:17:27 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"
#include "DiamondTrap.hpp"

int	main(void)
{
	DiamondTrap	diamond;
	diamond.printClapTrap();
	diamond.whoAmI();
	diamond.attack("Clam");
	diamond.guardGate();
	diamond.highFivesGuys();
	diamond.takeDamage(20);
	diamond.printClapTrap();

	ScavTrap scav;
	scav.printClapTrap();

	FragTrap frag;
	frag.printClapTrap();
	
	return (0);
}
