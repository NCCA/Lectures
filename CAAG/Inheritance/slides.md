# Inheritance
### *from generalisation to specialisation*
Jon Macey

jmacey@bournemouth.ac.uk

---


## Introduction

- We have seen previously that we can combine objects together using composition and aggregation 
  - this means that we create a new object by combining other objects
- Inheritance differs from composition  as it involves creating new objects by inheriting the attributes and behaviors of other objects and then extending or specialising them.

--

## Terminology

<div>
<pre>
<code class="language-plantuml">
  @startuml
  Title A class hierarchy using inheritance

  SuperClass <|-- Subclass

  Parent <|-- Child
  Parent <|-- Derived
  Parent <|-- SubClass 
  SubClass <|-- Specialisation1
  SubClass <|-- Specialisation2
  SubClass <|-- Specialisation3


  @enduml
</code>
</pre>
</div>

- The inheritance hierarchy goes from generalisation at the top to a series of specialisations at the bottom.


--

## Inheritance 

- Inheritance allows the programmer to define a class in terms of another class
  - in effect we extend from the base class to create a new one.
- The supposed benefit of this is that it makes it easier to create and maintain code
  - However overuse of inheritance can lead to problems
- The idea of inheritance is we implement the [**is - a**](https://www.w3resource.com/java-tutorial/inheritance-composition-relationship.php) relationship as apposed to the **has - a** relationship.

---

## Inheritance in C++

- in C++ we use [*access specifiers*](https://en.cppreference.com/w/cpp/language/access) to define the accessibility of all members following

- ```public :``` members declared after the access specifier have public member access

- ```protected :``` members declared after the access specifier have protected member access

- ```private :``` members declared after the access specifier have private member access

--


# A Shape Class
<pre>
<code class="language-plantuml">
@startuml
skinparam classAttributeIconSize 0
class Shape {
 # m_width : float
 # m_height : float
 +  Shape()=default 
 +  Shape(const Shape &)=default 
 + ~Shape()=default 
 + setWidth(_w : float)
 + setHeight(_h : float)
 + width() : float
 + height() : float
 
}

@enduml
</code>
</pre>

- a simple Shape class, notice the attributes are marked as ```protected```

--


## [Shape.h](https://github.com/NCCA/CFGAA/blob/master/Lecture6Inheritance/Shape/include/Shape.h)


```
#ifndef SHAPE_H_
#define SHAPE_H_

class Shape
{
  public :
    Shape()=default;
    Shape(const Shape &)=default;
    ~Shape()=default;
    void setWidth(float _w);
    void setHeight(float _h);
    float width() const;
    float height() const;
  protected:
    float m_width=0.0f;
    float m_height=0.0f;
};

#endif
```

--

## [Shape.cpp](https://github.com/NCCA/CFGAA/blob/master/Lecture6Inheritance/Shape/src/Shape.cpp)

```
#include "Shape.h"

void Shape::setWidth(float _w)
{
  m_width=_w;
}
void Shape::setHeight(float _h)
{
  m_height=_h;
}

float Shape::width() const
{
  return m_width;
}
float Shape::height() const
{
  return m_height;
}
```

--


# Shape Class

- The shape class can be used as a normal class, at present there is no inheritance

```
#include <iostream>
#include "Shape.h"

int main()
{
  Shape s;
  s.setWidth(10);
  s.setHeight(20);
  std::cout<<"Shape "<<s.width()<<' '<<s.height()<<'\n';
}
```

---

## Class inheritance syntax

- ```public :``` the public and protected members of the base class listed after the access specifier keep their member access in the derived class while the private members of the base class are inaccessible to the derived class

- ```protected :``` the public and protected members of the base class listed after the access specifier are protected members of the derived class while the private members of the base class are inaccessible to the derived class

--

## Class inheritance syntax

- ```private :``` the public and protected members of the base class listed after the access specifier are private members of the derived class while the private members of the base class are inaccessible to the derived class

- this is not used that much, but some design patterns may use this. 
- basically composition :- is-implemented-in-terms-of. 
  -  private inheritance is purely an implementation technique.

--

## Rectangle Class

<pre>
<code class="language-plantuml">
@startuml
skinparam classAttributeIconSize 0
class Shape {
 # m_width : float
 # m_height : float
 +  Shape()=default 
 +  Shape(const Shape &)=default 
 + ~Shape()=default 
 + setWidth(_w : float)
 + setHeight(_h : float)
 + width() : float
 + height() : float
 
}

class Rectangle {
 +  Rectangle(_w : float _h : float) 
 +  Rectangle(const Shape &)=default 
 + ~Rectangle()=default 
 + getArea() : float
 
}
Shape <|-- Rectangle

@enduml
</code>
</pre>


--

## [Rectangle.h](https://github.com/NCCA/CFGAA/blob/master/Lecture6Inheritance/Shape/include/Rectangle.h)

```
#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "Shape.h"

class Rectangle : public Shape
{
  public :
    Rectangle(float _w, float _h);
    ~Rectangle()=default;
    Rectangle(const Rectangle &)=default;
    float getArea() const;
};

#endif

```

- note Rectangle has no attributes as they are inherited from Shape

--

## [Rectangle.cpp](https://github.com/NCCA/CFGAA/blob/master/Lecture6Inheritance/Shape/src/Rectangle.cpp)

```
#include "Rectangle.h"

Rectangle::Rectangle(float _w, float _h)
{
  m_width=_w;
  m_height=_h;
}

float Rectangle::getArea() const
{
  return m_width*m_height;
}
```

- note how we can refer to ```m_width``` and ```m_height``` in the derived class.

--

## [RectangleMain.cpp](https://github.com/NCCA/CFGAA/blob/master/Lecture6Inheritance/Shape/src/RectangleMain.cpp)

```
#include <iostream>
#include "Rectangle.h"

int main()
{
  Rectangle r(10.0f,8.0f);
  std::cout<<"Area r is "<<r.getArea()<<'\n';
  auto r2=r;
  r2.setWidth(8.0f);
  r2.setHeight(2.0f);
  std::cout<<"Area r2 is "<<r2.getArea()<<'\n';
}
```

- can call methods from the base class

---


## Further Reading

- http://www.gotw.ca/publications/mill06.htm


