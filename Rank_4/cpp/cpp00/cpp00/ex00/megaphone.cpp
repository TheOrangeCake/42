/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:27:11 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/05 10:27:12 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cctype>
#include <string>

int main(int ac, char **av) 
{
	switch (ac)
	{
		case 1:
			std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
			break;
		default:
			int	i = 1;
			while (av[i] != NULL)
			{
				std::string replace = av[i];
				for (size_t j = 0; j < replace.size(); j++)
					replace[j] = (char)std::toupper((int)av[i][j]);
				std::cout << replace;
				i++;
			}
			std::cout << std::endl;
			break;
	}
	return 0;
  }