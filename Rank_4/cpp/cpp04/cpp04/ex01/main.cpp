/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:57:16 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/22 13:46:32 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include "Brain.hpp"

int	main(void)
{
	// const Animal Elephant;
	const Animal* j = new Dog();
	const Animal* i = new Cat();

	delete j;
	delete i;

	std::cout << std::endl;

	Animal	*zoo[10];
	for (int i = 0; i < 5; i++) {
		zoo[i] = new Dog();
	}
	for (int i = 5; i < 10; i++) {
		zoo[i] = new Cat();
	}
	for (int i = 0; i < 10; i++) {
		delete zoo[i];
	}

	std::cout << std::endl;

	Cat *original = new Cat();
	Cat *copy = new Cat();

	original->setIdea(0, "I am the original");
	copy->setIdea(0, "I am the copied");
	std::cout << "Original: " <<original->getIdea(0) << std::endl;
	std::cout << "Copy: " <<copy->getIdea(0) << std::endl;
	*copy = *original;
	std::cout << "Original: " <<original->getIdea(0) << std::endl;
	std::cout << "Copy: " <<copy->getIdea(0) << std::endl;
	delete original;
	delete copy;
	
	return (0);
}