#include "cards.hh"


Cards::Cards():
    top_(nullptr)
{

}

Card_data *Cards::get_topmost()
{
    return top_;
}

void Cards::add(int id)
{
    Card_data* new_card = new Card_data();

    new_card->data = id;
    new_card->next = top_;
    new_card->previous = nullptr;

    // If there is a top card, update it to point to the previous card in the data structure
    if(top_ != nullptr)
    {
        top_->previous = new_card;
    }

    top_ = new_card;
}

void Cards::print_from_top_to_bottom(std::ostream &s)
{
    Card_data* current_card = top_;
    int current_number = 1;

    while( current_card != nullptr)
    {
        s << current_number << ": " << current_card->data << std::endl;

        // Updating pointer to point to the next card in data structure
        current_card = current_card->next;
        current_number++;
    }
}

bool Cards::remove(int &id)
{
    // Data structure is empty
    if(top_ == nullptr)
    {
        return false;
    }

    id = top_->data;

    Card_data* removable = top_;
    top_ = top_->next;

    // If there is a top card, update it to NOT point to a nonexistent previous card
    if(top_ != nullptr)
    {
        top_->previous = nullptr;
    }

    delete removable;
    removable = nullptr;

    return true;
}

bool Cards::bottom_to_top()
{
    if(top_ == nullptr)
    {
        return false;
    }

    if(top_->next == nullptr)
    {
        return true;
    }

    // Find last card
    Card_data* bottom_card = top_;
    while(bottom_card->next != nullptr)
    {
        bottom_card = bottom_card->next;
    }

    // Find second to last card
    Card_data* new_bottom = top_;
    while(new_bottom->next != bottom_card)
    {
        new_bottom = new_bottom->next;
    }

    // Update top card and bottom card
    bottom_card->next = top_;
    bottom_card->previous = nullptr;
    top_->previous = bottom_card;
    top_ = bottom_card;
    new_bottom->next = nullptr;

    return true;
}

bool Cards::top_to_bottom()
{
    // Data structure has no cards
    if(top_ == nullptr)
    {
        return false;
    }

    // Data structure has 1 card
    if(top_->next == nullptr)
    {
        return true;
    }

    // "Find" top card
    Card_data* top_card = top_;

    // Find last card
    Card_data* bottom_card = top_;
    while(bottom_card->next != nullptr)
    {
        bottom_card = bottom_card->next;
    }

    // Update top card and bottom card
    top_ = top_->next;
    top_->previous = nullptr;
    bottom_card->next = top_card;
    top_card->next = nullptr;
    top_card->previous = bottom_card;

    return true;
}

void Cards::print_from_bottom_to_top(std::ostream &s)
{
    Card_data* current_card = top_;
    int current_number = 1;

    // Find last card in data structure
    while(current_card->next != nullptr)
    {
        current_card = current_card->next;
    }

    while( current_card != nullptr)
    {
        s << current_number << ": " << current_card->data << std::endl;

        // Updating pointer to point to the previous card in data structure
        current_card = current_card->previous;
        current_number++;
    }
}

Cards::~Cards()
{
    Card_data* current_card = top_;
    Card_data* other_cards = nullptr;

    while(current_card != nullptr)
    {
        other_cards = current_card->next;
        delete current_card;

        current_card = other_cards;
    }

    top_ = nullptr;
}
