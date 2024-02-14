#include <iostream>
#include <string>
#include <fstream>
#include <map>

using namespace std;

int main()
{
    map<string, int> students;

    string input_file_string;
    cout << "Input file: ";
    cin >> input_file_string;

    ifstream input_file(input_file_string);

    if(not input_file)
    {
        cout << "Error! The file " << input_file_string << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }

    cout << "Final scores:" << endl;
    string row;
    string student_name;
    int points;
    bool first_half;
    string points_string;

    while(getline(input_file, row))
    {
        student_name = "";
        points = 0;
        points_string = "";
        first_half = true;

        for(char character : row)
        {
            if(character == ':')
            {
                first_half = false;
                continue;
            }

            if(first_half)
            {
                student_name += character;
                continue;
            }

            points_string += character;
        }
        points = stoi(points_string);

        students[student_name] += points;
    }

    for(pair<string, int> student_info : students)
    {
        cout << student_info.first << ": " << student_info.second << endl;
    }


    input_file.close();
    return EXIT_SUCCESS;
}
