/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 11:38:48 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/25 15:25:02 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTER_HPP
# define INTER_HPP

template <typename A, typename L>
void iter(A *a, L len, void f(A)) {
	int size = static_cast<int>(len);

	for (int i = 0; i < size; i++) {
		f(a[i]);
	}
}

#endif