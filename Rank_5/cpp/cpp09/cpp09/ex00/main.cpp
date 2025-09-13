/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:44:39 by hoannguy          #+#    #+#             */
/*   Updated: 2025/09/13 16:47:40 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int ac, char **av) {
	BitcoinExchange	bitcoin;
	
	if (ac == 2) {
		if (bitcoin.BitcoinHandler("data.csv", DATABASE) == -1)
			return -1;
		if (bitcoin.BitcoinHandler(av[1], INPUT) == -1)
			return -1;
	} else {
		std::cerr << "Error: could not open file." << std::endl;
		return -1;
	}
	return 0;
}