/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 13:46:32 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/27 16:04:23 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_TPP
#define ARRAY_TPP

template <typename T>
Array<T>::Array() {
	this->array = new T[0];
	this->a_size = 0;
}

template <typename T>
Array<T>::Array(unsigned int n) {
	if (n > 0) {
		this->array = new T[n];
		this->a_size = n;
	}
}

template <typename T>
Array<T>::Array(Array& copy) {
	this->a_size = copy.size();
	this->array = new T[this->a_size];
	for (int i = 0; i < this->a_size; i++){
		this->array[i] = copy[i];
	}
}

template <typename T>
Array<T>& Array<T>::operator =(Array& assign) {
	if (this != &assign) {
		delete[] this->array;
		this->a_size = assign.size();
		this->array = new T[this->a_size];
		for (int i = 0; i < this->a_size; i++){
		this->array[i] = assign[i];
		}
	}
	return *this;
}

template <typename T>
Array<T>::~Array() {
	delete[] this->array;
}

template <typename T>
T& Array<T>::operator [](int index) {
	if (index < 0 || index >= this->size()) {
		throw std::exception();
	}
	return (this->array[index]);
}

template <typename T>
int Array<T>::size() const {
	return (this->a_size);
}

#endif