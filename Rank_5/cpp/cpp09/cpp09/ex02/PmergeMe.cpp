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
	this->v_main_chain = 0;
	this->d_main_chain = 0;
	this->v_odd = -1;
	this->d_odd = -1;
}
PmergeMe::PmergeMe(const PmergeMe& copy) {
	*this = copy;
}
PmergeMe& PmergeMe::operator =(const PmergeMe& assign) {
	if (this != &assign) {
		this->v_list = assign.v_list;
		this->d_list = assign.d_list;
		this->v_time = assign.v_time;
		this->d_time = assign.d_time;
		this->input = assign.input;
		this->v_output = assign.v_output;
		this->d_output = assign.d_output;
		this->v_num_comp = assign.v_num_comp;
		this->d_num_comp = assign.d_num_comp;
		this->v_main_chain = assign.v_main_chain;
		this->d_main_chain = assign.d_main_chain;
		this->v_pairs = assign.v_pairs;
		this->d_pairs = assign.d_pairs;
		this->v_odd = assign.v_odd;
		this->d_odd = assign.d_odd;
	}
	return *this;
}
PmergeMe::~PmergeMe() {

}

// >---------------------------------------------------- VECTOR

void PmergeMe::vSavePair() {
	struct pair	pair;

	for (size_t i = 0; i < v_list.size() - 1; i += 2) {
		pair.a = v_list[i];
		pair.b = v_list[i + 1];
		v_pairs.push_back(pair);
	}
}

void PmergeMe::vMainChain() {
	size_t	b;

	b = 0;
	for (size_t i = 1; i < v_list.size(); i += 2) {
		std::swap(v_list[b], v_list[i]);
		b++;
		v_main_chain++;
	}
}

std::vector<int>::iterator PmergeMe::v_binary_search(std::vector<int>::iterator end, int target) {
	std::vector<int>::iterator	begin;
	std::vector<int>::iterator	mid;

	begin = v_list.begin();
	while (begin < end) {
		mid = begin + (end - begin) / 2;
		if (*mid < target)
			begin = mid + 1;
		else
			end = mid;
		v_num_comp++;
	}
	return begin;
}

void PmergeMe::vBinaryInsertRest(int old_jacobsthal) {
	std::vector<int>::iterator	v_it;
	std::vector<int>::iterator	v_end;
	int							index;

	for (int k = old_jacobsthal; k < v_main_chain; k++) {
			index = k - 1;
			v_end = std::find(v_list.begin(), v_list.end(), v_pairs[index].b);
			v_it = v_binary_search(v_end, v_pairs[index].a);
			v_list.erase(std::find(v_end, v_list.end(), v_pairs[index].a));
			v_list.insert(v_it, v_pairs[index].a);
	}
	if (v_odd != -1) {
		v_it = v_binary_search(v_list.end(), v_odd);
		v_list.erase(v_list.end() - 1);
		v_list.insert(v_it, v_odd);
	}
}

void PmergeMe::vBinaryInsert() {
	std::vector<int>::iterator	v_it;
	std::vector<int>::iterator	v_end;
	int							old_jacobsthal;
	int							new_jacobsthal;
	int							index;
	int							i;

	old_jacobsthal = 0;
	i = 2;
	while (true) {
		new_jacobsthal = jacobsthal(i);
		if (new_jacobsthal > v_main_chain) {
				vBinaryInsertRest(old_jacobsthal);
			break;
		}
		for (int k = new_jacobsthal; k > old_jacobsthal; --k) {
			index = k - 1;
			v_end = std::find(v_list.begin(), v_list.end(), v_pairs[index].b);
			v_it = v_binary_search(v_end, v_pairs[index].a);
			v_list.erase(std::find(v_end, v_list.end(), v_pairs[index].a));
			v_list.insert(v_it, v_pairs[index].a);
		}
		old_jacobsthal = new_jacobsthal;
		i++;
	}
}

void PmergeMe::vMerge(size_t left, size_t mid, size_t right) {
	std::vector<int>	temp;
	size_t				i;
	size_t				j;

	i = left;
	j = mid;
	while (i < mid && j < right) {
		if (v_list[i] <= v_list[j])
			temp.push_back(v_list[i++]);
		else
			temp.push_back(v_list[j++]);
		v_num_comp++;
	}
    while (i < mid)
		temp.push_back(v_list[i++]);
	while (j < right)
		temp.push_back(v_list[j++]);
	for (size_t k = 0; k < temp.size(); ++k)
		v_list[left + k] = temp[k];
}

