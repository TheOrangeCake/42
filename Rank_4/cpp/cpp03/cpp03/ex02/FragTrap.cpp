/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 00:32:44 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/17 00:55:24 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap::FragTrap() : ClapTrap() {
	std::cout << "FragTrap: Default constructor called" << std::endl;
	_hp = 100;
	_mp = 100;
	_atk = 30;
}

FragTrap::FragTrap(std::string name) : ClapTrap(name) {
	std::cout << "FragTrap: Name constructor called" << std::endl;
	_hp = 100;
	_mp = 100;
	_atk = 30;
}

FragTrap::FragTrap(const FragTrap& copy) : ClapTrap() {
	std::cout << "FragTrap: Copy constructor called" << std::endl;
	*this = copy;
}

FragTrap& FragTrap::operator=(const FragTrap& assign) {
	std::cout << "FragTrap: Assign operator overload called" << std::endl;
	this->_name = assign._name;
	this->_hp = assign._hp;
	this->_mp = assign._mp;
	this->_atk = assign._atk;
	return (*this);
}

FragTrap::~FragTrap() {
	std::cout << "FragTrap: Destructor called" << std::endl;
}

void FragTrap::printClapTrap() const {
	std::cout << "FragTrap " << this->_name << " has " << this->_hp << " hp, ";
	std::cout << this->_mp << " mp and " << this->_atk << " atk." << std::endl;
}

void FragTrap::highFivesGuys(void) {
	std::cout << this->_name << " says: Let's high five!" << std::endl;
}