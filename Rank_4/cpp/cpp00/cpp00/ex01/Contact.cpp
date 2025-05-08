/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:57:16 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/07 13:57:18 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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