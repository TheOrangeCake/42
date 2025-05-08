/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:57:24 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/07 20:39:47 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"
#include "PhoneBook.hpp"
#include <iomanip>
#include <iostream>
#include <limits>

std::string truncate(std::string str)
{
	if (str.size() >= 10)
		return (str.substr(0, 9) + ".");
	else
		return str;
}

void print_list(PhoneBook phonebook)
{
	std::cout << std::setfill (' ') << std::setw(10) << "index";
	std::cout << "   |   ";
	std::cout << std::setfill (' ') << std::setw(10) << "First name";
	std::cout << "   |   ";
	std::cout << std::setfill (' ') << std::setw(10) << "Last name";
	std::cout << "   |   ";
	std::cout << std::setfill (' ') << std::setw(10) << "Nickname" << std::endl;
	for (int i = 0; i < 8; i++) {
		Contact contact = phonebook.get_contact(i);
		if (contact.f_name_getter().empty())
			break;
		else
		{
			std::cout << std::setfill (' ') << std::setw(10) << i;
			std::cout << "   |   ";
			std::cout << std::setfill (' ') << std::setw(10) << truncate(contact.f_name_getter());
			std::cout << "   |   ";
			std::cout << std::setfill (' ') << std::setw(10) << truncate(contact.l_name_getter());
			std::cout << "   |   ";
			std::cout << std::setfill (' ') << std::setw(10) << truncate(contact.nickname_getter()) << std::endl;
		}
	}
}

void print_contact(PhoneBook phonebook)
{
	int	index;
	std::cout << "Enter index: ";
	std::cin >> index;
	if (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input" << std::endl;
	}
	else
	{
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (index >= 0 && index < 8)
		{
			Contact contact = phonebook.get_contact(index);
			if (contact.f_name_getter().empty())
				std::cout << "Contact is empty" << std::endl;
			else
			{
				std::cout << "Firstname: " << contact.f_name_getter() << std::endl;
				std::cout << "Lastname: " << contact.l_name_getter() << std::endl;
				std::cout << "Nickname: " << contact.nickname_getter() << std::endl;
				std::cout << "Phone: " << contact.phone_getter() << std::endl;
				std::cout << "Darkest secret: " << contact.secret_getter() << std::endl;
			}
		}
		else
			std::cout << "Index must be between 0 and 7" << std::endl;
	}
}

std::string get_input(std::string question, std::string err_message)
{
	std::string temp;

	while (true)
	{
		std::cout << question;
		std::getline(std::cin, temp);
		if (temp.empty())
			std::cout << err_message << std::endl;
		else
			return (temp);
	}
	return (temp);
}

Contact new_contact() 
{
	std::string f_name;
	std::string l_name;
	std::string nickname;
	std::string phone;
	std::string secret;

	f_name = get_input("Enter first name: ", "First name can not be empty");
	l_name = get_input("Enter last name: ", "Last name can not be empty");
	nickname = get_input("Enter nickname: ", "Nickname can not be empty");
	phone = get_input("Enter phone number: ", "Phone number can not be empty");
	secret = get_input("Tell me your darkest secret: ", "Tell me, I promise i will only tell my cats");
	Contact contact(f_name, l_name, nickname, phone, secret);
	return (contact);
}

int main(void) {
	PhoneBook phonebook;
	std::string command;

	while (1)
	{
		std::cout << "Enter command: ";
		if(!std::getline(std::cin, command))
			return (1);
		if (!command.compare("ADD"))
		{
			phonebook.add_contact(new_contact());
		}
		else if (!command.compare("SEARCH"))
		{
			print_list(phonebook);
			print_contact(phonebook);
		}
		else if (!command.compare("EXIT"))
			return (0);
		else
			std::cout << "Invalid command" << std::endl;
	}
	return (0);
}
