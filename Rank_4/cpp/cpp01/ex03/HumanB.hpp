/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:54:12 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/08 18:17:50 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANB_HPP
#define HUMANB_HPP
#include <string>
#include <iostream>
#include "Weapon.hpp"

class HumanB {
	private:
		std::string name;
		Weapon *weapon;

	public:
		HumanB();
		HumanB(std::string name);
		HumanB(std::string name, Weapon &weapon);
		~HumanB();

		void attack();
		void setWeapon(Weapon &weapon);
};

#endif