/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 12:40:48 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/30 15:36:41 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Account.hpp"
#include <iostream>
#include <ctime>
#include <iomanip>

int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

Account::Account() {
}

Account::Account(int initial_deposit) :
	_accountIndex(0),
	_amount(initial_deposit),
	_nbDeposits(0),
	_nbWithdrawals(0)
	{
	this->_accountIndex = Account::_nbAccounts;
	_displayTimestamp();
	std::cout << "index:" << this->_accountIndex
	<< ";amount:" << initial_deposit << ";created" << std::endl;
	Account::_nbAccounts += 1;
	Account::_totalAmount += this->_amount;
}

Account::~Account() {
	_displayTimestamp();
	std::cout << "index:" << this->_accountIndex
	<< ";amount:" << this->checkAmount() << ";closed" << std::endl;
}

int Account::checkAmount(void) const {
	return (this->_amount);
}

void Account::_displayTimestamp(void) {
	std::time_t now = std::time(0);
	std::tm *current = std::localtime(&now);

	std::cout << "[" << (current->tm_year + 1900)
	<< std::setw(2) << std::setfill('0') << current->tm_mon + 1
	<< std::setw(2) << std::setfill('0') << current->tm_mday 
	<< "_"
	<< std::setw(2) << std::setfill('0') << current->tm_hour
	<< std::setw(2) << std::setfill('0') << current->tm_min
	<< std::setw(2) << std::setfill('0') << current->tm_sec
	<< "]";
}

void Account::displayAccountsInfos(void) {
	_displayTimestamp();
	std::cout << "accounts:" << Account::_nbAccounts << ";total:"
	<< Account::_totalAmount << ";deposits:" << Account::_totalNbDeposits
	<< ";withdrawals:" << Account::_totalNbWithdrawals << std::endl;
}

int Account::getNbAccounts(void) {
	return (Account::_nbAccounts);
}

int Account::getTotalAmount(void) {
	return (Account::_totalAmount);
}

int Account::getNbDeposits(void) {
	return (Account::_totalNbWithdrawals);
}

int Account::getNbWithdrawals(void) {
	return (Account::_totalNbWithdrawals);
}

void Account::displayStatus(void) const {
	_displayTimestamp();
	std::cout << "index:" << this->_accountIndex
	<< ";amount:" << this->_amount << ";deposits:" << this->_nbDeposits
	<< ";withdrawals:" << this->_nbWithdrawals << std::endl;
}

void Account::makeDeposit(int deposit) {
	int p_amount = this->_amount;
	this->_amount += deposit;
	this->_nbDeposits += 1;
	Account::_totalAmount += deposit;
	Account::_totalNbDeposits += 1;
	_displayTimestamp();
	std::cout << "index:" << this->_accountIndex
	<< ";p_amount:" << p_amount << ";deposits:" << deposit
	<< ";amount:" << this->_amount << ";nb_deposits:"
	<< this->_nbDeposits << std::endl;
}

bool Account::makeWithdrawal(int withdrawal) {
	int p_amount = this->_amount;
	if (this->_amount < withdrawal) {
		_displayTimestamp();
		std::cout << "index:" << this->_accountIndex
		<< ";p_amount:" << p_amount << ";withdrawal:refused" << std::endl;
		return (false);
	}
	this->_amount -= withdrawal;
	this->_nbWithdrawals += 1;
	Account::_totalAmount -= withdrawal;
	Account::_totalNbWithdrawals += 1;
	_displayTimestamp();
	std::cout << "index:" << this->_accountIndex
	<< ";p_amount:" << p_amount << ";withdrawal:" << withdrawal
	<< ";amount:" << this->_amount << ";nb_withdrawals:"
	<< this->_nbWithdrawals << std::endl;
	return (true);
}