/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:05:38 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/22 18:02:11 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"

AMateria::AMateria() {
}

AMateria::AMateria(std::string const & type) : type(type) {
}

AMateria::AMateria(const AMateria& copy) {
	this->type = copy.type;
}

AMateria& AMateria::operator=(const AMateria& assign) {
	if (this != &assign)
		this->type = assign.type;
	return (*this);
}

AMateria::~AMateria() {
}

std::string const & AMateria::getType() const {
	return (this->type);
}

void AMateria::use(ICharacter& target) {
	std::cout << "Why isn't this abtracted?" << std::endl;
	(void)target;
}