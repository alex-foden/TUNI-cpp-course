#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void read_write_to_file(ifstream& input, ofstream& output)
{
    string row;
    int row_number = 1;

    while(getline(input, row))
    {
        output << row_number << " " << row << endl;
        row_number++;
    }

    input.close();
    output.close();
}



int main()
{
    string input_file;
    string output_file;
    cout << "Input file: ";
    cin >> input_file;
    cout << "Output file: ";
    cin >> output_file;

    ifstream input(input_file);

    if(not input)
    {
        cout << "Error! The file " << input_file << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }

    ofstream output(output_file);
    read_write_to_file(input, output);

    return EXIT_SUCCESS;
}
