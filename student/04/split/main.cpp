#include <iostream>
#include <string>
#include <vector>


// TODO: Implement split function here
// Do not change main function
std::vector<std::string> split(std::string input, char seperator, bool ignore_empty = false)
{
    std::vector<std::string> result;
    std::string tmp = input;

    while ( tmp.find(seperator) != std::string::npos )
    {
        std::string word = tmp.substr(0, tmp.find(seperator));
        tmp = tmp.substr(tmp.find(seperator) + 1, tmp.size());

        if ( not (ignore_empty and word.empty()) )
        {
            result.push_back(word);
        }
    }
    if ( not (ignore_empty and tmp.empty()) )
    {
        result.push_back(tmp);
    }

    return result;
}


int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
