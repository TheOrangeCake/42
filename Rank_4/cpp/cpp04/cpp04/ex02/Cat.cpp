/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:48:19 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/21 18:46:33 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat() : AAnimal() {
	std::cout << "A Cat was born" << std::endl;
	this->type = "Cat";
	this->_brain = new Brain();
}

Cat::Cat(const Cat& copy) : AAnimal() {
	std::cout << "Cat cloned" << std::endl;
	this->_brain = new Brain();
	*this = copy;
}

Cat& Cat::operator=(const Cat& assign) {
	if (this != &assign)
	{
		std::cout << "Cat reassigned" << std::endl;
		this->type = assign.type;
		*(this->_brain) = *(assign._brain);
	}
	return (*this);
}

Cat::~Cat() {
	std::cout << "Cat petted and went to sleep" << std::endl;
	delete this->_brain;
}

void Cat::makeSound() const {
	std::cout << "Miao Miao" << std::endl;
}

void Cat::setIdea(int number, std::string idea) {
	this->_brain->setIdea(number, idea);
}

std::string Cat::getIdea(int number) const {
	return (this->_brain->getIdea(number));
}
