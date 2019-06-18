#ifndef INTVALUE_H_
#define INTVALUE_H_

#include <iostream>

class IntValue
{
  public : 
    IntValue(int _a) : m_a(_a) {}
    void square() { m_a*=m_a;}
    void print() const {std::cout<<m_a<<'\n';}
  private : 
    int m_a;
};

#endif