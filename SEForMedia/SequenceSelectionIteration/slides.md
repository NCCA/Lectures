
# Lecture 3
## Sequence, Selection and Iteration
## Python Programming Constructs
<p/>Jon Macey <br/>
<p/>jmacey@bournemouth.ac.uk


---

## Overview

- In this lecture we are going to look at programming structures, whilst we are going to use python as the language of choice the concepts are common to most programming languages.
   
- <a href="https://github.com/NCCA/SEForMedia/tree/main/Lecture3" target="_blank">Code examples GitHub</a>

- <a href="https://mybinder.org/v2/gh/NCCA/SEForMedia/HEAD?labpath=Lecture3%2FLecture3.ipynb" target="_blank">Interactive Jupyter Notebooks</a>

---

## What are control Structures?

- Most programming tasks can be split into a combination of the following elements
  - Sequences
  - Selection
  - Iteration
- Whenever I learn a new language I see how these are represented syntactically as this makes learning the language easier.

--

## Sequences

- As the name suggest a sequence is a fixed set of instructions 
- They are always carried out in the same order
- With the use of functions we can bundle other sequences together to make programs easier to read / maintain
- The following example shows this in action

--

## [sequence.py](https://github.com/NCCA/SEForMedia/blob/main/Lecture3/sequence.py)

```python

#!/usr/bin/env python

i=1
print(f'Sequence {i=}')
i=i+1
print(f'Sequence {i=}')
i+=1 # note this is the same as i=i+1
print(f'Sequence {i=}')
i+=1
print(f'Sequence {i=}')
```

```
Sequence i=1
Sequence i=2
Sequence i=3
Sequence i=4
```

--

## Let's make this more visual

- Python has a module called "Turtle" which allows for simple 2D drawing

> Turtle graphics is a popular way for introducing programming to kids. It was part of the original Logo programming language developed by Wally Feurzeig, Seymour Papert and Cynthia Solomon in 1967.

--

## Let's make this more visual

> Imagine a robotic turtle starting at (0, 0) in the x-y plane. After an import turtle, give it the command turtle.forward(15), and it moves (on-screen!) 15 pixels in the direction it is facing, drawing a line as it moves. Give it the command turtle.right(25), and it rotates in-place 25 degrees clockwise.

--

## [turtle_sequence.py](https://github.com/NCCA/SEForMedia/blob/main/Lecture3/turtle_sequence.py)

```python
#!/usr/bin/env python
import turtle 
# create an instance of the turtle object and call it turtle
turtle = turtle.Turtle()
# now we set the shape (default is an arrow)
turtle.shape("turtle")
# now we will run a sequence moving forward then turn left by 90 degrees
turtle.forward(100)
turtle.left(90)
turtle.forward(100)
turtle.left(90)
turtle.forward(100)
turtle.left(90)
turtle.forward(100)
```


--

## [two_squares.py](https://github.com/NCCA/SEForMedia/blob/main/Lecture3/two_squares.py)

```python
#!/usr/bin/env python

import turtle 
# create an instance of the turtle object and call it turtle
turtle = turtle.Turtle()
# now we set the shape (default is an arrow)
turtle.shape("turtle")
# now we will run a sequence moving forward then turn left by 90 degrees
turtle.penup()
turtle.goto(-100,0)

turtle.pendown()
turtle.forward(100)
turtle.left(90)
turtle.forward(100)
turtle.left(90)
turtle.forward(100)
turtle.left(90)
turtle.forward(100)

turtle.penup()
turtle.goto(100,0)

turtle.pendown()
turtle.forward(100)
turtle.left(90)
turtle.forward(100)
turtle.left(90)
turtle.forward(100)
turtle.left(90)
turtle.forward(100)
```

--

## Problems

