/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:48:41 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/07 20:29:39 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP
#include <iostream>
#include <string>

class Zombie {
	private:
		std::string name;

	public:
		Zombie();
		Zombie(std::string name);
		~Zombie();
		
		void announce(void);
};

Zombie *newZombie(std::string name);
void randomChump(std::string name);
	
#endif