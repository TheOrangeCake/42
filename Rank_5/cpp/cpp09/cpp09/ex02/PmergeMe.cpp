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
	this->v_num_comp = 0;
	this->d_num_comp = 0;
	this->v_max = -1;
	this->d_max = -1;
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
		this->v_output = assign.v_output;
		this->d_output = assign.d_output;
		this->v_num_comp = assign.v_num_comp;
		this->d_num_comp = assign.d_num_comp;
		this->v_max = assign.v_max;
		this->d_max = assign.d_max;
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
		v_list.push_back(n);
		d_list.push_back(n);
	}
	for (std::vector<int>::iterator it = v_list.begin(); it != v_list.end(); ++it) {
		ss << *it << " ";
	}
	this->input = ss.str();
	this->input.erase(this->input.size() - 1);
	return 0;
}

void PmergeMe::savePair(int mode) {
	struct pair	pair;

	pairs.clear();
	if (mode == VECTOR) {
		for (size_t i = 0; i < v_list.size() - 1; i += 2) {
			pair.a = v_list[i];
			pair.b = v_list[i + 1];
			pairs.push_back(pair);
		}
		if (v_list.size() % 2 != 0)
			odd = v_list[v_list.size() - 1];
	}
	if (mode == DEQUE) {
		for (size_t i = 0; i < d_list.size() - 1; i += 2) {
			pair.a = d_list[i];
			pair.b = d_list[i + 1];
			pairs.push_back(pair);
		}
		if (d_list.size() % 2 != 0)
			odd = d_list[d_list.size() - 1];
	}
}

void PmergeMe::mainChain(int mode) {
	size_t	b;

	b = 0;
	if (mode == VECTOR) {
		for (size_t i = 1; i < v_list.size(); i += 2) {
			std::swap(v_list[b], v_list[i]);
			b++;
		}
	}
	if (mode == DEQUE) {
		for (size_t i = 1; i < d_list.size(); i += 2) {
			std::swap(d_list[b], d_list[i]);
			b++;
		}
	}
}

unsigned int binary_search(int start, int end, int target, int num_comp) {
	
}

void PmergeMe::binaryInsert(int mode) {

	if (mode == VECTOR) {

	} if (mode == DEQUE) {
		
	}
}

void PmergeMe::vFordJohnson(size_t n) {
	size_t	left;
	size_t	right;

	if (n >= v_list.size()) {
		v_max = n / 2;
		this->savePair(VECTOR);
		this->mainChain(VECTOR);
		// for (std::vector<int>::iterator it = this->v_list.begin(); it != this->v_list.end(); ++it) {
		// 	std::cout << *it << " ";
		// }
		// std::cout << std::endl;
		this->binaryInsert(VECTOR);
		// for (std::vector<int>::iterator it = this->v_list.begin(); it != this->v_list.end(); ++it) {
		// 	std::cout << *it << " ";
		// }
		// std::cout << std::endl;
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
		v_num_comp++;
	}
	vFordJohnson(n * 2);
}

void PmergeMe::vSort() {
	clock_t				start;
	clock_t				end;
	std::stringstream	s;

	start = clock();
	if (v_list.size() > 1)
		vFordJohnson(2);
	end = clock();
	v_time = 1000000.0 * (end - start) / CLOCKS_PER_SEC;
	for (std::vector<int>::iterator it = v_list.begin(); it != v_list.end(); ++it) {
		s << *it << " ";
	}
	v_output = s.str();
	v_output.erase(v_output.size() - 1);
}

void PmergeMe::dFordJohnson(size_t n) {
	size_t	left;
	size_t	right;

	if (n >= d_list.size()) {
		d_max = n / 2;
		this->savePair(DEQUE);
		this->mainChain(DEQUE);
		return;
	}
	for (size_t i = 0; i + n <= d_list.size(); i += n) {
		left = i + n / 2 - 1;
		right = i + n - 1;
		if (d_list[left] > d_list[right]) {
			for (size_t j = 0; j < n / 2; j++) {
				std::swap(d_list[i + j], d_list[i + n / 2 + j]);
			}
		}
		d_num_comp++;
	}
	dFordJohnson(n * 2);
}

void PmergeMe::dSort() {
	clock_t				start;
	clock_t				end;
	std::stringstream	s;

	start = clock();
	if (d_list.size() > 1)
		dFordJohnson(2);
	end = clock();
	d_time = 1000000.0 * (end - start) / CLOCKS_PER_SEC;
	for (std::deque<int>::iterator it = d_list.begin(); it != d_list.end(); ++it) {
		s << *it << " ";
	}
	d_output = s.str();
	d_output.erase(d_output.size() - 1);
}

void PmergeMe::printResult() const {
	std::cout << "Before:\t" << input << std::endl;
	std::cout << "vAfter:\t" << v_output << std::endl;
	std::cout << "dAfter:\t" << d_output << std::endl;
	std::cout << "Time to process a range of " << v_list.size() << " elements with std::vector : " << v_time << " us"<< std::endl;
	std::cout << "Time to process a range of " << d_list.size() << " elements with std::deque  : " << d_time << " us"<< std::endl;
}

int PmergeMe::getVNumComp() const {
	return this->v_num_comp;
}

int PmergeMe::getDNumComp() const {
	return this->d_num_comp;
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
