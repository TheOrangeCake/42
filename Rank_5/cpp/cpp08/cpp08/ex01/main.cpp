/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 23:00:55 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/28 19:12:04 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>

int main(void) {
	srand(time(NULL));
	{
		std::cout << "--- Add more than N test ---" << std::endl;
		Span sp = Span(2);
		try {
			sp.addNumber(1);
			sp.addNumber(12);
			sp.addNumber(123);
		} catch (std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
		// sp.print_vector();
	}
	std::cout << std::endl;
	{
		std::cout << "--- ShortestSpan and longestSpan tests ---" << std::endl;
		Span sp = Span(5);
		sp.addNumber(6);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);
		
		std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
		std::cout << "Longest span: " << sp.longestSpan() << std::endl;
		sp.print_vector();
	}
	std::cout << std::endl;
	{
		std::cout << "--- Not enough number exception tests ---" << std::endl;
		Span sp = Span(1);
		sp.addNumber(6);
		try {
			sp.shortestSpan();
		} catch (std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
		try {
			sp.longestSpan();
		} catch (std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
	}
	std::cout << std::endl;
	{
		std::cout << "--- Empty object exception tests ---" << std::endl;
		Span sp = Span();
		try {
			sp.shortestSpan();
		} catch (std::exception& e) {
				std::cerr << e.what() << std::endl;
		}
		try {
			sp.longestSpan();
		} catch (std::exception& e) {
				std::cerr << e.what() << std::endl;
		}
	}
	std::cout << std::endl;
	{
		std::cout << "--- Huge numbers test ---" << std::endl;

		int number = 20000;
		
		std::vector<int> extra;
		extra.reserve(number);
		for (int i = 0; i < number; i++) {
			extra.push_back(rand());
		}
		Span sp = Span(number);
		try {
			sp.addNumbers(extra.begin(), extra.end());
		} catch (std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
		std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
		std::cout << "Longest span: " << sp.longestSpan() << std::endl;	
	}
	return (0);
}