/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:45:14 by hoannguy          #+#    #+#             */
/*   Updated: 2025/09/01 17:45:14 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

void BitcoinExchange::parseDataBase(std::string data) {
	(void) data;
}

BitcoinExchange::BitcoinExchange() {
	std::fstream	file;
	char*			buffer;
	long			length;
	std::string		data;

	file.open("data.csv", std::fstream::in);
	if (!file.is_open()) {
		throw BitcoinExchange::DataBaseException();
	}
	file.seekg(0, file.end);
	length = file.tellg();
	file.seekg(0, file.beg);
	buffer = new char[length];
	file.read(buffer, length);
	if (!file) {
		delete[] buffer;
		throw BitcoinExchange::DataBaseException();
	}
	data.assign(buffer);
	delete[] buffer;
	this->parseDataBase(data);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& copy) {
	*this = copy;
}

BitcoinExchange& BitcoinExchange::operator =(const BitcoinExchange& assign) {
	this->input = assign.input;
	this->dataBase = assign.dataBase;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {

}

float BitcoinExchange::getDataPrice(std::string date) const {
	float	price;

	(void)date;
	price = -1.0f;
	// get the date here, if date doesnt exist,
	// then get the closest previous date.
	return price;
}

const char* BitcoinExchange::DataBaseException::what() const throw() {
	return "Error: Fail to open or read database file!";
}

std::ostream& operator <<(std::ostream& o, std::map<std::string, float> dataBase) {
	o << "date,exchange_rate" <<std::endl;
	for (std::map<std::string, float>::iterator it = dataBase.begin(); it != dataBase.end(); ++it) {
		o << it->first << "," << it->second << std::endl;
	}
	return o;
}