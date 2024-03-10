#include <iostream>
#include "queue.hh"

// Implement the member functions of Queue here

Queue::Queue(unsigned int cycle):
    cycle_(cycle)
{

}

Queue::~Queue()
{
    Vehicle* current_car = first_;
    Vehicle* other_cars = nullptr;

    while(current_car != nullptr)
    {
        other_cars = current_car->next;
        delete current_car;

        current_car = other_cars;
    }

    first_ = nullptr;
    last_ = nullptr;
}

void Queue::enqueue(const string &reg)
{
    if(is_green_ == true)
    {
        std::cout << "GREEN: The vehicle " << reg << " need not stop to wait" << std::endl;
        return;
    }

    Vehicle* new_car = new Vehicle();

    new_car->reg_num = reg;
    new_car->next = nullptr;

    if(first_ == nullptr)
    {
        first_ = new_car;
        last_ = new_car;
        return;
    }

    if(last_ != nullptr)
    {
        last_->next = new_car;
        last_ = new_car;
    }
}

void Queue::switch_light()
{
    if(is_green_ == false)
    {
        is_green_ = true;
        print();

        if(first_ != nullptr)
        {
            for(unsigned int cycle = 1; cycle <= cycle_; cycle++)
            {
                dequeue_();
            }

            is_green_ = false;
            return;
        }

        return;
    }

    if(is_green_ == true)
    {
        is_green_ = false;

        print();
    }
}

void Queue::reset_cycle(unsigned int cycle)
{
    cycle_ = cycle;
}

void Queue::print() const
{
    string light;
    Vehicle* current_car = first_;

    if(is_green_ == true)
    {
        if(first_ == nullptr)
        {
            std::cout << "GREEN: No vehicles waiting in traffic lights" << std::endl;
            return;
        }

        std::cout << "GREEN: Vehicle(s) ";

        unsigned int cycle = 1;

        while(current_car != nullptr and cycle <= cycle_)
        {
            std::cout << current_car->reg_num << " ";
            cycle++;
            current_car = current_car->next;
        }

        std::cout << "can go on" << std::endl;
    }

    if(is_green_ == false)
    {
        if(first_ == nullptr)
        {
            std::cout << "RED: No vehicles waiting in traffic lights" << std::endl;
            return;
        }

        std::cout << "RED: Vehicle(s) ";

        while(current_car != nullptr)
        {
            std::cout << current_car->reg_num << " ";
            current_car = current_car->next;
        }

        std::cout << "waiting in traffic lights" << std::endl;
    }
}

void Queue::dequeue_()
{
    if(is_green_ == false)
    {
        return;
    }

    if(first_ == nullptr)
    {
        return;
    }

    if(first_->next == nullptr)
    {
        delete first_;
        first_ = nullptr;
        return;
    }

    Vehicle* first_car = first_;
    first_ = first_->next;
    delete first_car;
    first_car = nullptr;
}
