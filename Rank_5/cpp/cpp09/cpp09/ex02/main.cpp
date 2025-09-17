/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:44:39 by hoannguy          #+#    #+#             */
/*   Updated: 2025/09/17 13:34:37 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int ac, char **av) {
	PmergeMe	item;
	std::string	input;
	int			i;

	if (ac == 1) {
		std::cerr << "Error: no input numbers!" << std::endl;
		return -1;
	}
	if (ac == 2) {
		input += av[1];
	} else {
		i = 1;
		while (av[i] != NULL) {
			input.append(av[i]).append(" ");
			i++;
		}
		input.erase(input.size() - 1);
	}
	if (item.populate(input) == -1)
		return -1;
	item.vSort();
	item.dSort();
	item.printResult();
	return 0;
}

// ./PmergeMe `shuf -i 1-1000 -n 10 | tr "\n" " " `

// src: p287
// https://books.google.ch/books?id=kM5v2YqMVuoC&pg=PA286&redir_esc=y#v=onepage&q&f=false
