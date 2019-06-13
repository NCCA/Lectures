#ifndef PIZZABUILDER_H__
#define PIZZABUILDER_H__

#include "Pizza.h"
// "Abstract Builder"
class PizzaBuilder
{
public:
  Pizza* getPizza()
  {
    return m_pizza;
  }
  void createNewPizzaProduct()
  {
    m_pizza = new Pizza;
  }
  virtual void buildDough() = 0;
  virtual void buildSauce() = 0;
  virtual void buildTopping() = 0;
protected:
  Pizza* m_pizza;
};

#endif
