# Lecture 2 
## Introduction to Python

<p/>Jon Macey <br/>

<p/>jmacey@bournemouth.ac.uk

---

## What is python

- Python is a high-level, interpreted programming language
- It is designed to be simple to use, readable and versatile 
- It was created by Guido van Rossum and first released in 1991. 
- It has now developed into one of the most popular languages for programming

--

## Why Python?
- **Easy to Learn and Use:** simple syntax that is easy to understand, making it an ideal language for beginners. 
- **Interpreted Language:** Python code is executed line-by-line, which makes it easier to debug and test
- **Versatile and Multi-Paradigm:** Python supports multiple programming paradigms, including procedural, object-oriented, and functional programming.

--

## Why Python?

- **Extensive Standard Library and Third-Party Modules:** Python comes with a large standard library and has a vast ecosystem of third-party libraries and frameworks, making it suitable for various applications.
- **Platform Independent:** Python code can run on various operating systems like Windows, macOS, and Linux without requiring modifications.


---

## Keywords

- Python has a few core keywords.
- These are reserved words and can't be used for other [identifiers](https://en.wikipedia.org/wiki/Identifier_(computer_languages))

``` python
>>> import keyword
>>> print(keyword.kwlist)
['False', 'None', 'True', 'and', 'as', 'assert', 'async', 'await', 
 'break', 'class', 'continue', 'def', 'del', 'elif', 'else', 'except', 
 'finally', 'for', 'from', 'global', 'if', 'import', 'in', 'is', 
 'lambda', 'nonlocal', 'not', 'or', 'pass', 'raise', 'return', 'try',
  'while', 'with', 'yield']

```

--

##  Usage

- **Conditional Statements:** if, elif, else
- **Loops:** for, while, break, continue
- **Functions and Classes:** def, class, return, lambda
- **Error Handling:** try, except, finally, raise
- **Logical Operators:** and, or, not, is, in
- **Context Management:** with, as
- **Boolean Values:** True, False, None
- **Variable Scope:** global, nonlocal
- **Asynchronous Programming:** async, await

--

## Identifiers

- In Python (and most programming languages), an **identifier** is a name used to identify a variable, function, class, module, or other objects. 
- Identifiers are essentially the labels you use in your code to reference these objects, making them accessible and manipulatable.

--

## Identifier rules

1. **Must Begin with a Letter or an Underscore (****_****):** Identifiers cannot start with a number. They must start with a letter (A-Z or a-z) or an underscore (_).
2. **Can Contain Letters, Digits, and Underscores:** After the first character, identifiers can include letters, digits (0-9), and underscores.
3. **Case Sensitive:** Identifiers are case-sensitive, meaning var, Var, and VAR would be treated as different identifiers.
4. **No Reserved Keywords:** Identifiers cannot be the same as Python’s reserved keywords 

--

## [Naming is hard](https://hilton.org.uk/blog/why-naming-things-is-hard)

- Whilst the rules above are fairly simple, choosing good identifiers is hard
- Good names are crucial for readability, maintainability, and understanding the purpose of your code. 
  - Be Descriptive and Specific
  - Use Consistent Naming Conventions (see PEP-8)
  - Avoid Ambiguity and Confusion
  - Keep it simple and clear (short but not too short)
  - Use Context from the Code / problem domain

--

## Soft Keywords

- New in version 3.10.
- Some identifiers are only reserved under specific contexts. 
- These are known as soft keywords. 
- The identifiers ```match```, ```case``` and ```_``` can syntactically act as keywords in contexts related to the pattern matching statement, but this distinction is done at the parser level, not when tokenizing.

---

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
    - note long is removed in python 3 and int should be used
  - float (floating point real values)
  - complex (complex numbers)

--


  ## [numbers_demo.py](https://github.com/NCCA/SEForMedia/blob/main/Lecture2/numbers_demo.py)

```python
#!/usr/bin/env python

#!/usr/bin/env python

integer_variable=1  
float_variable=1.2
complex_variable=4+5j

print(f"{integer_variable} is of type {type(integer_variable)}")
print(f"{float_variable} is of type {type(float_variable)}")
print(f"{complex_variable} is of type {type(complex_variable)}")


```

```
1 is of type <class 'int'>
1.2 is of type <class 'float'>
(4+5j) is of type <class 'complex'>
```


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

## [operations.py](https://github.com/NCCA/SEForMedia/blob/main/Lecture2/operations.py)

```python
#!/usr/bin/env python

# modify x and y for different numeric types
x=2
y=5
print(f'{x+y=}')
print(f'{x-y=}')
print(f'{x*y=}')
print(f'{x/y=}')
print(f'{x//y=}')
print(f'{-x=}')
print(f'{+x=}')
print(f'{x**y=}')
```

```
x+y=7
x-y=-3
x*y=10
x/y=0.4
x//y=0
-x=-2
+x=2
x**y=32
```

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

