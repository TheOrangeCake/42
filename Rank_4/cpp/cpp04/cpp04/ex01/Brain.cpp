/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:32:35 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/21 17:09:10 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

Brain::Brain() {
	std::cout << "A new Brain was formed" << std::endl;
}

Brain::Brain(const Brain& copy) {
	std::cout << "Brain copied" << std::endl;
	*this = copy;
}

Brain& Brain::operator=(const Brain& assign) {
	if (this != &assign)
	{
		std::cout << "Brain reassigned" << std::endl;
		for (int i = 0; i < 100; i++) {
			this-> _ideas[i] = assign._ideas[i];
		}
	}
	return (*this);
}

Brain::~Brain() {
	std::cout << "Brain exploded!" << std::endl;
}

void Brain::setIdea(int number, std::string idea) {
	if (number >= 0 && number <= 99)
		this->_ideas[number] = idea;
	else
		std::cout << "Out of Brain range" << std::endl;
}

std::string Brain::getIdea(int number) const {
	if (number >= 0 && number <= 99)
		return (this->_ideas[number]);
	else
	{
		std::cout << "Out of Brain range" << std::endl;
		return ("Invalid number");
	}
}