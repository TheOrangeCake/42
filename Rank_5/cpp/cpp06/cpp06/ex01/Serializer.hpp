/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 22:23:02 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/22 23:17:49 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERIALIZER_HPP
# define SERIALIZER_HPP
# include <string>
# include "data.hpp"
# include <stdint.h>

class Serializer {
	private:
		Serializer();
		Serializer(Serializer& copy);
		Serializer& operator =(Serializer& assign);
		~Serializer();

	public:
		static uintptr_t serialize(Data* ptr);
		static Data* deserialize(uintptr_t raw);
};

// uintptr_t: Integer type capable of holding a value converted 
// from a void pointer and then be converted back to that type
// with a value that compares equal to the original pointer.
#endif