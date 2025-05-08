/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:45:42 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/08 16:56:38 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_HPP
#define WEAPON_HPP
#include <string>

class Weapon {
	private:
		std::string type;

	public:
		Weapon();
		Weapon(std::string type);
		~Weapon();

		const std::string &getType();
		void setType(std::string type);
};

#endif