#ifndef ACCOUNT_HH
#define ACCOUNT_HH

#include <string>

class Account
{
public:
    // Constructor
    Account(const std::string& owner, bool has_credit = false);

    // More methods
    void print();
    void set_credit_limit(const int credit_limit);
    void save_money(const int money_saved);
    void take_money(const int money_taken);
    void transfer_to(Account& transfer_receiver, int money_transferred);

private:
    // Generates IBAN (based on running_number_ below).
    // Allows no more than 99 accounts.
    void generate_iban();

    // Used for generating IBAN.
    // Static keyword means that the value of running_number_ is the same for
    // all Account objects.
    // In other words, running_number_ is a class-wide attribute, there is
    // no own copies of it for each object of the class.
    static int running_number_;

    // More attributes/methods
    const std::string owner_;
    bool has_credit_;
    int credit_limit_;
    int balance_;
    std::string iban_;
};

#endif // ACCOUNT_HH
