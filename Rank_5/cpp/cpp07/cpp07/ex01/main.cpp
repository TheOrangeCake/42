/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 11:38:26 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/25 15:29:51 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iter.hpp"
#include <iostream>
#include <string>

template <typename T>
void test_function1(T a) {
	
}

void test_function(int i) {
	std::cout << i << std::endl;
}

int main(void) {
	{
		int arr[5] = {1, 3, 5, 7 ,9};
		size_t size = 5;
		// int size = 5;
		// float size = 5.9f;
		// std::string size = "5";
		
		iter(arr, size, test_function);
	}
}