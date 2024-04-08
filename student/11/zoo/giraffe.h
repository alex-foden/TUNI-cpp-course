#ifndef GIRAFFE_H
#define GIRAFFE_H
#include "mammal.h"


class Giraffe: public Mammal
{
public:
    Giraffe();
    void make_noise(std::ostream& output);
};

#endif // GIRAFFE_H
