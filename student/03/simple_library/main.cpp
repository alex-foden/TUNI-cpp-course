#include "date.hh"
#include "book.hh"
#include <iostream>

using namespace std;

int main()
{
    // Creating a date
    Date today(5, 5, 2020);

    // Creating a book
    Book book1("Kivi", "Seitseman veljesta");
    book1.print();

    // Loaning a book
    book1.loan(today);

    // Two weeks later
    today.advance(14);

    // Trying to loan a loaned book
    book1.loan(today);
    book1.print();

    // Renewing a book
    book1.renew();
    book1.print();

    // Returning the book
    book1.give_back();

    // Trying to renew an available book
    book1.renew();
    book1.print();

    // Loaning again (two weeks later)
    book1.loan(today);
    book1.print();

    return 0;
}
