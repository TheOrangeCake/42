/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 13:46:20 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/27 14:44:55 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
#define ARRAY_HPP

template <typename T>
class Array {
	private:
		T 	*array;
		int a_size;

	public:
		Array();
		Array(unsigned int n);
		Array(Array& copy);
		Array& operator =(Array& assign);
		~Array();

		T& operator [](int index);
		int size() const;
};

#include "Array.tpp"
#endif