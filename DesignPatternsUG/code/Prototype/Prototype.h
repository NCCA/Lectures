#ifndef PROTOTYPE_H__
#define PROTOTYPE_H__
// based on example http://en.wikipedia.org/wiki/Prototype_pattern
#include <iostream>

// Prototype
class Prototype
{
public:
    virtual ~Prototype() { }

    virtual Prototype* clone() const = 0;
};



#endif

