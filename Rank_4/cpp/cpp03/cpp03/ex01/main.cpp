/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:03:13 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/17 00:35:57 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int	main(void)
{
	ScavTrap queen;
	queen.printClapTrap();
	queen.attack("Oyster");
	queen.printClapTrap();
	queen.beRepaired(20);
	queen.printClapTrap();
	queen.guardGate();

	ScavTrap king("King Crab");
	king.printClapTrap();
	king.guardGate();
	king = queen;
	king.printClapTrap();

	return (0);
}
