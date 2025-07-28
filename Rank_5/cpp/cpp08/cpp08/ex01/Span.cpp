/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 23:01:40 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/28 19:12:55 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

Span::Span() : limit(0) {
	try {
		this->stock.reserve(0);
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}

Span::Span(unsigned int N) : limit(N) {
	try {
		this->stock.reserve(N);
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}

Span::Span(const Span& copy) {
	*this = copy;
}

Span& Span::operator =(const Span& assign) {
	if (this != &assign) {
		this->stock = assign.stock;
		this->limit = assign.limit;
	}
	return (*this);
}
Span::~Span() {
}

void Span::addNumber(int number) {
	if (this->stock.size() < this->limit) {
		this->stock.push_back(number);
	} else {
		throw std::length_error("Not enough space!");
	}
}

int Span::shortestSpan() {
	if (this->limit <= 1 || this->stock.empty()) {
		throw std::length_error("Not enough number to find shortest span!");
	}
	std::vector<int> temp = this->stock;
	std::sort(temp.begin(), temp.end());
	int shortest = *(temp.begin() + 1) - *(temp.begin());
	int tmp;
	for (std::vector<int>::iterator it = temp.begin() + 1; it < temp.end() - 1; it++) {
		tmp = *(it + 1) - *it;
		if (tmp < shortest) {
			shortest = tmp;
		}
	}
	return (shortest);
}

int Span::longestSpan() {
	if (this->limit <= 1 || this->stock.empty()) {
		throw std::length_error("Not enough number to find longest span!");
	}
	int max = *std::max_element(this->stock.begin(), this->stock.end());
	int min = *std::min_element(this->stock.begin(), this->stock.end());
	return (max - min);
}

void Span::addNumbers(std::vector<int>::iterator listBegin, std::vector<int>::iterator listEnd) {
	if (this->stock.size() + std::distance(listBegin, listEnd) > limit) {
		throw std::length_error("Not enough space!");
	}
	this->stock.insert(this->stock.end(), listBegin, listEnd);
}

void Span::print_vector() {
	std::cout << "List of number:" << std::endl;
	for (std::vector<int>::iterator it = this->stock.begin(); it != this->stock.end(); it++) {
		std::cout << *it << std::endl;
	}
}