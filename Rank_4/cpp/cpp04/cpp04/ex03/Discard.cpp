/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Discard.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:50:59 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/22 19:11:35 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Discard.hpp"

AMateria** Discard::_pile = NULL;
int	Discard::_size = 0;

void Discard::storeMateria(AMateria* m) {
	if (_pile == NULL)
	{
		_size += 1;
		_pile = new AMateria*[_size];
		_pile[0] = m;
	}
	else
	{
		AMateria **temp = new AMateria*[_size + 1];
		for (int i = 0; i < _size; i++)
			temp[i] = _pile[i];
		temp[_size] = m;
		delete[] _pile;
		_pile = temp;
		_size += 1;
	}
}

void Discard::printMateria() {
	if (_pile == NULL)
		std::cout << "Discard pile is empty" << std::endl;
	else
	{
		for (int i = 0; i < _size; i++) {
			if (_pile[i] != NULL)
				std::cout << "Index: " << i << " | Materia: " << _pile[i]->getType() << std::endl;
			else
				std::cout << "Index: " << i << " | Materia: Empty" << std::endl;
		}
	}
}

void Discard::deletePile() {
	if (_pile != NULL)
	{
		for (int i = 0; i < _size; i++)
			delete _pile[i];
		delete[] _pile;
		_pile = NULL;
		_size = 0;
	}
}