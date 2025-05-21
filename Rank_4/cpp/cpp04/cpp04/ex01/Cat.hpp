/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:37:43 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/21 17:05:25 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
#define CAT_HPP
#include "Animal.hpp"
#include "Brain.hpp"

class Cat : public Animal {
	private:
		Brain* _brain;

	public:
		Cat();
		Cat(const Cat& copy);
		Cat& operator=(const Cat& assign);
		virtual ~Cat();

		virtual void	makeSound() const;
		void			setIdea(int number, std::string idea);
		std::string 	getIdea(int number) const;
};

#endif