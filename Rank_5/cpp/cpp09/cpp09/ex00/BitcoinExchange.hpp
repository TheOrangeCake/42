/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:45:35 by hoannguy          #+#    #+#             */
/*   Updated: 2025/09/01 17:45:35 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

class BitcoinExchange {
	private:
		std::map<std::string, float>	dataBase;
		std::string						input;

		void		parseDataBase(std::string data);

	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& copy);
		BitcoinExchange& operator =(const BitcoinExchange& assign);
		~BitcoinExchange();

		float		getDataPrice(std::string date) const;

		class DataBaseException : public std::exception {
			public:
				virtual const char* what() const throw();
		};
};

std::ostream& operator <<(std::ostream& o, std::map<std::string, float> dataBase);

#endif