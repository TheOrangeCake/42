#include "Contact.hpp"
#include "PhoneBook.hpp"
#include <iomanip>
#include <iostream>
#include <limits>

void print_contact(PhoneBook phonebook) {
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
			Contact contact = phonebook.search_contact(index);
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

Contact new_contact() {
	std::string f_name;
	std::string l_name;
	std::string nickname;
	std::string phone;
	std::string secret;

	while (true)
	{
		std::cout << "Enter first name: ";
		std::getline(std::cin, f_name);
		if (f_name.empty())
			std::cout << "First name is empty" << std::endl;
		else
			break;
	}
	while (true)
	{
		std::cout << "Enter last name: ";
		std::getline(std::cin, l_name);
		if (l_name.empty())
			std::cout << "Last name is empty" << std::endl;
		else
			break;
	}
	while (true)
	{
		std::cout << "Enter nickname: ";
		std::getline(std::cin, nickname);
		if (nickname.empty())
			std::cout << "Nickname is empty" << std::endl;
		else
			break;
	}
	while (true)
	{
		std::cout << "Enter phone number: ";
		std::getline(std::cin, phone);
		if (phone.empty())
			std::cout << "Phone number is empty" << std::endl;
		else
			break;
	}
	while (true)
	{
		std::cout << "Enter your darkest secret: ";
		std::getline(std::cin, secret);
		if (secret.empty())
			std::cout << "Cmon, give me your secret" << std::endl;
		else
			break;
	}
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
			print_contact(phonebook);
		}
		else if (!command.compare("EXIT"))
			return (0);
		else
			std::cout << "Invalid command" << std::endl;
	}
	return (0);
}