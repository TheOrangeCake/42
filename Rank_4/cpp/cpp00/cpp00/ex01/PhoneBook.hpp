#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP
#include "Contact.hpp"

class PhoneBook {
	public:
		Contact contacts[8];
		int	total_contacts;
	
	public:
		PhoneBook();
		void add_contact(Contact contact);
		void show_contact();
		Contact get_contact(int index);
};

#endif