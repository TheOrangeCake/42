/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:03:13 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/17 00:31:00 by hoannguy         ###   ########.fr       */
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

	ScavTrap king("King Crab");
	king.printClapTrap();
	king = queen;
	king.printClapTrap();

	return (0);
}
