#ifndef COCKATOO_H
#define COCKATOO_H
#include "bird.hh"


class Cockatoo: public Bird
{
public:
    Cockatoo();
    void sing(std::ostream& output);
};

#endif // COCKATOO_H
