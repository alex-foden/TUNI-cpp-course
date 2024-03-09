#include "list.hh"
#include <iostream>
#include <string>

using namespace std;

List::List(): first_(nullptr), last_(nullptr) {
}

List::~List() {
   while ( first_ != nullptr ) {
      List_item* item_to_be_released = first_;
      first_ = first_->next;

      delete item_to_be_released;
   }
}

void List::print() const {
   List_item* item_to_be_printed = first_;
   int running_number = 1;

   while ( item_to_be_printed != nullptr ) {
      cout << running_number << ". " << item_to_be_printed->task << endl;
      ++running_number;
      item_to_be_printed = item_to_be_printed->next;
   }
}

void List::add_back(const string& task_to_be_added) {
   List_item* new_item = new List_item{task_to_be_added, nullptr};

   if ( first_ == nullptr ) {
      first_ = new_item;
      last_ = new_item;
   } else {
      last_->next = new_item;
      last_ = new_item;
   }
}

bool List::remove_front(string& removed_task) {
   if ( is_empty() ) {
      return false;
   }

   List_item* item_to_be_removed = first_;

   removed_task = item_to_be_removed->task;

   if ( first_ == last_ ) {
      first_ = nullptr;
      last_ = nullptr;
   } else {
      first_ = first_->next;
   }

   delete item_to_be_removed;

   return true;
}

bool List::is_empty() const {
   if ( first_ == nullptr ) {
      return true;
   } else {
      return false;
   }
}
