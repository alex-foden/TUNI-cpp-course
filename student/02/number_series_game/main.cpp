#include <iostream>


int main()
{
    std::cout << "How many numbers would you like to have? ";
    int number = 0;
    std::cin >> number;
    std::string output = "";

    for (int i = 1; i <= number; i++)
    {
        if (i % 3 == 0 and i % 7 == 0) {output = "zip boing";}

        else if (i % 3 == 0) {output = "zip";}

        else if (i % 7 == 0) {output = "boing";}

        else {output = std::to_string(i);}

        std::cout << output << std::endl;
    }

    return EXIT_SUCCESS;
}
