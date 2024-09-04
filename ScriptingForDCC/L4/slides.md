# Modern Python

Jon Macey

jmacey@bournemouth.ac.uk 

---


## Introduction

- This lecture is intended to introduce some modern features of Python
- It is not intended to be a complete guide to Python (see my [Python course](https://nccastaff.bournemouth.ac.uk/jmacey/Python/) for that)
- This is intended to build on the python you used in the first year
    - and introduce some new concepts such as Object Oriented Programming (OOP)

--

## Python 2 vs Python 3

- Python 2 is no longer supported and was EOL in 2020 there are still some legacy systems that use it
    - Some pipelines in industry still use Python 2.7 in places!
- Luckily most of the DCC tools now use Python3 only however we still lag behind the latest version of Python
- Python 3.11.x is the latest version but most DCC tools use 3.9 or 3.10
- Each new version of python adds new features but sometimes we cant use them.

--

## Example

<asciinema-player src="/jmacey/Lectures/ScriptingForDCC/L4/versions.cast" cols=120 rows=30></asciinema-player>

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

![altimage](images/aggregation.svg)

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

## override constructor

<iframe src="https://trinket.io/embed/python/a7998b03b8" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>

---

# Functional approaches

- functional programming is a style of programming that treats computation as the evaluation of mathematical functions and avoids changing-state and mutable data
- Python is not a functional language but it does support some functional features
- These are useful for writing clean and concise code and will be encountered in certain code bases.

--

## map,filter,reduce

- Map, Filter, and Reduce are three of the core paradigms of functional programming. 
- The allow us to remove loops and branches from our code and make it more concise
- Most of the time in CGI we do the same thing over lots of data
    - e.g. we want to move all the selected objects in a scene

- These functions basically allow us to apply a function to a list of data [(iterables in python)](https://docs.python.org/3/glossary.html#term-iterable).

--

## map,filter,reduce

- map and filter come built-in with Python (in the __builtins__ module) 
- reduce,  needs to be imported as it resides in the [functools](https://docs.python.org/3/library/functools.html) module. 

- we will look at some examples of these in the following slides

--

## [map](https://docs.python.org/3/library/functions.html#map)

- ```map(func,iterables)```
- ```map()`````` passes each element in the iterable through a function and returns the result of all elements having passed through the function.
- ```map()``` returns a map object which is an iterator, so we can iterate over it, if a list is needed we can construct to ```list()```function.
    - Note python2 used to return a list from map which cause some issues when moving from 2-3

--

## [lambda.py](https://github.com/NCCA/ScriptingForDCC/blob/master/Lecture4/lambda.py)

```python
#!/usr/bin/env python


def double(x):
    """This function multiplies its argument by two."""
    return x * 2


a = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
print(a)

# This code applies the double function to each element in the list a and prints the resulting list.
new_list = []
for i in a:
    new_list.append(double(i))
print(new_list)

# This code applies the double_lambda function to each element in the list a and prints the resulting list.
# The map() function applies a given function to each element of an iterable and returns a map object
# # which can be converted to a list.

double_lambda = lambda x: x * 2
map_list = list(map(double_lambda, a))
print(map_list)
# Note we can also use an existing function in map as well as a lambda

func_list=list(map(double, a))
print(func_list)

# or inline the lambda
print(list(map(lambda x: x * 2, a)))
```

--

## [filter](https://docs.python.org/3/library/functions.html#filter)

- ```filter(func,iterables)```
- ```filter()``` offers a way to filter out elements from a list that don’t satisfy certain criteria.
- The function passed to filter() must return a boolean value (either True or False).

--

## [filter.py](https://github.com/NCCA/ScriptingForDCC/blob/master/Lecture4/filter.py)

```python
#!/usr/bin/env python
from __future__ import annotations
import random

random.seed(1234)  # get the same result each time


class Point3:
    """A 3D point class"""

    def __init__(self, x: float = 0.0, y: float = 0.0, z: float = 0.0) -> None:
        """Initialize a Point3 instance"""
        self.x = x
        self.y = y
        self.z = z

    def rand_point() -> Point3:
        """Return a random point"""
        return Point3(
            random.uniform(-10, 10), random.uniform(10, -10), random.uniform(-10, 10)
        )

    def __repr__(self) -> str:
        """Return a string representation of a Point3"""
        return f"Point3({self.x}, {self.y}, {self.z})"


# create 10 random points
points = [Point3.rand_point() for i in range(10)]
print(points)
print(len(points))

above_ground = list(filter(lambda p: p.y >= 0.0, points))
print(above_ground)
print(len(above_ground))

# we can also do this with a list comprehension
above_ground_lc = [p for p in points if p.y >= 0.0]
print(above_ground_lc)
print(len(above_ground_lc))
```

--

## [reduce](https://docs.python.org/3/library/functools.html#functools.reduce)

- ```reduce(func,iterables)```
- ```reduce()``` is useful when you need to apply a function to an iterable and reduce it to a single cumulative value.
- ```reduce()``` works by calling the function that you passed for the first two items in the sequence.

```python
from functools import reduce
reduce(lambda x, y: x+y, [1, 2, 3, 4, 5])
15
```

--

## [reduce.py](https://github.com/NCCA/ScriptingForDCC/blob/master/Lecture4/reduce.py)

```python
#!/usr/bin/env python
from __future__ import annotations
import random
from functools import reduce
from typing import List

try:
    import matplotlib.pyplot as plt

    plot = True

except ImportError:
    plot = False

random.seed(1234)  # get the same result each time


class Point3:
    """A 3D point class"""

    def __init__(self, x: float = 0.0, y: float = 0.0, z: float = 0.0) -> None:
        """Initialize a Point3 instance"""
        self.x = x
        self.y = y
        self.z = z

    def rand_point(range: float = 10.0) -> Point3:
        """Return a random point"""
        return Point3(
            random.uniform(-range, range),
            random.uniform(range, -range),
            random.uniform(-range, range),
        )
        return Point3(self.x + other.x, self.y + other.y, self.z + other.z)

    def __add__(self, rhs: Point3) -> Point3:
        """Add two Point3 instances"""
        return Point3(self.x + rhs.x, self.y + rhs.y, self.z + rhs.z)

    def __truediv__(self, rhs : List[int,float,Point3]) -> Point3:
        p = Point3(self.x, self.y, self.z)
        """Add two Point3 instances"""
        if isinstance(rhs, Point3):
            p.x /= rhs.x
            p.y /= rhs.y
            p.z /= rhs.z
        else:
            p.x /= rhs
            p.y /= rhs
            p.z /= rhs
        return p

    def __repr__(self) -> str:
        """Return a string representation of a Point3"""
        return f"Point3({self.x}, {self.y}, {self.z})"

    def __iter__(self):
        yield self.x
        yield self.y
        yield self.z


# create 10 random points
points = [Point3.rand_point() for i in range(100)]
print(points)
# use reduce to find the centroid of the points

centroid = reduce(lambda p1, p2: p1 + p2, points) / len(points)
print(centroid)

# This code does about the same thing as above
c = Point3(0, 0, 0)
for p in points:
    c += p
print(c / len(points))

if plot:
    for x, y, _ in points:
        plt.scatter(x, y)
    plt.scatter(centroid.x, centroid.y, marker="x")
    plt.show()
```

--

## List comprehensions

- List comprehensions are a way of creating lists based on existing lists
- They can also be used to apply a function or lambda to a list
- In many cases they are more concise than a loop but can be less intuitive to read
- They may also be faster than a for loop

--

## List comprehensions?

- Most things that can be done with a map,filter can be done with a list comprehension
- The following example shows how to use a list comprehension to create a list of squares

```python
squares = [x**2 for x in range(10)]
print(squares)
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
```

--

## map,filter,reduce

- List comprehensions create lists again, so using only list comprehensions is not going to work in a reduce

```python
#!/usr/bin/env python

from functools import reduce

a=list(range(10))
b=[x*2 for x in a]
print("map using list comprehension")
print(f"{a}\n{b}")

print("filter using list comprehension")
c=[x for x in a if x%2==0]
print(f"{a}\n{c}")

print("reduce using list comprehension (not recommended)")
total = sum([a[0]] + [x for x in a[1:]])
print(f"{a}\n{total}")
```

--

## Convert loops to list comprehensions

```python
#!/usr/bin/env python

import random
import string


def rand_name(min: int = 5, max: int = 20) -> str:
    return "".join(
        random.choices(string.ascii_letters)
        + (
            random.choices(
                string.ascii_letters + string.digits, k=random.randint(min, max)
            )
        )
    )


# create a list of 10 random strings of length 5-20
names = [rand_name() for _ in range(10)]
print(names)

# create a list of the string lengths next to the strings and sort
# as the length is the 2nd element we need to use the key parameter
lengths = sorted([(name, len(name)) for name in names], key=lambda x: x[1])
print(lengths)

# double loop
for x in range(3):
    for y in range(5, 8):
        print(f"{x} * {y} = {x*y}")

# list comprehension
print([f"{x} * {y} = {x*y}" for x in range(3) for y in range(5, 8)])

```

--

## So what should I use?

- In general it is best to use the most readable code
- If you are working in a team then it is best to use the style that the team uses
- It is really powerfull but what does this (out of context code) do?

```python
self.m = [list(item) for item in zip(*self.m)]
```

---

## Working with lists

- Python has a number of built in functions for working with lists
- These are useful for manipulating lists and can be used to make code more concise
- The following slides show some of the more useful functions

--

## [all](https://docs.python.org/3/library/functions.html#all)

- ```all(iterable)```
- Return True if all elements of the iterable are true (or if the iterable is empty).

```python
all([True, True, True])
True
all([True, False, True])
False
all([])
True
```

--

## [any](https://docs.python.org/3/library/functions.html#any)

- ```any(iterable)```
- Return True if any element of the iterable is true. If the iterable is empty, return False.

```python
any([True, True, True])
True
any([True, False, True])
True
any([])
False
```

--

## Example

```python
#!/usr/bin/env python
from __future__ import annotations
import random

random.seed(1234)  # get the same result each time


class Point3:
    """A 3D point class"""

    def __init__(self, x: float = 0.0, y: float = 0.0, z: float = 0.0) -> None:
        """Initialize a Point3 instance"""
        self.x = x
        self.y = y
        self.z = z

    def rand_point() -> Point3:
        """Return a random point"""
        return Point3(
            random.uniform(-10, 10), random.uniform(10, -10), random.uniform(-10, 10)
        )

    def __repr__(self) -> str:
        """Return a string representation of a Point3"""
        return f"Point3({self.x}, {self.y}, {self.z})"


# create 10 random points
points = [Point3.rand_point() for i in range(10)]

if any([p.y < 0 for p in points]):
    print("At least one point has a negative y value")

if all([p.y > 0 for p in points]):
    print("All points have a positive y value")
else :
    print("Not all points have a positive y value")


```

--

## [enumerate](https://docs.python.org/3/library/functions.html#enumerate)

- ```enumerate(iterable, start=0)```
- Return an enumerate object. iterable must be a sequence, an iterator, or some other object which supports iteration.

```python
seasons = ['Spring', 'Summer', 'Autumn', 'Winter']
list(enumerate(seasons))
[(0, 'Spring'), (1, 'Summer'), (2, 'Autumn'), (3, 'Winter')]
list(enumerate(seasons, start=1))
[(1, 'Spring'), (2, 'Summer'), (3, 'Autumn'), (4, 'Winter')]
```

--

## [zip](https://docs.python.org/3/library/functions.html#zip)

- ```zip(*iterables)```
- Make an iterator that aggregates elements from each of the iterables.

```python
x = [1, 2, 3]
y = [4, 5, 6]
zipped = zip(x, y)
list(zipped)
[(1, 4), (2, 5), (3, 6)]
```

---

# References

- https://docs.python.org/3/library/functions.html
