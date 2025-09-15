/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 17:15:44 by hoannguy          #+#    #+#             */
/*   Updated: 2025/09/13 17:15:44 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP
#include <iostream>
#include <stack>
#include <sstream>

class RPN {
	private:
		std::stack<long>	list;
		
		int	operation(const std::string& item);
		int	first_second(std::string& input);

	public:
		RPN();
		RPN(const RPN& copy);
		RPN& operator =(const RPN& assign);
		~RPN();

		int	doTheMagic(std::string& input);
};

bool	isOperator(const std::string& input);
long	str_to_int(std::string& input);

#endif