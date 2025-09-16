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
#include <ctime>
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
		double				v_time;
		double				d_time;
		std::string			input;
		std::string			v_output;
		std::string			d_output;
		int					v_num_comp;
		int					d_num_comp;
		int					v_max;
		int					d_max;
		std::vector<pair>	pairs;
		int					odd;

	public:
		PmergeMe();
		PmergeMe(const PmergeMe& copy);
		PmergeMe& operator =(const PmergeMe& assign);
		~PmergeMe();

		int		populate(const std::string& input);
		void	vSort();
		void	dSort();
		void	vFordJohnson(size_t n);
		void	dFordJohnson(size_t n);
		void	savePair(int mode);
		void	mainChain(int mode);
		void	binaryInsert(int mode);
		void	printResult() const;
		int		getVNumComp() const;
		int		getDNumComp() const;
};

unsigned int	jacobsthal(int k);
unsigned int	num_of_comp(const int elements);
unsigned int	binary_search(int start, int end, int target, int num_comp);

#endif


	// for (std::vector<int>::iterator it = this->v_list.begin(); it != this->v_list.end(); ++it) {
	// 	std::cout << *it << " ";
	// }
	// std::cout << std::endl;
