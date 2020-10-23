# Classes and Object Orientation in C++

Jon Macey

jmacey@bournemouth.ac.uk

---


## Classes	in Practice

- It is standard practice to split the class into two separate files.
- A .h (.H) Header file is used to define the class and prototype the methods and data for this class.
- A .cpp (.C) file is used to contain the actual class code and algorithmic elements.
- To link these two elements together we need to tell the compiler which class the methods in the .cpp file belong to.

--


## C++ Scope Resolution Operator [::](https://msdn.microsoft.com/en-us/library/b451xz31.aspx)
- The :: (scope resolution) operator is used to qualify hidden names so that you can still use them. 
- This is how C++ allows us to have different classes with the same member function names (polymorphism)
- We use the :: to imply membership to a particular class and differentiate the different methods / class relationships


--

## [C++ class syntax](http://en.cppreference.com/w/cpp/language/class)

```
#ifndef COLOUR_H_
#define COLOUR_H_


class Colour
{
  public :

    Colour()=default;
    ~Colour()=default;
    Colour(float _r, float _g,float _b, float _a=1.0f) :
      m_r{_r},m_g{_g},m_b{_b},m_a{_a} {}
    Colour(const Colour &_c)=default;
    // accessors
    float red() const ;
    float green() const ;
    float blue() const ;
    float alpha() const ;
    // mutators see here for param passing guidelines
    // https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#fcall-parameter-passing
    void set(float _r, float _g, float _b, float _a=1.0f);
    void setRed(float _r);
    void setGreen(float _g);
    void setBlue(float _b);
    void setAlpha(float _a);

    void clamp(float _min,float _max);
    void mix(const Colour &_in, float _t);
    static Colour mix(const Colour &_a, const Colour &_b, float _t);
  private:

    float m_r=0.0f;
    float m_g=0.0f;
    float m_b=0.0f;
    float m_a=1.0f;
};
#endif

```

--


## [C++ class syntax](http://en.cppreference.com/w/cpp/language/class)
- we use the ``` class ``` keyword to define a class
- ``` class [name] { }; ```
- ``` { }; ``` scope defines members of the class
	- ``` public : ``` defines publicly visible area
	- ``` private : ```  defines hidden area
- classes are usually defined in a .h file

--

## [Special member functions](https://en.cppreference.com/w/cpp/language/member_functions#Special_member_functions)

- Some member functions are special : they can defined by the compiler even if not defined by the user.
  - Default constructor
  - Copy constructor
  - Move constructor (since C++11)
  - Copy assignment operator
  - Move assignment operator (since C++11)
  - Destructor
- These Special member functions are the only functions that can be defaulted  ```= default``` 

--

## A Simple class

```
class Point
{
  int x,y;
};
```
- Is this a valid class? If so explain what we get with it?

--

## [Loads of free stuff](https://www.youtube.com/watch?v=4AfRAVcThyA&t=2428s)

```
class Point
{
  private :
    int x,y;
  public :
    Point()=default;
    ~Point() noexcept = default;
    Point(const Point &)=default;
    Point & operator=(const Point &)=default;
    Point(Point &&)=default;
    Point & operator=(Point &&)=default;
    
};
```
- But always try to be explicit in your code! 

--

## Point

<div class="stretch">

<iframe width="1200px" height="800px" src="https://godbolt.org/e#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAKxAEZSBnVAV2OUxAHIBSAJgGY8AO2QAbZlgDU3fgGFmBPKMIBPGdm4AGAIJ9BI8VJmyAtphMk1/DTrEBDBg0kAFVMIJbdAdgBCnyZIADsR4AG52BJiSIP4Bku6SAB6kVj7SOgGBzABGysjRsQGu7hAAlDIAIlgAZnbMoh78fhlxAH7FQgRlkkKomInsgQTS/BWSNXUNMs3acS5unRBoQgzDHcN8AGzloxP1jTNz69K8m5KogZjEESSVS6grawsbpztVmLX704XzJcdbWzeeymTR%2B/1O50u1yIxDu4M2gMqwIOP083C8FW%2BOk8CRMdmEZTRvjBzyCWNmcWOgV4lUC5KOpMC/Ag1J2hziq3QIBAzCEeAAjsxMAB9IawuTrdRBOmjTncvEAaxFvIFQuMkushNB2JaASJFU4pVIoi4AFZOKQhFxNBbUFxZHw/Lw0kxWOwTvxaBaCNbDUaFSBTZpjVwACwWq2cG2kO2cC0MEDBn1Rw2kOCwJBoEyBJRXciULM50RXFCiOxCYBB4PVJSRYgJiDZX2kbLCOzEFRcL2kLNmToAeSEok7KdIWDxFeLzfwxEwyEUoUwCdH/TnCg4nG77kwJtHBBCJl9RuU2QTkCNF0UD2XAFpOZVkI7HbRQ5J4yw2BxaMezRHm7HEgADk2G9NlfewK0kU0ADpNFgyQIFwQgSA9ehJFkVBs1zYhUNKb0j39QNg13cNLX/Lh40TUhkxtUof04Xg/1HWN8JTOjSEXes8AeEBQyAA%3D"></iframe>

