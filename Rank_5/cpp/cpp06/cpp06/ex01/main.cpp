/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 22:22:42 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/23 21:14:07 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"
#include "data.hpp"
#include <string>
#include <iostream>

int main(void)
{
	uintptr_t item;
	Data *olddata = new Data;
	Data *newdata;

	olddata->i = 42;
	olddata->str = "Lausanne";

	item = Serializer::serialize(olddata);
	newdata = Serializer::deserialize(item);

	std::cout << "old data address: " << &olddata << std::endl;
	std::cout << "old data contains: " << olddata << std::endl;
	std::cout << "old i: " << olddata->i << std::endl;
	std::cout << "old str: " << olddata->str << std::endl;
	std::cout << "----" << std::endl;
	std::cout << "new data address: " << &newdata << std::endl;
	std::cout << "new data contains: " << newdata << std::endl;
	std::cout << "new i: " << newdata->i << std::endl;
	std::cout << "new str: " << newdata->str << std::endl;

	delete olddata;
	return (0);
}