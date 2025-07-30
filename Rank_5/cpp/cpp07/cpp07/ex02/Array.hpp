/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 13:46:20 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/30 15:06:27 by hoannguy         ###   ########.fr       */
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
		const T& operator [](int index) const;
		int size() const;
};

#include "Array.tpp"
#endif