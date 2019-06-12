#ifndef COOK_H__
#define COOK_H__
class Cook
{
  public:
    void setPizzaBuilder(PizzaBuilder* pb)
    {
      m_pizzaBuilder = pb;
    }
    Pizza* getPizza()
    {
      return m_pizzaBuilder->getPizza();
    }
    void constructPizza()
    {
      m_pizzaBuilder->createNewPizzaProduct();
      m_pizzaBuilder->buildDough();
      m_pizzaBuilder->buildSauce();
      m_pizzaBuilder->buildTopping();
    }
  private:
    PizzaBuilder* m_pizzaBuilder;
};

#endif
