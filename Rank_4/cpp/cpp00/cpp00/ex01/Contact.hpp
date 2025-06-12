/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:57:20 by hoannguy          #+#    #+#             */
/*   Updated: 2025/06/12 22:02:23 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
#define CONTACT_HPP
#include <string>

class Contact {
	private:
		std::string f_name;
		std::string l_name;
		std::string nickname;
		std::string phone;
		std::string secret;

	public:
		Contact();
		Contact(std::string f_name, std::string l_name,
			std::string nickname, std::string phone, std::string secret);
		std::string f_name_getter();
		std::string l_name_getter();
		std::string nickname_getter();
		std::string phone_getter();
		std::string secret_getter();
};

#endif