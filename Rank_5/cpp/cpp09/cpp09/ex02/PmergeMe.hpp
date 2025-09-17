/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 23:53:12 by hoannguy          #+#    #+#             */
/*   Updated: 2025/09/13 23:53:12 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP
#include <cmath>
#include <sys/time.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <deque>
#include <algorithm>

#define VECTOR 1
#define DEQUE 2

struct pair {
	int	a;
	int	b;
};

class PmergeMe {
	private:
		std::vector<int>	v_list;
		std::deque<int>		d_list;
		long				v_time;
		long				d_time;
		std::string			input;
		std::string			v_output;
		std::string			d_output;
		int					v_num_comp;
		int					d_num_comp;
		int					v_main_chain;
		int					d_main_chain;
		std::vector<pair>	v_pairs;
		std::vector<pair>	d_pairs;
		int					v_odd;
		int					d_odd;

	public:
		PmergeMe();
		PmergeMe(const PmergeMe& copy);
		PmergeMe& operator =(const PmergeMe& assign);
		~PmergeMe();

		void						vSort();
		void						vFordJohnson();
		void						vSavePair();
		void						vMainChain();
		void						vMergeSort(size_t left, size_t right);
		void						vMerge(size_t left, size_t mid, size_t right);
		void						vBinaryInsert();
		void						vBinaryInsertRest(int old_jacobsthal);
		std::vector<int>::iterator	v_binary_search(std::vector<int>::iterator end, int target);


		void						dSort();
		void						dFordJohnson();
		void						dSavePair();
		void						dMainChain();
		void						dMergeSort(size_t left, size_t right);
		void						dMerge(size_t left, size_t mid, size_t right);
		void						dBinaryInsert();
		void						dBinaryInsertRest(int old_jacobsthal);
		std::deque<int>::iterator	d_binary_search(std::deque<int>::iterator end, int target);

		int							populate(const std::string& input);
		void						printResult();
		bool						sorted(int mode);

		int							getVNumComp() const;
		int							getDNumComp() const;
		int							getElements() const;
};

int	jacobsthal(int k);
int	num_of_comp(const int elements);

#endif


	// for (std::vector<int>::iterator it = this->v_list.begin(); it != this->v_list.end(); ++it) {
	// 	std::cout << *it << " ";
	// }
	// std::cout << std::endl;