</div>


---

## [Constructors (ctor)](http://www.modernescpp.com/index.php/c-core-guidelines-constructors)
- When an object is created there are certain processes which must take place
- Instantiation always involves the allocation of memory for the objects state data.
- The methods do not require and memory as these are consistent for all objects of the class and are handled in the class itself.
- The special method which allocates the memory for an object is know as the 'constructor'
	- There are three basic types of constructor
	- The default constructor
	- User defined Constructor
	- The Copy Constructor

--

## [The default constructor](http://en.cppreference.com/w/cpp/language/default_constructor)

- The default constructor takes no parameters and has no return type
- It performs no processing on the object data just memory allocation
- It will always be called by the compiler if no user defined constructor is provided
- The default constructor is not referred to by the programmer in the class definition
- however since C++ 11 we should try and use ```=default```

--

## [User Defined Constructors](https://msdn.microsoft.com/en-GB/library/s16xw1a8.aspx)
- These constructors may be used to pass parameter values to the object
- These may be used to set default object values
- It is possible to have more than one constructor in a class passing different parameters
- This is known as “overloading” and gives more flexibility to the way the object can be instantiated

--

## User Defined Constructor

```
    Colour(float _r, float _g,float _b, float _a=1.0f) :
          m_r{_r},m_g{_g},m_b{_b},m_a{_a} {}
```

- set each of the attributes to a default value by calling  it’s own ctor
-  yes float has a constructor as do all C++ data types 

```
int a=int(2);
float b=float(4.5f);
```

--

## [C++ 11 in class initialisation](http://en.cppreference.com/w/cpp/language/initializer_list)

- C++ 11 allows you to set attribute values directly in the class

```
private :
	float m_r=0.0f;
	float m_g=0.0f;
	float m_b=0.0f;
	float m_a=1.0f;

```

--

