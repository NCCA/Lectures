#ifndef SPICY_H__
#define SPICY_H__

class SpicyPizzaBuilder : public PizzaBuilder
{

public:
  virtual void buildDough()
  {
    m_pizza->setDough("pan baked");
  }
  virtual void buildSauce()
  {
    m_pizza->setSauce("hot");
  }
  virtual void buildTopping()
  {
    m_pizza->setTopping("pepperoni+salami");
  }
};

#endif
