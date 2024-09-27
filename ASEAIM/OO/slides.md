# Lecture 4 Object Oriented Programming
Jon Macey

jmacey@bournemouth.ac.uk

---

## Procedural Programming 
- In procedural programming we use
	- data structures to store information
	- function (passing in the structures) to process the information
- This can lead to complex / large function prototypes passing in and out large amounts of data.

--

## Object Oriented Programming
- In OO Programming we tend to combine both the data and the functions that act on them into a single unit.
- We then place an “interface” to this data know as methods which are allowed to act upon the data in a prescribed way.
- The traditional model of OO is to model “real world” objects, however as we shall discuss this is not really the case.

--


### [Object Oriented Programming is Inherently Harmful](http://harmful.cat-v.org/software/OO_programming/)

- “Object-oriented programming is an exceptionally bad idea which could only have originated in California.” – Edsger Dijkstra
- “object-oriented design is the roman numerals of computing.” – Rob Pike
- “The phrase "object-oriented” means a lot of things. Half are obvious, and the other half are mistakes.“ – Paul Graham

--

### [Object Oriented Programming is Inherently Harmful](http://harmful.cat-v.org/software/OO_programming/)

- “Implementation inheritance causes the same intertwining and brittleness that have been observed when goto statements are overused. As a result, OO systems often suffer from complexity and lack of reuse.” – John Ousterhout Scripting, IEEE Computer, March 1998
- “Sometimes, the elegant implementation is just a function. Not a method. Not a class. Not a framework. Just a function.” – [John Carmack](http://www.gamasutra.com/view/news/169296/Indepth_Functional_programming_in_C.php)

--

### [Object Oriented Programming is Inherently Harmful](http://harmful.cat-v.org/software/OO_programming/)


- “The problem with object-oriented languages is they’ve got all this implicit environment that they carry around with them. You wanted a banana but what you got was a gorilla holding the banana and the entire jungle.” – Joe Armstrong
- “I used to be enamored of object-oriented programming. I’m now finding myself leaning toward believing that it is a plot designed to destroy joy.” – Eric Allman

--

### [Object Oriented Programming is Inherently Harmful](http://harmful.cat-v.org/software/OO_programming/)


- OO is the “structured programming” snake oil of the 90' Useful at times, but hardly the “end all” programing paradigm some like to make out of it.
- And, at least in it’s most popular forms, it’s can be extremely harmful and dramatically increase complexity.
- Inheritance is more trouble than it’s worth. Under the doubtful disguise of the holy “code reuse” an insane amount of gratuitous complexity is added to our environment, which makes necessary industrial quantities of syntactical sugar to make the ensuing mess minimally manageable.


---

## Agents and Communities
- The common "model" of teaching OO is :-
	- An Object Oriented program is structured as a community of interacting agents called objects.
	- Each object has a role to play.
	- Each object provides a service or performs an action that is used by other members of the community

--

## Patterns
- As we will see when building and designing these communities patterns will appear.
- These “design patterns” can be seen as “a general reusable solution to a commonly occurring problem”
- In OO design patterns typically show relationships and interactions between classes or objects, without specifying the final application classes or objects that are involved.


--

# [Gang of Four](https://en.wikipedia.org/wiki/Design_Patterns)

- GOF: "Gang of Four", ie Gamma, Helm, Johnson, Vlissides, authors of "Design Patterns: Elements of Reusable Object-Oriented Software”
- Classic text on OO Design
- Two main considerations 
  - Program to an 'interface', not an 'implementation'.
  - Favour  ‘object composition’ over ‘class inheritance’


--

#[S.O.L.I.D. ](https://en.wikipedia.org/wiki/SOLID_(object-oriented_design)
- A mnemonic to remember the first five principles of Object Oriented design
- Single responsibility, Open-closed, Liskov substitution, Interface segregation and Dependency inversion
- The principles when applied together intend to make it more likely that a programmer will create a system that is easy to maintain and extend over time

--

# [Single Responsibility](http://www.oodesign.com/single-responsibility-principle.html) 
- A class should do only one thing
- This should be entirely encapsulated in the class
- All services (methods) should be narrowly aligned to this responsibility

--

# [Open / Closed](http://www.oodesign.com/open-close-principle.html)
- “software entities (classes, modules, functions, etc.) should be open for extension, but closed for modification”
- This means we shouldn’t modify the source but extend the code using inheritance
- This is sometimes know as “implementation inheritance” 
- This can be done using Abstract base classes

--

## [Liskov substitution principle](http://www.oodesign.com/liskov-s-substitution-principle.html)
- “objects in a program should be replaceable with instances of their subtypes without altering the correctness of that program”
- For a mutable objects  “if S is a subtype of T, then objects of type T in a program may be replaced with objects of type S without altering any of the desirable properties of that program”

--

## [Interface segregation principle](http://www.oodesign.com/interface-segregation-principle.html)
- no client should be forced to depend on methods it does not use.
- ISP splits interfaces which are very large into smaller and more specific ones so that clients will only have to know about the methods that are of interest to them
- Sometimes called “role interfaces”
- This means we make classes “thin” not fat general purpose ones (which sometimes lead to software bloat)

--

## [Dependency inversion principle](http://www.oodesign.com/dependency-inversion-principle.html)
- “One should Depend upon Abstractions. Do not depend upon concretions”
  - High level modules should not depend on low level modules. Both should depend on abstractions.
  - Abstractions should not depend upon details. Details should depend upon abstractions.


---

## Messages and Methods
- Actions are initiated in OO programming by the transmission of a message to an agent (an object) responsible for the action.
- The message encodes the request for an action and is accompanied by any additional information (arguments) needed to carry out that request.
- The receiver is the object to whom the message is sent
- If the receiver accepts the message, it also accepts the responsibility to carry out the indicated action.
- In response to a message, the receiver will perform some method to satisfy the request

--

## Messages vs Procedure calls

```python
#!/usr/bin/env python


def sqr(v: int) -> int:
    return v * v


value = 10
print(f"{sqr(value)=}")
```

--

## Messages vs Procedure calls

- in an Object oriented system we would instead as a class to square itself
- this is done via a message

```
#!/usr/bin/env python

# Note this is a bad design to illustrate a point!
class IntValue:
    def __init__(self, value: int) -> None:
        self.value = value

    def square(self):
        self.value = self.value * self.value

a = IntValue(10)
b = IntValue(20)

a.square()
b.square()
print(f"{a.value=} {b.value=}")

```


--

## Advantages
- Now we have a class we can have many instances of the same same class (each know as an object)
- Each class has it's own unique data (indicated by the self in python)
- We will delve deeper into this syntax later in the lecture

--

# Responsibilities

- In message passing there is a designated receiver. 
- This may not be known until runtime (know as runtime polymorphism)
- This is a form of late binding, this happens at runtime and not compile time like a procedural program.

> Ask not what you can do to your data structures.
Ask what your data structures can do for you. 

[Budd (2002)](http://web.engr.oregonstate.edu/~budd/Books/oopintro3e/info/ReadMe.html)

---

## Object Oriented Concepts [(Kay 1993)](http://gagne.homedns.org/~tgagne/contrib/EarlyHistoryST.html)

- Everything is an Object.
- Computation is performed by objects communicating with each other (via messaging)
- Each Object has it’s own Memory 
- Every object is an instance of a class.
- The class is a repository for behaviour associated with an object.
- Classes are organised into a singly rooted tree structure called the inheritance hierarchy. 

--

## Classes

- Almost everything in python is an object 
- Try typing ```help(float)``` in the terminal
- Each of these have methods (functions) that can be invoked using the ```.``` operator

```python
#!/usr/bin/env python

a = float(10.3)
print(a.conjugate())
print(a.as_integer_ratio())
print(a.hex())
```


--

## The Anatomy of a class

- in some languages data is hidden away (encapsulation) and only accessible via methods of the class
- Python does not do this directly, however we will see how we can simulate this later


---

# Class Diagrams
<div>
<pre>
<code class="language-plantuml">
  @startuml
  Title A class hierachy using inheritance

  SuperClass <|-- Subclass

  Parent <|-- Child
  Parent <|-- Derived
  Parent <|-- SubClass


  @enduml
</code>
</pre>
</div>

<div>
<pre>
<code class="language-plantuml">
  @startuml
  Title  One to many relationship
  class "Class" as a  
  class "Class" as b
  a "1" -o  "*" b : "                 "
  @enduml
</code>
</pre>
</div>

<div>
<pre>
<code class="language-plantuml">
@startuml

Title Zero or One to many relationship
class "Class" as a  
class "Class" as b
a "0..1" -o "*" b : "               "


@enduml
</code>
</pre>
</div>



--

#Associations
- Represents the relation from one class to another
- Most association will be 
  - Has
  - Owns
  - Uses
- In pythons it often translates to an attribute
- Try to be more explicit
  - Renders to
  - Reflects
  - Supports

--

# Associations
- The numbers
  - How many X can Y have
  - How many Y can X have
- Syntax
  - 0..1 May have ONE, or NONE
  - 0..* May have SEVERAL, including NONE
  - 1 Has ONE and only ONE
  - 1..* Has at least ONE, but can have SEVERAL

--


# Composition

<div>
<pre>
<code class="language-plantuml">
@startuml

Title Car has (a)n Engine
"Car      " "0..1" -* "1..1" Engine : "               "

@enduml
</code>
</pre>
</div>

```python 
class Engine :
    self.m_cc=1200;


class Car :
    self.engine = Engine()
```

- Use a filled diamond it always gives a multiplicity of 1 or 0..1
- This implies ownership and when the car is destroyed so is the Engine

--

# Aggregation

<div>
<pre>
<code class="language-plantuml">
@startuml

"World  " "0..1" -o "1..*" Mesh : "                        "

@enduml
</code>
</pre>
</div>


- Aggregation differs from composition as it doesn’t necessarily imply ownership.
- This is usually implemented by containing a reference to another object where the lifetime is determined elsewhere
- This implies a pointer (or smart pointer) of some kind in some languages (not python)

--

# Generalisation
- In C++ this translates to inheritance
- Sometimes we have classes so general they can’t be created (Abstract classes)
- The hierarchy goes from Generalisation to specialisation
- Use a lot in things like Qt [QOBJECT](http://doc.qt.io/qt-5/qobject.html)

---

## methods

- Methods are functions which operate upon the data in the class
- python has a number of special methods that start and end with ```__``` 
- these are know as "dunder" or magic methods we will investigate this when we look at writing our own classes

--

## mutable vs immutable
- A mutable object is one where the data may be modified after creation.
- An immutable object once created may not be modified
- We can further add to this distinction by mixing elements of both in a class
- Methods may also be tagged to say if they modify the internal state of the class or not. 

---

## Unified Modelling Language (UML) 

- Unified Modelling Language (UML) is a standardised general-purpose modelling language
- UML has a number of graphical element which allows us to describe various components of a software system in a standardised way
- We shall use the UML notation for class diagram when designing our classes as well as other elements from the UML 2.x standard

--

# UML Classes

<img src="images/uml1.png" width="100%">

--

## Specifying Attributes
- attributes are specified in the following way
- ```[visibility] name : [data type] ```
- data type is any class type or built in data type

<img src="images/uml2.png" width="100%">

--

## Specifying Methods
- Methods are defined as follows
- ```[visibility] Name( [param] ) : [return type]```
- ```param := [name] : [data type]```
- can have param,param ... 
<img src="images/uml3.png" width="80%">

--

## Accessors and Mutators
- In the previous example we had the methods below
- These methods are know as 
	- Accessors (or get methods) the one returning the value
	- Mutators (or set methods ) which is used to set the class attribute value
- You will notice the get method has a const at the end of the definition as it doesn’t mutate the class

```
float red() const {return m_r;}
void  red(float _r){m_r=_r;}
```

--

## Accessors [(Priess 1998)](http://www.brpreiss.com/books/opus5/html/book.html)
- An accessor is a method that accesses (returns) an attribute of an object but doesn’t modify the object
- In the simplest case, an accessor just returns the value of one of the attributes. 
- In general, an accessor performs some computation using the attributes as long as that computation does not modify any of the attributes.

--

## Mutators [(Priess 1998)](http://www.brpreiss.com/books/opus5/html/book.html)
- A mutator is a method that can modify an object. 
- In the simplest case, a mutator just assigns a new value to one of the attributes. 
- In general, a mutator performs some computation and modifies any number of attributes.

---

## Object Orientation

- Python is fully object−oriented and supports class inheritance
- Defining a class in Python is simple  as with functions, there is no separate interface definition (as used in languages like c++)
- A Python class starts with the reserved word class, followed by the class name.
- Technically, that's all that's required, since a class doesn't need to inherit from any other class.

--

## Python Classes

- Typically a Python class is a self contained .py module with all the code for that module contained within it.
- The class may also have special methods to initialise the data and setup any basic functions

```
class ClassName :
  <statement 1>
  .
  .
  .
  <statement N>
```

--

## A simple Colour Class

<iframe src="https://trinket.io/embed/python/0e6f206748" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>

--

## ```__init__```

- Is the python class initialiser, at it’s simplest level it can be thought of as a constructor but it isn’t!
- The instantiation operation (“calling” a class object) creates an empty object. 
- The ```__init__``` method allows use to set an initial state
- The actual process is the python constructor is ```__new__```
- Python uses automatic two-phase initialisation 
  - ```__new__``` returns a valid but (usually) unpopulated object, 
  - which then has ```__init__``` called on it automatically.

--

  ## methods

- The class methods are defined within the same indentation scope of the rest of the class
- There is no function overloading in Python, meaning that you can't have multiple functions with the same name but different arguments
- The last method defined with a name will be used

--


## self

- There are no shorthands in Python for referencing the object’s members from its methods the method function is declared with an explicit first argument representing the object, which is provided implicitly by the call.
- By convention the first argument of a method is called self. 
- The name self has absolutely no special meaning to Python. 
- Note, however, that by not following the convention your code may be less readable to other Python programmers, and it is also conceivable that a class browser program might be written that relies upon such a convention.


--

## Problems

- some programming languages allow us to define multiple constructors for different types
	- python does not so I can construct the class with a string as demonstrated
- There are different ways to overcome this
	- using type hints to show what should be used [type hints](https://www.python.org/dev/peps/pep-0484/)
	- check type in constructor and respond
	- use [@classmethod](https://stackabuse.com/pythons-classmethod-and-staticmethod-explained/) 

--


## [@classmethod](https://docs.python.org/3/library/functions.html#classmethod)

- the classmethod returns a new instance of an object
<iframe src="https://trinket.io/embed/python/2b7e59ef2b" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>


---

## encapsulation

- In python there is no private or protected encapsulation
- We can access all class attributes using the . operator
- We can also declare instance variables where ever we like in the methods (for example ```self.foo=10 ``` in a method will be available once that method has been called)
- By convention it would be best to declare all instance variables (attributes) in the  ```__init__``` method

--

## Making attributes private
- Whilst python doesn’t support private encapsulation we can fake it using name mangling
- If we declare the ```class``` attributes using ```__``` they will be mangled and hidden from the outside of the class
- This is shown in the following example

--

## Attribute Access

<iframe src="https://trinket.io/embed/python/ecc0bb72db" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>

--


## ```__del__```
- ```__del__``` is analogous to the destructor
- It defines behaviour for when an object is garbage collected
- As there is no explicit delete in python it is not always called
- Be careful, however, as there is no guarantee that ```__del__``` will be executed if the object is still alive when the interpreter exits
- ```__del__``` can't serve as a replacement for good coding practice

---


## [vec3 class](https://github.com/NCCA/DemoPythonCode/blob/master/Classes/Vec3.py)
- The following examples are going to use the following Vec3 class definition

```python
class Vec3 :
	''' a simple Vec3 class for basic 3D calculations etc'''
	def __init__(self,x=0.0,y=0.0,z=0.0) :
		self.x=x
		self.y=y
		self.z=z


	def __str__(self) :
		''' this method will return our data when doing something like print v '''
		return "[%f,%f,%f]" %(self.x,self.y,self.z)

	def __eq__(self,rhs) :
		''' equality test'''
		return self.x == rhs.x and self.y == rhs.y and self.z == rhs.z

	def __ne__(self,rhs) :
		''' not equal test'''
		return self.x != rhs.x or self.y != rhs.y or self.z != rhs.z


	def __add__(self,rhs) :
		''' overloaded + operator for Vec3 = V1+V2'''
		r=Vec3()
		r.x=self.x+rhs.x
		r.y=self.y+rhs.y
		r.z=self.z+rhs.z
		return r

	def __sub__(self,rhs) :
		''' overloaded - operator for Vec3 = V1-V2'''
		r=Vec3()
		r.x=self.x-rhs.x
		r.y=self.y-rhs.y
		r.z=self.z-rhs.z
		return r

	def __mul__(self,rhs) :
		''' overloaded * scalar operator for Vec3 = V1*S'''
		r=Vec3()
		r.x=self.x*rhs
		r.y=self.y*rhs
		r.z=self.z*rhs
		return r

	def __rmul__(self,lhs) :
		''' overloaded * scalar operator for Vec3 = V1*S'''
		r=Vec3()
		r.x=self.x*lhs
		r.y=self.y*lhs
		r.z=self.z*lhs
		return r

	def __iadd__(self,rhs) :
		''' overloaded +- operator for V1+=V2'''
		self.x+=rhs.x
		self.y+=rhs.y
		self.z+=rhs.z
		return self

	def __imul__(self,rhs) :
		''' overloaded *= scalar operator for V1*=2'''
		self.x*=rhs
		self.y*=rhs
		self.z*=rhs
		return self
```

--

## Comparison Operators

- ```__cmp__(self,other)``` is the default comparison operator
- It actually implements behavior for all of the comparison operators (<, ==, !=, etc.)
- It is however best to define your own operators using the individual operator overloads as shown in the next code segment

--

## Comparison Operators

```python
# equality operator ==
__eq__(self,rhs) 
# inequality operator !=
__ne__(self,rhs) 
# less than operator <
__lt__(self,rhs) 
# greater than operator >=
__gt__(self,rhs) 
# less or equal than operator <=
__le__(self,rhs) 
# greater than or equal operator >=
__ge__(self,rhs)

```

--

## ```__str__```
- is used with the built in print function, we can just format the string to do what we want.
- There is also a ```__repr__``` method  used to print a human readable presentation of an object.

--

## Numeric Operators

- The numeric operators are fairly easy, python supports the following operators which take a right hand side argument.

```python
__add__(self, other)
__sub__(self, other)
__mul__(self, other) 
__floordiv__(self, other) 
__div__(self, other) 
__truediv__(self, other) # python 3
__mod__(self, other) 
__divmod__(self, other)
__pow__  # the ** operator
__lshift__(self, other) #<< 
__rshift__(self, other) #>> 
__and__(self, other) # bitwise & 
__or__(self, other) # bitwise | 
__xor__(self, other) # ˆ operator
```

--

## Reflected Operators

- In the previous examples the operators would work like this ```Vec3 * 2``` to make operators that work the other way round we use reflected operators
- In most cases, the result of a reflected operation is the same as its normal equivalent, so you may just end up defining ```__radd__``` as calling ```__add__``` and so on. 

--

## Reflected Operators

```python
__radd__(self, other)
__rsub__(self, other)
__rmul__(self, other) 
__rfloordiv__(self, other) 
__rdiv__(self, other) 
__rtruediv__(self, other) # python 3 
__rmod__(self, other) 
__rdivmod__(self, other)
__rpow__ # the ** operator 
__rlshift__(self, other) #<< 
__rrshift__(self, other) #>> 
__rand__(self, other) # bitwise & 
__ror__(self, other) # bitwise | 
__rxor__(self, other) # ˆ operator

```

--

## Augmented Assignment
- These are the += style operators
```python
__iadd__(self, other)
__isub__(self, other)
__imul__(self, other) 
__ifloordiv__(self, other) 
__idiv__(self, other) 
__itruediv__(self, other) # python 3 
__imod__(self, other) 
__idivmod__(self, other)
__ipow__ # the ** operator 
__ilshift__(self, other) #<< 
__irshift__(self, other) #>> 
__iand__(self, other) # bitwise & 
__ior__(self, other) # bitwise | 
__ixor__(self, other) # ˆ operator
```

--

## Class Representation
- There are quite a few other special class methods that can be used if required

```python
__unicode__(self)
__format__(self, formatstr)
__hash__(self)
__nonzero__(self)
__dir__(self)
__sizeof__(self)
```

---

## Composition and Aggregation

- To build more complex classes we can use composition, we just need to import the correct module

![altimage](./images/aggregation.svg)

--

## Aggregation

<iframe src="https://trinket.io/embed/python/d627452b0b" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>

---

## Inheritance

- in python inheritance is generated by passing in the parent class(es) to the child class
- This will allow all the base class functions to be accessed or override them if defined in the child
- The first example shows a basic inheritance

--

## example

<iframe src="https://trinket.io/embed/python/4ae08d5413" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>

--

## override

<iframe src="https://trinket.io/embed/python/4e308c128f" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>

--

## over ride constructor

<iframe src="https://trinket.io/embed/python/a7998b03b8" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>

---

## References

- [http://en.wikipedia.org/wiki/Environment_variable](http://en.wikipedia.org/wiki/Environment_variable)
- [http://en.wikipedia.org/wiki/Main_function_(programming)](http://en.wikipedia.org/wiki/Main_function_(programming))
- [http://docs.python.org/library/shutil.html](http://docs.python.org/library/shutil.html)
- [http://www.devshed.com/c/a/Python/String-Manipulation/](http://www.devshed.com/c/a/Python/String-Manipulation/)
- [http://docs.python.org/library/string.html](http://docs.python.org/library/string.html)
- [http://www.rafekettler.com/magicmethods.html](http://www.rafekettler.com/magicmethods.html)


--

# References

- Gamma, Erich; Helm, Richard; Johnson, Ralph; Vlissides, John 1994. Design Patterns: Elements of Reusable Object-Oriented Software. Addison-Wesley.
- Steve McConnell. 2004. Code Complete, Second Edition. Microsoft Press, Redmond, WA, USA.
- Martin Reddy, 2011. API Design for C++ Morgan Kaufmann.
- Andrei Alexandrescu  2001. Modern C++ Design, Addison-Wesley.

--

# References

- https://www.tutorialsteacher.com/python/magic-methods-in-python
- http://en.wikipedia.org/wiki/SOLID
- http://en.wikipedia.org/wiki/Liskov_substitution_principle
- “The Pragmatic Programmer”  Andrew Hunt  , David Thomas
- http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.50.3681&rep=rep1&type=pdf


