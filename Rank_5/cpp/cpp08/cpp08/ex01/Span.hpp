/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 23:01:06 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/28 19:10:20 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
#define SPAN_HPP
#include <vector>
#include <exception>
#include <iostream>
#include <algorithm>

class Span {
	private:
		std::vector<int> stock;
		unsigned int limit;

	public:
		Span();
		Span(unsigned int N);
		Span(const Span& copy);
		Span& operator =(const Span& assign);
		~Span();
		
		void addNumber(int number);
		int shortestSpan();
		int longestSpan();
		
		void addNumbers(std::vector<int>::iterator listBegin, std::vector<int>::iterator listEnd);

		void print_vector();
};

#endif