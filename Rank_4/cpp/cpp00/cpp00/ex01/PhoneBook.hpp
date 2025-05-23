/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:57:33 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/07 13:57:33 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP
#include "Contact.hpp"

class PhoneBook {
	private:
		Contact contacts[8];
		int	total_contacts;
	
	public:
		PhoneBook();
		void add_contact(Contact contact);
		void show_contact();
		Contact get_contact(int index);
};

#endif