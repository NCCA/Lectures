# Test Driven Development
## With Python

<p/>Jon Macey <br/>

<p/>jmacey@bournemouth.ac.uk

---

##[Test Driven Development (TDD)](http://butunclebob.com/ArticleS.UncleBob.TheThreeRulesOfTdd)
1. You are not allowed to write any production code unless it is to make a failing unit test pass.
2. You are not allowed to write any more of a unit test than is sufficient to fail; and compilation failures are failures.
3. You are not allowed to write any more production code than is sufficient to pass the one failing unit test.
<center/><iframe width="560" height="315" src="https://www.youtube.com/embed/KtHQGs3zFAM?start=96" frameborder="0" allowfullscreen></iframe>

--

## Test Driven Development (TDD)
- An important aspect of TDD is that changes are made incrementally, in small steps. 
- You write a short test, then write enough code to make that test pass, and then repeat.
- After every small change, you recompile your code and rerun the tests. 
- Working in these small steps means that if a test starts to fail, then in all probability this will be caused by the code you wrote since the last test run. 

--

# TDD in Python

- As python is an interpreted language this is slightly different
- however the main processes are the same
- We have a number of testing frameworks we can use
  - pytest (needs to be installed using pip)
  - unittest (part of the standard python library)
  - doctest (part of the standard python library)


---


## Unit Testing
- A unit test is used to verify a single, minimal unit of source code, such as a method or a class.
- The purpose is to isolate the smallest testable part and verify that they work in isolation.
- They usually run very fast and are typically some form of assertation.
  - True means the test passes
  - false a fail

--

## Unit Testing
- Unit tests tend to be written by developers so are "White Box" tests as the developers know about the source.
- usually tests are placed in a subdirectory of the project
- can have a make test portion of the makefile.

--

## Writing Good Tests
- Writing good tests is hard.
  - Developers tend to write "[clean tests](http://www.planetgeek.ch/wp-content/uploads/2014/11/Clean-Code-V2.4.pdf)" (i.e. test that it works)
  - can be better to write "dirty tests" (i.e. try to break code)
- as mentioned before a systematic approach is best

--

