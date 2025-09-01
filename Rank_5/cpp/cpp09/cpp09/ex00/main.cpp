/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:44:39 by hoannguy          #+#    #+#             */
/*   Updated: 2025/09/01 17:44:39 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int ac, char **av) {
	(void)av;

	if (ac == 2) {
		try {
			BitcoinExchange	bitcoin;

		} catch(BitcoinExchange::DataBaseException& e) {
			std::cerr << e.what() << std::endl;
			return -1;
		}
	} else {
		std::cerr << "Error: could not open file." << std::endl;
		return -1;
	}
	return 0;
}