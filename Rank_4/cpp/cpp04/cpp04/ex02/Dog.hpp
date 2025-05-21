/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:17:28 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/21 18:36:49 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
#define DOG_HPP
#include "AAnimal.hpp"
#include "Brain.hpp"

class Dog : public AAnimal {
	private:
		Brain* _brain;

	public:
		Dog();
		Dog(const Dog& copy);
		Dog& operator=(const Dog& assign);
		virtual ~Dog();

		virtual void	makeSound() const;
		void			setIdea(int number, std::string idea);
		std::string 	getIdea(int number) const;
};

#endif