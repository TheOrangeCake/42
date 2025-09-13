/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:45:35 by hoannguy          #+#    #+#             */
/*   Updated: 2025/09/13 13:34:25 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <sstream>

#define DATABASE 1
#define INPUT 2
class BitcoinExchange {
	private:
		std::map<std::string, float>	dataBase;
		std::string						input;

		int			parseDataBase(std::string& data);
		std::string	parseDate(std::string& input);
		float		parseValue(std::string& input, int flag);

	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& copy);
		BitcoinExchange& operator =(const BitcoinExchange& assign);
		~BitcoinExchange();

		float							getDataPrice(std::string& date);
		std::map<std::string, float>	getDataBase() const;
		BitcoinExchange&				setDataBase(std::string date, float value);
		void							handleInput(const char *input);

		class DateFormatException : public std::exception {
			public :
				virtual const char* what() const throw();
		};
		class ValueFormatException : public std::exception {
			public :
				virtual const char* what() const throw();
		};
		class ValueLowException : public std::exception {
			public :
				virtual const char* what() const throw();
		};
		class ValueHighException : public std::exception {
			public :
				virtual const char* what() const throw();
		};
		class InputFormatException : public std::exception {
			public:
				virtual const char* what() const throw();
		};
};

std::ostream& operator <<(std::ostream& o, std::map<std::string, float> dataBase);

#endif