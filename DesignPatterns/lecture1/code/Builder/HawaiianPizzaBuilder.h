#ifndef HAWAIIAN_H__
#define HAWAIIAN_H__

class HawaiianPizzaBuilder : public PizzaBuilder
{

public:
  virtual void buildDough()
  {
    m_pizza->setDough("cross");
  }
  virtual void buildSauce()
  {
    m_pizza->setSauce("mild");
  }
  virtual void buildTopping()
  {
    m_pizza->setTopping("ham+pineapple");
  }
};

#endif
