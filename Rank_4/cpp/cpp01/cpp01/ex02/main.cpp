/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:34:59 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/08 15:40:39 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>

int main(void)
{
	std::string name = "HI THIS IS BRAIN";

	std::string *stringPTR = &name;
	std::string &stringREF = name;

	std::cout << "Print address" << std::endl;
	std::cout << &name << std::endl;
	std::cout << stringPTR << std::endl;
	std::cout << &stringREF << std::endl;

	std::cout << "Print value" << std::endl;
	std::cout << name << std::endl;
	std::cout << *stringPTR << std::endl;
	std::cout << stringREF << std::endl;
}