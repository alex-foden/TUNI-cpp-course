#include "student.hh"
#include "date.hh"
#include <iostream>

using namespace std;

int main()
{
    Student stud1("Teemu Teekkari", Date(1, 1, 2000));
    stud1.start_studies(Date(21, 8, 2023));
    stud1.complete_course(5);
    stud1.print();

    Student stud2("Aatu Arkkari", Date(31, 12, 1999));
    stud2.start_studies(Date(28, 8, 2023));

    if(stud1.older_than(stud2))
    {
        cout << "Teemu is older than Aatu" << endl;
    }
    else
    {
        cout << "Aatu is older than Teemu" << endl;
    }

    if(stud1.studied_longer_than(stud2))
    {
        cout << "Teemu has studied longer than Aatu" << endl;
    }
    else
    {
        cout << "Aatu has studied longer than Teemu" << endl;
    }

    return 0;
}
