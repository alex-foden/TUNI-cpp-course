#include <cstdlib>
#include <iostream>

void swap(int& integer1, int& integer2)
{
    int helper_variable = integer1;
    integer1 = integer2;
    integer2 = helper_variable;
}



#ifndef UNIT_TESTING
int main()
{
    std::cout << "Enter an integer: ";
    int i = 0;
    std::cin >> i;

    std::cout << "Enter another integer: ";
    int j = 0;
    std::cin >> j;

    swap(i, j);
    std::cout << "The integers are " << i << " and " << j << std::endl;

    return EXIT_SUCCESS;
}
#endif
