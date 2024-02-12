#ifndef CARDS_HH
#define CARDS_HH

#include <iostream>
#include <memory>


  struct Card_data {
    int data;
    std::shared_ptr<Card_data> next;
  };


class Cards {

    public:
      // A dynamic structure must have a constructor
      // that initializes the top item as nullptr.
      Cards();

      // Adds a new card with the given id as the topmost element.
      void add(int id);

      // Prints the content of the data structure with ordinal numbers to the
      // output stream given as a parameter starting from the first element.
      void print(std::ostream& s);

      // Removes the topmost card and passes it in the reference parameter id to the caller.
      // Returns false, if the data structure is empty, otherwise returns true.
      bool remove(int& id);

      // Reverses the content of the data structure as opposite.
      void reverse();

    private:
      std::shared_ptr<Card_data> top_;
};

#endif // CARDS_HH
