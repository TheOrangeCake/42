/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:58:30 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/21 15:59:22 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal() : type("Mammals") {
	std::cout << "An Animal was born" << std::endl;
}

Animal::Animal(const Animal& copy) {
	std::cout << "Animal cloned" << std::endl;
	*this = copy;
}

Animal& Animal::operator=(const Animal& assign) {
	if (this != &assign)
	{
		std::cout << "Animal reassigned" << std::endl;
		this->type = assign.type;
	}
	return (*this);
}

Animal::~Animal() {
	std::cout << "An Animal was blasted to oblivion" << std::endl;
}

void Animal::makeSound() const {
	std::cout << "I speak universal language" << std::endl;
}

std::string Animal::getType() const {
	return (this->type);
}