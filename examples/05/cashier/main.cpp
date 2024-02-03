#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <iomanip>

using namespace std;

const string QUIT = "-";

// Forward declarations
void print_pricelist(const map<string, double>& prices);
void print_receipt(const map<string, double>& prices,
                    const map<string, int>& basket);


int main() {
    // first: product, second: price
    map<string, double> pricelist = {
        { "milk",      1.05 },
        { "cheese",    4.95 },
        { "glue",      3.65 },
        { "pepper",    2.10 },
        { "cream",     1.65 },
        { "chocolate", 2.00 },
    };

    print_pricelist(pricelist);

    // Reading the shopping basket should probably be
    // implemented as a function.
    map<string, int> shopping_basket;
    while ( true ) {
        cout << "Please input product name (or '-' to end): ";
        string product_name = "";
        getline(cin, product_name);

        if ( product_name == QUIT ) {
            break;
        }

        map<string, double>::iterator product_iter;
        product_iter = pricelist.find(product_name);
        if ( product_iter == pricelist.end() ) {
            cout << "Unknown product name!" << endl;
            continue;
        }

        // first: product, second: quantity
        map<string, int>::iterator basket_iter;
        basket_iter = shopping_basket.find(product_name);
        if ( basket_iter == shopping_basket.end() ) {
            shopping_basket.insert({ product_name, 1 });
            // Or alternatively:
            // shopping_basket[product_name] = 1;
        } else {
            ++shopping_basket.at(product_name);
        }
    }

    print_receipt(pricelist, shopping_basket);

    return EXIT_SUCCESS;
}

void print_pricelist(const map<string, double>& prices) {
    cout << "Pricelist:" << endl;
    // first: product  second: price
    for ( auto product : prices ) {
        cout << left << setw(10)
             << product.first
             << right << setprecision(2) << fixed
             << product.second << endl;
    }
}

void print_receipt(const map<string, double>& prices,
                    const map<string, int>& basket) {
    double total_price = 0.0;

    cout << "Receipt:" << endl;

    // prices:  first: product  second: price
    // basket:  first: product  second: quantity
    for ( auto item : basket ) {
        double item_price = item.second * prices.at(item.first);
        cout << left << setw(3) << item.second
             << left << setw(10)
             << item.first
             << right << setprecision(2) << fixed
             << item_price
             << endl;
        total_price += item_price;
    }

    cout << "Total price: "
         << setprecision(2) << fixed
         << total_price << endl;
}
