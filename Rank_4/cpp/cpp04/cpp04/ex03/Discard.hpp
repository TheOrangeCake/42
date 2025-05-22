/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Discard.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:49:02 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/22 18:27:07 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISCARD_HPP
#define DISCARD_HPP
#include "AMateria.hpp"
#include "Character.hpp"

class Discard {
	private:
		static AMateria **_pile;
		static int		_size;

		Discard();
		Discard(const Discard& copy);
		Discard& operator=(const Discard& assign);
		~Discard();

	public:
		static void storeMateria(AMateria* m);
		static void printMateria();
		static void deletePile();
};

#endif