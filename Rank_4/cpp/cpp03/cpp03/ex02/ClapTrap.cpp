/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:02:24 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/19 13:17:58 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap() : _name("Crab"), _hp(10), _mp(10), _atk(0) {
	std::cout << "ClapTrap: Default constructor called" << std::endl;
}

ClapTrap::ClapTrap(std::string name) {
	std::cout << "ClapTrap: Name constructor called" << std::endl;
	this->_name = name;
}

ClapTrap::ClapTrap(const ClapTrap& copy) {
	std::cout << "ClapTrap: Copy constructor called" << std::endl;
	*this = copy;
}

ClapTrap& ClapTrap::operator=(const ClapTrap& assign) {
	std::cout << "ClapTrap: Assign operator overload called" << std::endl;
	this->_name = assign._name;
	this->_hp = assign._hp;
	this->_mp = assign._mp;
	this->_atk = assign._atk;
	return (*this);
}

ClapTrap::~ClapTrap() {
	std::cout << "ClapTrap: Destructor called" << std::endl;
}

void ClapTrap::attack(const std::string& target) {
	if (this->_mp > 0 && this->_hp > 0)
	{
		std::cout << "ClapTrap " << this->_name << " attacks " << target;
		std::cout << ", causing " << this->_atk << " points of damage!" << std::endl;
		this->_mp -= 1;
	}
	else if (this->_hp <= 0)
		std::cout << "Failed! " << this->_name << " has no health left!" << std::endl;
	else
		std::cout << "Failed! " << this->_name << " has no energy point left!" << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount) {
	std::cout << this->_name << " has taken " << amount << " damages." << std::endl;
	this->_hp -= amount;
	if (this->_hp < 0)
		this->_hp = 0;
}

void ClapTrap::beRepaired(unsigned int amount) {
	if (this->_mp > 0)
	{
		std::cout << this->_name << " is healed for " << amount << " hp." << std::endl;
		this->_hp += amount;
		this->_mp -= 1;
	}
	else
		std::cout << "Failed! " << this->_name << " has no energy point left!" << std::endl;
}

void ClapTrap::printClapTrap() const {
	std::cout << "ClapTrap " << this->_name << " has " << this->_hp << " hp, ";
	std::cout << this->_mp << " mp and " << this->_atk << " atk." << std::endl;
}
