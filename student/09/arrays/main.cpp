#include "array_operations.hh"
#include <iostream>
#include <algorithm>

using namespace std;

const int ITEM_NUMBER = 30;

int main() {

    // Declaring an array with 30 elements, which begins with 4 non-zero values,
    // and the rest of the values are zero.
    int array[ITEM_NUMBER] = { 1, 3, 6, 9 };

    // Example on how to apply algorithm library to a C array
    sort(array, array + ITEM_NUMBER);

    for(int* position = array; position < array + ITEM_NUMBER; ++position){
        cout << *position << " ";
    }
    cout << endl;

    // point a
    cout << greatest_v1(array, ITEM_NUMBER) << endl;
    cout << greatest_v2(array, array + ITEM_NUMBER) << endl;

    // point b
    int target_array[ITEM_NUMBER];
    copy(array, array + ITEM_NUMBER, target_array);

    for(int* position = target_array; position < target_array + ITEM_NUMBER; ++position){
        cout << *position << " ";
    }
    cout << endl;

    // point c
    reverse(array, array + ITEM_NUMBER);

    for(int* position = array; position < array + ITEM_NUMBER; ++position){
        cout << *position << " ";
    }
    cout << endl;
}
