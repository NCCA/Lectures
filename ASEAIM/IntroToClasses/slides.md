# Lecture 4 
## Intro to OO in Python

<p/>Jon Macey <br/>

<p/>jmacey@bournemouth.ac.uk


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

![altimage](../images/aggregation.svg)

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

- [http://en.wikipedia.org/wiki/Main_function_(programming)](http://en.wikipedia.org/wiki/Main_function_(programming))
- [http://www.rafekettler.com/magicmethods.html](http://www.rafekettler.com/magicmethods.html)