- [f-strings](https://docs.python.org/3/tutorial/inputoutput.html) are very powerful and can be used to format strings in a number of ways

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


### [Floating Point (Real) numbers](https://github.com/NCCA/SEForMedia/blob/main/Lecture2/float_assignment.py)

- To represent fractions we use floating point numbers
- we need to be explicit

```python
#!/usr/bin/env python

a=1
b=1.0
c=float(1)
print(f"{a=} {b=} {c=}")
print(f"{type(a)=}")
print(f"{type(b)=}")
print(f"{type(c)=}")

```
```
a=1 b=1.0 c=1.0
type(a)=<class 'int'>
type(b)=<class 'float'>
type(c)=<class 'float'>
```



--

## [Floats can be problematic](https://github.com/NCCA/SEForMedia/blob/main/Lecture2/float_compare.py)

```python
#!/usr/bin/env python

print(0.2+0.2 == 0.4)
print(0.1+0.2 == 0.3)

print( f"{0.2+0.2=}" )
print( f"{0.1+0.2=}" )

print(f"{(0.1+0.2).hex()=}")
print(f"{(0.3).hex()=}")
```

```
True
False
0.2+0.2=0.4
0.1+0.2=0.30000000000000004
(0.1+0.2).hex()='0x1.3333333333334p-2'
(0.3).hex()='0x1.3333333333333p-2'
```

--


## [Floats are complex](https://evanw.github.io/float-toy/)
<div class="stretch">
<iframe src="https://evanw.github.io/float-toy/" width=1000 height=600></iframe>
</div>

---

## [Strings](https://github.com/NCCA/SEForMedia/blob/main/Lecture2/strings.py)
 - Python strings are [immutable](https://en.wikipedia.org/wiki/Immutable_object)
 - Python allows for either pairs of single or double quotes

```python
hello = "hello world"
print(hello)

text='We can use single "quotes"'

print(text)

text="""Triple single or double quotes
can be used for longer strings. These will
Be
printed
verbatim"""

print(text)

print(u'Unicode strings start with u but not all terminals can print these chars \U0001D6D1 ')
print(u'Omega:  Ω')
```

--

## Strings

 - Subsets of strings can be taken using the slice operator 
   - ( ```[ ]``` and ```[ : ]``` ) with indexes starting at 0 in the beginning of the string and working their way from -1 at the end
 - The plus ( ```+``` ) sign is the string concatenation operator, and the asterisk ( ```*``` ) is the repetition operator.

--

## [Strings](https://github.com/NCCA/SEForMedia/blob/main/Lecture2/string_slice.py) 

```python
#!/usr/bin/env python

str = 'Hello python'

# Prints complete string
print (f"{str=}")
# Prints first character of the string
print (f"{str[0]=}")
# Prints characters starting from 3rd to 6th
print (f"{str[2:5]=}")
# Prints string starting from 3rd character
print (f"{str[2:]=}")
# Prints string two times
print (f"{str * 2=}")
# Prints concatenated string
print (str + " with added text")
```

```
str='Hello python'
str[0]='H'
str[2:5]='llo'
str[2:]='llo python'
str * 2='Hello pythonHello python'
Hello python with added text
```

---

## Lists

  - A list is the most common of the Python data containers / types. 
  - It can hold mixed data, include lists of lists
  - A list is contained within the [] brackets and is analogous to C arrays
  - Like a string data is accessed using the slice operator ( ```[ ]``` and ```[ : ]``` ) with indexes starting at 0 in the beginning of the list and working their way to end-1.
  - The + operator concatenates and the * duplicates

--

## [Lists](https://github.com/NCCA/SEForMedia/blob/main/Lecture2/list.py)
```python
#!/usr/bin/env python

list_1 = [123,"hello",2.45,3+2J]
list_2=[" ","world"]

print(f"{list_1=}")
print(f"{list_1[1]=}")
print(f"{list_1[2:]=}")

hello=list_1[1]+list_2[0]+list_2[1]
print(f"{hello=}")

# this is very much python2 but still common in python3
for i in range(0,len(list_1)) :
    print(f"{list_1[i]=}")
# lists are iterable so we can do this which is preferred in python3
for ch in list_1 :
    print(f"{ch=}")

print('Using enumerate which gives us the index and value')
for num,ch in enumerate(list_1) :
    print(f'{num} {ch}')
```


--

## Tuples

- A tuple can be thought of as a read only list.
- it uses parenthesis to contain the list data

--

## [Tuples](https://github.com/NCCA/SEForMedia/blob/main/Lecture2/tuples.py)
```python
#!/usr/bin/env python

tuple_1 = (123,"hello",2.45,3+2J)
tuple_2=(" ","world")

print( f"{tuple_1=}")
print(f"{tuple_1[1]=}")
print(f"{tuple_1[2:]=}")

hello=tuple_1[1]+tuple_2[0]+tuple_2[1]
print(f"{hello=}")
tuple_1[0]=3
```

```
tuple_1=(123, 'hello', 2.45, (3+2j))
tuple_1[1]='hello'
tuple_1[2:]=(2.45, (3+2j))
hello='hello world'
Traceback (most recent call last):
  File "/Volumes/teaching/Code/SEForMedia/Lecture2/./tuples.py", line 12, in <module>
    tuple_1[0]=3
TypeError: 'tuple' object does not support item assignment
```

---


## slice operators

- slice operators are used to extract parts of sequences like strings, lists, tuples, and other iterable objects. 
- Slicing allows you to access a subset of the elements in these sequences using a specific syntax.

--

## slice operators

- The basic syntax for slicing is:
- 
```sequence[start:stop:step]```

- start: The index where the slice starts (inclusive). If omitted, it defaults to the beginning of the sequence (0).
- stop: The index where the slice ends (exclusive). If omitted, it defaults to the end of the sequence.
- step: The interval between elements in the slice. If omitted, it defaults to 1.

--

## [Slice Operators](https://github.com/NCCA/SEForMedia/blob/main/Lecture2/slice.py)

```python
#!/usr/bin/env python
# create a list of 10 elements
a=list(range(10))

print(f"{a[::1]=}")
print(f"{a[::-1]=}")
print(f"{a[1:10:2]=}")
print(f"{a[:-1:1]=}")
del a[::2]
print(f"{a=}")
print(f"{list(range(10))[slice(0, 5, 2)]=}")
```

```
a[::1]=[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
a[::-1]=[9, 8, 7, 6, 5, 4, 3, 2, 1, 0]
a[1:10:2]=[1, 3, 5, 7, 9]
a[:-1:1]=[0, 1, 2, 3, 4, 5, 6, 7, 8]
a=[1, 3, 5, 7, 9]
list(range(10))[slice(0, 5, 2)]=[0, 2, 4]
```

---

## Python Dictionaries

- Python dictionaries are a powerful key / value data structure which allows the storing of different data types in the same data set
- It is similar to an associative array or hash map in other programming languages
- Many Python API’s use dictionaries to store values and variable length function parameters

--

## [Python Dictionaries](https://github.com/NCCA/SEForMedia/blob/main/Lecture2/dictionary.py)

```python
#!/usr/bin/env python

colours={
          'red' : [1,0,0],
          'green' : [0,1,0],
          'blue' : [0,0,1],
          'white' : [1,1,1],
          'black' : [0,0,0]
}

print(f"{colours.get('red')=}")
print(f"{colours.get('green')=}")
print(f"{colours.get('purple')=}")
# can also use
print(f"{colours['white']=}")
# but
print(f"{colours['purple']=}")
```

```
colours.get('red')=[1, 0, 0]
colours.get('green')=[0, 1, 0]
colours.get('purple')=None
colours['white']=[1, 1, 1]
Traceback (most recent call last):
  File "/Volumes/teaching/Code/SEForMedia/Lecture2/./dictionary.py", line 17, in <module>
    print(f"{colours['purple']=}")
KeyError: 'purple'
```



---

## Type Conversion
- Python allows type conversion via a number of functions, the most common are

| Function                | Description                                                          |
|-------------------------|----------------------------------------------------------------------|
| ```int(x ,base)```      | Converts x to an integer. base specifies the base if x is a string   |
| ```long(x,base)```      | Converts x to an long int. base specifies the base if x is a string. |
| ```float(x)```          | Converts x to an float.                                              |
| ```str(x)```            | Converts x to a string representation                                |

--

## [Type Conversion](https://github.com/NCCA/SEForMedia/blob/main/Lecture2/typeconvert.py)

```python
#!/usr/bin/env python
# create a list of 10 elements
a=list(range(10))

print(f"{a[::1]=}")
print(f"{a[::-1]=}")
print(f"{a[1:10:2]=}")
print(f"{a[:-1:1]=}")
del a[::2]
print(f"{a=}")
print(f"{list(range(10))[slice(0, 5, 2)]=}")
```

```
int_text='12' type <class 'str'>
float_text='0.23123' type <class 'str'>
int_data=123 type <class 'int'>
Traceback (most recent call last):
  File "/Volumes/teaching/Code/SEForMedia/Lecture2/./conversion.py", line 18, in <module>
    err=float("12.3.4")
ValueError: could not convert string to float: '12.3.4'
```

---

## Python Membership Operators
- There are two membership operators in python “in” and “not in”
- These can be used to test for membership in lists, tuples and strings

--

## [Membership](https://github.com/NCCA/SEForMedia/blob/main/Lecture2/membership.py)

```python
#!/usr/bin/env python

data = (123,"hello",2.45,3+2J)
numbers=[1,2,3,4,5]

print(f"{data=}")
print(f"{numbers=}")

print( f"{'world' in data=}")
print( f"{'text' not in numbers=}")
print( f"{99 in numbers=}")
print( f"{2 in numbers=}")



image_types=['png','tiff','tif','jpg','gif']
# note use of lower to ensure we check against correct values
if 'TIFF'.lower() or 'jpg'.lower() in image_types :
  print('Have image')
```

```
data=(123, 'hello', 2.45, (3+2j))
numbers=[1, 2, 3, 4, 5]
'world' in data=False
'text' not in numbers=True
99 in numbers=False
2 in numbers=True
Have image
```

---




## References / Further Reading

- https://www.python.org/doc/
- https://www.python.org/about/gettingstarted/
- https://wiki.python.org/moin/BeginnersGuide