void PmergeMe::vMergeSort(size_t left, size_t right) {
	size_t	mid;

	if (right - left <= 1)
		return;
	mid = left + (right - left) / 2;
	vMergeSort(left, mid);
	vMergeSort(mid, right);
	vMerge(left, mid, right);
}

void PmergeMe::vFordJohnson() {
	for (size_t i = 0; i < v_list.size() - 1; i += 2) {
		if (v_list[i] > v_list[i + 1])
			std::swap(v_list[i], v_list[i + 1]);
		v_num_comp++;
	}
	this->vSavePair();
	if (v_list.size() % 2 != 0)
		v_odd = v_list.back();
	this->vMainChain();
}

void PmergeMe::vSort() {
	struct timeval		start;
	struct timeval		end;
	long				sec;
	long				usec;
	std::stringstream	s;

	gettimeofday(&start, 0);
	if (v_list.size() > 1) {
		vFordJohnson();
		vMergeSort(0, v_main_chain);
		vBinaryInsert();
	}
	gettimeofday(&end, 0);
	sec = end.tv_sec - start.tv_sec;
	usec = end.tv_usec - start.tv_usec;
	v_time = sec * 1000000 + usec;
	for (std::vector<int>::iterator it = v_list.begin(); it != v_list.end(); ++it) {
		s << *it << " ";
	}
	v_output = s.str();
	v_output.erase(v_output.size() - 1);
}

// ----------------------------------------------------< VECTOR


// >---------------------------------------------------- DEQUE

void PmergeMe::dSavePair() {
	struct pair	pair;

	for (size_t i = 0; i < d_list.size() - 1; i += 2) {
		pair.a = d_list[i];
		pair.b = d_list[i + 1];
		d_pairs.push_back(pair);
	}
}

void PmergeMe::dMainChain() {
	size_t	b;

	b = 0;
	for (size_t i = 1; i < d_list.size(); i += 2) {
		std::swap(d_list[b], d_list[i]);
		b++;
		d_main_chain++;
	}
}

std::deque<int>::iterator PmergeMe::d_binary_search(std::deque<int>::iterator end, int target) {
	std::deque<int>::iterator	begin;
	std::deque<int>::iterator	mid;

	begin = d_list.begin();
	while (begin < end) {
		mid = begin + (end - begin) / 2;
		if (*mid < target)
			begin = mid + 1;
		else
			end = mid;
		d_num_comp++;
	}
	return begin;
}

void PmergeMe::dBinaryInsertRest(int old_jacobsthal) {
	std::deque<int>::iterator	d_it;
	std::deque<int>::iterator	d_end;
	int							index;

	for (int k = old_jacobsthal; k < d_main_chain; k++) {
			index = k - 1;
			d_end = std::find(d_list.begin(), d_list.end(), d_pairs[index].b);
			d_it = d_binary_search(d_end, d_pairs[index].a);
			d_list.erase(std::find(d_end, d_list.end(), d_pairs[index].a));
			d_list.insert(d_it, d_pairs[index].a);
	}
	if (d_odd != -1) {
		d_it = d_binary_search(d_list.end(), d_odd);
		d_list.erase(d_list.end() - 1);
		d_list.insert(d_it, d_odd);
	}
}

void PmergeMe::dBinaryInsert() {
	std::deque<int>::iterator	d_it;
	std::deque<int>::iterator	d_end;
	int							old_jacobsthal;
	int							new_jacobsthal;
	int							index;
	int							i;

	old_jacobsthal = 0;
	i = 2;
	while (true) {
		new_jacobsthal = jacobsthal(i);
		if (new_jacobsthal > d_main_chain) {
				dBinaryInsertRest(old_jacobsthal);
			break;
		}
		for (int k = new_jacobsthal; k > old_jacobsthal; --k) {
			index = k - 1;
			d_end = std::find(d_list.begin(), d_list.end(), d_pairs[index].b);
			d_it = d_binary_search(d_end, d_pairs[index].a);
			d_list.erase(std::find(d_end, d_list.end(), d_pairs[index].a));
			d_list.insert(d_it, d_pairs[index].a);
		}
		old_jacobsthal = new_jacobsthal;
		i++;
	}
}