- There is a lot of repeated code
- It is hard to read and maintainability is low
- This is where [functions](https://www.w3schools.com/python/python_functions.asp) come into play


---

## Functions in Python

- A function is a block of code which only runs when it is called.
- You can pass data, known as parameters, into a function.
- A function can return data as a result.

--

##  ```def```

- The ```def``` keyword is used to define a function or method of a class.

```
def <function>(<params>):
    <body>
```

--

## Function components

|<small>Component</small>	 | <small>Meaning</small> |
|------------|---------|
|<small>```def```	</small>	| <small>The keyword that informs Python that a function is being defined </small>	|
|<small> ```<function_name>```</small>	 |	<small>A valid Python identifier that names the function</small>	 |
|<small> ```<parameters>```</small>	 |	<small>An optional, comma-separated list of parameters that may be passed to the function </small>	|
|<small> ```:``` </small>	|	<small>Punctuation that denotes the end of the Python function header (the name and parameter list)</small>	 |
|<small> ```<statement(s)>```</small>	 |	<small>A block of valid Python statements</small>	 |

--

## [indentation](https://www.python.org/dev/peps/pep-0008/)

- Python uses indentation to block code 
  - convention states we use 4 spaces for indentation (see PEP-8)
- This is unusual as most programming languages use {}
- This can lead to problem, especially when mixing tabs and spaces (python 3 doesn't allow this)
- I will show different examples of this as we go 
- usually this will follow a statement and the ```:``` operator to indicate the start of the block

--


## A simple [Function](https://realpython.com/defining-your-own-python-function/)

```python
#!/usr/bin/env python

def add(a,b) :
    return a+b

a=1
b=2
c=add(a,b)
print(f"{c=}")
str1="hello"
str2=" python"
result=add(str1,str2);
print(f"{result=}")

print(f" {add(1.0,2)=}")
```

```
c=3
result='hello python'
 add(1.0,2)=3.0
```

--

### What happens when I use a function?
<iframe width="800" height="500" frameborder="0" src="http://pythontutor.com/iframe-embed.html#code=def%20add%28a,b%29%20%3A%0A%20%20%20%20return%20a%2Bb%0A%0Ax%3D1%0Ay%3D2%0Aresult%3Dadd%28x,y%29%0Ax%3D%22hello%22%0Ay%3D%22world%22%0Aresult%3Dadd%28x,y%29%0A&codeDivHeight=400&codeDivWidth=350&cumulative=false&curInstr=0&heapPrimitives=nevernest&origin=opt-frontend.js&py=3&rawInputLstJSON=%5B%5D&textReferences=false"> </iframe>

--

## Functions in practice 

- A function needs to be declared before it is called
- These can be placed externally (in another file / module)
- Usually a function will have parameters and it can also return values

--

## Let's design a function

- In one of the earlier examples we used the turtle to draw two squares
- This is idea for a function so we can design one but what do we need?
  - a [name](https://en.wikipedia.org/wiki/Naming_convention_%28programming%29 )
  - useful parameters (and perhaps useful defaults)
  - possible return values

--

## How do we specify a Square?

- There are many ways to do this
  1. Top (x,y) Bottom (x,y)
  2. Start Pos (x,y) Width Height
  3. Center (x,y) Width / Height

- Which one to choose is a matter of design (the hard part)
- Pays to be consistent with other functions
- What other parameters could be add?

--

## [turtle_square.py](https://github.com/NCCA/SEForMedia/blob/main/Lecture3/turtle_square.py)

```python
#!/usr/bin/env python
import turtle

def square(turtle: 'Turtle', x: float, y: float, width: float, height: float) -> None:
    """
    Draws a square using the given turtle object.

    Args:
        turtle (Turtle): The turtle object used to draw the square.
        x (float): The x-coordinate of the starting position.
        y (float): The y-coordinate of the starting position.
        width (float): The width of the square.
        height (float): The height of the square.

    Returns:
        None
    """
    turtle.penup()
    turtle.goto(x,y);
    turtle.pendown()
    turtle.forward(width)
    turtle.left(90)
    turtle.forward(height)
    turtle.left(90)
    turtle.forward(width)
    turtle.left(90)
    turtle.forward(height)

turtle=turtle.Turtle()

square(turtle,20,20,100,100)
```

--

## Type Hints and docstrings

- You will notice there is a lot of extra text here
- This is known as a [docstring](https://www.python.org/dev/peps/pep-0257/)
- This is a way of documenting your code and is very useful for others (and yourself) to understand what the function does

--

## Not quite Rothko

- This demo is a little more complex, it has two files 
- Square.py and rothko.py
- The Square.py file contains the square function which can be run stand alone
- alternatively it may be imported into another file




--

## Is that all for Functions?

- There is a lot more to discuss
- We will look in more depth at other features as we progress
- for now we will continue with some more programming constructs

---

## Selection

- selections allow us to make choices
- most programming languages have at least the if else construct
  - some languages have more (switch case )
- The result of an if operation is a boolean (true / false) value and code is executed or not depending upon these value
- In python we use the following constructs


--


## [selection.py](https://github.com/NCCA/SEForMedia/blob/main/Lecture3/selection.py)

```python
#!/usr/bin/env python

value = input("Enter some text and press enter : ")

if len(value) > 10:
    print("the length of the string is over 10")
else:
    print("the length of the string is under 10")
```


--

## [elif.py](https://github.com/NCCA/SEForMedia/blob/main/Lecture3/elif.py)

- In python we use the ```elif``` keyword to add more conditions

```python
#!/usr/bin/env python

try :
    number = int(input("please enter a number between 1 and 100 : "))
except ValueError:
    print("you did not enter a number")

if number < 1 or number > 100:
    print("the number is not between 1 and 100")
elif number < 50:
    print("the number is less than 50")
else:
    print("the number is greater than 50")
```

--

## try / except

- note in this example we use a try / except block to catch the exception if the user enters a non number
- this is a common pattern in python to catch exceptions
- we will look at this in more detail later

--

## Python Comparison Operators
<small>given ```a=10 b=20```</small>

| <small>Operators    </small>              | <small>Description               </small>                                                                 | <small>Example  </small>          |
|----------------------------|--------------------------------------------------------------------------------------------|--------------------|
| <small>```==```    </small>                | <small>equality operator returns true if values are the same </small>                                     | <small>(a==b) is not true  </small>|
| <small>```!=```  </small>                  | <small>not equal operator             </small>                                                            | <small>(a!=b) is true   </small>   |
| <small>```>```    </small>                 | <small>Checks if the value of left operand is greater than the value of right operand  </small>           |  <small>(a>b) is not true  </small> |
| <small>```<```    </small>                 |  <small>Checks if the value of left operand is less than the value of right operand   </small>              |  <small>(a>b) is true     </small>  |
| <small>```>=```    </small>                |  <small>Checks if the value of left operand is greater than or equal to the value of right operand  </small>| <small> (a>=b) is not true </small> |
| <small>```<=```    </small>                |  <small>Checks if the value of left operand is less than or equal to the value of right operand   </small>  | <small> (a<=) is true   </small>    |

--

## [compare.py](https://github.com/NCCA/SEForMedia/blob/main/Lecture3/compare.py)

```python
#!/usr/bin/env python

a=10
b=20
print(f"{a=}, {b=}")
print(f"{a==b=}")
print(f"{a!=b=}")
print(f"{a>b=}")
print(f"{a<b=}")
print(f"{a>=b=}")
print(f"{a<=b=}")
```

--


## Python Logical Operators

<small>given ```a=true b=False```</small>

| <small>Operators    </small>              | <small>Description               </small>                                                                 | <small>Example  </small>          |
|----------------------------|--------------------------------------------------------------------------------------------|--------------------|
| <small>```and```    </small>                | <small>Logical and </small>                                     | <small>a and b is False  </small>|
| <small>```or```  </small>                  | <small>Logical or             </small>                                                            | <small>a or b is True   </small>   |
| <small>```not```   </small>| <small>Logical not   </small>                                    | <small>not (a and b) is True  </small>   |

--

## [logic.py](https://github.com/NCCA/SEForMedia/blob/main/Lecture3/logic.py)

```python
#!/usr/bin/env python

a=True
b=False

print(f"{a=}, {b=}")
print(f"{a and b=}")
print(f"{a or b=}")
print(f"{not(a and b)=}")
```

```
a=True, b=False
a and b=False
a or b=True
not(a and b)=True
```

--


## [and gates](https://en.wikipedia.org/wiki/AND_gate)

<div class="stretch">
<iframe src="../../Python/and.html" style="border:0px #FFFFFF solid;" name="code" scrolling="yes" frameborder="1" marginheight="0px" marginwidth="0px" height="100%" width="100%"></iframe>
</div>

<p/><small/>simcirjs from https://kazuhikoarase.github.io/simcirjs/

--

## [or gates](https://en.wikipedia.org/wiki/OR_gate)

<div class="stretch">
<iframe src="../../Python/or.html" style="border:0px #FFFFFF solid;" name="code" scrolling="yes" frameborder="1" marginheight="0px" marginwidth="0px" height="100%" width="100%"></iframe>
</div>

<p/><small/>simcirjs from https://kazuhikoarase.github.io/simcirjs/


--

# [not gate (invertor)](https://en.wikipedia.org/wiki/Inverter_(logic_gate)

<div class="stretch">
<iframe src="../../Python/not.html" style="border:0px #FFFFFF solid;" name="code" scrolling="yes" frameborder="1" marginheight="0px" marginwidth="0px" height="100%" width="100%"></iframe>
</div>
 
<p/><small/>simcirjs from https://kazuhikoarase.github.io/simcirjs/

--

## Selection

- selections can be embedded to create quite complex hierarchies of “questions”
- This can sometimes make reading code and maintenance hard especially with the python white space rules as code quite quickly becomes complex to read
- We usually prefer to put complex sequences in functions to make the code easier to read / maintain
- can also be simplified using set operators such as ```in```

--

## [match_case.py](https://github.com/NCCA/SEForMedia/blob/main/Lecture3/match_case.py)

- Python 3.10 and above also has a new feature called [match](https://docs.python.org/3/library/match.html) which is a more powerful version of the switch statement in other languages. 
  
```python
#!/usr/bin/env python

format = "png"

match format:
    case "png":
        print("PNG format selected")
    case "jpeg":
        print("JPEG format selected")
    case "gif":
        print("GIF format selected")
    case _:
        print("Unknown format selected")

```

---


## iteration

- iteration is the ability to repeat sections of code 
- python has two main looping constructs 
  - for each
  - while
- for-each loops operate on ranges of data 
- while loops repeat while a condition is met

--

## [for](https://docs.python.org/3/tutorial/controlflow.html#for-statements)

- A for loop is used for iterating over a sequence 
  - list, tuple, dictionary, set, string
- The iteration is always in the order that they appear in the sequence

--

## [for.py](https://github.com/NCCA/SEForMedia/blob/main/Lecture3/for.py)

```python
#!/usr/bin/env python

list_of_ints =[1,2,3,4,5]
tuple_of_strings=('a','b','c')
a_string ='hello loops'
for i in list_of_ints :
    print(f"{i=}")
print()
for i in tuple_of_strings :
    print(f"{i=}")
print()
for i in a_string :
    print(f"{i=}")

```

```
i=1
i=2
i=3
i=4
i=5

i='a'
i='b'
i='c'

i='h'
i='e'
i='l'
i='l'
i='o'
i=' '
i='l'
i='o'
i='o'
i='p'
i='s'
```

--

## [```range```](https://docs.python.org/3/tutorial/controlflow.html#the-range-function)

- ```for``` loops are quite often used in conjunction with the ```range``` function
- we use range to generate a sequence and the for runs through each element of the range as show in [range.py](https://github.com/NCCA/SEForMedia/blob/main/Lecture3/range.py)


```
range(start,stop,step)
```
```python
#!/usr/bin/env python

for i in range(5):
    print(f"{i=}")  

for x in range(1, 6):
    print(f"{x=}")

for j in range(1, 10, 2):
    print(f"{j=}")
```


--

## [```break```](https://docs.python.org/3/tutorial/controlflow.html#break-and-continue-statements-and-else-clauses-on-loops)

- The ```break``` clause allows us to jump out of a loop
- It is usually used in conjunction with an if statement as shown in [break.py](https://github.com/NCCA/SEForMedia/blob/main/Lecture3/break.py)

```python
#!/usr/bin/env python
import random

# note this is called a list comprehension
# it is a way to create a list in one line of code
numbers = [ random.uniform(-1,10) for i in range(0,10)]
print(numbers)
for n in numbers :
    print(f"{n=}")
    if n < 0.0 :
        print(f'found a negative exiting {n}')
        break
```

--

## [```continue```](https://docs.python.org/3/tutorial/controlflow.html#break-and-continue-statements-and-else-clauses-on-loops)

- continue will stop the current loop and jump to the next item

```python
#!/usr/bin/env python

a=range(0,10)
even=[]
for i in a :
    if i % 2 : # is it even?
        continue
    even.append(i)
print(f"{even=}")
```

--

##  [```-```]()
- ```_``` can be used as a general purpose "throwaway" variable name it is not mandated by the language but is a convention that is widely used

```python
#!/usr/bin/env python

sum = 2
for _ in range(0,10) : 
    sum+=sum
print(f"{sum=}")
```
```
sum=2048
```

--

## [for_dictionary.py](https://github.com/NCCA/SEForMedia/blob/main/Lecture3/for_dictionary.py)

- the dictionary ```items()``` method returns the key and the value, we could use just ```keys()``` or ```values()```

```python
colours = {'red' : [1,0,0],
           'green' : [0,1,0],
           'blue' : [0,0,1]}

print(f"{colours.items()=}")

# note for can unpack the key and value from the dictionary
for colour,value in colours.items() :
    print(f"{colour=} := {value=}")

for colour in colours.keys() :
    print(f"{colour=}")

for values in colours.values() :
    print(f"{values=}")
```

---

## the [```while```]() statement

-  the while loop executes a set of statements as long as a condition is ```True```  as shown in [while.py](https://github.com/NCCA/SEForMedia/blob/main/Lecture3/while.py)

```python
#!/usr/bin/env python

i=10
while(i>=0) :
    print(f"{i=}")
    i-=1
``` 

--

## [input_validation.py](https://github.com/NCCA/SEForMedia/blob/main/Lecture3/input_validation.py)

- while is useful for input validation 

```python
#!/usr/bin/env python


def get_int() :
  while True:
    try:
      userInput = int(input('please enter an int >'))       
    except ValueError:
      print("Not an integer! Try again.")
      continue
    else:
      return userInput 
      break 


end=get_int()
for i in range(0,end) :
    print(i)
```

--

## [exceptions](https://docs.python.org/3/tutorial/errors.html)

- python uses exceptions to tell us something has gone wrong there are a number of build in exceptions [exception1.py]() will throw one. 

```python
#!/usr/bin/env python
a = 10 / 0
int("hello")
colours = {"red": [1, 0, 0]}
colours["purple"]
"2" + 2

```

```
Traceback (most recent call last):
  File "/Volumes/teaching/Code/SEForMedia/Lecture3/./exception1.py", line 2, in <module>
    a=10/0
      ~~^~
ZeroDivisionError: division by zero
```

--

## [zen of python](https://peps.python.org/pep-0020/)

> Errors should never pass silently.

> Unless explicitly silenced.

- this is a key part of python, it is better to fail fast and know what has gone wrong than to have a silent error that is hard to debug
- this is why we have exceptions

--

## [try / except blocks](https://docs.python.org/3/reference/compound_stmts.html#try)

- when we want to execute some code that may throw an exception we place it in a ```try : ``` block 
- we then use the ```except [type]: ``` block

```python
#!/usr/bin/env python

a=10
b=0
try :
    print('Doing Division {}'.format(a/b))
except ZeroDivisionError:
    print('Cant divide by zero')

print('now do something else')
``` 


--

## built in exceptions

- python  has many build in exceptions a list can be found [here](https://docs.python.org/3/library/exceptions.html#concrete-exceptions)
- We can also generate our own exceptions using the ```raise``` keyword
- this is useful when we design our own API's and want to provide useful error messages

--

## looping for x and y

- This example shows how we can loop from -10 in the x and y in increments of 0.5
- In C / C++ we would use a for loop
```c++
for(float y=-10.0f; y<10.0f; ++y)
{
    for(float x=-10.0f; x<10.0f; ++x)
    {
      std::cout<<x<<' '<<y<<'\n';
    }
}
```

--

## float loop

```python
#!/usr/bin/env python

y=-10.0

while y<=2.0 :
    x=-2.0
    while x<=2.0 :
        print(f"{x=},{y=}")
        x+=0.5
    y+=0.5
```

--

## Generating values 

- it is quite common to generate values using list comprehensions
- this is a way to generate a list in one line of code
- this is a very powerful feature of python

```python
n =((a,b)for a in range(0,5)for b in range(0,5))
for i in n :
    print(i)
```

```
(0, 0)
(0, 1)
(0, 2)
(0, 3)
(0, 4)
(1, 0)
(1, 1)
(1, 2)
(1, 3)
(1, 4)
(2, 0)
(2, 1)
(2, 2)
(2, 3)
(2, 4)
(3, 0)
(3, 1)
(3, 2)
(3, 3)
(3, 4)
(4, 0)
(4, 1)
(4, 2)
(4, 3)
(4, 4)
```

--

## using [numpy](https://numpy.org/) for float values

- range only give integer values, we can get float values using the [```numpy.arange```](https://numpy.org/doc/stable/reference/generated/numpy.arange.html) function

```python
#!/usr/bin/env python

import numpy as np

cords = ((x, y) for x in np.arange(-1.0, 1.0, 0.5) for y in np.arange(-1.0, 1.0, 0.5))
for x, y in cords:
    print(x, y)

```

--

## [Recursion](https://en.wikipedia.org/wiki/Recursion_(computer_science))

- Recursion occurs when a thing is defined in terms of itself or of its type
- in programming this usually done by defining a function and call the same function within itself
- obviously we will need some way of escaping this else it will go on forever
- We use this quite a lot in graphics to traverse hierarchies.  

--

## [recursion_turtle.py]() 

```python
#!/usr/bin/env python
import turtle

turtle = turtle.Turtle()
turtle.speed(0)

def spiral(n):
    if n < 300:
        turtle.forward(n)
        turtle.right(91)
        spiral(n+2)


spiral(2)
```

--

## [recursion_tree.py]()

```python
#!/usr/bin/env python
import turtle


def tree(turtle, length):
    if length > 5:
        turtle.forward(length)
        turtle.right(20)
        tree(turtle, length - 15)
        turtle.left(40)
        tree(turtle, length - 15)
        turtle.right(20)
        turtle.backward(length)


turtle = turtle.Turtle()
turtle.penup()
turtle.goto(0, -150)
turtle.left(90)
turtle.pendown()
tree(turtle, 75)

``` 

---

## Generator Functions and ```yield```

- Generator functions are a special kind of python function that returns what is know as a "Lazy iterator"
  - This means the value is only retrieved when needed using the ```next()``` function
- This can be useful when reading large files or other big data sets
- In the following example we will use it to provide sequential colour values

--

## [colour_yield.py]()

```python

#!/usr/bin/env python

import turtle
from turtle import colormode
import random


def colour_function(increment: int = 25) -> tuple:
    """
    Generates a color based on the given increment.

    Args:
    increment (int, optional): The increment value used to generate the color. Defaults to 25.

    Returns:
    tuple: A tuple representing an RGB color, where each value is an integer between 0 and 255.
    """
    red = 0
    green = 0
    blue = 0
    while True:
        colour = (red, green, blue)
        red = red + increment
        if red >= 255:
            red = 0
            green = green + increment
        if green >= 255:
            green = 0
            blue = blue + increment
        if blue >= 255:
            blue = 0
            red = 0
            green = 0
        yield colour


colour = colour_function()
turtle = turtle.Turtle()
turtle.speed(0)
colormode(255)
for i in range(0, 100000):
    current_colour = next(colour)
    print(f"{current_colour=}")
    turtle.color(current_colour)
    turtle.goto(random.uniform(-100, 100), random.uniform(-100, 100))
```
--

## Python Iterators

- An iterator is an object that contains a countable number of values.
  - this means we can traverse through all the values
- an iterator is an object which implements the iterator protocol, which consist of the methods __iter__() and __next__().
- Lists, tuples, dictionaries, and sets are all iterable objects (containers).
- As are strings

--

## Iterator Example

```python
fruit = ("apple", "banana", "cherry")
fruit_it = iter(fruit)

print(next(fruit_it))
print(next(fruit_it))
print(next(fruit_it))

try :
    print(next(fruit_it))
except StopIteration:
    print("none left")
```

---

## [L-Systems](https://en.wikipedia.org/wiki/L-system)

```python
#!/usr/bin/env python
import turtle
from turtle import colormode
from typing import Type
import random


def generate_rule_string(axiom: str, rules: dict[str, str], iterations: int) -> str:
    """
    Generates a rule string based on the given axiom, rules, and number of iterations.

    Args:
        axiom (str): The initial string to start the generation process.
        rules (dict[str, str]): A dictionary where keys are characters in the axiom and values are the replacement strings.
        iterations (int): The number of iterations to apply the rules.

    Returns:
        str: The generated rule string after applying the rules for the specified number of iterations.
    """
    derived = [axiom]  # this is the first seed
    for _ in range(iterations):  # now loop for each iteration
        next_sequence = derived[-1]  # grab the last rule
        next_axiom = [
            rule(char, rules) for char in next_sequence
        ]  # for each element in the rule expand
        derived.append(
            "".join(next_axiom)
        )  # append to the list, we will only need the last element
    return derived


def rule(sequence: str, rules: dict[str, str]) -> str:
    """
    Applies the given rules to the sequence.

    Args:
        sequence (str): The initial string to which the rules will be applied.
        rules (dict[str, str]): A dictionary where keys are characters in the sequence and values are the replacement strings.

    Returns:
        str: The resulting string after applying the rules to the sequence.
    """
    if sequence in rules:
        return rules[sequence]
    return sequence


def draw_lsystem(turtle: Type[turtle], commands: str, length: float, angle: float) -> None:
    """
    Draws an L-system based on the given commands.

    Args:
        turtle (Turtle): The turtle object used to draw the L-system.
        commands (str): The string of commands to control the turtle.
        length (float): The length of each step the turtle takes.
        angle (float): The angle by which the turtle turns.

    Returns:
        None
    """
    stack = []
    for command in commands:
        turtle.pendown()
        if command in ["F", "G", "R", "L", "A"]:  # forward rules for some l system grammars
            turtle.forward(length)
        elif command in ["f", "B"]:
            turtle.penup()
            turtle.forward(length)
        elif command == "+":
            turtle.right(angle)
        elif command == "-":
            turtle.left(angle)
        elif command == "[":
            stack.append((turtle.position(), turtle.heading()))  # save turtle values
        elif command == "]":
            turtle.penup()  # were moving back to save pos
            position, heading = stack.pop()
            turtle.goto(position)
            turtle.setheading(heading)


# F -> Forward
# X -> A place holder for movements
# [ push position and direction onto stack
# ] pop position and direction back to turtle
# + Turn Left
# - Turn Right

axiom = "X"  # start
rules = {"X": "F+[[X]-X]-F[-FX]+X", "F": "FF"}  # fern
iterations = 4  # lower is quicker
length = 10  # lower this if more iterations
angle = 25  # change this to make different shapes

colormode(255)
g = generate_rule_string(axiom, rules, iterations)
print(g[-1])

turtle = turtle.Turtle()
turtle.speed(100)
turtle.penup()
turtle.goto(0, -200)
turtle.left(90)

turtle.color((0, 128, 0))
draw_lsystem(turtle, g[-1], 10, 25)

```

---

## References

- [Python Control Flow](https://docs.python.org/3/tutorial/controlflow.html)
- [Python Functions](https://docs.python.org/3/tutorial/controlflow.html#defining-functions)
- [Python Exceptions](https://docs.python.org/3/tutorial/errors.html)
- [Python Iterators](https://docs.python.org/3/tutorial/classes.html#iterators)