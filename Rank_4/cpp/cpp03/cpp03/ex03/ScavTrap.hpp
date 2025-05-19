/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 23:27:16 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/19 12:55:02 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP
#include "ClapTrap.hpp"

class ScavTrap : virtual public ClapTrap {
	public:
		ScavTrap();
		ScavTrap(std::string name);
		ScavTrap(const ScavTrap& copy);
		ScavTrap& operator=(const ScavTrap& assign);
		~ScavTrap();

		void	attack(const std::string& target);
		void	guardGate();
		void	printClapTrap() const;

	static const int scav_hp = 100;
	static const int scav_mp = 50;
	static const int scav_atk = 20;
};

#endif