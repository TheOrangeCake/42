#include "Phonebook.hpp"
#include <iostream>

PhoneBook::PhoneBook() {
	total_contacts = 0;
}

void PhoneBook::add_contact(Contact contact) {
	int index = total_contacts % 8;
	contacts[index] = contact;
	total_contacts += 1;
}

void PhoneBook::show_contact() {
	for (int i = 0; i < total_contacts; i++) {
		Contact contact = contacts[i];
		std::cout << "print formated info here" << std::endl;
	}
}

Contact PhoneBook::search_contact(int index) {
	return (contacts[index]);
}