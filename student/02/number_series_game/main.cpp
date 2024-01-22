#include <iostream>


int main()
{
    std::cout << "How many numbers would you like to have? ";
    int number = 0;
    std::cin >> number;

    for (int i = 1; i <= number; i++)
    {
        if (i % 3 == 0) {std::cout << "zip" << std::endl;}

        else {std::cout << i << std::endl;}

    }

    return EXIT_SUCCESS;
}
