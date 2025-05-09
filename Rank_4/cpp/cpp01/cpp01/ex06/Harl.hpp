/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:35:17 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/09 14:56:47 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HARL_HPP
#define HARL_HPP
#include <string>
#include <iostream>

class Harl {
	private:
		void _debug(void) const;
		void _info(void) const;
		void _warning(void) const;
		void _error(void) const;

	public:
		Harl();
		~Harl();
		void complain(std::string level) const;
};

#endif