void PmergeMe::dMerge(size_t left, size_t mid, size_t right) {
	std::deque<int>	temp;
	size_t			i;
	size_t			j;

	i = left;
	j = mid;
	while (i < mid && j < right) {
		if (d_list[i] <= d_list[j])
			temp.push_back(d_list[i++]);
		else
			temp.push_back(d_list[j++]);
		d_num_comp++;
	}
    while (i < mid)
		temp.push_back(d_list[i++]);
	while (j < right)
		temp.push_back(d_list[j++]);
	for (size_t k = 0; k < temp.size(); ++k)
		d_list[left + k] = temp[k];
}

void PmergeMe::dMergeSort(size_t left, size_t right) {
	size_t	mid;

	if (right - left <= 1)
		return;
	mid = left + (right - left) / 2;
	dMergeSort(left, mid);
	dMergeSort(mid, right);
	dMerge(left, mid, right);
}

void PmergeMe::dFordJohnson() {
	for (size_t i = 0; i < d_list.size() - 1; i += 2) {
		if (d_list[i] > d_list[i + 1])
			std::swap(d_list[i], d_list[i + 1]);
		d_num_comp++;
	}
	this->dSavePair();
	if (d_list.size() % 2 != 0)
		d_odd = d_list.back();
	this->dMainChain();
}

void PmergeMe::dSort() {
	struct timeval		start;
	struct timeval		end;
	long				sec;
	long				usec;
	std::stringstream	s;

	gettimeofday(&start, 0);
	if (d_list.size() > 1) {
		dFordJohnson();
		dMergeSort(0, d_main_chain);
		dBinaryInsert();
	}
	gettimeofday(&end, 0);
	sec = end.tv_sec - start.tv_sec;
	usec = end.tv_usec - start.tv_usec;
	d_time = sec * 1000000 + usec;
	for (std::deque<int>::iterator it = d_list.begin(); it != d_list.end(); ++it) {
		s << *it << " ";
	}
	d_output = s.str();
	d_output.erase(d_output.size() - 1);
}

// ----------------------------------------------------< DEQUE

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
		if (n < 0) {
			std::cerr << "Error: negative number " << n << std::endl;
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

void PmergeMe::printResult() {
	std::cout << "Before:\t" << input << std::endl;
	if (sorted(VECTOR) == false)
		std::cout << "Error: vector not sorted!" << std::endl;
	std::cout << "vAfter:\t" << v_output << std::endl;
	if (sorted(DEQUE) == false)
		std::cout << "Error: deque not sorted!" << std::endl;
	std::cout << "dAfter:\t" << d_output << std::endl;
	std::cout << "Time to process a range of " << v_list.size() << " elements with std::vector : " << v_time << " us"<< std::endl;
	std::cout << "Time to process a range of " << d_list.size() << " elements with std::deque  : " << d_time << " us"<< std::endl;
}

bool PmergeMe::sorted(int mode) {
	if (mode == VECTOR) {
		for (size_t i = 1; i < v_list.size(); i++) {
			if (v_list[i] < v_list[i - 1])
				return false;
		}
	}
	if (mode == DEQUE) {
		for (size_t i = 1; i < d_list.size(); i++) {
			if (d_list[i] < d_list[i - 1])
				return false;
		}
	}
	return true;
}

int PmergeMe::getVNumComp() const {
	return this->v_num_comp;
}

int PmergeMe::getDNumComp() const {
	return this->d_num_comp;
}

int PmergeMe::getElements() const {
	return v_list.size();
}

int jacobsthal(int k) {
	return static_cast<int>((std::pow(2, k + 1) + (k % 2 == 0 ? 1 : -1)) / 3);
}

int num_of_comp(const int elements) {
	int		sum;
	double	value;

	sum = 0;
	for (int k = 1; k <= elements; ++k) {
		value = (3.0 / 4.0) * k;
		sum += static_cast<int>(ceil(log2(value)));
	}
	return sum;
}
