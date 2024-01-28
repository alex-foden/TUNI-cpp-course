#include "book.hh"
#include <iostream>



Book::Book(std::string author, std::string title):
    author_(author), title_(title), loan_date_(), return_date_(), is_available_(true)
{

}

Book::~Book()
{

}

void Book::print()
{
    std::cout << author_ << " : " << title_ << std::endl;

    if (is_available_ == true)
    {
        std::cout << "- available" << std::endl;
    }

    else
    {
        std::cout << "- loaned: ";
        loan_date_.print();
        std::cout << "- to be returned: ";
        return_date_.print();
    }

}

void Book::loan(const Date& today)
{
    if (is_available_ == false)
    {
        std::cout << "Already loaned: cannot be loaned" << std::endl;
        return;
    }

    is_available_ = false;
    loan_date_ = today;
    return_date_ = today;
    return_date_.advance(28);
}

void Book::renew()
{
    if (is_available_ == true)
    {
        std::cout << "Not loaned: cannot be renewed" << std::endl;
        return;
    }

    return_date_.advance(28);
}

void Book::give_back()
{
    is_available_ = true;
}
