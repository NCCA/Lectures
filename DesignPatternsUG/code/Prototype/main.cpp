#include <iostream>
#include <cstdlib>
#include "Prototype.h"
int main()
{
  Prototype* prototype = new ConcretePrototype(2);
  for (int i = 1; i < 10; ++i)
  {
    ConcretePrototype* tempotype = dynamic_cast<ConcretePrototype*>(prototype->clone());
    tempotype->setX(tempotype->getX() * i);
    tempotype->printX();
    delete tempotype;
  }
  delete prototype;

  return EXIT_SUCCESS;
}
