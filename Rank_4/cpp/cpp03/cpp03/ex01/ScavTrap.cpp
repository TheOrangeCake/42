/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 23:26:56 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/17 00:28:59 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap() : ClapTrap() {
	_hp = 100;
	_mp = 50;
	_atk = 20;
	std::cout << "ScavTrap: Default constructor called" << std::endl;
}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name) {
	_hp = 100;
	_mp = 50;
	_atk = 20;
	std::cout << "ScavTrap: Name constructor called" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap& copy) : ClapTrap() {
	std::cout << "ScavTrap: Copy constructor called" << std::endl;
	*this = copy;
}

ScavTrap& ScavTrap::operator=(const ScavTrap& assign) {
	std::cout << "ScavTrap: Assign operator overload called" << std::endl;
	this->_name = assign._name;
	this->_hp = assign._hp;
	this->_mp = assign._mp;
	this->_atk = assign._atk;
	return (*this);
}

ScavTrap::~ScavTrap() {
	std::cout << "ScavTrap: Destructor called" << std::endl;
}

void ScavTrap::attack(const std::string& target) {
	if (this->_mp > 0 && this->_hp > 0)
	{
		std::cout << "ScavTrap " << this->_name << " attacks " << target;
		std::cout << ", causing " << this->_atk << " points of damage!" << std::endl;
		this->_mp -= 1;
	}
	else if (this->_hp <= 0)
		std::cout << "Failed! ScavTrap " << this->_name << " has no health left!" << std::endl;
	else
		std::cout << "Failed! ScavTrap " << this->_name << " has no energy point left!" << std::endl;
}


void ScavTrap::guardGate() const {
	std::cout << "ScavTrap " << this->_name << " is now in Gate keeper mode." << std::endl;
}

void ScavTrap::printClapTrap() const {
	std::cout << "ScavTrap " << this->_name << " has " << this->_hp << " hp, ";
	std::cout << this->_mp << " mp and " << this->_atk << " atk." << std::endl;
}