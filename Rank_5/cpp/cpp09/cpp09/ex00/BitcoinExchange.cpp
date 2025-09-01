/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:45:14 by hoannguy          #+#    #+#             */
/*   Updated: 2025/09/01 23:34:36 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

float BitcoinExchange::parseValue(std::string& input, int flag) {
	std::stringstream	value(input);
	float				f;

	value >> f;
	if (value.fail() || !value.eof()) {
		throw BitcoinExchange::ValueFormatException();
	}
	if (f < 0) {
		throw BitcoinExchange::ValueLowException();
	}
	if (flag == INPUT && f > 1000) {
		throw BitcoinExchange::ValueHighException();
	}
	return f;
}

std::string BitcoinExchange::parseDate(std::string& input) {
	int						year;
	std::string::size_type	first_pos;
	int						month;
	std::string::size_type	second_pos;
	int						day;
	std::stringstream		stream;

	first_pos = input.find("-");
	if (first_pos == std::string::npos) {
		throw BitcoinExchange::DateFormatException();
	}
	stream.str(input.substr(0, first_pos));
	stream >> year;
	if (stream.fail() || year < 2000 || year > 3000) {
		throw BitcoinExchange::DateFormatException();
	}
	second_pos = input.find("-", first_pos + 1);
	if (second_pos == std::string::npos) {
		throw BitcoinExchange::DateFormatException();
	}
	stream.str(input.substr(first_pos + 1, second_pos - (first_pos + 1)));
	stream.clear();
	stream >> month;
	if (stream.fail() || month < 1 || month > 12) {
		throw BitcoinExchange::DateFormatException();
	}
	stream.str(input.substr(second_pos + 1));
	stream.clear();
	stream >> day;
	if (stream.fail() || day < 1 || day > 31) {
		throw BitcoinExchange::DateFormatException();
	}
	// check day for month and leap year
	
	return input;
}

void BitcoinExchange::parseDataBase(std::string& data) {
	std::string::size_type	endline_pos;
	std::string::size_type	comma_pos;
	std::string				line;
	std::string				date;
	std::string				value;

	endline_pos = data.find("\n");
	if (endline_pos == std::string::npos) {
		throw BitcoinExchange::DatabaseFormatException();
	}
	data.erase(0, endline_pos + 1);
	while (!data.empty()) {
		endline_pos = data.find("\n");
		if (endline_pos == std::string::npos) {
			throw BitcoinExchange::DatabaseFormatException();
		}
		line = data.substr(0, endline_pos);
		data.erase(0, endline_pos + 1);
		comma_pos = line.find(",");
		if (comma_pos == std::string::npos) {
			throw BitcoinExchange::DatabaseFormatException();
		}
		try {
			date = line.substr(0, comma_pos);
			value = line.substr(comma_pos + 1);
			setDataBase(parseDate(date), parseValue(value, DATABASE));
		} catch (std::exception& e) {
			throw BitcoinExchange::DatabaseFormatException();
		}
	}
}

BitcoinExchange::BitcoinExchange() {
	std::fstream	file;
	char*			buffer;
	long			length;
	std::string		data;

	file.open("data.csv", std::fstream::in);
	if (!file.is_open()) {
		throw BitcoinExchange::DatabaseOpenException();
	}
	file.seekg(0, file.end);
	length = file.tellg();
	file.seekg(0, file.beg);
	buffer = new char[length + 1];
	buffer[length] = '\0';
	file.read(buffer, length);
	if (!file) {
		delete[] buffer;
		throw BitcoinExchange::DatabaseOpenException();
	}
	data.assign(buffer);
	delete[] buffer;
	try {
		this->parseDataBase(data);
	} catch(std::exception& e) {
		throw BitcoinExchange::DatabaseFormatException();
	}
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

std::map<std::string, float> BitcoinExchange::getDataBase() const {
	return this->dataBase;
}

BitcoinExchange& BitcoinExchange::setDataBase(std::string date, float value) {
	this->dataBase[date] = value;
	return *this;
}

const char* BitcoinExchange::DatabaseOpenException::what() const throw() {
	return "Error: fail to open or read database file!";
}
const char* BitcoinExchange::DatabaseFormatException::what() const throw() {
	return "Error: database format error!";
}
const char* BitcoinExchange::DateFormatException::what() const throw() {
	return "Error: date format error!";
}
const char* BitcoinExchange::ValueFormatException::what() const throw() {
	return "Error: value format error!";
}
const char* BitcoinExchange::ValueLowException::what() const throw() {
	return "Error: not a positive number.";
}
const char* BitcoinExchange::ValueHighException::what() const throw() {
	return "Error: too large a number.";
}

std::ostream& operator <<(std::ostream& o, std::map<std::string, float> dataBase) {
	o << "date,exchange_rate" <<std::endl;
	for (std::map<std::string, float>::iterator it = dataBase.begin(); it != dataBase.end(); ++it) {
		o << it->first << "," << it->second << std::endl;
	}
	return o;
}