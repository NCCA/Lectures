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

## Python in DCC Tools

- Maya 2020 and below uses Python version 2.7. 11 on all supported platforms
	- no timeline I can find for upgrade to 3

- Houdini 18.0 features preliminary Python 3 support in the form of a separate set of Houdini build downloads. 

- The Foundry seem to be working on Python 3 Support

- Most Pixar tools (Renderman / USD) work with both Python 2.7 and Python 3

--

## Python 3 

- The latest version of python3 is [3.9](https://www.python.org/downloads/release/python-390/)

- Note that most VFX tools will use 3.7 for the next few years once transitioned
- This is not much of an issue but some nice features such as [f-strings](https://realpython.com/python-f-strings/) are not present.
- [more features here](https://docs.python.org/3/whatsnew/3.8.html)


---

## Keywords

- The following identifiers are keywords in python and must not be used as identifiers
``` python
and       del       from      not       while
as        elif      global    or        with
assert    else      if        pass      yield
break     except    import    print
class     exec      in        raise
continue  finally   is        return
def       for       lambda    try
```

--

## Data Types

- Python is a dynamically typed language, this means that variable values are checked at run-time (sometimes known as “lazy binding”). 
- All variables in Python hold references to objects, and these references are passed to functions by value.
- Python has 5 standard data types
  - numbers, string, list, tuple, dictionary

--

## Numbers

- Python supports four different numerical types:
  - int (signed integers)
  - long (long integers [can also be represented in octal and hexadecimal])
  - float (floating point real values)
  - complex (complex numbers)


--


## unsigned bytes

<div class="stretch">
<iframe src="bytes.html" style="border:0px #FFFFFF solid;" name="code" scrolling="yes" frameborder="1" marginheight="0px" marginwidth="0px" height="100%" width="100%"></iframe>
</div>

--

## signed bytes

<div class="stretch">
<iframe src="signedbyte.html" style="border:0px #FFFFFF solid;" name="code" scrolling="yes" frameborder="1" marginheight="0px" marginwidth="0px" height="100%" width="100%"></iframe>
</div>

--


  ## [numbers](https://github.com/NCCA/DemoPythonCode/blob/master/Basic/numbers.py)

<div class="stretch">
<iframe src="numbers.html" style="border:0px #FFFFFF solid;" name="code" scrolling="yes" frameborder="1" marginheight="0px" marginwidth="0px" height="100%" width="100%"></iframe>
</div>

--

## [Floats are complex](https://evanw.github.io/float-toy/)

<iframe src="https://evanw.github.io/float-toy/" width=1000 height=600></iframe>

--

## Strings
 - Python strings are immutable
 - Python allows for either pairs of single or double quotes
 - Subsets of strings can be taken using the slice operator ( [ ] and [ : ] ) with indexes starting at 0 in the beginning of the string and working their way from -1 at the end
 - The plus ( + ) sign is the string concatenation operator, and the asterisk ( * ) is the repetition operator.

--

## [Strings](https://github.com/NCCA/DemoPythonCode/blob/master/Basic/strings.py) 

 <div class="stretch">
<iframe src="strings.html" style="border:0px #FFFFFF solid;" name="code" scrolling="yes" frameborder="1" marginheight="0px" marginwidth="0px" height="100%" width="100%"></iframe>
</div>

--

## Lists

  - A list is the most common of the Python data containers / types. 
  - It can hold mixed data, include lists of lists
  - A list is contained within the [] brackets and is analogous to C arrays
  - Like a string data is accessed using the slice operator ( [ ] and [ : ] ) with indexes starting at 0 in the beginning of the list and working their way to end-1.
  - The + operator concatenates and the * duplicates

--

## [Lists](https://github.com/NCCA/DemoPythonCode/blob/master/Basic/list.py)

<div class="stretch">
<iframe src="lists.html" style="border:0px #FFFFFF solid;" name="code" scrolling="yes" frameborder="1" marginheight="0px" marginwidth="0px" height="100%" width="100%"></iframe>
</div>

--

## Tuples

- A tuple can be thought of as a read only list.
- it uses parenthesis to contain the list data

--

## [Tuples](https://github.com/NCCA/DemoPythonCode/blob/master/Basic/tuple.py)
<div class="stretch">
<iframe src="tuple.html" style="border:0px #FFFFFF solid;" name="code" scrolling="yes" frameborder="1" marginheight="0px" marginwidth="0px" height="100%" width="100%"></iframe>
</div>

--

## [Slice Operators](https://github.com/NCCA/DemoPythonCode/blob/master/Basic/slice.py)
<div class="stretch">
<iframe src="slice.html" style="border:0px #FFFFFF solid;" name="code" scrolling="yes" frameborder="1" marginheight="0px" marginwidth="0px" height="100%" width="100%"></iframe>
</div>

--

## Python Dictionaries

- Python dictionaries are a powerful key / value data structure which allows the storing of different data types in the same data set
- It is similar to an associative array or hash map in other programming languages
- Many Python API’s use dictionaries to store values and variable length function parameters

--

## [Python Dictionaries](https://github.com/NCCA/DemoPythonCode/blob/master/Basic/dictionary.py)
<div class="stretch">
<iframe src="dictionary.html" style="border:0px #FFFFFF solid;" name="code" scrolling="yes" frameborder="1" marginheight="0px" marginwidth="0px" height="100%" width="100%"></iframe>
</div>

--

## Type Conversion
- Python allows type conversion via a number of functions, the most common are

| Function                | Description                                                          |
|-------------------------|----------------------------------------------------------------------|
| ```int(x ,base)```      | Converts x to an integer. base specifies the base if x is a string   |
| ```long(x,base)```      | Converts x to an long int. base specifies the base if x is a string. |
| ```float(x)```          | Converts x to an float.                                              |
| ```complex(real,img)``` | Generate a complex number                                            |
| ```str(x)```            | Converts x to a string representation                                |

--

## [Type Conversion](https://github.com/NCCA/DemoPythonCode/blob/master/Basic/convert.py)

<div class="stretch">
<iframe src="convert.html" style="border:0px #FFFFFF solid;" name="code" scrolling="yes" frameborder="1" marginheight="0px" marginwidth="0px" height="100%" width="100%"></iframe>
</div>

--

## Python Membership Operators
- There are two membership operators in python “in” and “not in”
- These can be used to test for membership in lists, tuples and strings

--

## [Membership](https://github.com/NCCA/DemoPythonCode/blob/master/Basic/membership.py)

<div class="stretch">
<iframe src="membership.html" style="border:0px #FFFFFF solid;" name="code" scrolling="yes" frameborder="1" marginheight="0px" marginwidth="0px" height="100%" width="100%"></iframe>
</div>

---



---

## References

- [http://vt100.net/docs/tp83/chapter5.html](http://vt100.net/docs/tp83/chapter5.html)
- [http://www.artima.com/weblogs/viewpost.jsp?thread=4829](http://www.artima.com/weblogs/viewpost.jsp?thread=4829)
- [http://www.tutorialspoint.com/python/python_variable_types.htm](http://www.tutorialspoint.com/python/python_variable_types.htm)


--

## References

- [http://en.wikipedia.org/wiki/Environment_variable](http://en.wikipedia.org/wiki/Environment_variable)
- [http://en.wikipedia.org/wiki/Main_function_(programming)](http://en.wikipedia.org/wiki/Main_function_(programming))
- [http://docs.python.org/library/shutil.html](http://docs.python.org/library/shutil.html)
- [http://www.devshed.com/c/a/Python/String-Manipulation/](http://www.devshed.com/c/a/Python/String-Manipulation/)
- [http://docs.python.org/library/string.html](http://docs.python.org/library/string.html)
- [http://www.rafekettler.com/magicmethods.html](http://www.rafekettler.com/magicmethods.html)

