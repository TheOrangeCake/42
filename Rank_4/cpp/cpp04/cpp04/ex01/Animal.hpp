/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:57:50 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/21 16:19:25 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
#define ANIMAL_HPP
#include <string>
#include <iostream>

class Animal {
	protected:
		std::string type;
	
	public:
		Animal();
		Animal(const Animal& copy);
		Animal& operator=(const Animal& assign);
		virtual ~Animal();
		
		virtual void makeSound() const;
		std::string getType() const;
};

#endif