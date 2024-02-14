#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>


using namespace std;

int main()
{
    map<string, vector<int>> wordcount;

    string input_file_string = "";
    cout << "Input file: ";
    cin >> input_file_string;

    ifstream input_file(input_file_string);
    if(not input_file)
    {
        cout << "Error! The file " << input_file_string << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }


    string row;
    int row_number = 1;
    vector<string> row_check;
    while(getline(input_file, row))
    {
        istringstream iss(row);
        vector<std::string> sentence;
        string token;

        while (std::getline(iss, token, ' ')) {
            sentence.push_back(token);
        }

        for(string word : sentence)
        {
            if(find(row_check.begin(), row_check.end(), word) == row_check.end())
            {
                wordcount[word].push_back(row_number);
            }

        }

        row_number++;
        row_check.clear();
    }


    for(pair<string, vector<int>> word : wordcount)
    {
        cout << word.first << " " << word.second.size() << ": ";
        for(int row : word.second)
        {
            if(row != word.second.back())
            {
                cout << row << ", ";
                continue;
            }
            cout << row;

        }
        cout << endl;
    }
    return EXIT_SUCCESS;
}
