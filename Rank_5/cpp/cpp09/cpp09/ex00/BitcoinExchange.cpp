/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:45:14 by hoannguy          #+#    #+#             */
/*   Updated: 2025/09/13 13:35:18 by hoannguy         ###   ########.fr       */
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
	bool					leap;

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
	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
		throw BitcoinExchange::DateFormatException();
	}
	leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	if ((month == 2 && leap == false && day > 28)
	|| (month == 2 && leap == true && day > 29)) {
		throw BitcoinExchange::DateFormatException();
	}
	return input;
}

int BitcoinExchange::parseDataBase(std::string& data) {
	std::string::size_type	endline_pos;
	std::string::size_type	comma_pos;
	std::string				line;
	std::string				date;
	std::string				value;

	endline_pos = data.find("\n");
	if (endline_pos == std::string::npos) {
		std::cerr << "Error: fail to open or read database file!" << std::endl;
		return -1;
	}
	data.erase(0, endline_pos + 1);
	while (!data.empty()) {
		endline_pos = data.find("\n");
		if (endline_pos == std::string::npos) {
			std::cerr << "Error: fail to open or read database file!" << std::endl;
			return -1;
		}
		line = data.substr(0, endline_pos);
		data.erase(0, endline_pos + 1);
		comma_pos = line.find(",");
		if (comma_pos == std::string::npos) {
			std::cerr << "Error: fail to open or read database file!" << std::endl;
			return -1;
		}
		try {
			date = line.substr(0, comma_pos);
			value = line.substr(comma_pos + 1);
			setDataBase(parseDate(date), parseValue(value, DATABASE));
		} catch (std::exception& e) {
			std::cerr << e.what() << std::endl;
			return -1;
		}
	}
	return 0;
}

BitcoinExchange::BitcoinExchange() {
	std::fstream	file;
	char*			buffer;
	long			length;
	std::string		data;

	file.open("data.csv", std::fstream::in);
	if (!file.is_open()) {
		std::cerr << "Error: fail to open or read database file!" << std::endl;
		throw std::exception();
	}
	file.seekg(0, file.end);
	length = file.tellg();
	file.seekg(0, file.beg);
	buffer = new char[length + 1];
	buffer[length] = '\0';
	file.read(buffer, length);
	if (!file) {
		delete[] buffer;
		std::cerr << "Error: fail to open or read database file!" << std::endl;
		throw std::exception();
	}
	data.assign(buffer);
	delete[] buffer;
	if (this->parseDataBase(data) == -1)
		throw std::exception();
}

void BitcoinExchange::handleInput(const char *input) {
	std::fstream	file;
	char*			buffer;
	long			length;
	std::string		data;

	file.open(input, std::fstream::in);
	if (!file.is_open()) {
		std::cerr << "Error: fail to open or read input file!" << std::endl;
		throw std::exception();
	}
	file.seekg(0, file.end);
	length = file.tellg();
	file.seekg(0, file.beg);
	buffer = new char[length + 1];
	buffer[length] = '\0';
	file.read(buffer, length);
	if (!file) {
		delete[] buffer;
		std::cerr << "Error: fail to open or read input file!" << std::endl;
		throw std::exception();
	}
	data.assign(buffer);
	delete[] buffer;
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

float BitcoinExchange::getDataPrice(std::string& date) {
	float									price;
	std::map<std::string, float>::iterator	it;

	if (this->dataBase.count(date) == 1)
		price = this->dataBase[date];
	else {
		it = dataBase.lower_bound(date);
		if (it == dataBase.begin()) {
			return -1.0f;
		} else {
			--it;
			price = it->second;
		} 
	}
	return price;
}

std::map<std::string, float> BitcoinExchange::getDataBase() const {
	return this->dataBase;
}

BitcoinExchange& BitcoinExchange::setDataBase(std::string date, float value) {
	this->dataBase[date] = value;
	return *this;
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
const char* BitcoinExchange::InputFormatException::what() const throw() {
	return "Error: input format error!";
}

std::ostream& operator <<(std::ostream& o, std::map<std::string, float> dataBase) {
	o << "date,exchange_rate" <<std::endl;
	for (std::map<std::string, float>::iterator it = dataBase.begin(); it != dataBase.end(); ++it) {
		o << it->first << "," << it->second << std::endl;
	}
	return o;
}