/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:44:43 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/08 18:21:04 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon() {
	type = "sword";
}

Weapon::Weapon(std::string type) {
	this->type = type;
}

Weapon::~Weapon() {
	
}

const std::string &Weapon::getType() {
	std::string &temp = type;
	return (temp);
}

void Weapon::setType(std::string type) {
	this->type = type;
}