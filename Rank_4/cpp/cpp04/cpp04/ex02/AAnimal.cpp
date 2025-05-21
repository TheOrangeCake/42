/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAnimal.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:58:30 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/21 18:57:29 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AAnimal.hpp"

AAnimal::AAnimal() : type("Mammals") {
	std::cout << "An AAnimal was born" << std::endl;
}

AAnimal::AAnimal(const AAnimal& copy) {
	std::cout << "AAnimal cloned" << std::endl;
	*this = copy;
}

AAnimal& AAnimal::operator=(const AAnimal& assign) {
	if (this != &assign)
	{
		std::cout << "AAnimal reassigned" << std::endl;
		this->type = assign.type;
	}
	return (*this);
}

AAnimal::~AAnimal() {
	std::cout << "An AAnimal was blasted to oblivion" << std::endl;
}

std::string AAnimal::getType() const {
	return (this->type);
}