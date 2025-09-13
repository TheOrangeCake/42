/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:45:14 by hoannguy          #+#    #+#             */
/*   Updated: 2025/09/13 17:12:31 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {

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

double BitcoinExchange::parseValue(std::string& input, int mode) {
	std::stringstream	value(input);
	double				d;

	value >> d;
	if (value.fail() || !value.eof()) {
		throw BitcoinExchange::ValueFormatException();
	}
	if (d < 0) {
		throw BitcoinExchange::ValueLowException();
	}
	if (mode == INPUT && d > 1000) {
		throw BitcoinExchange::ValueHighException();
	}
	return d;
}

std::string BitcoinExchange::parseDate(std::string& input) {
	int						year;
	std::string::size_type	first_pos;
	int						month;
	std::string::size_type	second_pos;
	int						day;
	std::stringstream		stream;
	bool					leap;

	if (input.size() != 10) {
		throw BitcoinExchange::DateFormatException();
	}
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

int BitcoinExchange::handleDataBase(std::string& line) {
	std::string::size_type	comma_pos;
	std::string				date;
	std::string				value;
		
	comma_pos = line.find(",");
	if (comma_pos == std::string::npos) {
		std::cerr << "Error: data base file bad format!" << std::endl;
		return -1;
	}
	try {
		date = line.substr(0, comma_pos);
		value = line.substr(comma_pos + 1);
		setDataBase(parseDate(date), parseValue(value, DATABASE));
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		std::cerr << "-> " << line << std::endl;
		return -1;
	}
	return 0;
}

void BitcoinExchange::handleInput(std::string& line) {
	std::string::size_type	pipe_pos;
	std::string				date;
	std::string				value;
	double					d;

	pipe_pos = line.find(" | ");
	if (pipe_pos == std::string::npos) {
		std::cerr << "Error: bad input => " << line << std::endl;
		return;
	}
	try {
		date = line.substr(0, pipe_pos);
		date = parseDate(date);
		value = line.substr(pipe_pos + 3);
		d = parseValue(value, INPUT);
		d *= this->getDataPrice(date);
		std::cout << date << " => " << value << " = " << std::setprecision(15) << d << std::endl;
		
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}

int BitcoinExchange::handleData(std::string& data, int mode) {
	std::string::size_type	endline_pos;
	std::string				line;

	endline_pos = data.find("\n");
	if (endline_pos == std::string::npos) {
		if (mode == DATABASE) {
			std::cerr << "Error: data base file bad format!" << std::endl;
		}
		if (mode == INPUT) {
			std::cerr << "Error: input file bad format!" << std::endl;
		}
		return -1;
	}
	if (mode == DATABASE) {
		if (data.substr(0, endline_pos) != "date,exchange_rate") {
			std::cerr << "Error: data base file header must be \"date,exchange_rate\"" << std::endl;
			std::cerr << "Warning: first line will be deleted" << std::endl;
		}
	}
	if (mode == INPUT) {
		if (data.substr(0, endline_pos) != "date | value") {
			std::cerr << "Error: input file header must be \"date | value\"" << std::endl;
			std::cerr << "Warning: first line will be deleted" << std::endl;
		}
	}
	data.erase(0, endline_pos + 1);
	while (!data.empty()) {
		endline_pos = data.find("\n");
		if (endline_pos == std::string::npos) {
			if (mode == DATABASE) {
				std::cerr << "Error: data base file bad format!" << std::endl;
			}
			if (mode == INPUT) {
				std::cerr << "Error: input file bad format!" << std::endl;
			}
			return -1;
		}
		line = data.substr(0, endline_pos);
		data.erase(0, endline_pos + 1);
		if (line.empty()) {
			std::cout << std::endl;
			continue;
		}
		if (mode == DATABASE) {
			if (handleDataBase(line) == -1) {
				return -1;
			}
		}
		if (mode == INPUT) {
			handleInput(line);
		}
	}
	return 0;
}

int BitcoinExchange::BitcoinHandler(const char *input, int mode) {
	std::fstream	file;
	char*			buffer;
	long			length;
	std::string		data;

	if ((mode != DATABASE && mode != INPUT) || input == NULL) {
		std::cerr << "Error: function handleData() only accept DATABASE or INPUT modes!" << std::endl;
		return -1;
	}
	file.open(input, std::fstream::in);
	if (!file.is_open()) {
		if (mode == INPUT)
			std::cerr << "Error: fail to open input file!" << std::endl;
		if (mode == DATABASE)
			std::cerr << "Error: fail to open data base file!" << std::endl;
		return -1;
	}
	file.seekg(0, file.end);
	length = file.tellg();
	file.seekg(0, file.beg);
	buffer = new char[length + 1];
	buffer[length] = '\0';
	file.read(buffer, length);
	if (!file) {
		delete[] buffer;
		if (mode == INPUT)
			std::cerr << "Error: fail to read input file!" << std::endl;
		if (mode == DATABASE)
			std::cerr << "Error: fail to read data base file!" << std::endl;
		return -1;
	}
	data.assign(buffer);
	file.close();
	delete[] buffer;
	if (this->handleData(data, mode) == -1)
		return -1;
	return 0;
}

double BitcoinExchange::getDataPrice(std::string& date) {
	double									price;
	std::map<std::string, double>::iterator	it;

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

std::map<std::string, double> BitcoinExchange::getDataBase() const {
	return this->dataBase;
}

BitcoinExchange& BitcoinExchange::setDataBase(std::string date, double value) {
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

std::ostream& operator <<(std::ostream& o, std::map<std::string, double> dataBase) {
	o << "date,exchange_rate" <<std::endl;
	for (std::map<std::string, double>::iterator it = dataBase.begin(); it != dataBase.end(); ++it) {
		o << it->first << "," << it->second << std::endl;
	}
	return o;
}