#ifndef CARDS_HH
#define CARDS_HH

#include <iostream>

struct Card_data {
  int data;
  Card_data* next;
};

class Cards {

    public:
      // A dynamic structure must have a constructor
      // that initializes the top item as nullptr.
      Cards();

      // Get the topmost card for testing.
      // Note: Usually allowing such access to the inner mechanisms ( through non-const pointer )
      // of the class is against many programming principles. It is now too,
      // but also required for complete tests.
      Card_data* get_topmost();

      // Adds a new card with the given id as the topmost element.
      void add(int id);

      // Prints the content of the data structure with ordinal numbers to the
      // output stream given as a parameter starting from the first element.
      void print_from_top_to_bottom(std::ostream& s);

      // Removes the topmost card and passes it in the reference parameter id to the caller.
      // Returns false, if the data structure is empty, otherwise returns true.
      bool remove(int& id);

      // Moves the last element of the data structure as the first one.
      // Returns false, if the data structure is empty, otherwise returns true.
      bool bottom_to_top();

      // Moves the first element of the data structure as the last one.
      // Returns false, if the data structure is empty, otherwise returns true.
      bool top_to_bottom();

      // Prints the content of the data structure with ordinal numbers to the
      // output stream given as a parameter starting from the last element.
      void print_from_bottom_to_top(std::ostream& s);

      // A dynamic data structure must have a destructor
      // that can be called to deallocate memory,
      // when the data structure is not needed any more.
      ~Cards();

    private:
      Card_data* top_;

      // You can use the function below in the implementation of
      // the method print_from_bottom_to_top.
      int recursive_print(Card_data* top, std::ostream& s);
};

#endif // CARDS_HH
