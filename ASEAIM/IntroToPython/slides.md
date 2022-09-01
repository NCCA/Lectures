# Lecture 2 
## Introduction to Python

<p/>Jon Macey <br/>

<p/>jmacey@bournemouth.ac.uk

---

## Keywords

- The following identifiers are keywords in python and must not be used as identifiers

``` python
False      await      else       import     pass
None       break      except     in         raise
True       class      finally    is         return
and        continue   for        lambda     try
as         def        from       nonlocal   while
assert     del        global     not        with
async      elif       if         or         yield
```

--

## Soft Keywords

- New in version 3.10.

- Some identifiers are only reserved under specific contexts. 
- These are known as soft keywords. 
- The identifiers ```match```, ```case``` and ```_``` can syntactically act as keywords in contexts related to the pattern matching statement, but this distinction is done at the parser level, not when tokenizing.

--

## Data Types

- Python is a dynamically typed language, this means that variable values are checked at run-time (sometimes known as “lazy binding”).
- All variables in Python hold references to objects, and these references are passed to functions by value.
- Python has 5 standard data types
  - numbers, string, list, tuple, dictionary

---

## Numbers

- Python supports four different numerical types:
  - int (signed integers)
  - long (long integers [can also be represented in octal and hexadecimal]) 
    - note long is removed in python 3 and int should be used
  - float (floating point real values)
  - complex (complex numbers)

--


  ## numbers

<div class="stretch">
<iframe src="https://trinket.io/embed/python/cbb53e2114" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>
</div>

