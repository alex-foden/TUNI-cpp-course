#include <iostream>

using namespace std;

bool is_lower_case(const string input)
{
    for (size_t i = 0; i < input.size(); i++)
    {
        if (not islower(input.at(i)))
        {
            return false;
        }
    }
    return true;
}

bool contains_all_alphabets(const string input)
{
    for (char c = 'a'; c <= 'z'; c++)
    {
        if (input.find(c) == string::npos)
        {
            return false;
        }
    }
    return true;
}

string encrypt(const string text, const string key)
{
    string encrypted_text = "";

    for (size_t i = 0; i < text.size(); i++)
    {
        char character = text.at(i);
        uint ascii = character;

        uint position = ascii - static_cast<uint>('a');
        char encrypted_char = key.at(position);
        encrypted_text += encrypted_char;
    }

    return encrypted_text;
}

int main()
{
    cout << "Enter the encryption key: ";
    string key = "";
    getline(cin, key);


    if (key.size() < 26)
    {
        cout << "Error! The encryption key must contain 26 characters." << endl;
        return EXIT_FAILURE;
    }

    if (is_lower_case(key) == false)
    {
        cout << "Error! The encryption key must contain only lower case characters." << endl;
        return EXIT_FAILURE;
    }



    if (contains_all_alphabets(key) == false)
    {
        cout << "Error! The encryption key must contain all alphabets a-z." << endl;
        return EXIT_FAILURE;
    }

    cout << "Enter the text to be encrypted: ";
    string text = "";
    getline(cin, text);

    if (is_lower_case(text) == false)
    {
        cout << "Error! The text to be encrypted must contain only lower case characters." << endl;
        return EXIT_FAILURE;
    }

    string encrypted_text = encrypt(text, key);

    cout << "Encrypted text: " << encrypted_text << endl;



    return EXIT_SUCCESS;
}
