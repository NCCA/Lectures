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

### Can anyone spot and issues with this Design?

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

class Square {
 +  Square(_d : float ) 
 +  Square(const Shape &)=default 
 + ~Square()=default 
 + getArea() : float
}

class Circle {
 +  Circle(_radius : float ) 
 +  Circle(const Shape &)=default 
 + ~Circle()=default 
 + getArea() : float
 # m_radius : float
}

Shape <|-- Rectangle
Shape <|-- Square
Shape <|-- Circle

@enduml
</code>
</pre>

--

## [Circle - Ellipse problem](https://en.wikipedia.org/wiki/Circle%E2%80%93ellipse_problem)


<pre>
<code class="language-plantuml">
@startuml
skinparam classAttributeIconSize 0

class Ellipse {
 + stretchX()
 + stretchY()
- int m_x;
- int m_y;
}

class Circle {
}

Ellipse <|-- Circle

@enduml
</code>
</pre>

- sometimes called the square–rectangle problem
- if we call ```Circle.stretchX()``` is the circle still a circle?
- we are breaking the rules of S.O.L.I.D. 

--

## Solutions

- changing the model (re-design the code?)
- using a different language 
  - some languages support better approaches to OO than others, we are stuck with C++ so not possible
- use a different paradigm

--

## One possible solution

```
Circle::stretchX(float _x) { m_x = m_y = _x; }
Circle::stretchY(float _y) { m_y = m_y = _y; }
```

- is this a good design ?


---


## Practical C++ inheritance

- The following examples will demonstrate some practical C++ inheritance models
- It must be noted that some people are very critical of the C++ inheritance model

