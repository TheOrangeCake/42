/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 21:15:08 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/23 22:43:28 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

Base *generate(void) {
	int	type;

	type = std::rand() % 4;
	switch(type) {
		case 0:
			std::cout << "Object A was created" << std::endl;
			return (new A);
		case 1:
			std::cout << "Object B was created" << std::endl;
			return (new B);
		case 2:
			std::cout << "Object C was created" << std::endl;
			return (new C);
		default:
			std::cout << "No Object was created" << std::endl;
			return (NULL);
	}
}

void identify(Base* p) {
	A *a = dynamic_cast<A*>(p);
	if (a != NULL) {
		std::cout << "Pointer of type A" << std::endl;
		return ; 
	}
	B *b = dynamic_cast<B*>(p);
	if (b != NULL) {
		std::cout << "Pointer of type B" << std::endl;
		return ; 
	}
	C *c = dynamic_cast<C*>(p);
	if (c != NULL) {
		std::cout << "Pointer of type C" << std::endl;
		return ; 
	}
	std::cout << "Pointer to NULL" << std::endl;
}

void identify(Base& p) {
	try {
		dynamic_cast<A&>(p);
		std::cout << "Reference of type A" << std::endl;
		return ;
	} catch (std::exception& e) {
		try {
			dynamic_cast<B&>(p);
			std::cout << "Reference of type B" << std::endl;
			return ;
		} catch (std::exception& e) {
			try {
				dynamic_cast<C&>(p);
				std::cout << "Reference of type C" << std::endl;
				return ;
			} catch (std::exception& e) {
				std::cout << "Reference to NULL" << std::endl;
			}
		}
	}
}

int main()
{
	std::srand(std::time(NULL));
	sleep(rand() % 3);
	Base *base;

	base = generate();
	Base &ref = *base;

	identify(base);
	identify(ref);
	
	if (base != NULL)
		delete base;
}