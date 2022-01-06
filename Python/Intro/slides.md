# Lecture 1 
## Introduction to Python

<p/>Jon Macey <br/>

<p/>jmacey@bournemouth.ac.uk

---

## Python
  - python is a very flexible programming language, it can be used in a number of different ways.
  - Most of our animation packages allow for embedded python scripting
  - We can also write complex programs which run stand alone, and if written correctly can run on all operating systems


---


## Hello World

<div class="stretch">
<iframe src="https://trinket.io/embed/python/1976ed6780" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>
</div>

--

## import this

<div class="stretch">
<iframe src="https://trinket.io/embed/python/0e02216451" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>
</div>

--

## import antigravity

<img style="border: 0;" src="../images/antigrav.png" width="40%">
- [python easter eggs](http://digitizor.com/easter-eggs-in-python/)

---

## Lecture Series Outline

- Some basic python commands and techniques
- Interaction with the operating system
- Reading and Writing data to files
- Object Orientation in Python
- Some basic python for the major animation packages 

--

## This lecture

- Today we are going to look at the different versions of python
- some of the basic python building blocks of the language
- some simple concepts

---

## Getting started
- At it’s simplest level python can be used as a simple command interpreter
- We type python into the terminal and we get a prompt which lets us enter commands
- This is know as the REPL [Read, Eval, Print, Loop](https://en.wikipedia.org/wiki/Read%E2%80%93eval%E2%80%93print_loop)
- If nothing else we can use this as a basic calculator
- It is also useful for trying simple bits of code which we wish to put into a larger system

--

## Python 2.7

- Python 2.7 will not be maintained past 1/1/2020. 
- Most of our Animation tools and pipelines still use Python 2.7
- The [vfx reference platform](https://vfxplatform.com/#footnote-python3) is planning to move to Python 3.x
- Transition is slow, but we can plan for the [__future__](https://docs.python.org/3/library/__future__.html)
	- Sometimes this can break things but for simple scripts we can try to future proof


--

## [Python in DCC Tools](https://vfxpy.com/)

- Maya 2020 and below uses Python version 2.7. 11 on all supported platforms
	- Maya 2022 uses Python 3.7.x
- Houdini 18.0 features preliminary Python 3 support in the form of a separate set of Houdini build downloads. 
  - Houdini 19 uses 3.7
- The Foundry seem to be working on Python 3 Support
- Most Pixar tools (Renderman / USD) work with both Python 2.7 and Python 3

--

## Python 3 

- The latest version of python3 is [3.10.0](https://www.python.org/downloads/)
- Note that most VFX tools will use 3.7 for the next few years once transitioned with plans for 3.9 for 2022
- This is not much of an issue but some nice features such as [f-strings](https://realpython.com/python-f-strings/) are not present.
- [more features here](https://docs.python.org/3/whatsnew/3.8.html)


--

## Python Implementations

- Standard python used by most people is CPython (this is also in the DCC tools)
- [iPython](https://ipython.org/) is another version used for many things, including the Jupyter Project
  - This can be installed using [anaconda](https://www.anaconda.com/)
- There are other [alternatives](https://www.python.org/download/alternatives/)

--

## [PyEnv](https://github.com/pyenv/pyenv)

- It can be difficult to manage different version of python on all platforms
  - If you need to use a specific version (for example the same as the DCC)
- I suggest using PyEnv to manage this (it will be in the lab machines under linux soon)
- This basically installs a local version you can use and install packages to using [pip](https://pip.pypa.io/en/stable/)

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

# What Next

- Next time we will look at some more programming constructs
- How functions work in python
- How to make programs out of our scripts