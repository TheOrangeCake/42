/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:01:48 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/16 23:44:23 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <iostream>
#include <string>

class ClapTrap {
	protected:
		std::string _name;
		int			_hp;
		int			_mp;
		int			_atk;

	public:
		ClapTrap();
		ClapTrap(std::string name);
		ClapTrap(const ClapTrap& copy);
		ClapTrap& operator=(const ClapTrap& assign);
		~ClapTrap();

		void	attack(const std::string& target);
		void	takeDamage(unsigned int amount);
		void	beRepaired(unsigned int amount);
		void	printClapTrap() const;

		// std::string getName() const;
		// int			getHp() const;
		// int			getMp() const;
		// int			getAtk() const;

		// void	setName(std::string name);
		// void	setHp(int amount);
		// void	setMp(int amount);
		// void	setAtk(int amount);
};

#endif