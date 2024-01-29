#include "account.hh"
#include <iostream>

Account::Account(const std::string& owner, bool has_credit):
    owner_(owner), has_credit_(has_credit)
{
    generate_iban();
}

void Account::print()
{
    std::cout << owner_ << " : " << iban_ << " : " << balance_ << std::endl;
}

void Account::set_credit_limit(const int credit_limit)
{
    if (has_credit_ == false)
    {
        std::cout << "Cannot set credit limit: the account has no credit card" << std::endl;
    }

    else
    {
        credit_limit_ = credit_limit;
    }
}

void Account::save_money(const int money_saved)
{
    balance_ += money_saved;
}

void Account::take_money(const int money_taken)
{
    if (has_credit_ == false)
    {
        if (money_taken > balance_)
        {
            std::cout << "Cannot take money: balance underflow" << std::endl;
        }

        else
        {
            balance_ -= money_taken;
            std::cout << money_taken << " euros taken: new balance of " <<
                         iban_ << " is " << balance_ << " euros" << std::endl;
        }
    }


    else
    {
        if (balance_ - money_taken < credit_limit_ * -1)
        {
            std::cout << "Cannot take money: credit limit underflow" << std::endl;
        }

        else
        {
            balance_ -= money_taken;
            std::cout << money_taken << " euros taken: new balance of " <<
                         iban_ << " is " << balance_ << " euros" << std::endl;
        }
    }
}

void Account::transfer_to(Account& transfer_receiver, int money_transferred)
{
    if (has_credit_ == false)
    {
        if (money_transferred > balance_)
        {
            std::cout << "Cannot take money: balance underflow" << std::endl;
            std::cout << "Transfer from " << iban_ << " failed" << std::endl;
        }

        else
        {
            balance_ -= money_transferred;
            transfer_receiver.balance_ += money_transferred;
            std::cout << money_transferred << " euros taken: new balance of " <<
                         iban_ << " is " << balance_ << " euros" << std::endl;
        }
    }


    else
    {
        if (balance_ - money_transferred < credit_limit_ * -1)
        {
            std::cout << "Cannot take money: credit limit underflow" << std::endl;
            std::cout << "Transfer from " << iban_ << " failed" << std::endl;
        }

        else
        {
            balance_ -= money_transferred;
            transfer_receiver.balance_ += money_transferred;
            std::cout << money_transferred << " euros taken: new balance of " <<
                         iban_ << " is " << balance_ << " euros" << std::endl;
        }
    }
}



// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}