- The [type()](https://docs.python.org/3/library/functions.html#type) function returns the type of the specified object

--

## [operations on numbers](https://docs.python.org/3/library/stdtypes.html#typesnumeric)

| operation | Result |
|--------|-------|
| ``` x+y``` | sum of x and y |
| ``` x-y``` | difference of x and y |
| ``` x*y``` | product of x and y |
| ``` x/y``` | quotient of x and y |
| ``` x//y``` | floored quotient of x and y |
| ``` -x``` | x negated |
| ``` +x``` | x unchanged |
| ``` x**y``` | x to the power y |

--

## Number Operations 
<div class="stretch">
<iframe src="https://trinket.io/embed/python/46b8cf8940" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>

</div>

--

# [.format](https://docs.python.org/3/tutorial/inputoutput.html)

- The string format function replaces the ```{}``` placeholders with variables

```
print('{} {} {}'.format(1,a,b))
```


- Python 3.8 gives us a new syntax 


```
print(f'{1} {a} {b}')
```

- We will look at format in more detail soon

--

## [int](https://docs.python.org/3/library/stdtypes.html#typesnumeric)

- In Python, integers are zero, positive or negative whole numbers without a fractional part and having unlimited precision
- Python 3 has unlimited size for integers
- Python 2 used two types normal and long.

```
# python 2
>>> 2/3
0

# python 3
>>> 2/3
0.6666666666666666
```

--


## Floating Point (Real) numbers

- To represent fractions we use floating point numbers
- we need to be explicit

<div class="stretch">
<iframe src="https://trinket.io/embed/python/dea20fc3ff" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>
</div>

--

## Floats can be problematic

<div class="stretch">
<iframe src="https://trinket.io/embed/python/4b40ddea31" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>
</div>

--


## [Floats are complex](https://evanw.github.io/float-toy/)
<div class="stretch">
<iframe src="https://evanw.github.io/float-toy/" width=1000 height=600></iframe>
</div>

---

## Strings
 - Python strings are [immutable](https://en.wikipedia.org/wiki/Immutable_object)
 - Python allows for either pairs of single or double quotes

<div class="stretch">
<iframe src="https://trinket.io/embed/python/3c3f22912a" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>
<div>

--

## Strings

 - Subsets of strings can be taken using the slice operator 
   - ( ```[ ]``` and ```[ : ]``` ) with indexes starting at 0 in the beginning of the string and working their way from -1 at the end
 - The plus ( ```+``` ) sign is the string concatenation operator, and the asterisk ( ```*``` ) is the repetition operator.

--

## [Strings](https://github.com/NCCA/DemoPythonCode/blob/master/Basic/strings.py) 

<div class="stretch">
<iframe src="https://trinket.io/embed/python/ae83940224" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>
</div>


---

## Lists

  - A list is the most common of the Python data containers / types. 
  - It can hold mixed data, include lists of lists
  - A list is contained within the [] brackets and is analogous to C arrays
  - Like a string data is accessed using the slice operator ( ```[ ]``` and ```[ : ]``` ) with indexes starting at 0 in the beginning of the list and working their way to end-1.
  - The + operator concatenates and the * duplicates

--

## [Lists](https://github.com/NCCA/DemoPythonCode/blob/master/Basic/list.py)

<div class="stretch">
<iframe src="https://trinket.io/embed/python/a8804f84c8" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>
</div>

--

## Tuples

- A tuple can be thought of as a read only list.
- it uses parenthesis to contain the list data

--

## [Tuples](https://github.com/NCCA/DemoPythonCode/blob/master/Basic/tuple.py)
<div class="stretch">
<iframe src="https://trinket.io/embed/python/1eacddd6e3" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>
</div>

--

## [Slice Operators](https://github.com/NCCA/DemoPythonCode/blob/master/Basic/slice.py)
<div class="stretch">
<iframe src="https://trinket.io/embed/python/d2a27c8c48" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>
</div>

---

## Python Dictionaries

- Python dictionaries are a powerful key / value data structure which allows the storing of different data types in the same data set
- It is similar to an associative array or hash map in other programming languages
- Many Python API’s use dictionaries to store values and variable length function parameters

--

## [Python Dictionaries](https://github.com/NCCA/DemoPythonCode/blob/master/Basic/dictionary.py)
<div class="stretch">
<iframe src="https://trinket.io/embed/python/9fd202917b" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>
</div>

--

## Type Conversion
- Python allows type conversion via a number of functions, the most common are

| Function                | Description                                                          |
|-------------------------|----------------------------------------------------------------------|
| ```int(x ,base)```      | Converts x to an integer. base specifies the base if x is a string   |
| ```long(x,base)```      | Converts x to an long int. base specifies the base if x is a string. |
| ```float(x)```          | Converts x to an float.                                              |
| ```str(x)```            | Converts x to a string representation                                |

--

## [Type Conversion](https://github.com/NCCA/DemoPythonCode/blob/master/Basic/convert.py)

<div class="stretch">
<iframe src="https://trinket.io/embed/python/6a5d6c82f4" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>
</div>

--

## Python Membership Operators
- There are two membership operators in python “in” and “not in”
- These can be used to test for membership in lists, tuples and strings

--

## [Membership](https://github.com/NCCA/DemoPythonCode/blob/master/Basic/membership.py)

<div class="stretch">
<iframe src="https://trinket.io/embed/python/985dafe0e2" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>
</div>

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

## Sequences

<iframe src="https://trinket.io/embed/python/d986b1a5fb" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>

--

## Let's make this more visual

- Python has a module called "Turtle" which allows for simple 2D drawing

> Turtle graphics is a popular way for introducing programming to kids. It was part of the original Logo programming language developed by Wally Feurzeig, Seymour Papert and Cynthia Solomon in 1967.

- I learnt a lot of programming from this.

--

## Let's make this more visual

> Imagine a robotic turtle starting at (0, 0) in the x-y plane. After an import turtle, give it the command turtle.forward(15), and it moves (on-screen!) 15 pixels in the direction it is facing, drawing a line as it moves. Give it the command turtle.right(25), and it rotates in-place 25 degrees clockwise.


--

## A Sequence

<iframe src="https://trinket.io/embed/python/d7e9c4e7f7" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>

--

## Two Squares

<iframe src="https://trinket.io/embed/python/b67ab452a3" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>

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

|Component	 | Meaning |
|------------|---------|
|```def```	| The keyword that informs Python that a function is being defined |
| ```<function_name>``` |	A valid Python identifier that names the function |
| ```<parameters>``` |	An optional, comma-separated list of parameters that may be passed to the function |
| ```:``` |	Punctuation that denotes the end of the Python function header (the name and parameter list) |
| ```<statement(s)>``` |	A block of valid Python statements |

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

<iframe src="https://trinket.io/embed/python/0da890d686" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>

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

## Square Example 1

<iframe src="https://trinket.io/embed/python/35051ca01d" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>


--

## Not quite Rothko

<iframe src="https://trinket.io/embed/python/e921ea00c2" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>



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


## simple if statement

<iframe src="https://trinket.io/embed/python/39713d2c94" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>


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

<iframe src="https://trinket.io/embed/python/e2c242a4d7" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>

--


## Python Logical Operators

<small>given ```a=true b=False```</small>

| <small>Operators    </small>              | <small>Description               </small>                                                                 | <small>Example  </small>          |
|----------------------------|--------------------------------------------------------------------------------------------|--------------------|
| <small>```and```    </small>                | <small>Logical and </small>                                     | <small>a and b is False  </small>|
| <small>```or```  </small>                  | <small>Logical or             </small>                                                            | <small>a or b is True   </small>   |
| <small>```not```   </small>| <small>Logical not   </small>                                    | <small>not (a and b) is True  </small>   |

--

<iframe src="https://trinket.io/embed/python/e2d9dfb5e6" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>

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

## example

<iframe src="https://trinket.io/embed/python/ad7b258486" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>


--

## [```range```](https://docs.python.org/3/tutorial/controlflow.html#the-range-function)

- ```for``` loops are quite often used in conjunction with the ```range``` function
- we use range to generate a sequence and the for runs through each element of the range

```
range(start,stop,step)
```

- By default an integer range value is returned

--

## [```break```](https://docs.python.org/3/tutorial/controlflow.html#break-and-continue-statements-and-else-clauses-on-loops)

- The ```break``` clause allows us to jump out of a loop
- It is usually used in conjunction with an if statement

<iframe src="https://trinket.io/embed/python/f6d47d3f6d" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>


--

## [```continue```](https://docs.python.org/3/tutorial/controlflow.html#break-and-continue-statements-and-else-clauses-on-loops)

- continue will stop the current loop and jump to the next item

<iframe src="https://trinket.io/embed/python/98eff37dc4" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>


--

##  [```-```]()
- ```_``` can be used as a general purpose "throwaway" variable name

<iframe src="https://trinket.io/embed/python/9be5ad2635" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>


--

## for an dictionaries

- the dictionary ```items()``` method returns the key and the value, we could use just ```keys()``` or ```values()```

<iframe src="https://trinket.io/embed/python/635c786486" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>

---

## the [```while```]() statement

-  the while loop executes a set of statements as long as a condition is ```True``` 

<iframe src="https://trinket.io/embed/python/4ecccf600a" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>


--

## input validation

- while is useful for input validation 

<iframe src="https://trinket.io/embed/python/45117bc136" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>

--

## [exceptions](https://docs.python.org/3/tutorial/errors.html)

- python uses exceptions to tell us something has gone wrong there are a number of build in exceptions

<iframe src="https://trinket.io/embed/python/6ae6b5ac79?runMode=console" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>

--

## [try / except blocks](https://docs.python.org/3/reference/compound_stmts.html#try)

- when we want to execute some code that may throw an exception we place it in a ```try : ``` block 
- we then use the ```except [type]: ``` block
<iframe src="https://trinket.io/embed/python/e2cd8c8401" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>

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

<iframe src="https://trinket.io/embed/python/a33d95720c" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>


--

## Generating values 

- it is quite common to generate values within a list constructor 

<iframe src="https://trinket.io/embed/python/3a23dd86b8" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>


--

## using [numpy](https://numpy.org/) for float values

- range only give integer values, we can get float values using the [```numpy.arange```](https://numpy.org/doc/stable/reference/generated/numpy.arange.html) function

<iframe src="https://trinket.io/embed/python/d84219882a" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>


--

## Recursion

- Recursion occurs when a thing is defined in terms of itself or of its type
- in programming this usually done by defining a function and call the same function within itself
- obviously we will need some way of escaping this else it will go on forever
- We use this quite a lot in graphics to traverse hierarchies.  

--

## Recursion 

<iframe src="https://trinket.io/embed/python/704181b38f" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>

--

## Recursion 2

<iframe src="https://trinket.io/embed/python/631a6e404a" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>

---

## Generator Functions and ```yield```

- Generator functions are a special kind of python function that returns what is know as a "Lazy iterator"
  - This means the value is only retrieved when needed using the ```next()``` function
- This can be useful when reading large files or other big data sets
- In the following example we will use it to provide sequential colour values

--

## Colours

<iframe src="https://trinket.io/embed/python/7fe74b873b" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>

--

## Python Iterators

- An iterator is an object that contains a countable number of values.
  - this means we can traverse through all the values
- an iterator is an object which implements the iterator protocol, which consist of the methods __iter__() and __next__().
- Lists, tuples, dictionaries, and sets are all iterable objects (containers).
- As are strings

--

## Iterator Example

<iframe src="https://trinket.io/embed/python/b1304fb411" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>


---

## [L-Systems](https://en.wikipedia.org/wiki/L-system)

<iframe src="https://trinket.io/embed/python/c13ac3c881" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>

---
