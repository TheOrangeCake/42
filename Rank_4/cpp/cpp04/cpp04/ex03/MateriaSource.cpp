/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:44:48 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/22 19:41:18 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"

MateriaSource::MateriaSource() {
	for (int i = 0; i < 4; i++) {
		_source[i] = NULL;
	}
}

MateriaSource::MateriaSource(const MateriaSource& copy) {
	*this = copy;
}

MateriaSource& MateriaSource::operator=(const MateriaSource& assign) {
	if (this != &assign)
	{
		for (int i = 0; i < 4; i++) {
			if (this->_source[i] != NULL)
				delete this->_source[i];
			if (assign._source[i] != NULL)
				this->_source[i] = assign._source[i]->clone();
			else
				this->_source[i] = NULL;
		}
	}
	return (*this);
}

MateriaSource::~MateriaSource() {
	for (int i = 0; i < 4; i++)
		delete this->_source[i];
}

void MateriaSource::learnMateria(AMateria* m) {
	for (int i = 0; i < 4; i++) {
		if (this->_source[i] == NULL)
		{
			this->_source[i] = m;
			return ;
		}
	}
	std::cout << "Learn fail! All source slots are in use." << std::endl;
	delete m;
}

AMateria* MateriaSource::createMateria(std::string const & type) {
	for (int i = 0; i < 4; i++) {
		if (this->_source[i] != NULL)
		{
			if (this->_source[i]->getType() == type)
				return (this->_source[i]->clone());
		}
	}
	std::cout << "There is no such type in source" << std::endl;
	return (0);
}