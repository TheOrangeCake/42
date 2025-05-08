/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:45:21 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/08 18:22:17 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"

HumanB::HumanB() {
	name = "Default Human B";
	weapon = NULL;
}

HumanB::HumanB(std::string name) {
	this->name = name;
	weapon = NULL;
}

HumanB::HumanB(std::string name, Weapon &weapon) {
	this->name = name;
	this->weapon = &weapon;
}

HumanB::~HumanB() {
	
}

void HumanB::attack() {
	if (weapon == NULL)
		std::cout << name << " doesn't have any weapon" <<std::endl;
	else
		std::cout << name << " attacks with their " << weapon->getType() << std::endl;
}

void HumanB::setWeapon(Weapon &weapon) {
	this->weapon = &weapon;
}