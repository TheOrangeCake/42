/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:44:39 by hoannguy          #+#    #+#             */
/*   Updated: 2025/09/13 23:33:50 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int ac, char **av) {
	RPN			rpn;
	std::string	input;
	int			i;

	if (ac == 1) {
		std::cerr << "Error: Missing arguments" << std::endl;
		return -1;
	}
	i = 1;
	if (ac > 2) {
		while (av[i] != NULL) {
			input.append(av[i]).append(" ");
			i++;
		}
		input.erase(input.size() - 1);
	} else
		input += av[i];
	if (rpn.doTheMagic(input) == -1) {
		std::cerr << "Error" << std::endl;
		return -1;
	}
	return 0;
}

// Both = 15
// 1 2 * 2 / 2 + 5 * 6 - 1 3 * - 4 5 * * 8 /
// 1 2 '*' 2 / 2 + 5 '*' 6 - 1 3 '*' - 4 5 '*' '*' 8 / 