## Qualities of a good test 
- **Fast** tests should run quickly so the tester can get rapid feedback.
  - may be done as part of continuous integration / build such as [jenkins](https://jenkins.io/)
- **Stable** test should be repeatable, independent and consistent. 
  - this can be made more stable using mock objects.


--

## Qualities of a good test
- **Portable** test should work across multiple platforms
  - floating point comparison due to architecture can cause issues here.
- **High Coding Standard** try to use the same coding standard in tests as in production code
- **Reproducible failure** if a test fails it should be easy to reproduce the fail.
  - logging is essential to pinpoint the reason for the failure.

---

## What to test?
- There are a range of QA techniques that can be applied to the writing of tests.
- Depending upon the type of the test these may change 
  - Unit vs Integration etc
- But in general the following strategy can be followed

--

## Condition testing
- you should use the knowledge of the code structure to test all conditions

```
if :

elif :

else :


``` 

- we need to ensure all paths through the code are tested (there are tools)

--

## Equivalence classes

- a set of test inputs that all have the same expected behavior.
- example

```python 
# valid input range 0-65535
def fsqrt(v) :
  # some code
```
- in this case we must test
  - negative numbers (-10)
  - valid number (10)
  - out of range (100000)
  - other types?

--

## Boundary conditions

- Most errors occur around the boundary of expected values.
- Tests should work around these boundaries 
- Example for a list of length n
  - test inserting at position 0,1,n-1 and n

--

## Parameter testing

- A test for any method or function should vary all parameters to the function to verify the full range of functionality
- example [fopen](http://www.cplusplus.com/reference/cstdio/fopen/) mode parameter

```
#include <stdio.h>
FILE * fopen ( const char * filename, const char * mode );
```

- can take the values "r", "w" and "a" in addition to optional "+" and "b" characters in each case. 
- A thorough test should test all 12 combinations.

--

## Return value assertion

- ensures that a function returns correct results for different combinations of its input parameters.
- should also test pass by reference / pointer output parameters
- can be automated using look up tables of results and combined with boundary / equivalence testing

--

## Getter/setter pairs

- Most classes will have getter setter pairs
- as a general rule test that calling the getter before calling the setter returns an appropriate default result 
- and that calling the getter after the setter will return the appropriate value

```
AssertEqual(obj.GetValue(), 0, "test default"); 
obj.SetValue(42);
AssertEqual(obj.GetValue(), 42, "test set then get");

```

---

## A practical example Vec3

<pre><code class="language-plantuml">
@startuml
skinparam classAttributeIconSize 0
class Vec3 {
 + x : float
 + y : float
 + z : float
 
 +  Vec3(x : float , y : float, z : float)
 +  normalize() : Vec3
 +  length() : Vec3 
 
}

@enduml
</code></pre>

- we are going to develop a simple Vec3 class using TDD

--

## Project Setup 

<img src="layout.png" width="100%">

```
mkdir Vec3
cd Vec3
mkdir tests
touch __init__.py
touch Vec3.py
touch tests/__init__.py
touch tests/test_Vec3.py
```

- https://docs.python.org/3/tutorial/modules.html
- note test_ in file names helps with auto-discovery or tests 


--

## tests/test_Vec3.py

```
import unittest
from Vec3 import Vec3
import math

class TestVec3(unittest.TestCase) :
  def test_1(self) :
    self.assert(True == False) # note failing test

```

```
python3 -m unittest

F
======================================================================
FAIL: test_1 (tests.test_Vec3.TestVec3)
----------------------------------------------------------------------
Traceback (most recent call last):
  File "/Users/jmacey/teaching/Code/DemoPythonCode/Testing/Vec3/tests/test_Vec3.py", line 8, in test_1
    self.assertTrue(True == False)
AssertionError: False is not true

----------------------------------------------------------------------
Ran 1 test in 0.000s

FAILED (failures=1)
```

--

## Now Repeat

- We have written enough code to ensure we have a failing test, lets modify to make it closer to a TDD approach

```
import unittest
from Vec3 import Vec3
import math

class TestVec3(unittest.TestCase) :
  def test_default(self) :
    a=Vec3()
    self.assertAlmostEqual(a.x,0.0)
    self.assertAlmostEqual(a.y,0.0)
    self.assertAlmostEqual(a.z,0.0)    
```

- the rest of this code will be developed live.

---

## Doctests

- Doctest is a different approach
- we actually write the tests in the documentation
- personally I don't like this and prefer the unittest approach

--

## Example

```python

class Vec3 :
  x : float 
  y : float 
  z : float
  def __init__(self, x=0.0, y=0.0,z=0.0) :
    """Initialise the Vec3 class

    Default Initialiser
    >>> a=Vec3()

    >>> a.x
    0.0
    >>> a.y
    0.0
    >>> a.z
    0.0

    Let's try a user defined values
    >>> a=Vec3(0.5,0.2,8.0)

    >>> a.x
    0.5

    >>> a.y
    0.2

    >>> a.z
    8.0

    This should throw an exception as we are contructing for a string
    >>> a=Vec3('a','b','c') # doctest: +IGNORE_EXCEPTION_DETAIL
    ValueError: this class only accepts numeric values
    """
    try :
      self.x = float(x)
      self.y = float(y)
      self.z = float(z)
    except ValueError as e:
      raise ValueError("this class only accepts numeric values") from e


if __name__ == "__main__":
    import doctest
    doctest.testmod()
```

--


## Output

```
python -m doctest Vec3.py  -v

Trying:
    a=Vec3()
Expecting nothing
ok
Trying:
    a.x
Expecting:
    0.0
ok
Trying:
    a.y
Expecting:
    0.0
ok
Trying:
    a.z
Expecting:
    0.0
ok
Trying:
    a=Vec3(0.5,0.2,8.0)
Expecting nothing
ok
Trying:
    a.x
Expecting:
    0.5
ok
Trying:
    a.y
Expecting:
    0.2
ok
Trying:
    a.z
Expecting:
    8.0
ok
2 items had no tests:
    Vec3
    Vec3.Vec3
1 items passed all tests:
   8 tests in Vec3.Vec3.__init__
8 tests in 3 items.
8 passed and 0 failed.
Test passed.

```