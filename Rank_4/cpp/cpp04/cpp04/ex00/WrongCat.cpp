/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:00:47 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/21 15:04:24 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "WrongCat.hpp"

WrongCat::WrongCat() : WrongAnimal() {
	std::cout << "A WrongCat was born" << std::endl;
	this->type = "WrongCat";
}

WrongCat::WrongCat(const WrongCat& copy) : WrongAnimal() {
	std::cout << "WrongCat cloned" << std::endl;
	*this = copy;
}

WrongCat& WrongCat::operator=(const WrongCat& assign) {
	std::cout << "WrongCat reassigned" << std::endl;
	this->type = assign.type;
	return (*this);
}

WrongCat::~WrongCat() {
	std::cout << "WrongCat petted and went to sleep" << std::endl;
}

void WrongCat::makeSound() const {
	std::cout << "WrongMiao WrongMiao" << std::endl;
}