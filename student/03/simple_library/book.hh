#ifndef BOOK_HH
#define BOOK_HH

#include "date.hh"
#include <string>


class Book
{
    public:
        Book(std::string author, std::string title);
        ~Book();

        void print();
        void loan(const Date& today);
        void renew();
        void give_back();


    private:
        std::string author_;
        std::string title_;
        Date loan_date_;
        Date return_date_;
        bool is_available_;
};

#endif // BOOK_HH
