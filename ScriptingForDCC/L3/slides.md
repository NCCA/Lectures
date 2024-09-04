# Testing and TDD

Jon Macey

jmacey@bournemouth.ac.uk 

---


## Introduction

- Testing is a huge area of software development
- Becomes vitally important if developing API's for 3rd party use
  - need to ensure you don't break others code

--

## Types of Testing

- [Unit Testing](https://en.wikipedia.org/wiki/Unit_testing)
> "Is the execution of a complete class, routine, or small program that has been written by a single programmer or team of programmers, which is tested in isolation from the more complex system".

--


## Types of Testing

- [Component Testing](http://sqa.stackexchange.com/questions/12630/what-is-component-testing-and-how-to-write-component-test-cases)
> "Is the execution of a  class, package, small program or other program element that has been written by a single programmer or team of programmers, which is tested in isolation from the more complex system".

--

## Types of Testing

- [Integration Testing](http://softwaretestingfundamentals.com/integration-testing/)
> "Is the combined execution of two or more classes, packages, components or sub-systems that have been created by multiple programmers or programming teams. This type of testing typically starts as soon as there are two classes to test and continues until the entire system is complete".

--

## Types of Testing

- [Regression Testing](https://en.wikipedia.org/wiki/Regression_testing)
> "Is the repetition of previously executed test cases for the purpose of finding defects in software that previously passed the same set of tests"


--

## Types of Testing

- [System Testing ](https://en.wikipedia.org/wiki/System_testing)
> "Is the execution of the software in its final configuration, including integration with other software and hardware systems. It tests for security, performance, resource loss, timing problems, and other issues that can't be tested at lower levels of integration"

---

## Developer Testing
- Developer can test during construction
- Test first or Test Last?
  - Test First Write tests then write code
  - Write code then write tests

--

## Tests First
- Writing test cases before writing the code doesn't take more time.
- Can help to detect defects earlier (and correct them)
- Make you think about the requirements more
  - can expose requirements problems earlier
- Generally considered best to write tests first

---

## Approaches
- Needs to be systematic
  - Test for each relevant requirement
  - Test for each relevant design concern

--

## [White Box Testing](https://en.wikipedia.org/wiki/White-box_testing)
- Tests are developed with knowledge of the source code.
- Written using the same programming language as the API / Code 
- Tests the flow / structure of the code 

--

## [Black Box Testing](https://en.wikipedia.org/wiki/Black-box_testing)
- Test developed based on specification
- Has no knowledge of the underlying code (hence can work on API / LIBS)
- Can be executed by using an end user application.

--

## [Grey Box Testing](https://en.wikipedia.org/wiki/Gray_box_testing)
- A combination of Black / White Box testing
- Testing is implemented with knowledge of internals but using external applications

---

## [Non Functional Testing](https://en.wikipedia.org/wiki/Non-functional_testing)
- These tests may also be required for API's and larger systems.
- **Performance Testing** :- usually speed or memory requirements
- **Load Testing** :- put stress on the system (users, network, disk etc etc)
- **Scalability Testing** :- test with large amounts of data (capacity / volume testing)

--

## [Non Functional Testing](https://en.wikipedia.org/wiki/Non-functional_testing)
- **Soak Testing** :- run the software continuously over an extended period to ensure it is robust (memory leaks etc)
- **Security Testing** :- test the security requirements for the code, such as confidentiality, authentication etc.
- **Concurrency Testing** :- test that the code will work in a concurrent environment (threading, shared data etc).

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

## [example](http://www.apibook.com/blog/archives/category/test)

- given the following C++ function to convert a string to a double

```
bool stringToDouble(const std::string &str, double &result);
```

- Given this function the unit test perform a series of checks to ensure that it works as expected

--

## example

```
/// \file   main.cpp
/// \author Martin Reddy
/// \brief  An example of a unit test.
///
/// Copyright (c) 2010, Martin Reddy. All rights reserved.
void Test_StringToDouble()
{
	double value;

	Assert(StringToDouble("1", value), "+ve test");
	AssertEqual(value, 1.0, "'1' == 1.0");

	Assert(StringToDouble("-1", value), "-ve test");
	AssertEqual(value, -1.0, "'-1' == -1.0");

	Assert(StringToDouble("0.0", value), "zero");
	AssertEqual(value, 0.0, "'0.0' == 0.0");

	Assert(StringToDouble("-0", value), "minus zero");
	AssertEqual(value, -0.0, "'-0' == -0.0");
	AssertEqual(value, 0.0, "'-0' == 0.0");

	Assert(StringToDouble("3.14159265", value), "pi");
	AssertEqual(value, 3.14159265, "pi value");

	Assert(StringToDouble("2e10", value), "+ve scientific");
	AssertEqual(value, 2e10, "");

	Assert(StringToDouble("+4.3e-10", value), "-ve scientific");
	AssertEqual(value, 4.3e-10, "");

	AssertFalse(StringToDouble("", value), "empty");
	AssertFalse(StringToDouble("   ", value), "whitespace");
	AssertFalse(StringToDouble("+-1", value), "+-");
	AssertFalse(StringToDouble("1.1.0", value), "multiple points");
	AssertFalse(StringToDouble("text", value), "not a number");

	cout << "SUCCESS! Unit test passed." << endl;
}
```

--

## [JUnit](http://junit.org/junit4/)

- You will notice the various Assert functions in the previous example
- These are common functions in unit testing frameworks, which follow the JUnit style
- What is wrong with the AssertEqual test below WRT the previous example

```
// define some simple assertion routines
void Assert(bool result, const std::string &desc)
{
	if (result)
		return;
	std::cout << "FAIL: " << desc << '\n';
}

void AssertFalse(bool result, const std::string &desc)
{
	Assert(! result, desc);
}

void AssertEqual(double val1, double val2, const std::string &desc)
{
	if (val1 == val2)
		return;
	std::cout << "FAIL: " << desc << '\n';
	std::cout << val1 << " != " << val2 << '\n';
}
```

--

## example

- The previous example is very simple
- In real software we may have dependencies upon other objects or external resources
- This lead to two different views on Unit Testing

--

## Fixture Setup
- The classic approach to unit testing is to initialize a consistent environment or fixture before each test is run
- this is usually done in a setup() type function 
  - will copy resources
  - load databases
  - initialize singletons / state.
- may have a tearDown() function to clean up after

--

## Stub / mock objects
- In this approach code under test is isolated from the rest of the system by creating sub / mock objects that stand in for the dependencies
- The result is completely isolated from the system (i.e. files, databases etc)
  - Creation of sub / mock objects can be tedious
  - But can be more flexible than the real system
  - Useful if things like network failure need to be tested as we can simulate this

---

## Writing Good Tests

- Writing good tests is hard.
  - Developers tend to write "[clean tests](http://www.planetgeek.ch/wp-content/uploads/2014/11/Clean-Code-V2.4.pdf)" (i.e. test that it works)
  - can be better to write "dirty tests" (i.e. try to break code)
- as mentioned before a systematic approach is best

--

## Qualities of a good test 
- **Fast** tests should run quickly so the tester can get rapid feedback.
  - may be done as part of continuous integration / build such as [github actions](https://github.com/features/actions)
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
if() ...
else ...

switch()
{
  case 'a' ....
}
``` 

- we need to ensure all paths through the code are tested.

--

## Equivalence classes

- a set of test inputs that all have the same expected behaviour.
- example

```
// valid input range 0-65535
float sqrt(unsigned short _v);
```
- in this case we must test
  - negative numbers (-10)
  - valid number (10)
  - out of range (100000)

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

--

## Other tests
- **Operation order** :- Varying the sequence of operations to perform the same test 
- **Regression testing** :- testing against earlier version (files, scenes etc) 
- **Buffer Overruns** :- test what happens with corruptions of memory
- **Memory ownership** :- check ownership of memory / pointers (can also do NULL input tests with this)

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


---

## 3rd Party testing Frameworks
- [there are many 3rd party testing frameworks](https://en.wikipedia.org/wiki/List_of_unit_testing_frameworks)
- these cover many languages but most have similar idioms / syntax
- for C++ I typically [google test](https://github.com/google/googletest)
- For a quick overview see the [primer](https://github.com/google/googletest/blob/master/googletest/docs/Primer.md) 

--

## Python Testing Frameworks

- [PyUnit](https://docs.python.org/3/library/unittest.html) is a simple unit testing framework that ships with python 
- [PyTest](https://docs.pytest.org/en/7.4.x/) has more expressive and flexible assertion handling compared to unittest.
- [Doctest](https://docs.python.org/3/library/doctest.html) is a simple framework that allows you to embed tests in the docstrings of your code.
  - However these can be read from a text file as well.

--

## Python Testing Frameworks

- I will use a combination of PyUnit and PyTest for most of my examples
- Whilst doctest is useful it is not as flexible as PyUnit / PyTest
  - personally I think it adds too much noise to the code

--

## unittest

- Uses the same process of [asserts](https://docs.python.org/3/library/unittest.html#assert-methods)

|Method | Checks that| New in |
|-------|------------|--------|
|assertEqual(a, b) | a == b | |
|assertNotEqual(a, b) | a != b | |
|assertTrue(x) | bool(x) is True | |
|assertFalse(x) | bool(x) is False | |
|assertIs(a, b) | a is b | 3.1 |
|assertIsNot(a, b) | a is not b | 3.1 |
|assertIsNone(x) | x is None | 3.1 |

--

## Asserts continued

|Method | Checks that| New in |
|-------|------------|--------|
|assertIsNotNone(x) | x is not None | 3.1 |
|assertIn(a, b) | a in b | 3.1 |
|assertNotIn(a, b) | a not in b | 3.1 |
|assertIsInstance(a, b) | isinstance(a, b) | 3.2 |
|assertNotIsInstance(a, b) | not isinstance(a, b) | 3.2 |

--

## Specific asserts

|Method | Checks that| New in |
|-------|------------|--------|
| assertAlmostEqual(a, b) | round(a-b, 7) == 0 | |
| assertNotAlmostEqual(a, b) | round(a-b, 7) != 0 | |
| assertGreater(a, b) | a > b | 3.1 |
| assertGreaterEqual(a, b) | a >= b | 3.1 |
| assertLess(a, b) | a < b | 3.1 |
| assertLessEqual(a, b) | a <= b | 3.1 |

--

## Specific asserts

|Method | Checks that| New in |
|-------|------------|--------|
| assertRegex(s, r)| r.search(s)| 3.1 |
| assertNotRegex(s, r)| not r.search(s)| 3.2 |
| assertCountEqual(a,b) | a and b have the same elements in the same number, regardless of their order. | 3.2 |

---

## PyTest 

- PyTest is a more expressive and flexible testing framework than unittest
- It has a number of [asserts](https://docs.pytest.org/en/7.4.x/assert.html) that are similar to unittest
- But also has a number of [other features](https://docs.pytest.org/en/7.4.x/contents.html#toc) that make it more flexible

- In particular to use it allows the use of the [approx](https://docs.pytest.org/en/latest/reference/reference.html#pytest-approx) function to test floats

--

## PyTest Fixtures

- PyTest has a number of [fixtures](https://docs.pytest.org/en/7.4.x/fixture.html) that can be used to setup tests
- these use the [decorator](https://peps.python.org/pep-0318/) syntax to define the fixture

```python
@pytest.fixture

```

---

## Getting Started

- The typical TDD process is to start with a failing test and then write the code to make it pass.
- In the current case we are going to implement and design a Vec3 class
- We will store x,y,z components as floats (this becomes problematic with python)
- We will start with a simple test to check that the class exists

--

## A Vec3 class

- We are going to develop a simple Vec3 class with associated methods for simple math functions.
- The overall design of the class is based on this [blog post](https://nccastaff.bournemouth.ac.uk/jmacey/post/PythonClasses/pyclasses/)

- The class will be stored in a file called Vec3.py and use the [```__slots__```](https://docs.python.org/3/reference/datamodel.html#slots) dunder method to store the data.

--

## Vec3.py

```python
"""
Simple Float only Vec3 class for 3D graphics
"""
from __future__ import annotations
import math


class Vec3:
    __slots__ = ["x", "y", "z"]
    """by using slots we fix our class attributes to x,y,z
    Note below we use type hints to help mypy but these 
    are still part of the slots and there is no class dictionary"""
    x: float
    y: float
    z: float

    def __init__(self, x: float = 0.0, y: float = 0.0, z: float = 0.0) -> None:
        """We prefer float here hence the type hint however other will still work"""
        self.x = x
        self.y = y
        self.z = z

    def __add__(self, rhs: Vec3) -> Vec3:
        "return a+b vector addition"
        r = Vec3()
        r.x = self.x + rhs.x
        r.y = self.y + rhs.y
        r.z = self.z + rhs.z
        return r

    def __iadd__(self, rhs: Vec3) -> Vec3:
        "return a+=b vector addition"
        self.x += rhs.x
        self.y += rhs.y
        self.z += rhs.z
        return self

    def __sub__(self, rhs: Vec3) -> Vec3:
        "return a+b vector addition"
        r = Vec3()
        r.x = self.x - rhs.x
        r.y = self.y - rhs.y
        r.z = self.z - rhs.z
        return r

    def __isub__(self, rhs: Vec3) -> Vec3:
        "return a+=b vector addition"
        self.x -= rhs.x
        self.y -= rhs.y
        self.z -= rhs.z
        return self

    """Note mypy will give error here 
    error: Argument 1 of "__eq__" is incompatible with supertype "object"; supertype defines the argument type as "object"  [override]
    note: This violates the Liskov substitution principle
    note: See https://mypy.readthedocs.io/en/stable/common_issues.html#incompatible-overrides
    note: It is recommended for "__eq__" to work with arbitrary objects, for example:
    
    We add the ignore here as this is what we want to do
    """

    def __eq__(self, rhs: Vec3) -> bool:  # type: ignore[override]
        "test a==b using math.isclose"
        if not isinstance(rhs, Vec3):
            return NotImplemented
        return (
            math.isclose(self.x, rhs.x)
            and math.isclose(self.y, rhs.y)
            and math.isclose(self.z, rhs.z)
        )

    def __neq__(self, rhs: Vec3) -> bool:
        "test a==b using math.isclose"
        if not isinstance(rhs, Vec3):
            return NotImplemented
        return (
            math.isclose(self.x, rhs.x)
            or math.isclose(self.y, rhs.y)
            or math.isclose(self.z, rhs.z)
        )

    def __neg__(self) -> Vec3:
        self.x = -self.x
        self.y = -self.y
        self.z = -self.z
        return self

    def set(self, x: float, y: float, z: float) -> None:
        "set from x,y,z"
        try:
            self.x = float(x)
            self.y = float(y)
            self.z = float(z)
        except ValueError:
            print("need float values")
            raise

    def dot(self, rhs: Vec3) -> float:
        "return the dot product this vector with rhs"
        return self.x * rhs.x + self.y * rhs.y + self.z * rhs.z

    def length(self) -> float:
        "length of vector"
        return math.sqrt(self.x**2 + self.y**2 + self.z**2)

    def length_squared(self) -> float:
        "square length of vector"
        return self.x**2 + self.y**2 + self.z**2

    def inner(self, rhs: Vec3) -> float:
        return (self.x * rhs.x) + (self.y * rhs.y) + (self.z * rhs.z)

    def cross(self, rhs: Vec3) -> Vec3:
        return Vec3(
            self.y * rhs.z - self.z * rhs.y,
            self.z * rhs.x - self.x * rhs.z,
            self.x * rhs.y - self.y * rhs.x,
        )

    def normalize(self) -> None:
        "normalize this vector"
        len = self.length()
        try:
            self.x /= len
            self.y /= len
            self.z /= len
        except ZeroDivisionError:
            raise

    def reflect(self, n: Vec3) -> Vec3:
        d = self.dot(n)
        #  I - 2.0 * dot(N, I) * N
        return Vec3(
            self.x - 2.0 * d * n.x, self.y - 2.0 * d * n.y, self.z - 2.0 * d * n.z
        )

    def __repr__(self) -> str:
        return f"Vec3 [{self.x},{self.y},{self.z}]"

    def __str__(self) -> str:
        return f"[{self.x},{self.y},{self.z}]"

    def __mul__(self, rhs: float) -> Vec3:
        "piecewise scalar multiplication"
        if isinstance(rhs, (float, int)):
            self.x *= rhs
            self.y *= rhs
            self.z *= rhs
            return self
        else:
            raise ValueError

    def __rmul__(self, rhs: float) -> Vec3:
        "piecewise scalar multiplication"
        return self * rhs
```

--

## Type Annotation (Hints)

- Type hints were added to python 3.5 as a way of adding support for linters and 3rd party tools to check code for possible errors. 
- These have no effect of the running of the code and are not mandatory, however they are good software engineering practice and we encourage their use throughout your code.

- For a quick intro to the type hints look [here](https://nccastaff.bournemouth.ac.uk/jmacey/sfdcc/seminars/TypeHints/TypeHints/)


--

## [MyPy](https://mypy.readthedocs.io/en/stable/)


<asciinema-player src="/jmacey/Lectures/ScriptingForDCC/L3/mypy.cast" cols=120 rows=30></asciinema-player>


---

## Vec3 unittests

- The whole of this class was written using TDD, and we will do more practice in the lab
- I'm now presenting the whole complete class to show how things work
- typically we have a folder called tests added to out project
- we then inherit from the [```unittest.TestCase```]() class 

--

## tests/test_Vec3.py

```python
import math
import unittest

from Vec3 import Vec3


class TestVec3(unittest.TestCase):
    def test_ctor(self):
        v = Vec3()
        self.assertAlmostEqual(v.x, 0.0)
        self.assertAlmostEqual(v.y, 0.0)
        self.assertAlmostEqual(v.z, 0.0)

    def test_userCtor(self):
        v = Vec3(2.0, 3.0, 4.0)
        self.assertAlmostEqual(v.x, 2.0)
        self.assertAlmostEqual(v.y, 3.0)
        self.assertAlmostEqual(v.z, 4.0)

    def test_ctor_single_value(self):
        v = Vec3(x=2.0)
        self.assertAlmostEqual(v.x, 2.0)
        self.assertAlmostEqual(v.y, 0)
        self.assertAlmostEqual(v.z, 0)

        v = Vec3(y=2.0)
        self.assertAlmostEqual(v.x, 0.0)
        self.assertAlmostEqual(v.y, 2.0)
        self.assertAlmostEqual(v.z, 0)

        v = Vec3(z=2.0)
        self.assertAlmostEqual(v.x, 0.0)
        self.assertAlmostEqual(v.y, 0)
        self.assertAlmostEqual(v.z, 2.0)

    def test_add(self):
        a = Vec3(1, 2, 3)
        b = Vec3(4, 5, 6)
        c = a + b
        self.assertAlmostEqual(c.x, 5)
        self.assertAlmostEqual(c.y, 7)
        self.assertAlmostEqual(c.z, 9)

    def test_plus_equals(self):
        a = Vec3(1, 2, 3)
        b = Vec3(4, 5, 6)
        a += b
        self.assertAlmostEqual(a.x, 5)
        self.assertAlmostEqual(a.y, 7)
        self.assertAlmostEqual(a.z, 9)

    def test_sub(self):
        a = Vec3(1, 2, 3)
        b = Vec3(4, 5, 6)
        c = a - b
        self.assertAlmostEqual(c.x, -3)
        self.assertAlmostEqual(c.y, -3)
        self.assertAlmostEqual(c.z, -3)

    def test_sub_equals(self):
        a = Vec3(1, 2, 3)
        b = Vec3(4, 5, 6)
        a -= b
        self.assertAlmostEqual(a.x, -3)
        self.assertAlmostEqual(a.y, -3)
        self.assertAlmostEqual(a.z, -3)

    def test_set(self):
        a = Vec3()
        a.set(2.5, 0.1, 0.5)
        self.assertAlmostEqual(a.x, 2.5)
        self.assertAlmostEqual(a.y, 0.1)
        self.assertAlmostEqual(a.z, 0.5)

    def test_error_set(self):
        self.assertRaises(ValueError, Vec3.set, self, 2, 3, "hello")

    def test_dot(self):
        a = Vec3(1.0, 2.0, 3.0)
        b = Vec3(4.0, 5.0, 6.0)
        self.assertAlmostEqual(a.dot(b), 32.0)

    def test_length(self):
        a = Vec3(22, 1, 32)
        self.assertAlmostEqual(a.length(), 38.845, places=2)

    def test_length_squared(self):
        a = Vec3(22, 1, 32)
        self.assertAlmostEqual(a.length_squared(), 1509, places=2)

    def test_normalize(self):
        a = Vec3(22.3, 0.5, 10.0)
        a.normalize()
        self.assertAlmostEqual(a.x, 0.912266, places=5)
        self.assertAlmostEqual(a.y, 0.0204544, places=5)
        self.assertAlmostEqual(a.z, 0.409088, places=5)

    def test_equal(self):
        a = Vec3(0.1, 0.2, 0.3)
        b = Vec3(0.1, 0.2, 0.3)
        self.assertTrue(a == b)

    def test_not_equal(self):
        a = Vec3(0.3, 0.4, 0.3)
        b = Vec3(0.1, 0.2, 0.3)
        self.assertTrue(a != b)

    def test_inner(self):
        a = Vec3(1.0, 2.0, 3.0)
        b = Vec3(3.0, 4.0, 5.0)
        self.assertAlmostEqual(a.inner(b), 26.0)

    def test_negate(self):
        a = Vec3(0.1, 0.5, -12)
        a = -a
        self.assertAlmostEqual(a.x, -0.1)
        self.assertAlmostEqual(a.y, -0.5)
        self.assertAlmostEqual(a.z, 12.0)

    def test_reflect(self):
        N = Vec3(0, 1, 0)
        a = Vec3(2, 2, 0)
        a.normalize()
        ref = a.reflect(N)
        self.assertAlmostEqual(ref.x, 0.707, places=3)
        self.assertAlmostEqual(ref.y, -0.707, places=3)
        self.assertAlmostEqual(ref.z, 0)


    def test_cross(self):
        a = Vec3(0.0, 1.0, 0.0)
        b = Vec3(-1.0, 0.0, 0.0)
        c = a.cross(b)
        self.assertEqual(c, Vec3(0.0, 0.0, 1.0))

    def test_mul_scalar(self):
        a = Vec3(1.0, 1.5, 2.0)
        a = a * 2
        self.assertAlmostEqual(a.x, 2.0)
        self.assertAlmostEqual(a.y, 3.0)
        self.assertAlmostEqual(a.z, 4.0)

        a = Vec3(1.5, 4.2, 2.8)
        a = 2 * a
        self.assertAlmostEqual(a.x, 3.0)
        self.assertAlmostEqual(a.y, 8.4)
        self.assertAlmostEqual(a.z, 5.6)

        with self.assertRaises(ValueError):
            a = a * "hello"

    def test_getAttr(self):
        a = Vec3(1, 2, 3)
        self.assertAlmostEqual(getattr(a, "x"), 1.0)
        self.assertAlmostEqual(getattr(a, "y"), 2.0)
        self.assertAlmostEqual(getattr(a, "z"), 3.0)
        # check to see if we can get non attr
        self.assertRaises(AttributeError, getattr, a, "b")
        # check to see that adding an attrib fails
        self.assertRaises(AttributeError, setattr, a, "b", 20.0)

if __name__ == "__main__" :
    unittest.main()
```

--

## Running the tests

- To run the tests we can use the ```python -m unittest``` command or the ```pytest``` command

- as we have added the ```unittest.main()``` call to the end of the file we can also run the file directly

<asciinema-player src="/jmacey/Lectures/ScriptingForDCC/L3/tests1.cast" cols=120 rows=10></asciinema-player>

---

## Pytest examples

```python
import math
import pytest
from Vec3 import Vec3


class TestVec3 :
    def test_ctor(self):
        v = Vec3()
        assert v.x == pytest.approx(0.0)
        assert v.y == pytest.approx(0.0)
        assert v.z == pytest.approx(0.0)
    
    def test_userCtor(self):
        v = Vec3(2.0, 3.0, 4.0)
        assert v.x == pytest.approx(2.0)
        assert v.y == pytest.approx(3.0)
        assert v.z == pytest.approx(4.0)

    def test_ctor_single_value(self):
        v = Vec3(x=2.0)
        assert v.x == pytest.approx(2.0)
        assert v.y == pytest.approx(0.0)
        assert v.z == pytest.approx(0.0)

        v = Vec3(y=2.0)
        assert v.x == pytest.approx(0.0)
        assert v.y == pytest.approx(2.0)
        assert v.z == pytest.approx(0.0)

        v = Vec3(z=2.0)
        assert v.x == pytest.approx(0.0)
        assert v.y == pytest.approx(0.0)
        assert v.z == pytest.approx(2.0)

    def test_add(self):
        a = Vec3(1, 2, 3)
        b = Vec3(4, 5, 6)
        c = a + b
        assert c.x == pytest.approx(5.0)
        assert c.y == pytest.approx(7.0)
        assert c.z == pytest.approx(9.0)

    def test_plus_equals(self):
        a = Vec3(1, 2, 3)
        b = Vec3(4, 5, 6)
        a += b
        assert a.x == pytest.approx(5.0)
        assert a.y == pytest.approx(7.0)
        assert a.z == pytest.approx(9.0)

    def test_sub(self):
        a = Vec3(1, 2, 3)
        b = Vec3(4, 5, 6)
        c = a - b
        assert c.x == pytest.approx(-3.0)
        assert c.y == pytest.approx(-3.0)
        assert c.z == pytest.approx(-3.0)

    def test_sub_equals(self):
        a = Vec3(1, 2, 3)
        b = Vec3(4, 5, 6)
        a -= b
        assert a.x == pytest.approx(-3.0)
        assert a.y == pytest.approx(-3.0)
        assert a.z == pytest.approx(-3.0)

    def test_set(self):
        a = Vec3()
        a.set(2.5, 0.1, 0.5)
        assert a.x == pytest.approx(2.5)
        assert a.y == pytest.approx(0.1)
        assert a.z == pytest.approx(0.5)

    def test_error_set(self):
        with pytest.raises(TypeError):
            Vec3.set( 2, 3, "hello")

    def test_dot(self):
        a = Vec3(1.0, 2.0, 3.0)
        b = Vec3(4.0, 5.0, 6.0)
        assert a.dot(b) == pytest.approx(32.0)

    def test_length(self):
        a = Vec3(22, 1, 32)
        assert a.length() == pytest.approx(38.845,rel=1e-3)

    def test_length_squared(self):
        a = Vec3(22, 1, 32)
        assert a.length_squared() == pytest.approx(1509)

    def test_normalize(self):
        a = Vec3(22.3, 0.5, 10.0)
        a.normalize()
        assert a.x == pytest.approx(0.912266) # rel=1e-3
        assert a.y == pytest.approx(0.0204544)
        assert a.z == pytest.approx(0.409088)

    def test_equal(self):
        a = Vec3(0.1, 0.2, 0.3)
        b = Vec3(0.1, 0.2, 0.3)
        assert a == b

    def test_not_equal(self):
        a = Vec3(0.3, 0.4, 0.3)
        b = Vec3(0.1, 0.2, 0.3)
        assert a!=b 

    def test_inner(self):
        a = Vec3(1.0, 2.0, 3.0)
        b = Vec3(3.0, 4.0, 5.0)
        assert a.inner(b) == pytest.approx(26.0)



    def test_negate(self):
        a = Vec3(0.1, 0.5, -12)
        a = -a
        assert a.x == pytest.approx(-0.1)
        assert a.y == pytest.approx(-0.5)
        assert a.z == pytest.approx(12.0)

        
    def test_reflect(self):
        N = Vec3(0, 1, 0)
        a = Vec3(2, 2, 0)
        a.normalize()
        ref = a.reflect(N)
        assert ref.x == pytest.approx(0.707,rel=1e-3 )
        assert ref.y == pytest.approx(-0.707,rel=1e-3)
        assert ref.z == pytest.approx(0,rel=1e-3    )

    def test_cross(self):
        a = Vec3(0.0, 1.0, 0.0)
        b = Vec3(-1.0, 0.0, 0.0)
        c = a.cross(b)
        assert c.x == pytest.approx(0.0)
        assert c.y == pytest.approx(0.0)
        assert c.z == pytest.approx(1.0)

    def test_mul_scalar(self):
        a = Vec3(1.0, 1.5, 2.0)
        a = a * 2
        assert a.x == pytest.approx(2.0)
        assert a.y == pytest.approx(3.0)
        assert a.z == pytest.approx(4.0)

        a = Vec3(1.5, 4.2, 2.8)
        a = 2 * a
        assert a.x == pytest.approx(3.0)
        assert a.y == pytest.approx(8.4)
        assert a.z == pytest.approx(5.6)

        with pytest.raises(ValueError):
            a = a * "hello"

    def test_getAttr(self):
        a = Vec3(1, 2, 3)
        assert getattr(a, "x") == pytest.approx(1.0)
        assert getattr(a, "y") == pytest.approx(2.0)
        assert getattr(a, "z") == pytest.approx(3.0)

        # check to see if we can get non attr
        with pytest.raises(AttributeError):
            getattr(a, "b")
        # check to see that adding an attrib fails
        with pytest.raises(AttributeError):
            setattr(a, "b", 20.0)

```

--

## Running the tests

- We can now use the ```pytest``` command to run the tests

<asciinema-player src="/jmacey/Lectures/ScriptingForDCC/L3/tests2.cast" cols=120 rows=10></asciinema-player>


---

## [coverage.py](https://coverage.readthedocs.io/en/7.3.0/)

- coverage is a python module that will allow us to run and test the test coverage of our code
  - this can help to identify areas not covered by tests
- it can be installed via pip

<asciinema-player src="/jmacey/Lectures/ScriptingForDCC/L3/coverage.cast" cols=120 rows=10></asciinema-player>

--

## PyTest coverage

- We need to run pytest with the coverage command as follows

```
coverage run -m pytest
```

- we can then generate a report using the ```coverage report``` command

<asciinema-player src="/jmacey/Lectures/ScriptingForDCC/L3/cov1.cast" cols=120 rows=10></asciinema-player>

--

## HTML report

- coverage html will generate an interactive html report

<iframe width="1024" height="450" src="https://nccastaff.bournemouth.ac.uk/jmacey/Lectures/ScriptingForDCC/L3/htmlcov" ></iframe>

---

# References
- Martin Reddy. 2011. API Design for C++ (1st ed.). Morgan Kaufmann Publishers Inc., San Francisco, CA, USA.
- Steve McConnell. 2004. Code Complete, Second Edition. Microsoft Press, Redmond, WA, USA.
