/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:48:19 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/21 14:56:43 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat() : Animal() {
	std::cout << "A Cat was born" << std::endl;
	this->type = "Cat";
}

Cat::Cat(const Cat& copy) : Animal() {
	std::cout << "Cat cloned" << std::endl;
	*this = copy;
}

Cat& Cat::operator=(const Cat& assign) {
	std::cout << "Cat reassigned" << std::endl;
	this->type = assign.type;
	return (*this);
}

Cat::~Cat() {
	std::cout << "Cat petted and went to sleep" << std::endl;
}

void Cat::makeSound() const {
	std::cout << "Miao Miao" << std::endl;
}