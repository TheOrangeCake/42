#include <iostream>
#include "Array.hpp"
#include "cstdlib"
#include <string>

#define MAX_VAL 5
int main(int, char**)
{
    std::cout << "--- Test default constructor ---" << std::endl;
    Array<std::string> a;
    std::cout <<"Size: " << a.size() << std::endl << std::endl;

    Array<std::string> numbers(MAX_VAL);
    std::string* mirror = new std::string[MAX_VAL];
    std::string value = "ab";
    for (int i = 0; i < MAX_VAL; i++)
    {
        value += "1";
        numbers[i] = value;
        mirror[i] = value;
    }
    std::cout << "--- Test parameter constructor ---" << std::endl;
    std::cout << "base\tmirror" << std::endl;
    for (int i = 0; i < MAX_VAL; i++)
    {
        std::cout << mirror[i] << "\t" << numbers[i] << std::endl;
        if (mirror[i] != numbers[i])
        {
            std::cerr << "didn't save the same value!!" << std::endl;
            return 1;
        }
    }
    std::cout << std::endl;
    //SCOPE
    {
        std::cout << "--- Test assign and copy constructor ---" << std::endl;
        Array<std::string> tmp = numbers;
        Array<std::string> test(tmp);
        std::cout << "base\tmirror" << std::endl;
        for (int i = 0; i < MAX_VAL; i++)
        {
            std::cout << test[i] << "\t" << tmp[i] << std::endl;
        }
    }
    std::cout << std::endl;
    try
    {
        std::cout << "--- Test exception lower bound ---" << std::endl;
        numbers[-2] = "test";
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    std::cout << std::endl;
    try
    {
        std::cout << "--- Test exception upper bound ---" << std::endl;
        numbers[MAX_VAL] = "test";
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cout << std::endl;
    std::cout << "--- Test modify values non const ---" << std::endl;
    std::cout << "base\tchange\t\tmirror" << std::endl;
    for (int i = 0; i < MAX_VAL; i++)
    {
        std::cout << numbers[i] << "\t";
        value += "2";
        numbers[i] = value;
        std::cout << numbers[i] << "\t" << mirror[i] << std::endl;
    }

    std::cout << std::endl;
    std::cout << "--- Test modify values const ---" << std::endl;
    const Array<std::string> test = numbers;
    std::cout << "Read: " << test[0] << std::endl;
    std::cout << "Write: uncomment main for compilation error" << std::endl;
    // test[0] = "test";
    // std::cout << "Test: " << test[0] << std::endl;
    delete [] mirror;
    return 0;
}
