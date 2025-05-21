/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:00:57 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/21 15:09:53 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal() : type("WrongMammals") {
	std::cout << "A WrongAnimal was born" << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal& copy) {
	std::cout << "WrongAnimal cloned" << std::endl;
	*this = copy;
}

WrongAnimal& WrongAnimal::operator=(const WrongAnimal& assign) {
	std::cout << "WrongAnimal reassigned" << std::endl;
	this->type = assign.type;
	return (*this);
}

WrongAnimal::~WrongAnimal() {
	std::cout << "A WrongAnimal was blasted to oblivion" << std::endl;
}

void WrongAnimal::makeSound() const {
	std::cout << "I speak fake language" << std::endl;
}

std::string WrongAnimal::getType() const {
	return (this->type);
}