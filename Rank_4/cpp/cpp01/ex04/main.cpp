/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:25:23 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/08 22:08:05 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>
#include <fstream>

int	main(int ac, char **av)
{
	if (ac == 4)
	{
		std::string file_name = av[1];
		std::string s1 = av[2];
		std::string s2 = av[3];
		
		std::ifstream file(file_name.c_str());
		if (!file.is_open())
		{
			std::cerr << "Fail to open fail" <<std::endl;
			return (1);
		}
		std::ofstream new_file((file_name + ".replace").c_str());
		if (!new_file.is_open())
		{
			std::cerr << "Fail to open fail" <<std::endl;
			return (1);
		}

		std::string line;
		size_t s1_size = s1.size();
		while (std::getline(file, line))
		{
			if (av[2] != NULL && av[2][0] != '\0')
			{
				while (true)
				{
					std::size_t pos = line.find(s1);
					if (pos == std::string::npos)
						break;
					line.erase(pos, s1_size);
					line.insert(pos, s2);
				}
			}
			new_file << line << std::endl;
		}

		file.close();
		new_file.close();
	}
	else
	{
		std::cerr << "Incorrect number of argument" << std::endl;
		return (1);
	}
	return (0);
}