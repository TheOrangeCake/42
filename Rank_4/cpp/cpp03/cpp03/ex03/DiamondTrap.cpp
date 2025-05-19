/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 09:06:45 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/19 13:13:49 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap() : ClapTrap(), ScavTrap(), FragTrap() {
	std::cout << "DiamondTrap: Default constructor called" << std::endl;
	this->_name = "Diamond Crab";
	this->ClapTrap::_name += "_clap_name";
	_hp = FragTrap::frag_hp;
	_mp = ScavTrap::scav_mp;
	_atk = FragTrap::frag_atk;
}

DiamondTrap::DiamondTrap(std::string name) : ClapTrap(name + "_clap_name"), ScavTrap(), FragTrap() {
	std::cout << "DiamondTrap: Name constructor called" << std::endl;
	this->_name = name;
	_hp = FragTrap::frag_hp;
	_mp = ScavTrap::_mp;
	_atk = FragTrap::frag_atk;
}

DiamondTrap::DiamondTrap(const DiamondTrap& copy) : ClapTrap(), ScavTrap(), FragTrap() {
	std::cout << "DiamondTrap: Copy constructor called" << std::endl;
	*this = copy;
}

DiamondTrap& DiamondTrap::operator=(const DiamondTrap& assign) {
	std::cout << "DiamondTrap: Assign operator overload called" << std::endl;
	this->_name = assign._name;
	this->ClapTrap::_name = assign.ClapTrap::_name;
	this->_hp = assign._hp;
	this->_mp = assign._mp;
	this->_atk = assign._atk;
	return (*this);
}

DiamondTrap::~DiamondTrap() {
	std::cout << "DiamondTrap: Destructor called" << std::endl;
}

void DiamondTrap::attack(const std::string& target) {
	ScavTrap::attack(target);
}

void DiamondTrap::whoAmI() {
	std::cout << "DiamondTrap: " << this->_name;
	std::cout << " and ClapTrap: " << this->ClapTrap::_name << std::endl;
}

void DiamondTrap::printClapTrap() const {
	std::cout << "DiamondTrap " << this->_name << " has " << this->_hp << " hp, ";
	std::cout << this->_mp << " mp and " << this->_atk << " atk." << std::endl;
}