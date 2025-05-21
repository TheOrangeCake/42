/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:57:16 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/21 15:10:17 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int	main(void)
{
	const Animal* meta = new Animal();
	const Animal* j = new Dog();
	const Animal* i = new Cat();

	std::cout << meta->getType() << " " << std::endl;
	std::cout << j->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;
	meta->makeSound();
	i->makeSound();
	j->makeSound();
	
	delete meta;
	delete j;
	delete i;

	std::cout << std::endl;
	
	const WrongAnimal* fake_animal = new WrongAnimal();
	const WrongAnimal* fake_cat = new WrongCat();

	std::cout << fake_animal->getType() << std::endl;
	std::cout << fake_cat->getType() << std::endl;
	fake_animal->makeSound();
	fake_cat->makeSound();

	delete fake_animal;
	delete fake_cat;
	return (0);
}