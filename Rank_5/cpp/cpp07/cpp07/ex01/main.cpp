/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 11:38:26 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/30 14:40:13 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iter.hpp"
#include <iostream>
#include <string>

// class Awesome
// {
//   public:
//     Awesome( void ) : _n( 42 ) { return; }
//     int get( void ) const { return this->_n; }
//   private:
//     int _n;
// };

// std::ostream & operator<<( std::ostream & o, Awesome const & rhs )
// {
//   o << rhs.get();
//   return o;
// }

template< typename T >
void print( T& x )
{
  std::cout << x << std::endl;
  return;
}

// int main() {
// 	int tab[] = { 0, 1, 2, 3, 4 };
// 	Awesome tab2[5];

// 	iter( tab, 5, print<const int> );
// 	iter( tab2, 5, print<Awesome> );

// 	return 0;
// }

void add_5(int& a) {
	a += 5;
}

void add_5(float& a) {
	a += 5;
}

int main(void) {
	{
		std::cout << "--- Case 1: print array function TEMPLATE ---" << std::endl;
		std::cout << "test 1: char array:" << std::endl;
		char arr1[4] = {'c', 'h', 'a', 'r'};
		size_t size1 = 4;
		iter(arr1, size1, print);
		std::cout << std::endl;

		std::cout << "test 2: int array:" << std::endl;
		int arr2[3] = {1, 3, 5};
		int size2 = 3;
		iter(arr2, size2, print<const long>);
		std::cout << std::endl;

		std::cout << "test 3: string array:" << std::endl;
		std::string arr3[4] = {"This", "is", "42", "Lausanne"};
		float size3 = 4.7f;
		iter(arr3, size3, print);
		std::cout << std::endl;
	}
	{
		std::cout << std::endl;
		std::cout << "--- Case 2: add 5 function ---" << std::endl;
		std::cout << "test 1: int array:" << std::endl;
		int arr1[3] = {1, 3, 5};
		double size1 = 3.523423;
		iter(arr1, size1, add_5);
		for (int i = 0; i < 3; i++) {
			std::cout << arr1[i] << std::endl;
		}
		std::cout << std::endl;

		std::cout << "test 2: float array:" << std::endl;
		float arr2[3] = {4.5f, 3.8f, 10.2f};
		long size2 = 3;
		iter(arr2, size2, add_5);
		for (int i = 0; i < 3; i++) {
			std::cout << arr2[i] << std::endl;
		}
		std::cout << std::endl;
	}
}
