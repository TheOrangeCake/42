/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:02:24 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/15 16:29:10 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap() : _name("Minion"), _hp(10), _mp(10), _atk(0) {
	std::cout << "Default constructor called" << std::endl;
}

ClapTrap::ClapTrap(std::string name) {
	std::cout << "Name constructor called" << std::endl;
	this->_name = name;
}

ClapTrap::ClapTrap(const ClapTrap& copy) {
	std::cout << "Copy constructor called" << std::endl;
	*this = copy;
}

ClapTrap& ClapTrap::operator=(const ClapTrap& assign) {
	std::cout << "Assign operator overload called" << std::endl;
	this->_name = assign._name;
	this->_hp = assign._hp;
	this->_mp = assign._mp;
	this->_atk = assign._atk;
	return (*this);
}

ClapTrap::~ClapTrap() {
	std::cout << "Destructor called" << std::endl;
}

void ClapTrap::printClapTrap() const {
	std::cout << "ClapTrap " << this->_name << " has " << this->_hp << " hp, ";
	std::cout << this->_mp << " mp and " << this->_atk << " atk." << std::endl;
}
