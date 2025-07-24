/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:24:24 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/24 15:52:01 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WHATEVER_HPP
# define WHATEVER_HPP

template <typename T>
void swap(T& a, T& b) {
	T c;
	c = a;
	a = b;
	b = c;
}

template <typename T>
T min(T a, T b) {
	if (a <= b) {
		return (a);
	} else {
		return (b);
	}
}

template <typename T>
T max(T a, T b) {
	if (a > b) {
		return (a);
	} else {
		return (b);
	}
}

#endif