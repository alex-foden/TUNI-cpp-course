#include <iostream>
#include <memory>
#include "cards.hh"


Cards::Cards(): top_( nullptr ) {
}


void Cards::add(int id) {
    std::shared_ptr<Card_data> new_card 
            = std::make_shared<Card_data>(Card_data{id, top_});
    top_ = new_card;
}

void Cards::print(std::ostream& s) {
   std::shared_ptr<Card_data> to_be_printed = top_;
   int nr = 1;

   while( to_be_printed != nullptr ) {
      s << nr << ": " << to_be_printed->data << std::endl;
      to_be_printed = to_be_printed->next;
      ++nr;
   }
}

bool Cards::remove(int &id)
{
    if(top_ == nullptr)
    {
        return false;
    }

    id = top_->data;

    top_ = top_->next;

    return true;
}

void Cards::reverse()
{
    std::shared_ptr<Card_data> reversed_deck_top = nullptr;

    while(top_ != nullptr)
    {
        std::shared_ptr<Card_data> moved_card = top_;
        top_ = top_->next;

        if(reversed_deck_top == nullptr)
        {
            moved_card->next = nullptr;
            reversed_deck_top = moved_card;
        }

        else
        {
            moved_card->next = reversed_deck_top;
            reversed_deck_top = moved_card;
        }
    }

    top_ = reversed_deck_top;
}
