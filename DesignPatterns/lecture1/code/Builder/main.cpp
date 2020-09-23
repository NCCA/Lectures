#include "PizzaBuilder.h"
#include "Cook.h"
#include "HawaiianPizzaBuilder.h"
#include "SpicyPizzaBuilder.h"
int main()
{
  Cook cook;
  PizzaBuilder* hawaiianPizzaBuilder = new HawaiianPizzaBuilder;
  PizzaBuilder* spicyPizzaBuilder   = new SpicyPizzaBuilder;

  cook.setPizzaBuilder(hawaiianPizzaBuilder);
  cook.constructPizza();

  Pizza* hawaiian = cook.getPizza();
  hawaiian->open();

  cook.setPizzaBuilder(spicyPizzaBuilder);
  cook.constructPizza();

  Pizza* spicy = cook.getPizza();
  spicy->open();

  delete hawaiianPizzaBuilder;
  delete spicyPizzaBuilder;
  delete hawaiian;
  delete spicy;
}