>[Inheritance in C++ is like a jig-saw where the pieces fit together, but the compiler has no way of checking that the resultant picture makes sense. In other words C++ has provided the syntax for classes and inheritance but not the semantics.](http://www.literateprogramming.com/c++critique.pdf)

--

## Practical C++ 11 inheritance

- C++ 11 introduced some new keywords to help overcome some of the issues identified in the previous paper.
- I intend to use C++ 11 syntax at all times and will not use older syntax
  - this will help to eliminate some of the edge cases and bugs people will usually get without them.
- for simplicity most of these examples will be single C++ files defining the classes inline. 
  - **I don't encourage this for normal usage!**

---

## [The inheritance of Constructors](https://github.com/NCCA/CFGAA/blob/master/Lecture6Inheritance/ConstructorInheritance/example1.cpp)

```
#include <iostream>

class Base
{
  public :
    Base(){std::cout<<"Base Ctor\n";}
    ~Base(){std::cout<<"Base dtor\n";}
};

class Derived : public  Base
{
  public :
    Derived() {std::cout<<"Derived ctor\n";}
    ~Derived() {std::cout<<"Derived dtor\n";}

};

int main()
{
  {
    std::cout<<"constructing Base b\n";
    Base b;
  }
  std::cout<<"\n\n";

  {
    std::cout<<"constructing Base b\n";
    Derived d;
  }

}
```

--

## [Simple Ctor](http://pythontutor.com/cpp.html#code=%23include%20%3Ciostream%3E%0A%0Aclass%20Base%0A%7B%0A%20%20public%20%3A%0A%20%20%20%20Base%28%29%7Bstd%3A%3Acout%3C%3C%22Base%20Ctor%5Cn%22%3B%7D%0A%20%20%20%20~Base%28%29%7Bstd%3A%3Acout%3C%3C%22Base%20dtor%5Cn%22%3B%7D%0A%7D%3B%0A%0Aclass%20Derived%20%3A%20public%20%20Base%0A%7B%0A%20%20public%20%3A%0A%20%20%20%20Derived%28%29%20%7Bstd%3A%3Acout%3C%3C%22Derived%20ctor%5Cn%22%3B%7D%0A%20%20%20%20~Derived%28%29%20%7Bstd%3A%3Acout%3C%3C%22Derived%20dtor%5Cn%22%3B%7D%0A%0A%7D%3B%0A%0Aint%20main%28%29%0A%7B%0A%20%20%7B%0A%20%20%20%20std%3A%3Acout%3C%3C%22constructing%20Base%20b%5Cn%22%3B%0A%20%20%20%20Base%20b%3B%0A%20%20%7D%0A%20%20std%3A%3Acout%3C%3C%22%5Cn%5Cn%22%3B%0A%0A%20%20%7B%0A%20%20%20%20std%3A%3Acout%3C%3C%22constructing%20Base%20b%5Cn%22%3B%0A%20%20%20%20Derived%20d%3B%0A%20%20%7D%0A%0A%7D&curInstr=0&mode=display&origin=opt-frontend.js&py=cpp&rawInputLstJSON=%5B%5D)

<img src="images/SimpleCtor.apng" width="100%">



--

## [User defined constructors](https://github.com/NCCA/CFGAA/blob/master/Lecture6Inheritance/ConstructorInheritance/example2.cpp) 

```
#include <iostream>

#include <iostream>

class Base
{
  public :
    Base()=default;
    Base(int _a) : m_a{_a} 
    {
      std::cout<<"Base Ctor "<<m_a<<'\n';
    }
    ~Base(){std::cout<<"Base dtor\n";}
  protected :
    int m_a=0;

};

class Derived : public  Base
{
  public :
    Derived()=default;
    Derived(int _a,int _b) : Base(_a), m_b{_b}
    {
      std::cout<<"Derived ctor "<<m_a<<' '<<m_b<<'\n';
    }
    ~Derived() {std::cout<<"Derived dtor\n";}

  protected :
    int m_b=0;
};

int main()
{
  {
    std::cout<<"constructing Base b\n";
    Base b(1);
  }
  std::cout<<"\n\n";

  {
    std::cout<<"constructing Base b\n";
    Derived d(2,4);
  }

  {
    Base b;
  }
  {
    Derived d;3
  }
}

```


--

## [User defined constructors](http://pythontutor.com/cpp.html#code=%23include%20%3Ciostream%3E%0A%0A%23include%20%3Ciostream%3E%0A%0Aclass%20Base%0A%7B%0A%20%20public%20%3A%0A%20%20%20%20Base%28%29%3Ddefault%3B%0A%20%20%20%20Base%28int%20_a%29%20%3A%20m_a%7B_a%7D%20%0A%20%20%20%20%7B%0A%20%20%20%20%20%20std%3A%3Acout%3C%3C%22Base%20Ctor%20%22%3C%3Cm_a%3C%3C'%5Cn'%3B%0A%20%20%20%20%7D%0A%20%20%20%20~Base%28%29%7Bstd%3A%3Acout%3C%3C%22Base%20dtor%5Cn%22%3B%7D%0A%20%20protected%20%3A%0A%20%20%20%20int%20m_a%3D0%3B%0A%0A%7D%3B%0A%0Aclass%20Derived%20%3A%20public%20%20Base%0A%7B%0A%20%20public%20%3A%0A%20%20%20%20Derived%28%29%3Ddefault%3B%0A%20%20%20%20Derived%28int%20_a,int%20_b%29%20%3A%20Base%28_a%29,%20m_b%7B_b%7D%0A%20%20%20%20%7B%0A%20%20%20%20%20%20std%3A%3Acout%3C%3C%22Derived%20ctor%20%22%3C%3Cm_a%3C%3C'%20'%3C%3Cm_b%3C%3C'%5Cn'%3B%0A%20%20%20%20%7D%0A%20%20%20%20~Derived%28%29%20%7Bstd%3A%3Acout%3C%3C%22Derived%20dtor%5Cn%22%3B%7D%0A%0A%20%20protected%20%3A%0A%20%20%20%20int%20m_b%3D0%3B%0A%7D%3B%0A%0Aint%20main%28%29%0A%7B%0A%20%20%7B%0A%20%20%20%20std%3A%3Acout%3C%3C%22constructing%20Base%20b%5Cn%22%3B%0A%20%20%20%20Base%20b%281%29%3B%0A%20%20%7D%0A%20%20std%3A%3Acout%3C%3C%22%5Cn%5Cn%22%3B%0A%0A%20%20%7B%0A%20%20%20%20std%3A%3Acout%3C%3C%22constructing%20Base%20b%5Cn%22%3B%0A%20%20%20%20Derived%20d%282,4%29%3B%0A%20%20%7D%0A%0A%20%20%7B%0A%20%20%20%20Base%20b%3B%0A%20%20%7D%0A%20%20%7B%0A%20%20%20%20Derived%20d%3B%0A%20%20%7D%0A%7D&curInstr=0&mode=display&origin=opt-frontend.js&py=cpp&rawInputLstJSON=%5B%5D)


<img src="images/UserCtor.apng" width="100%">


---


## [Inheriting Methods](https://github.com/NCCA/CFGAA/blob/master/Lecture6Inheritance/MethodInheritance/example1.cpp)

```
#include <iostream>

class Base
{
  public :
    Base(){std::cout<<"Base Ctor\n";}
    ~Base(){std::cout<<"Base dtor\n";}
    void whoAmI() const {std::cout<<"I am Base\n";}
};

class Derived : public  Base
{
  public :
    Derived() {std::cout<<"Derived ctor\n";}
    ~Derived() {std::cout<<"Derived dtor\n";}
    void whoAmI() const {std::cout<<"I am Derived\n";}

};

int main()
{
  {
    std::cout<<"constructing Base b\n";
    Base b;
    b.whoAmI();
  }
  std::cout<<"\n\n";

  {
    std::cout<<"constructing Derived b\n";
    Derived d;
    d.whoAmI();
  }
  std::cout<<'\n';
  {
    std::cout<< "construct Derived as Base \n";
    Base *ptr = new Derived;
    ptr->whoAmI();
    delete ptr;
  }
}
```

--

## What happened here

```
constructing Base b
Base Ctor
I am Base
Base dtor


constructing Derived b
Base Ctor
Derived ctor
I am Derived
Derived dtor
Base dtor

construct Derived as Base 
Base Ctor
Derived ctor
I am Base
```

--

## What happened here?


<iframe width="1000px" height="600px" src="https://godbolt.org/e#g:!((g:!((g:!((h:codeEditor,i:(fontScale:14,j:1,lang:c%2B%2B,selection:(endColumn:16,endLineNumber:33,positionColumn:16,positionLineNumber:33,selectionStartColumn:16,selectionStartLineNumber:33,startColumn:16,startLineNumber:33),source:'%0Aclass+Base%0A%7B%0A++public+:%0A++++Base()%3Ddefault%3B%0A++++~Base()%3Ddefault%3B%0A++++void+whoAmI()+const+%7B%7D%0A%7D%3B%0A%0Aclass+Derived+:+public++Base%0A%7B%0A++public+:%0A++++Derived()%3Ddefault%3B%0A++++~Derived()%3Ddefault%3B%0A++++void+whoAmI()+const+%7B%7D%0A%0A%7D%3B%0A%0Aint+main()%0A%7B%0A++%7B%0A++++Base+b%3B%0A++++b.whoAmI()%3B%0A++%7D%0A%0A++%7B%0A++++Derived+d%3B%0A++++d.whoAmI()%3B%0A++%7D%0A++%7B%0A++++Base+*ptr+%3D+new+Derived%3B%0A++++ptr-%3EwhoAmI()%3B%0A++++delete+ptr%3B%0A++%7D%0A%0A%7D'),l:'5',n:'0',o:'C%2B%2B+source+%231',t:'0')),header:(),k:50,l:'4',n:'0',o:'',s:0,t:'0'),(g:!((h:compiler,i:(compiler:clang500,filters:(b:'0',binary:'1',commentOnly:'0',demangle:'0',directives:'0',execute:'1',intel:'0',libraryCode:'1',trim:'0'),fontScale:14,j:1,lang:c%2B%2B,libs:!(),options:'-std%3Dc%2B%2B14+',selection:(endColumn:1,endLineNumber:1,positionColumn:1,positionLineNumber:1,selectionStartColumn:1,selectionStartLineNumber:1,startColumn:1,startLineNumber:1),source:1),l:'5',n:'0',o:'x86-64+clang+5.0.0+(Editor+%231,+Compiler+%231)+C%2B%2B',t:'0')),k:50,l:'4',n:'0',o:'',s:0,t:'0')),l:'2',n:'0',o:'',t:'0')),version:4"></iframe>


--

## What happened here?

- The compiler will bind the correct method for the type at compile time.
- There is a one to one mapping in the fist two examples
  ```Base::whoAmI()``` and ```Derived::whoAmI()```
- however the line of code

```
Base *ptr = new Derived;

```

- Will call the Derived constructor but still bind the method for the Base type.

---

## Meet the V-Table

- In the previous example the automatic variables are bound to the correct method, however the dynamic (heap) objects are not.
- This is because [*dynamic dispatch*](https://en.wikipedia.org/wiki/Dynamic_dispatch) or *runtime polymorphism* need a little more work
- This also means there will be more code overhead and perhaps slowdowns added to our code 

--

## [virtual functions](https://github.com/NCCA/CFGAA/blob/master/Lecture6Inheritance/MethodInheritance/example2.cpp)

```
#include <iostream>

class Base
{
  public :
    Base(){std::cout<<"Base Ctor\n";}
    ~Base(){std::cout<<"Base dtor\n";}
    virtual void whoAmI() const {std::cout<<"I am Base\n";}
};

class Derived1 : public  Base
{
  public :
    Derived1() {std::cout<<"Derived1 ctor\n";}
    ~Derived1() {std::cout<<"Derived1 dtor\n";}
    virtual void whoAmI() const override {std::cout<<"I am Derived1\n";}

};

class Derived2 : public  Base
{
  public :
    Derived2() {std::cout<<"Derived2 ctor\n";}
    ~Derived2() {std::cout<<"Derived2 dtor\n";}
    virtual void whoAmI() const override {std::cout<<"I am Derived2\n";}

};


int main()
{
  {
    std::cout<< "construct Derived1 as Base \n";
    Base *ptr = new Derived1;
    ptr->whoAmI();
    delete ptr;
    std::cout<< "\nconstruct Derived2 as Base \n";
    ptr = new Derived2;
    ptr->whoAmI();
    delete ptr;
    std::cout<< "\nconstruct Base as Base \n";
    ptr = new Base;
    ptr->whoAmI();
    delete ptr;
    
  }

}
```

--

## [watch the *this](http://pythontutor.com/cpp.html#code=%23include%20%3Ciostream%3E%0A%0Aclass%20Base%0A%7B%0A%20%20public%20%3A%0A%20%20%20%20Base%28%29%7Bstd%3A%3Acout%3C%3C%22Base%20Ctor%5Cn%22%3B%7D%0A%20%20%20%20~Base%28%29%7Bstd%3A%3Acout%3C%3C%22Base%20dtor%5Cn%22%3B%7D%0A%20%20%20%20virtual%20void%20whoAmI%28%29%20const%20%7Bstd%3A%3Acout%3C%3C%22I%20am%20Base%5Cn%22%3B%7D%0A%7D%3B%0A%0Aclass%20Derived1%20%3A%20public%20%20Base%0A%7B%0A%20%20public%20%3A%0A%20%20%20%20Derived1%28%29%20%7Bstd%3A%3Acout%3C%3C%22Derived1%20ctor%5Cn%22%3B%7D%0A%20%20%20%20~Derived1%28%29%20%7Bstd%3A%3Acout%3C%3C%22Derived1%20dtor%5Cn%22%3B%7D%0A%20%20%20%20virtual%20void%20whoAmI%28%29%20const%20override%20%7Bstd%3A%3Acout%3C%3C%22I%20am%20Derived1%5Cn%22%3B%7D%0A%0A%7D%3B%0A%0Aclass%20Derived2%20%3A%20public%20%20Base%0A%7B%0A%20%20public%20%3A%0A%20%20%20%20Derived2%28%29%20%7Bstd%3A%3Acout%3C%3C%22Derived2%20ctor%5Cn%22%3B%7D%0A%20%20%20%20~Derived2%28%29%20%7Bstd%3A%3Acout%3C%3C%22Derived2%20dtor%5Cn%22%3B%7D%0A%20%20%20%20virtual%20void%20whoAmI%28%29%20const%20override%20%7Bstd%3A%3Acout%3C%3C%22I%20am%20Derived2%5Cn%22%3B%7D%0A%0A%7D%3B%0A%0A%0Aint%20main%28%29%0A%7B%0A%20%20%7B%0A%20%20%20%20std%3A%3Acout%3C%3C%20%22construct%20Derived1%20as%20Base%20%5Cn%22%3B%0A%20%20%20%20Base%20*ptr%20%3D%20new%20Derived1%3B%0A%20%20%20%20ptr-%3EwhoAmI%28%29%3B%0A%20%20%20%20delete%20ptr%3B%0A%20%20%20%20std%3A%3Acout%3C%3C%20%22%5Cnconstruct%20Derived2%20as%20Base%20%5Cn%22%3B%0A%20%20%20%20ptr%20%3D%20new%20Derived2%3B%0A%20%20%20%20ptr-%3EwhoAmI%28%29%3B%0A%20%20%20%20delete%20ptr%3B%0A%20%20%20%20std%3A%3Acout%3C%3C%20%22%5Cnconstruct%20Base%20as%20Base%20%5Cn%22%3B%0A%20%20%20%20ptr%20%3D%20new%20Base%3B%0A%20%20%20%20ptr-%3EwhoAmI%28%29%3B%0A%20%20%20%20delete%20ptr%3B%0A%20%20%20%20%0A%20%20%7D%0A%0A%7D&curInstr=0&mode=display&origin=opt-frontend.js&py=cpp&rawInputLstJSON=%5B%5D)


<img src="images/Virtual1.apng" width="100%">


--

## What's missing?

- destructors need to be virtual too (use -Wall to get proper warnings)

```
clang11 -Wall example2.cpp 
example2.cpp:36:5: warning: delete called on non-final 'Base' that has virtual functions but
      non-virtual destructor [-Wdelete-non-virtual-dtor]
    delete ptr;
    ^
example2.cpp:40:5: warning: delete called on non-final 'Base' that has virtual functions but
      non-virtual destructor [-Wdelete-non-virtual-dtor]
    delete ptr;
    ^
example2.cpp:44:5: warning: delete called on non-final 'Base' that has virtual functions but
      non-virtual destructor [-Wdelete-non-virtual-dtor]
    delete ptr;
    ^
3 warnings generated.


```

--

## [example3.cpp](https://github.com/NCCA/CFGAA/blob/master/Lecture6Inheritance/MethodInheritance/example3.cpp)

```
#include <iostream>

class Base
{
  public :
    Base(){std::cout<<"Base Ctor\n";}
    virtual ~Base(){std::cout<<"Base dtor\n";}
    virtual void whoAmI() const {std::cout<<"I am Base\n";}
};

class Derived1 : public  Base
{
  public :
    Derived1() {std::cout<<"Derived1 ctor\n";}
    virtual ~Derived1() {std::cout<<"Derived1 dtor\n";}
    virtual void whoAmI() const override {std::cout<<"I am Derived1\n";}

};

class Derived2 : public  Base
{
  public :
    Derived2() {std::cout<<"Derived2 ctor\n";}
    virtual ~Derived2() {std::cout<<"Derived2 dtor\n";}
    virtual void whoAmI() const override {std::cout<<"I am Derived2\n";}

};

int main()
{
  {
    std::cout<< "construct Derived1 as Base \n";
    Base *ptr = new Derived1;
    ptr->whoAmI();
    delete ptr;
    std::cout<< "\nconstruct Derived2 as Base \n";
    ptr = new Derived2;
    ptr->whoAmI();
    delete ptr;
    std::cout<< "\nconstruct Base as Base \n";
    ptr = new Base;
    ptr->whoAmI();
    delete ptr;
    
  }
}

```

--

## vtable

<iframe width="1000px" height="600px" src="https://godbolt.org/e#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAM1QDsCBlZAQwBtMQBGAFlICsupVs1qhkAUgBMAISnTSAZ0ztkBPHUqZa6AMKpWAVwC2tLgA5SW9ABk8tTADljAI0zEuAVlIAHVAsLqtHqGJuY%2BfgF0tvZORq7unF5KKmp0DATMxATBxqacFsmYqoHpmQTRji5unooZWTmh%2BbVlFbHxngCUiqgGxMgcAOTiAAwAgsjCCgoA1NLMSiOj4gDssmPT094Gzqx4yNMgixsbc0oQHeIAzAAiWFTMBqwEV2ujx9MAbnhZBmzTAH6nTDnK63TD3R7PS6vd5fH5/D6oPDoaYAdwQqFGRgAkudpmhaAoCNMVrJltdFisKdDKWMJvMZtc3HgPph0JwDpttrt9rN5phKasjlydnsDsKNkziCy2ZwQTc7g8ni8JQCpTL2fKwRDlTT1sc4QRfqxPkiUejMTi8QSiSSheTaUsHXqlnTJozmaz0JJOVtRbygYKYSKeeL9ZLPWzJFrFZCVeG1ZHvTHwUqocGNobjabkWiMVjcR18XRbaSqY7yy7HXZiUZmHYQWMywmgdMAFTeAjEEk3ab2VHTdVezjxt7HTvEAC0V2wFoL8oz0yw7AImE2XdH7wnPeufcwA6HUc346708us/zVouLvey8wq/XxGPG23oL3A8DN5PU5nc6vz6XZR7zXCdRypAYulYEABg8AZSFMAZhjg1BoJ0OQ5GmBQej6NcpEuTg4IIaCkI6LoEEwZgsHcc5SAAaxADxhiEaDuDghCkNIFCBjghQQCYojEIg0g4FgJA0CMbw8HYMgKAgcTJOklBhFERimKoKTV2IXiIGcYi4OcOxMgAT2ggjSHEowtAIAB5WhWBMwTSCwOtRHYPSnO%2BIo1FZXjHMwAAPIoDFXUy4JrZR3N2ZxiGMvQsFC0guzwIw9K6Gh6CYNgOB4fhBGUsR0JkIQ8GcXjIC6VBO0CXzJyJdBQQkGQ5B4aYeKA4oNAgKwGlMbheCsVoqncSRhmWcJ/FSIJ9FyEA%2BvGyJaEGuJqhGsbCg62hSnqabQjm9bJq28o7EqZbhtG5ptpCXreCJFpjraFbRq6LDen6LhIOg2D4Pcrj/LMAA2Sd/u4fF8umDwADphih6YIFwQgSBJSR8NIaY9AkqS3CR/CizQpqZEI1KunoxjmIGVjvscrieL4xKibJyQ2J%2B6DCcE0jSFZLTAlmoA%3D%3D%3D"></iframe>



---


## [Abstract Classes](https://en.cppreference.com/w/cpp/language/abstract_class) 

- Abstract classes are used to represent general concepts which can be used as base classes for concrete classes.
- No objects of an abstract class can be created (except for base subobjects of a class derived from it) and no non-static data members of an abstract class can be declared.
- Abstract types cannot be used as parameter types, as function return types, or as the type of an explicit conversion;
- Pointers and references to an abstract class can be declared.


--

## [pure virtual methods](https://github.com/NCCA/CFGAA/blob/master/Lecture6Inheritance/AbstractClass/example1.cpp)

```

#include <iostream>

class AbstractNumber
{
  public : 
    AbstractNumber(int _v) : m_v{_v}{}
    ~AbstractNumber()=default;
    virtual void printValue() const = 0;
  private :
    int m_v;
};

int main()
{
  AbstractNumber n(100);
}
```

- we use the postfix =0 on a method to make it *pure virtual* 

--

## Can't compile an abstract class

```
clang11 -Wall example1.cpp  
example1.cpp:15:18: error: variable type 'AbstractNumber' is an abstract class
  AbstractNumber n(100);
                 ^
example1.cpp:8:18: note : unimplemented pure virtual method 'printValue' in 'AbstractNumber'
    virtual void printValue() const = 0;
                 ^
example1.cpp:10:9: warning: private field 'm_v' is not used [-Wunused-private-field]
    int m_v;
        ^
1 warning and 1 error generated.

```

--


## [example2.cpp](https://github.com/NCCA/CFGAA/blob/master/Lecture6Inheritance/AbstractClass/example2.cpp)

```
#include <iostream>

class AbstractNumber
{
  public : 
    AbstractNumber(int _v) : m_v{_v}{}
    ~AbstractNumber()=default;
    virtual void printValue() const = 0;
  protected :
    int m_v;
};

class Decimal : public  AbstractNumber
{
  public :
    Decimal(int _v) : AbstractNumber(_v) {}
    virtual void printValue() const {std::cout<<"Decimal is "<<m_v<<'\n';}
};

int main()
{
  Decimal n(100);
  n.printValue();
}
```

- anything that inherits from AbstractNumber must implement ```printValue()```

--

## [example3.cpp](https://github.com/NCCA/CFGAA/blob/master/Lecture6Inheritance/AbstractClass/example3.cpp)


```
#include <iostream>
#include <memory>

class AbstractNumber
{
  public : 
    AbstractNumber(int _v) : m_v{_v}{}
    ~AbstractNumber()=default;
    virtual void printValue() const = 0;
  protected :
    int m_v;
};

class Decimal : public  AbstractNumber
{
  public :
    Decimal(int _v) : AbstractNumber(_v) {}
    virtual void printValue() const override {std::cout<<"Decimal is "<<std::dec<<m_v<<'\n';}
};

class Hex : public  AbstractNumber
{
  public :
    Hex(int _v) : AbstractNumber(_v) {}
    virtual void printValue() const override {std::cout<<"Hex is "<< std::hex<<m_v<<'\n';}
};

class Octal : public  AbstractNumber
{
  public :
    Octal(int _v) : AbstractNumber(_v) {}
    virtual void printValue() const override {std::cout<<"Octal is "<< std::oct<<m_v<<'\n';}
};
int main()
{
  std::unique_ptr<AbstractNumber> number; 
  number.reset(new Hex(255));
  number->printValue();
  number = std::make_unique<Octal>(Octal(255));
  number->printValue();
  number = std::make_unique<Decimal>(Decimal(255));
  number->printValue();
  
}
```

---

## [Why use override](https://github.com/NCCA/CFGAA/blob/master/Lecture6Inheritance/Mismatch/example1.cpp)

```
#include <iostream>
#include <string>
class Base
{
  public : 
    Base()=default;
    virtual void whoAmI(const std::string &_name)
    {
      std::cout<<"std::string version Base "<<_name<<'\n';
    }
};

class Derived : public Base
{
  public : 
    Derived()=default;
    virtual void whoAmI(const char *_name) override
    {
      std::cout<<"const char * Derived "<<_name<<'\n';
    }
};

int main()
{
  Base b;
  b.whoAmI("instance b");
  Derived d;
  d.whoAmI("instance d");

}
```

```
example1.cpp:17:18: error: 'whoAmI' marked 'override' but does not override any member functions
    virtual void whoAmI(const char *_name) override
```

--

## [override](https://en.cppreference.com/w/cpp/language/override)

- In a member function declaration or definition, override ensures that the function is virtual and is overriding a virtual function from a base class. 
- The program is ill-formed (a compile-time error is generated) if this is not true.
- override is an identifier with a special meaning when used after member function declarators : it's not a reserved keyword otherwise.


---

## [final](https://en.cppreference.com/w/cpp/language/final)

- When used in a virtual function declaration or definition, final ensures that the function is virtual and specifies that it may not be overridden by derived classes. The program is ill-formed (a compile-time error is generated) otherwise.

- When used in a class definition, final specifies that this class may not appear in the base-specifier-list of another class definition (in other words, cannot be derived from). 

- final is an identifier with a special meaning when used in a member function declaration or class head. In other contexts it is not reserved and may be used to name objects and functions.

--

```
#include <iostream>

class Countdown final 
{

};

class ItsThe : public  Countdown
{

};

int main()
{
  ItsThe t;
}

```

```
example1.cpp:8:24: error: base 'Countdown' is marked 'final'
class ItsThe : public  Countdown
                       ^
example1.cpp:3:7: note : 'Countdown' declared here
class Countdown final 
      ^         ~~~~~
1 error generated.

```

---

## Is that all for Inheritance?

- Basically yes, the syntax and usage is fairly simple
- I have omitted some things ( for example [multiple inheritance](https://www.geeksforgeeks.org/multiple-inheritance-in-c/))
- As we will see next time, a lot of this will be used in Design Patterns
- Especially as we start using *"Abstractions instead of Concretions"*

---

## Further Reading

- http://www.gotw.ca/publications/mill06.htm
- https://en.cppreference.com/w/cpp/language/derived_class
- https://isocpp.org/wiki/faq/strange-inheritance 
- https://pabloariasal.github.io/2017/06/10/understanding-virtual-tables/




