#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using Network = std::map<std::string, std::vector<std::string>>;

const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";


std::vector<std::string> split(const std::string& s,
                               const char delimiter,
                               bool ignore_empty = false)
{
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

void store(Network& network, std::string& parent, std::string& child)
{
    if(network.find(parent) == network.end())
    {
        network[parent] = {};
    }

    if(find(network.at(parent).begin(), network.at(parent).end(), child) != network.at(parent).end())
    {
        return;
    }

    network[parent].push_back(child);
}

void print(const Network& network, std::string& id, int indent = 0)
{
    for(int i = 0; i < indent; i++)
    {
        std::cout << "..";
    }

    std::cout << id << std::endl;

    if(network.find(id) != network.end())
    {
        for(std::string child : network.at(id))
        {
            print(network, child, indent + 1);
        }
    }
}

int count(Network& network, std::string& id)
{
    int size = 0;

    if(network.find(id) != network.end())
    {
        for(std::string child : network.at(id))
        {
            ++size;
            size += count(network, child);
        }
    }

    return size;
}


int main()
{
    Network network;


    while(true)
    {
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        // Allowing empty inputs
        if(parts.size() == 0)
        {
            continue;
        }

        std::string command = parts.at(0);

        if(command == "S" or command == "s")
        {
            if(parts.size() != 3)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            store(network, id1, id2);

        }
        else if(command == "P" or command == "p")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            print(network, id);

        }
        else if(command == "C" or command == "c")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            std::cout << count(network, id) << std::endl;

        }
        else if(command == "D" or command == "d")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

        }
        else if(command == "Q" or command == "q")
        {
           return EXIT_SUCCESS;
        }
        else
        {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
