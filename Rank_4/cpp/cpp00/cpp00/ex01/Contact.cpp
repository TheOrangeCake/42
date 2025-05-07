#include "Contact.hpp"

Contact::Contact() {

}

Contact::Contact(std::string f_name, std::string l_name,
	std::string nickname, std::string phone, std::string secret) {
	this->f_name = f_name;
	this->l_name = l_name;
	this->nickname = nickname;
	this->phone = phone;
	this->secret = secret;
}

std::string Contact::f_name_getter() {
	return (this->f_name);
}

std::string Contact::l_name_getter() {
	return (this->l_name);
}

std::string Contact::nickname_getter() {
	return (this->nickname);
}

std::string Contact::phone_getter() {
	return (this->phone);
}

std::string Contact::secret_getter() {
	return (this->secret);
}