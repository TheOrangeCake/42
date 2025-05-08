/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:57:30 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/07 13:57:30 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
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

Contact PhoneBook::get_contact(int index) {
	return (contacts[index]);
}