#include "two_way_list.hh"
#include <cstdlib>

// Main function with non-covering tests
int main() {
    Two_way_list test_list;

    test_list.print();
    test_list.insert_in_numerical_order(5);  test_list.print();
    test_list.insert_in_numerical_order(2);  test_list.print();
    test_list.insert_in_numerical_order(8);  test_list.print();
    test_list.insert_in_numerical_order(0);  test_list.print();
    test_list.insert_in_numerical_order(10); test_list.print();

    test_list.insert_in_numerical_order(10); test_list.print();
    test_list.insert_in_numerical_order(0);  test_list.print();

    test_list.insert_in_numerical_order(4);  test_list.print();
    test_list.insert_in_numerical_order(6);  test_list.print();
    test_list.insert_in_numerical_order(1);  test_list.print();
    test_list.insert_in_numerical_order(9);  test_list.print();
    test_list.insert_in_numerical_order(1);  test_list.print();
    test_list.insert_in_numerical_order(9);  test_list.print();

    test_list.print_reverse();

    test_list.remove_value(1);  test_list.print();
    test_list.remove_value(9);  test_list.print();
    test_list.remove_value(0);  test_list.print();
    test_list.remove_value(10); test_list.print();
    test_list.remove_value(5);  test_list.print();

    return EXIT_SUCCESS;
}
