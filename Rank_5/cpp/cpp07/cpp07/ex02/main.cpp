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
    std::cout << "--- Test modify values ---" << std::endl;
    for (int i = 0; i < MAX_VAL; i++)
    {
        std::cout << numbers[i] << "\t";
        value += "1";
        numbers[i] = value;
        std::cout << numbers[i] << "\t" << mirror[i] << std::endl;
    }
    delete [] mirror;//
    return 0;
}

// int main(int, char**)
// {
//     std::cout << "--- Test default constructor ---" << std::endl;
//     Array<int> a;
//     std::cout <<"Size: " << a.size() << std::endl << std::endl;

//     Array<int> numbers(MAX_VAL);
//     int* mirror = new int[MAX_VAL];
//     srand(time(NULL));
//     for (int i = 0; i < MAX_VAL; i++)
//     {
//         const int value = rand();
//         numbers[i] = value;
//         mirror[i] = value;
//     }
//     std::cout << "--- Test parameter constructor ---" << std::endl;
//     for (int i = 0; i < MAX_VAL; i++)
//     {
//         std::cout << mirror[i] << "\t" << numbers[i] << std::endl;
//         if (mirror[i] != numbers[i])
//         {
//             std::cerr << "didn't save the same value!!" << std::endl;
//             return 1;
//         }
//     }
//     std::cout << std::endl;
//     //SCOPE
//     {
//         std::cout << "--- Test assign and copy constructor ---" << std::endl;
//         Array<int> tmp = numbers;
//         Array<int> test(tmp);
//         for (int i = 0; i < MAX_VAL; i++)
//         {
//             std::cout << test[i] << "\t" << tmp[i] << std::endl;
//         }
//     }
//     std::cout << std::endl;
//     try
//     {
//         std::cout << "--- Test exception lower bound ---" << std::endl;
//         numbers[-2] = 0;
//     }
//     catch(const std::exception& e)
//     {
//         std::cerr << e.what() << '\n';
//     }
//     std::cout << std::endl;
//     try
//     {
//         std::cout << "--- Test exception upper bound ---" << std::endl;
//         numbers[MAX_VAL] = 0;
//     }
//     catch(const std::exception& e)
//     {
//         std::cerr << e.what() << '\n';
//     }

//     std::cout << std::endl;
//     std::cout << "--- Test modify values ---" << std::endl;
//     for (int i = 0; i < MAX_VAL; i++)
//     {
//         std::cout << numbers[i] << "\t";
//         numbers[i] = rand();
//         std::cout << numbers[i] << "\t" << mirror[i] << std::endl;
//     }
//     delete [] mirror;//
//     return 0;
// }
