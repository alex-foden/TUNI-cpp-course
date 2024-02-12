#include "two_way_list.hh"
#include <iostream>
#include <memory>

using namespace std;

Two_way_list::Two_way_list():
    first_(nullptr),
    last_(nullptr),
    count_(0) {
}

int Two_way_list::length() const {
    return count_;
}

bool Two_way_list::has_value(int value) const {
    shared_ptr<List_item> current_ptr = first_;

    while ( current_ptr != nullptr ) {
        if ( current_ptr->data == value ) {
            return true;
        } else if ( current_ptr->data > value ) {
            return false;
        }

        current_ptr = current_ptr->next;
    }

    return false;
}

void Two_way_list::print() const {
    shared_ptr<List_item> printable_ptr = first_;

    cout << "Number of elements in the list: " << length() << endl;

    while ( printable_ptr != nullptr ) {
        cout << printable_ptr->data << " ";

        printable_ptr = printable_ptr->next;
    }

    cout << endl;
}


void Two_way_list::print_reverse() const {
    List_item* printable_ptr = last_;

    cout << "Number of elements in the list: " << length() << endl;

    while ( printable_ptr != nullptr ) {
        cout << printable_ptr->data << " ";

        printable_ptr = printable_ptr->prev;
    }

    cout << endl;
}


bool Two_way_list::remove_value(int removable_item) {
   if ( length() == 0 ) {
       return false;
   }

   shared_ptr<List_item> removable_ptr = first_;

   while ( true ) {
      if ( removable_ptr->data == removable_item ) {
         break;         // Removable value found.

      } else if ( removable_ptr->data > removable_item ) {
         return false;  // Value cannot lie in the rest of the list.

      } else if ( removable_ptr->next == nullptr ) {
         return false;  // Last element processed.

      } else {
         removable_ptr = removable_ptr->next;
      }
   }

   // At this point, we have found the removable value
   // and removable_ptr points to it.

   // Removable element is the only element of the list.
   if ( first_.get() == last_ ) {

      first_ = nullptr;
      last_ = nullptr;

   // Removable element is the first element of the list.
   } else if ( removable_ptr == first_ ) {

      first_ = first_->next;
      first_->prev = nullptr;

   // Removable element is the last element of the list.
   } else if ( removable_ptr.get() == last_ ) {

      last_ = last_->prev;
      last_->next = nullptr;

   // Removable element lies between the first and the last element.
   } else {

      removable_ptr->prev->next = removable_ptr->next;
      removable_ptr->next->prev = removable_ptr->prev;
   }

   --count_;

   return true;
}


bool Two_way_list::insert_in_numerical_order(int insertable_item) {
    shared_ptr<List_item> insertable_ptr(new List_item);

   insertable_ptr->data = insertable_item;

   // Inserting to an empty list
   if ( length() == 0 ) {

      insertable_ptr->next = nullptr;
      insertable_ptr->prev = nullptr;

      first_ = insertable_ptr;
      last_ = insertable_ptr.get();

   // Inserting to the front of the list
   } else if ( insertable_item < first_->data ) {

      insertable_ptr->next = first_;
      insertable_ptr->prev = nullptr;

      first_->prev = insertable_ptr.get();
      first_ = insertable_ptr;

   // Inserting to the back of the list
   } else if ( insertable_item > last_->data ) {

      insertable_ptr->next = nullptr;
      insertable_ptr->prev = last_;

      last_->next = insertable_ptr;
      last_ = insertable_ptr.get();

   // Inserting in the middle of the list
   } else {
      shared_ptr<List_item>
          current_ptr = first_;

      // Finding out the first element, the value of which is greater
      // or equal to insertable_item
      while ( current_ptr->data < insertable_item ) {
          current_ptr = current_ptr->next;
      }

      // The value cannot lie in the list more than once.
      if ( current_ptr->data == insertable_item ) {
          return false;
      }

      // Now current_ptr points to the first one of such elements in the list
      // that have greater value than insertable_item:
      // the new element will be inserted in the front of it.

      insertable_ptr->next = current_ptr;
      insertable_ptr->prev = current_ptr->prev;

      insertable_ptr->prev->next = insertable_ptr;
      insertable_ptr->next->prev = insertable_ptr.get();
   }

   ++count_;

   return true;
}
