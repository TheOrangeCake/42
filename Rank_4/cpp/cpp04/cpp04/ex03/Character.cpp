/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:04:25 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/22 19:43:18 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"

Character::Character() : _name("Default") {
	for (int i = 0; i < 4; i++)
		_inventory[i] = NULL;
}

Character::Character(std::string name) : _name(name) {
	for (int i = 0; i < 4; i++)
		_inventory[i] = NULL;
}

Character::Character(const Character& copy) {
	*this = copy;
}

Character& Character::operator=(const Character& assign) {
	if (this != &assign)
	{
		this->_name = assign._name;
		for (int i = 0; i < 4; i++) {
			if (this->_inventory[i] != NULL)
				delete this->_inventory[i];
			if (assign._inventory[i] != NULL)
				this->_inventory[i] = assign._inventory[i]->clone();
			else
				this->_inventory[i] = NULL;
		}
	}
	return (*this);
}

Character::~Character() {
	for (int i = 0; i < 4; i++)
		delete this->_inventory[i];
}

std::string const & Character::getName() const {
	return (this->_name);
}

void Character::equip(AMateria* m) {
	for (int i = 0; i < 4; i++) {
		if (this->_inventory[i] == NULL)
		{
			this->_inventory[i] = m;
			return ;
		}
	}
	std::cout << "Equip fail! All inventory slots are in use." << std::endl;
	delete m;
}

void Character::unequip(int idx) {
	if (idx < 0 || idx >= 4)
	{
		std::cout << "Invalid index" << std::endl;
		return ;
	}
	if (this->_inventory[idx] == NULL)
		std::cout << "Nothing to unequip!" << std::endl;
	else
	{
		Discard::storeMateria(this->_inventory[idx]);
		this->_inventory[idx] = NULL;
	}
}

void Character::use(int idx, ICharacter& target) {
	if (idx < 0 || idx >= 4)
	{
		std::cout << "Invalid index" << std::endl;
		return ;
	}
	if (this->_inventory[idx] == NULL)
		std::cout << "Attack fail! inventory slot is empty." << std::endl;
	else
		this->_inventory[idx]->use(target);
}