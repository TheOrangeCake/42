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

struct pair {
	int	a;
	int	b;
};

class PmergeMe {
	private:
		std::vector<int>	v_list;
		double				v_time;
		std::deque<int>		d_list;
		double				d_time;
		std::string			input;
		std::string			output;
		int					num_comp;
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
		void	dFordJohnson();
		void	printResult() const;
		int		getNumComp() const;
};

unsigned int	jacobsthal(int k);
unsigned int	num_of_comp(const int elements);

#endif