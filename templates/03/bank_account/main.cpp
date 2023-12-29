#include "account.hh"
#include <iostream>
#include <string>

using namespace std;

// Prints three accounts given as parameters.
// If we knew containers, we could use one to store accounts in it,
// and print the content of the container.
// In this way, we could print any number of accounts.
void print_three_accounts(const Account& a1, const Account& a2, const Account& a3)
{
    cout << endl;
    cout << "Printing all three accounts:" << endl;
    a1.print();
    a2.print();
    a3.print();
    cout << endl;
}

int main()
{
    cout << "1: Creating three accounts" << endl;
    Account current_account("Tupu");
    Account savings_account ("Hupu");
    Account credit_card_account("Lupu", true);

    // Setting credit limit for a credit card account
    credit_card_account.set_credit_limit(100);

    // Trying to set credit limit for a non-credit card account
    current_account.set_credit_limit(100);

    // Saving money in all three accounts
    current_account.save_money(100);
    savings_account.save_money(200);
    credit_card_account.save_money(300);

    print_three_accounts(current_account, savings_account, credit_card_account);

    cout << "2: Taking money succesfully:" << endl;
    current_account.take_money(50);
    print_three_accounts(current_account, savings_account, credit_card_account);

    cout << "3: Taking money unsuccesfully:" << endl;
    current_account.take_money(100);
    print_three_accounts(current_account, savings_account, credit_card_account);

    cout << "4: Taking money succesfully from a credit card account:" << endl;
    credit_card_account.take_money(310);
    print_three_accounts(current_account, savings_account, credit_card_account);

    cout << "5: Taking money unsuccesfully from a credit card account:" << endl;
    credit_card_account.take_money(100);
    print_three_accounts(current_account, savings_account, credit_card_account);

    cout << "6: Transferring money succesfully: " << endl;
    savings_account.transfer_to(credit_card_account, 50);
    print_three_accounts(current_account, savings_account, credit_card_account);

    cout << "7: Transferring money unsuccesfully: " << endl;
    savings_account.transfer_to(current_account, 200);
    print_three_accounts(current_account, savings_account, credit_card_account);

    cout << "8: Transferring money succesfully from a credit card account:" << endl;
    credit_card_account.transfer_to(savings_account, 60);
    print_three_accounts(current_account, savings_account, credit_card_account);

    cout << "9: Transferring money unsuccesfully from a credit card account:" << endl;
    credit_card_account.transfer_to(savings_account, 100);
    print_three_accounts(current_account, savings_account, credit_card_account);

    return 0;
}
