/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 00:33:03 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/19 12:56:32 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP
#include "ScavTrap.hpp"

class FragTrap : virtual public ClapTrap {
	public:
		FragTrap();
		FragTrap(std::string name);
		FragTrap(const FragTrap& copy);
		FragTrap& operator=(const FragTrap& assign);
		~FragTrap();

		void highFivesGuys(void);
		void printClapTrap() const;

	static const int frag_hp = 100;
	static const int frag_mp = 100;
	static const int frag_atk = 30;
};

#endif