/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 23:53:01 by hoannguy          #+#    #+#             */
/*   Updated: 2025/09/13 23:53:01 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {
	this->v_time = 0;
	this->d_time = 0;
	this->num_comp = 0;
}
PmergeMe::PmergeMe(const PmergeMe& copy) {
	*this = copy;
}
PmergeMe& PmergeMe::operator =(const PmergeMe& assign) {
	if (this != &assign) {
		this->v_list = assign.v_list;
		this->v_time = assign.v_time;
		this->d_list = assign.d_list;
		this->d_time = assign.d_time;
		this->input = assign.input;
		this->output = assign.output;
		this->num_comp = assign.num_comp;
		this->pairs = assign.pairs;
		this->odd = assign.odd;
	}
	return *this;
}
PmergeMe::~PmergeMe() {

}

int PmergeMe::populate(const std::string& input) {
	long				n;
	std::stringstream	s(input);
	std::stringstream	ss;

	while (!s.eof()) {
		s >> n;
		if (s.fail() || n > 2147483647 || n < -2147483648) {
			std::cerr << "Error: bad input format!" << std::endl;
			return -1;
		}
		if (std::find(v_list.begin(), v_list.end(), n) != v_list.end()) {
			std::cerr << "Error: duplicate number " << n << std::endl;
			return -1;
		}
		this->v_list.push_back(n);
		this->d_list.push_back(n);
	}
	for (std::vector<int>::iterator it = this->v_list.begin(); it != this->v_list.end(); ++it) {
		ss << *it << " ";
	}
	this->input = ss.str();
	this->input.erase(this->input.size() - 1);
	return 0;
}

void PmergeMe::vFordJohnson(size_t n) {
	size_t	left;
	size_t	right;

	if (n >= v_list.size()) {
		return;
	}
	for (size_t i = 0; i + n <= v_list.size(); i += n) {
		left = i + n/2 - 1;
		right = i + n - 1;
		if (v_list[left] > v_list[right]) {
			for (size_t j = 0; j < n/2; j++) {
				std::swap(v_list[i + j], v_list[i + n/2 + j]);
			}
		}
		num_comp++;
	}
	vFordJohnson(n * 2);

	// size_t	a;
	// a = 0;
	// for (size_t i = 1; i < v_list.size(); i += 2) {
	// 	std::swap(v_list[a], v_list[i]);
	// 	++a;
	// }
}

	// for (std::vector<int>::iterator it = this->v_list.begin(); it != this->v_list.end(); ++it) {
	// 	std::cout << *it << " ";
	// }
	// std::cout << std::endl;

void PmergeMe::vSort() {
	clock_t				start;
	clock_t				end;
	std::stringstream	s;

	start = clock();
	vFordJohnson(2);
	end = clock();
	this->v_time = 1000000.0 * (end - start) / CLOCKS_PER_SEC;
	for (std::vector<int>::iterator it = this->v_list.begin(); it != this->v_list.end(); ++it) {
		s << *it << " ";
	}
	this->output = s.str();
	this->output.erase(this->output.size() - 1);
}

void PmergeMe::dFordJohnson() {

}

void PmergeMe::dSort() {
	clock_t				start;
	clock_t				end;
	std::stringstream	s;

	start = clock();
	dFordJohnson();
	end = clock();
	this->d_time = 1000000.0 * (end - start) / CLOCKS_PER_SEC;
	for (std::vector<int>::iterator it = this->v_list.begin(); it != this->v_list.end(); ++it) {
		s << *it << " ";
	}
	this->output = s.str();
	this->output.erase(this->output.size() - 1);
}

void PmergeMe::printResult() const {
	std::cout << "Before:\t" << this->input << std::endl;
	std::cout << "After:\t" << this->output << std::endl;
	std::cout << "Time to process a range of " << this->v_list.size() << " elements with std::vector : " << this->v_time << " us"<< std::endl;
	std::cout << "Time to process a range of " << this->d_list.size() << " elements with std::deque  : " << this->d_time << " us"<< std::endl;
}

int PmergeMe::getNumComp() const {
	return this->num_comp;
}

unsigned int jacobsthal(int k) {
	return static_cast<unsigned int>((std::pow(2, k + 1) + (k % 2 == 0 ? 1 : -1)) / 3);
}

unsigned int num_of_comp(const int elements) {
	int		sum;
	double	value;

	sum = 0;
	for (int k = 1; k <= elements; ++k) {
		value = (3.0 / 4.0) * k;
		sum += static_cast<unsigned int>(ceil(log2(value)));
	}
	return sum;
}
