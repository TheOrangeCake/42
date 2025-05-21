/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:22:36 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/21 14:32:54 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog() : Animal() {
	std::cout << "A Dog was born" << std::endl;
	type = "Dog";
}

Dog::Dog(const Dog& copy) : Animal(){
	std::cout << "Dog cloned" << std::endl;
	*this = copy;
}

Dog& Dog::operator=(const Dog& assign) {
	std::cout << "Dog reassigned" << std::endl;
	this->type = assign.type;
	return (*this);
}

Dog::~Dog() {
	std::cout << "Dog petted and went to sleep" << std::endl;
}

void Dog::makeSound() const {
	std::cout << "Woof Woof" << std::endl;
}