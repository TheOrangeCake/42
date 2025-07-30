/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 19:14:22 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/30 15:24:10 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"
#include <iostream>
#include <string>
#include <list>
#include <deque>
#include <vector>

template <typename T>
void initiateStack(T& stack) {
	stack.push_back(1);
	stack.push_back(2);
	stack.push_back(3);
	stack.push_back(4);
	stack.push_back(5);
}

template <typename T>
void printStack(T& stack, int type) {
	switch (type) {
		case (1):
			std::cout << "Mutant: \t[ ";
			break;
		case(2):
			std::cout << "List: \t\t[ ";
			break;
		case(3):
			std::cout << "Deque: \t\t[ ";
			break;
		case(4):
			std::cout << "Vector: \t[ ";
			break;
		default:
			std::cout << "Invalid type" << std::endl;
			return;
	}
	for (typename T::iterator it = stack.begin(); it != stack.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << "]" << std::endl;
}


int main(void) {
	{
		std::cout << "--- Compare with list, deque and vector ---" << std::endl;
		MutantStack<int>	mstack;
		std::list<int>		alist;
		std::deque<int>		adeque;
		std::vector<int>	avector;
		
		mstack.push(1);
		mstack.push(2);
		mstack.push(3);
		mstack.push(4);
		mstack.push(5);
		initiateStack(alist);
		initiateStack(adeque);
		initiateStack(avector);
		
		printStack(mstack, 1);
		printStack(alist, 2);
		printStack(adeque, 3);
		printStack(avector, 4);
		
		std::cout << std::endl;
		std::cout << "Member functions:" << std::endl;
		std::cout << "type:\ts | l | d | v" << std::endl;
		std::cout << "top:\t" << mstack.top() << " | " << alist.front() << " | "
				<< adeque.front() << " | " << avector.front() << std::endl;
		std::cout << "empty:\t" << mstack.empty() << " | " << alist.empty() << " | "
				<< adeque.empty() << " | " << avector.empty() << std::endl;
		std::cout << "size:\t" << mstack.size() << " | " << alist.size() << " | "
				<< adeque.size() << " | " << avector.size() << std::endl;
		std::cout << "pop:\t" << std::endl;
		mstack.pop();
		alist.pop_back();
		adeque.pop_back();
		avector.pop_back();
		printStack(mstack, 1);
		printStack(alist, 2);
		printStack(adeque, 3);
		printStack(avector, 4);
	}
	std::cout << std::endl;
	{
		std::cout << "--- Test iterators ---" << std::endl;
		MutantStack<std::string>	mstack;
		mstack.push("I");
		mstack.push("am");
		mstack.push("at");
		mstack.push("42");
		mstack.push("Lausanne");
		printStack(mstack, 1);

		MutantStack<std::string>::iterator it = mstack.begin();
		MutantStack<std::string>::iterator ite = mstack.end();
		std::cout << "begin():\t" << *it << std::endl;
		// std::cout << "end():\t" << *ite << std::endl;
		std::cout << "++begin():\t" << *(++it) << std::endl;
		std::cout << "--end():\t" << *(--ite) << std::endl;
	}
	std::cout << std::endl;
	{
		std::cout << "--- Test copy and assignment ---" << std::endl;
		MutantStack<std::string>	mstack1;
		mstack1.push("I");
		mstack1.push("am");
		mstack1.push("at");
		mstack1.push("42");
		mstack1.push("Lausanne");
		
		MutantStack<std::string>	mstack2(mstack1);
		MutantStack<std::string>	mstack3;
		mstack3 = mstack1;

		std::cout << "Base:\t";
		printStack(mstack1, 1);
		std::cout << "Copy:\t";
		printStack(mstack2, 1);
		std::cout << "Assign:\t";
		printStack(mstack3, 1);
	}
	{
		std::cout << "--- Test const_iterator ---" << std::endl;
		MutantStack<std::string>	mstack;
		mstack.push("I");
		mstack.push("am");
		mstack.push("at");
		mstack.push("42");
		mstack.push("Lausanne");
		MutantStack<std::string>::const_iterator it = mstack.begin();
		MutantStack<std::string>::const_iterator ite = mstack.end();
		std::cout << "begin():\t" << *it << std::endl;
		--ite;
		std::cout << "end():\t\t" << *ite << std::endl;
		std::cout << "Uncomment for compilation error" << std::endl;
		// *it = "test";
		// std::cout << "begin():\t" << *it << std::endl;
		// *ite = "another test";
		// std::cout << "end():\t" << *ite << std::endl;
	}
	return (0);
}