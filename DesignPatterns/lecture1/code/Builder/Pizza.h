#ifndef PIZZA_H__
#define PIZZA_H__
#include <string>
#include <iostream>
// in terms of the pattern this is the "product"
// "Product"
class Pizza
{
  public:
  void setDough(const std::string &_dough)
  {
        m_dough = _dough;
  }
  void setSauce(const std::string &_sauce)
  {
        m_sauce = _sauce;
  }
  void setTopping(const std::string &_topping)
  {
        m_topping = _topping;
  }
  void open() const
  {
        std::cout << "Pizza with " << m_dough << " dough, " << m_sauce << " sauce and "
        << m_topping << " topping. \n";
  }
  private:
    std::string m_dough;
    std::string m_sauce;
    std::string m_topping;
};


#endif
