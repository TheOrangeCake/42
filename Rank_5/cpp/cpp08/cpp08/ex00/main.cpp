/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:21:57 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/27 22:59:40 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"
#include <string>
#include <vector>
#include <deque>
#include <list>

int main(void) {
	{
		std::cout << "--- Test vector ---" << std::endl;
		std::vector<int> numbers;
		numbers.reserve(5);
		numbers.push_back(1);
		numbers.push_back(5);
		numbers.push_back(9);
		numbers.push_back(7);
		numbers.push_back(5);
		std::cout << "Vector: ";
		for (std::vector<int>::iterator it = numbers.begin(); it != numbers.end(); it++) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		
		int number = 5;
		try {
			std::vector<int>::iterator it = easyfind(numbers, number);
			std::cout <<"Search: " << number << ". Position: " << it - numbers.begin() << std::endl;
		} catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
		
		number = 19;
		try {
			std::vector<int>::iterator it = easyfind(numbers, number);
			std::cout << "Search: " << number << ". Position: " << it - numbers.begin() << std::endl;
		} catch (std::exception& e) {
			std::cout << "Search: " << number << ". " << e.what() << std::endl;
		}
		
		std::cout << std::endl;
	}
	{
		std::cout << "--- Test deque ---" << std::endl;
		std::deque<int> numbers;
		numbers.push_back(1);
		numbers.push_back(3);
		numbers.push_front(9);
		numbers.push_back(7);
		numbers.push_front(5);
		std::cout << "Deque: ";
		for (std::deque<int>::iterator it = numbers.begin(); it != numbers.end(); it++) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		
		int number = 5;
		try {
			std::deque<int>::iterator it = easyfind(numbers, number);
			std::cout <<"Search: " << number << ". Position: " << it - numbers.begin() << std::endl;
		} catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
		
		number = 10;
		try {
			std::deque<int>::iterator it = easyfind(numbers, number);
			std::cout << "Search: " << number << ". Position: " << it - numbers.begin() << std::endl;
		} catch (std::exception& e) {
			std::cout << "Search: " << number << ". " << e.what() << std::endl;
		}
		
		std::cout << std::endl;
	}
	{
		std::cout << "--- Test list ---" << std::endl;
		std::list<int> numbers;
		numbers.push_back(12);
		numbers.push_back(47);
		numbers.push_front(9);
		numbers.push_back(70);
		numbers.push_front(85);
		std::cout << "List: ";
		for (std::list<int>::iterator it = numbers.begin(); it != numbers.end(); it++) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		
		int number = 70;
		try {
			easyfind(numbers, number);
			std::cout <<"Search: " << number << ". Found!" << std::endl;
		} catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
		
		number = 10;
		try {
			easyfind(numbers, number);
			std::cout << "Search: " << number << ". Found!" << std::endl;
		} catch (std::exception& e) {
			std::cout << "Search: " << number << ". " << e.what() << std::endl;
		}
		
		std::cout << std::endl;
	}
	return (0);
}