## [C++ 11 in class initialisation](http://en.cppreference.com/w/cpp/language/initializer_list)
- This saves a bit of typing, but the real benefits come in classes with multiple constructors. Often, all constructors use a common initializer for a member:
- for full explaination see [stroustrup](http://www.stroustrup.com/C++11FAQ.html) section :- In-class member initializers
- [C++ core guidelines has much more depth](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#S-ctor) 

--

## [copy ctor](http://en.cppreference.com/w/cpp/language/copy_constructor)
- The copy constructor creates a new class as a copy of an existing class
- As the classes are of the same type they both know about each others internal state (private attributes)
- To stop mutation of the class being copied we must make it read only
- To do this we use the const prefix on the ctor parameter being passed in.

--

## [copy ctor](http://en.cppreference.com/w/cpp/language/copy_constructor)

```
// pre c++ 11
Colour(const Colour &_c) : 
							m_r(_c.m_r),
							m_g(_c.m_g),
							m_b(_c.m_b),
							m_a(_c.m_a){}
// post c++ 11
Colour(const Colour &_c)=default;

```
- use const to make the class passed in read only
- use . to access the class attributes
- ```m_r(_c.m_r)``` is basically saying set the current class member ```m_r``` to the value of the parameter passed in ```_c.m_r```


---

#### [The Orthodox Canonical class form ( rule of 3)](http://en.cppreference.com/w/cpp/language/rule_of_three)
- As a general rule (and rules are made to be broken) all classes should define four important functions
	- A default constructor :- This is used internally to initialise objects and data members when no other value is avaliable
	- A copy constructor :- This is used , among other places, in the implementation of call-by-value parameters
	- An assignment operator. This is used to assign one value to another.
	- A destructor. This is invoked when an object is deleted. (more of this soon)

--

## Rule of 5 
- C++ 11 gives some new methods of object creation an ownership and gives us a new rule
	- destructor
	- copy constructor
	- move constructor
	- copy assignment operator
	- move assignment operator
- More in a later lecture.

--

## [Rule of Zero](https://en.cppreference.com/w/cpp/language/rule_of_three)

>Classes that have custom destructors, copy/move constructors or copy/move assignment operators should deal exclusively with ownership. Other classes should not have custom destructors, copy/move constructors or copy/move assignment operators.

- This rule also appears in the C++ Core Guidelines as C.20: If you can avoid defining default operations, do.


--

## [Rule of Zero](https://en.cppreference.com/w/cpp/language/rule_of_three)

- This does contradict with my previous statement of being explicit tho!

```
class rule_of_zero
{
    std::string cppstring;
 public:
    rule_of_zero(const std::string& arg) : cppstring(arg) {}
};
```

---

## [accessors (get Methods)](http://stackoverflow.com/questions/3647438/conventions-for-accessor-methods-getters-and-setters-in-c)
- in our Colour class these are the accessors 
```
// accessors
float red() const ;
float green() const ;
float blue() const ;
float alpha() const ;
```

- note the use of const here to say *"this method does not touch the class"*

--

## accessors

```
float Colour::red() const
{
  return m_r;
}

float Colour::green() const
{
  return m_g;
}

float Colour::blue() const
{
  return m_b;
}

float Colour::alpha() const
{
  return m_a;
}
```
- It is usual practice to put these methods in the .cpp file to keep the interface *clean*

--

## mutators (set Methods)

```
void set(float _r, float _g, float _b, float _a=1.0f);
void setRed(float _r);
void setGreen(float _g);
void setBlue(float _b);
void setAlpha(float _a);
```
- the mutators modify the class and hence can’t be const
- [A note on parameter passing](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#fcall-parameter-passing
)

--

## mutators

```
void Colour::set(float _r, float _g, float _b, float _a)
{
  m_r=_r;
  m_g=_g;
  m_b=_b;
  m_a=_a;
}

void Colour::setRed(float _r)
{
  m_r=_r;
}
void Colour::setGreen(float _g)
{
  m_g=_g;
}

void Colour::setBlue(float _b)
{
  m_b=_b;
}

void Colour::setAlpha(float _a)
{
  m_a=_a;
}

```

- note the coding standard uses the Qt Convention of prefixing with set

---

## Example a [Colour Class](https://github.com/NCCA/ASELectureCode/blob/master/Lecture5Classes/Colour/tests/tests.cpp)

- The Colour Class was developed using TDD 

```
#include "Colour.h"
#include <gtest/gtest.h>
using namespace ::testing;

TEST(Colour,defaultCtor)
{
  Colour c;
  EXPECT_FLOAT_EQ(c.red(),0.0f);
  EXPECT_FLOAT_EQ(c.green(),0.0f);
  EXPECT_FLOAT_EQ(c.blue(),0.0f);
  EXPECT_FLOAT_EQ(c.alpha(),1.0f);
}

```

--

# clamp

```
void Colour::clamp(float _min, float _max)
{
  auto clamp=[](float _v,float _min,float _max)
  {
  return (_v < _min) ? _min : (_max < _v) ? _max : _v;
  };

  m_r=clamp(m_r,_min,_max);
  m_g=clamp(m_g,_min,_max);
  m_b=clamp(m_b,_min,_max);
  m_a=clamp(m_a,_min,_max);

}
```
- note C++ 17 now has a std::clamp

--

## ?: what?
- The ?: construct is called an “arithmetic if”  or a “conditional expression” (Stroustrup 2009)
- It works by doing a test (bool expression) ? [true] : [false]
- This saves us writing long expressions or functions
- For example 
```
(a>=b) ? a:b;
int max(int _a, int _b)
{
	int m;
	if (a>=b)
		m=a; 
	else
		m=b; 
	return m;
}
```

--

## Linear Interpolation
- We can use linear interpolation to blend between two values using a real scalar value which ranges from 0.0 - 1.0
- The basic formula given two values a and b and the real scalar t we get 
$$ p=a+(b-a)\times t $$

--

## mix
- This function is doing basic linear interpolation of each of the colour components 
- design decision :- Should I be leaving the alpha as the original?

```
void Colour::mix(const Colour &_in, float _t)
{
  assert(_t>=0.0f && _t <= 1.0f);
  m_r=m_r+(_in.m_r-m_r)*_t;
  m_g=m_g+(_in.m_g-m_g)*_t;
  m_b=m_b+(_in.m_b-m_b)*_t;
  m_a=m_a+(_in.m_a-m_a)*_t;
}

```

--

## [assert](http://en.cppreference.com/w/cpp/error/assert)
- The assert function is a C++ macro which test the statement and if it evaluates to false will abort the program
- The assert macro is used for developing programs and testing for programmers
- We can disable it by defining the NDEBUG flag as part of our compile options (more of this in the lab session)
- Add DEFINES+= NDEBUG to the Qt Project


--

## [Static Class Methods](https://github.com/NCCA/ASELectureCode/blob/master/Lecture5Classes/Colour/src/Colour.cpp)

- A static member is shared by all objects of the class

```
static Colour mix(const Colour &_a, const Colour &_b, float _t);
```

```
Colour Colour::mix(const Colour &_a, const Colour &_b, float _t)
{
  Colour ret;
  ret.m_r=_a.m_r+(_b.m_r-_a.m_r)*_t;
  ret.m_g=_a.m_g+(_b.m_g-_a.m_g)*_t;
  ret.m_b=_a.m_b+(_b.m_b-_a.m_b)*_t;
  ret.m_a=_a.m_a+(_b.m_a-_a.m_a)*_t;
  return ret;
}
```


--


## [Static Class Methods](https://github.com/NCCA/ASELectureCode/blob/master/Lecture5Classes/Colour/tests/tests.cpp)


```
TEST(Colour,mixStatic)
{
  Colour a(0.0f,0.0f,0.0f,0.0f);
  Colour b(1.0f,1.0f,1.0f,1.0f);
  Colour res;
  for(float t=0.0f; t<=1.0f; t+=0.1f)
  {
    res=Colour::mix(a,b,t);
    EXPECT_FLOAT_EQ(res.red(),t);
    EXPECT_FLOAT_EQ(res.green(),t);
    EXPECT_FLOAT_EQ(res.blue(),t);
    EXPECT_FLOAT_EQ(res.alpha(),t);
  }
}

```


---



# [Using the Class](https://github.com/NCCA/ASELectureCode/blob/master/Lecture5Classes/Colour/Automatic/main.cpp)	

- Now we have defined the class we can use it to create different objects for us to use.
- Each of the objects must have some way of being referred to to we can differentiate it from the others
- The simplest way of doing this is by using a simple name as show in the next example 

--

```
#include "Colour.h"

int main()
{
  Colour c; // create automatic object on stack
  {
    Colour x(0.1f,0.2f,0.3f,0.4f);
    for(int i=0; i<10; ++i)
    {
        Colour y={1.0f,0.0f,0.0f,1.0f};
    }
  }
}
```

--

## Automatic Objects

<img src="images/AutomaticObject.apng" width="100%">

- note how the object y is created and destroyed each time.

--

# Objects

- Each of these Colour Objects are completely different instances of the class Colour
- Each one has it’s own name and it’s own memory space
- They are however each identical in the respect that they contain the same attributes (i.e. m_r etc) and each have the same methods which may be invoked.
- Each one of these objects has it’s own lifetime which is constrained within the { } of the main program
- These are called automatic objects (created on the stack)

--

# [The destructor](http://en.cppreference.com/w/cpp/language/destructor)
- The destructor is called when an object is destroyed
- The responsibility of the destructor is to cleanup after the object and de-allocate any memory that the object has created
- [As a general rule is you allocate anything dynamically in the class you need a dtor](http://www.modernescpp.com/index.php/c-core-guidelines-destructor-rules). 
- Even better use a smart pointer!


--

## Dynamic Objects

- Most of the time we will create Automatic objects, however sometimes we need to control the lifetime ourselves. 
- To do this we need to have a way to create and destroy our objects on the fly and re-allocate them at will
- This involves the use of pointers as show in the next example

--

## [Dynamic Objects](https://github.com/NCCA/ASELectureCode/blob/master/Lecture5Classes/Colour/Dynamic/main.cpp)

```
#include <iostream>
#include "Colour.h"
// Note :-
// You would never really write code like this!!!!!

int main()
{
  Colour *c; // create automatic object on stack
  auto x= new Colour(0.1f,0.2f,0.3f,0.4f);
  x->clamp(0.2f,0.3f);
  std::cout<<"x "<<x->red()<<' '<<x->green()<<' '<<x->blue()<<'\n';

  c = new Colour;
  std::cout<<"c "<<c->red()<<' '<<c->green()<<' '<<c->blue()<<'\n';
  delete c;
  c = new Colour(0.1f,0.2f,0.3f);
  std::cout<<"c "<<c->red()<<' '<<c->green()<<' '<<c->blue()<<'\n';
  delete c;

  delete x;

}

```

--

## Dynamic Objects

<img src="images/Dynamic.apng" width="100%">


---

## Why use a destructor?

- In the previous example the dtor just printed out that it had been called
- The following example will show the real reason for the dtor
- The class allocates a block of dynamic memory when it is created
- When it is destroyed we need to free this memory so the destructor does this
- We also implement a “deep copy” constructor

--

## [Mem.h](https://github.com/NCCA/ASELectureCode/blob/master/Lecture5Classes/Memory/include/Mem.h)

```
#ifndef MEM_H_
#define MEM_H_

/// @brief a class to allocate dynamic integers
/// demonstrates the use of the destructor
class Mem
{
	public :
		/// @brief ctor passing in the size of the memory
    /// @param[in] _size the size of the array to alloc
    Mem(int _size );
    /// @brief copy ctor explicitly copies the data
		/// @param [in] _m the Mem object to copy
		Mem( const Mem &_m );
    /// @brief dtor will deallocate m_mem if allocated
		~Mem();
    /// @param method to print out the memory
    void print();
    /// @param method to set the data value in the array
    /// @param[in] _offset the index into the memory array
    /// this is validated with an assert
    /// @param[in] _value the value to set m_mem[_offset] too
    void set(int _offset,int _value);

  private :
    /// @brief a pointer to the memory
    int *m_mem;
    /// @brief the size of the memory array
    int m_size;
};

#endif
```

--

## [Mem.cpp](https://github.com/NCCA/ASELectureCode/blob/master/Lecture5Classes/Memory/src/Mem.cpp)
```
#include "Mem.h"
#include <iostream>
#include <cassert>

Mem::Mem( int _size )
{
  std::cout<<"ctor called\n";
  // allocate a new block of memory
  m_mem = new int[_size];
  // retain the size of the allocated block
  m_size=_size;
}

Mem::Mem( const Mem &_m  )
{
  std::cout<<"Copy ctor Called\n";
  m_size=_m.m_size;
  // allocate new memory
  m_mem = new int[m_size];
  // now copy the data from the original
  // using a loop here but could use memcpy or std::copy is using an stl container
  for(int i=0; i<m_size; ++i)
  {
    m_mem[i]=_m.m_mem[i];
  }
//  m_size=_m.m_size;
//  m_mem=_m.m_mem;
}

Mem::~Mem()
{
  std::cout<<"dtor called\n";
  if(m_mem !=0)
  {
    delete [] m_mem;
  }
}


void Mem::print()
{
  for(int i=0; i<m_size; ++i)
  {
    std::cout<<m_mem[i]<<std::endl;
  }
}
void Mem::set( int _offset,  int _value )
{
  assert(_offset<m_size);
  m_mem[_offset]=_value;
}

```

--

## [Shallow Copy](http://pythontutor.com/cpp.html#code=%23include%20%3Ccstdlib%3E%0A%0Aclass%20Memory%0A%7B%0A%20%20public%20%3A%0A%20%20%20%20Memory%28%29%3Ddefault%3B%0A%20%20%20%20Memory%28size_t%20_size%29%3B%0A%20%20%20%20~Memory%28%29%3B%0A%20%20%20%20Memory%28const%20Memory%20%26%29%3Ddefault%3B%0A%20%20private%20%3A%0A%20%20%20%20size_t%20m_size%3D0%3B%0A%20%20%20%20int%20*m_data%3Dnullptr%3B%0A%7D%3B%0A%0AMemory%3A%3AMemory%28size_t%20_size%29%0A%7B%0A%20%20m_size%3D_size%3B%0A%20%20m_data%3Dnew%20int%5B_size%5D%3B%0A%7D%0A%0AMemory%3A%3A~Memory%28%29%0A%7B%0A%20%20delete%20%5B%5D%20m_data%3B%0A%7D%0A%0Aint%20main%28%29%0A%7B%0A%20%20Memory%20first%28100%29%3B%0A%20%20auto%20second%3Dfirst%3B%0A%20%20%0A%7D&curInstr=0&mode=display&origin=opt-frontend.js&py=cpp&rawInputLstJSON=%5B%5D)

<img src="images/ShallowCopy.apng" width="100%">

--

## Shallow Copy

- In a shallow copy we just copy the memory address of the first class to that of the second class
- This means that the second class shares the data with the first
- If the first is destroyed then this memory is no longer valid
- This is what the ```=default``` copy constructor will do
- In most cases this is not desirable

--


## Deep Copy
- With a deep copy the object allocates the same amount of space for the memory
- Then each element is copied from the original to the new one
- We need to implement the copy constructor ourselves

--

## [Deep Copy](http://pythontutor.com/cpp.html#code=%23include%20%3Ccstdlib%3E%0A%23include%20%3Ccstring%3E%0Aclass%20Memory%0A%7B%0A%20%20public%20%3A%0A%20%20%20%20Memory%28%29%3Ddefault%3B%0A%20%20%20%20Memory%28size_t%20_size%29%3B%0A%20%20%20%20~Memory%28%29%3B%0A%20%20%20%20Memory%28const%20Memory%20%26%29%3B%0A%20%20private%20%3A%0A%20%20%20%20size_t%20m_size%3D0%3B%0A%20%20%20%20int%20*m_data%3Dnullptr%3B%0A%7D%3B%0A%0AMemory%3A%3AMemory%28size_t%20_size%29%0A%7B%0A%20%20m_size%3D_size%3B%0A%20%20m_data%3Dnew%20int%5B_size%5D%3B%0A%20%20memset%28m_data,0,_size*sizeof%28int%29%29%3B%0A%7D%0A%0AMemory%3A%3AMemory%28const%20Memory%20%26_in%29%0A%7B%0A%20%20m_size%3D_in.m_size%3B%0A%20%20m_data%3Dnew%20int%5Bm_size%5D%3B%0A%20%20%0A%20%20for%28size_t%20i%3D0%3B%20i%3Cm_size%3B%20%2B%2Bi%29%0A%20%20%7B%0A%20%20%20%20m_data%5Bi%5D%3D_in.m_data%5Bi%5D%3B%0A%20%20%7D%0A%20%20%0A%7D%0A%0AMemory%3A%3A~Memory%28%29%0A%7B%0A%20%20delete%20%5B%5D%20m_data%3B%0A%7D%0A%0Aint%20main%28%29%0A%7B%0A%20%20Memory%20first%2810%29%3B%0A%20%20auto%20second%3Dfirst%3B%0A%20%20%0A%7D&curInstr=0&mode=display&origin=opt-frontend.js&py=cpp&rawInputLstJSON=%5B%5D)

<img src="images/DeepCopy.apng" width="100%">

--

## Deep Copy

- In the previous example I used a loop to copy the data as an illustration
- It is usually best to use [memcpy](https://en.cppreference.com/w/cpp/string/byte/memcpy) (or if using stl either built in assignment operators or [std::copy](https://en.cppreference.com/w/cpp/algorithm/copy))

--

## A Note on smart pointers

- Given the following code

```
#include <memory>

class Memory
{
  public :
    Memory(size_t _size);
    Memory(const Memory &_in)=default;
  private :
    size_t m_size=0;
    std::unique_ptr<int []> m_memory;
};

Memory::Memory(size_t _size)
{
  m_size=_size;
  m_memory=std::make_unique<int []>(_size);
}
int main()
{
  Memory m(100);
  auto m2=m;
}
```

--

## A Note on smart pointers

```
clang++ -std=c++14 main.cpp 
main.cpp:21:8: error: call to implicitly-deleted copy constructor of 'Memory'
  auto m2=m;
       ^  ~
main.cpp:7:5: note: explicitly defaulted function was implicitly deleted here
    Memory(const Memory &_in)=default;
    ^
main.cpp:10:29: note: copy constructor of 'Memory' is implicitly deleted because field 'm_memory'
      has a deleted copy constructor
    std::unique_ptr<int []> m_memory;
                            ^
/opt/rh/devtoolset-7/root/usr/lib/gcc/x86_64-redhat-linux/7/../../../../include/c++/7/bits/unique_ptr.h:657:7: note: 
      'unique_ptr' has been explicitly marked deleted here
      unique_ptr(const unique_ptr&) = delete;
      ^
1 error generated.

```

--

## A note on smart pointers

- Using a smart pointer like ```std::unique_ptr``` forces you to implement a copy ctor.

```
Memory::Memory(const Memory &_in)
{
  m_size=_in.m_size;
  m_memory=std::make_unique<int []>(m_size);
  memcpy(m_memory.get(),_in.m_memory.get(),m_size*sizeof(int));
}

```

---

### Inheritance From Generalization to Specialization

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


## [Shape.h](https://github.com/NCCA/ASELectureCode/blob/master/Lecture5Classes/Shape/include/Shape.h)


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

## [Shape.cpp](https://github.com/NCCA/ASELectureCode/blob/master/Lecture5Classes/Shape/src/Shape.cpp)

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

## [Rectangle.h](https://github.com/NCCA/ASELectureCode/blob/master/Lecture5Classes/Shape/include/Rectangle.h)

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

## [Rectangle.cpp](https://github.com/NCCA/ASELectureCode/blob/master/Lecture5Classes/Shape/src/Rectangle.cpp)

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

## [RectangleMain.cpp](https://github.com/NCCA/ASELectureCode/blob/master/Lecture5Classes/Shape/src/RectangleMain.cpp)

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

- The following examples will demonstrate the practical use of C++ inheritance 
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

## [The inheritance of Constructors](https://github.com/NCCA/ASELectureCode/blob/master/Lecture5Classes/ConstructorInheritance/example1.cpp)

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

## [User defined constructors](https://github.com/NCCA/ASELectureCode/blob/master/Lecture5Classes/ConstructorInheritance/example2.cpp) 

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


## [Inheriting Methods](https://github.com/NCCA/ASELectureCode/blob/master/Lecture5Classes/MethodInheritance/example1.cpp)

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

## What happened here?

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
- There is a one to one mapping in the fist two examples as the type is know
  ```Base::whoAmI()``` and ```Derived::whoAmI()```
- however the line of code

```
Base *ptr = new Derived;

```

- Will call the Derived constructor but still bind the method for the Base type as the compiler doesn't know the concrete type.

---

## Meet the V-Table

- In the previous example the automatic variables are bound to the correct method, however the dynamic (heap) objects are not.
- This is because [*dynamic dispatch*](https://en.wikipedia.org/wiki/Dynamic_dispatch) or *runtime polymorphism* needs a little more work
- This also means there will be more code overhead and perhaps slowdowns added to our code 

--

## [virtual functions](https://github.com/NCCA/ASELectureCode/blob/master/Lecture5Classes/MethodInheritance/example2.cpp)

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

## [example3.cpp](https://github.com/NCCA/ASELectureCode/blob/master/Lecture5Classes/MethodInheritance/example3.cpp)

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

## [pure virtual methods](https://github.com/NCCA/ASELectureCode/blob/master/Lecture5Classes/AbstractClass/example1.cpp)

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


## [example2.cpp](https://github.com/NCCA/ASELectureCode/blob/master/Lecture5Classes/AbstractClass/example2.cpp)

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

## [example3.cpp](https://github.com/NCCA/ASELectureCode/blob/master/Lecture5Classes/AbstractClassexample3.cpp)


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

## [Why use override](https://github.com/NCCA/ASELectureCode/blob/master/Lecture5Classes/Mismatch/example1.cpp)

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

--

# References
- Budd, T 2002 “An introduction to Object Oriented programming” 3rd Edition.  Addison Wesley
- Parsons, David. “Object Oriented Programming with C++” Thomson Learning; 2nd edition 8 Nov 2000
- Priess B. “Data Structures and Algorithms with Object-Oriented Design Patterns in C++”  Wiley 1998
- Eckel B.  “Thinking in C++, 2nd ed. Volume 1”  Prentice Hall 2000

--

# Further Reading
- http://en.wikipedia.org/wiki/Mutable_object
- http://www.parashift.com/c++-faq-lite/const-correctness.html
- http://en.wikipedia.org/wiki/Unified_Modeling_Language
- http://en.wikipedia.org/wiki/Class_diagram
- http://www.ibm.com/developerworks/rational/library/content/RationalEdge/sep04/bell/
- http://www.parashift.com/c++-faq-lite/inline-functions.html


