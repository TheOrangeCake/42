/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:22:36 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/21 17:11:17 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog() : Animal() {
	std::cout << "A Dog was born" << std::endl;
	type = "Dog";
	this->_brain = new Brain();
}

Dog::Dog(const Dog& copy) : Animal(){
	std::cout << "Dog cloned" << std::endl;
	this->_brain = new Brain();
	*this = copy;
}

Dog& Dog::operator=(const Dog& assign) {
	if (this != &assign)
	{
		std::cout << "Dog reassigned" << std::endl;
		this->type = assign.type;
		*(this->_brain) = *(assign._brain);
	}
	return (*this);
}

Dog::~Dog() {
	std::cout << "Dog petted and went to sleep" << std::endl;
	delete this->_brain;
}

void Dog::makeSound() const {
	std::cout << "Woof Woof" << std::endl;
}

void Dog::setIdea(int number, std::string idea) {
	this->_brain->setIdea(number, idea);
}

std::string Dog::getIdea(int number) const {
	return (this->_brain->getIdea(number));
}
