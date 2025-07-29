/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 19:15:33 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/29 13:52:19 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP
#include <stack>

template <typename T>
class MutantStack : public std::stack<T> {
	public:
		MutantStack();
		MutantStack(const MutantStack& copy);
		MutantStack<T>& operator =(const MutantStack& assign);
		virtual ~MutantStack();

		typedef typename std::stack<T>::container_type::iterator iterator;

		iterator begin();
		iterator end();
};

#include "MutantStack.tpp"

#endif