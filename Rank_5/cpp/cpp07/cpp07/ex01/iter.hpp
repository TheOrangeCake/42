/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 11:38:48 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/30 14:38:10 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTER_HPP
# define INTER_HPP
# include <string>

template <typename A, typename L>
void iter(A *a, L len, void (*f)(A&)) {
	if (a == NULL || f == NULL)
		return ;
	long size = static_cast<long>(len);

	for (long i = 0; i < size; i++) {
		f(a[i]);
	}
}

template <typename A, typename L, typename T>
void iter(A *a, L len, void (*f)(const T&)) {
	if (a == NULL || f == NULL)
		return ;
	long size = static_cast<long>(len);

	for (long i = 0; i < size; i++) {
		f(a[i]);
	}
}

#endif