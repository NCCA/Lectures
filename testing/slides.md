# Software Testing
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

- given the following function to convert a string to a double

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



//
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

--

## example [(Astels 2003)](http://wiki.c2.com/?TestDrivenDevelopmentaPracticalGuide) [(Reddy 2011)](http://www.apibook.com/blog/)
- start with a small test to verify the behavior of a MovieRating class

```
void TestNoRatings() 
{
  MovieRating *nemo = new MovieRating("Finding Nemo");
  AssertEqual(nemo->GetRatingCount(), 0, "no ratings"); 
}
```

--


## example

- Given this initial test code, you now write the simplest possible code to make the test pass

```
class MovieRating 
{
public:
  MovieRating(const std::string &name) {}
  int GetRatingCount() const { return 0; } 
};
```

- This API clearly doesn’t do a lot, but it does allow the test to pass

--


## example

```
void TestAverageRating()
{
  MovieRating *nemo = new MovieRating("Finding Nemo"); 
  nemo->AddRating(4.0f);
  nemo->AddRating(5.0f);
  AssertEqual(nemo->GetAverageRating(), 4.5f, "nemo avg rating");
}
```

--

## example

- Now you should extend the implementation to return the number of ratings added and the average of those ratings.

```
class MovieRating 
{
public:
  MovieRating(const std::string &name) :
         mNumRatings(0),
         mRatingsSum(0.0f) {}
  int GetRatingCount() const 
  {
    return mNumRatings; 
  }

  void AddRating(float r) 
  {
    mRatingsSum+=r;
    mNumRatings++; 
  }
  
  float GetAverageRating() const 
  {
    return (mRatingsSum / mNumRatings); 
  }
private:
  int mNumRatings;
  float mRatingsSum; 
};



```

--

## example

- Obviously you can continue this strategy by adding further tests 
- for example 
  - verify that calling GetAverage->Rating() with zero ratings does not crash 
  - verify adding out-of-range rating values is treated appropriately

---

## 3rd Party testing Frameworks
- [there are many 3rd party testing frameworks](https://en.wikipedia.org/wiki/List_of_unit_testing_frameworks)
- these cover many languages but most have similar idioms / syntax
- for NGL I have used [google test](https://github.com/google/googletest)
- For a quick overview see the [primer](https://github.com/google/googletest/blob/master/googletest/docs/Primer.md) 
- There is also a [mocking framework](https://github.com/google/googletest/blob/master/googlemock/README.md)

```
// Qt .pro (for university) usually /usr/local
INCLUDE_PATH+=/public/devel/include
LIBS+= -L/public/devel/lib -lgtest
```

--

## [gtest1 example](https://github.com/NCCA/TestingLecture/tree/master/gtest1)
- this example modifies the previous stringToDouble example from Reddy.

```
#include <string>

bool stringToDouble(const std::string &_str, double &io_result)
{
  bool success=true;
  try
  {
    io_result = std::stod(_str);
  }
  catch(std::invalid_argument)
  {
    success=false;
  }
  return success;
}

```

--

## [gtest1 example](https://github.com/NCCA/TestingLecture/tree/master/gtest1)

```
#include <gtest/gtest.h>
#include "str2double.h"

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(str2Double,positiveTest)
{
  double value;
  ASSERT_TRUE(stringToDouble("1", value));
  ASSERT_DOUBLE_EQ(value, 1.0);
}

```

```
Starting /Users/jmacey/teaching/Code/TestingLecture/gtestAssert/gtest1...
[==========] Running 1 test from 1 test case.
[----------] Global test environment set-up.
[----------] 1 test from str2Double
[ RUN      ] str2Double.positiveTest
[       OK ] str2Double.positiveTest (0 ms)
[----------] 1 test from str2Double (0 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test case ran. (0 ms total)
[  PASSED  ] 1 test.
```

--

## Basic Assertions 

- These assertions do basic true/false condition testing.

| <small/>**Fatal assertion** | <small/>**Nonfatal assertion** | <small/>**Verifies** |
|:--------------------|:-----------------------|:-------------|
| <small/>`ASSERT_TRUE(`_condition_`)`;  | <small/>`EXPECT_TRUE(`_condition_`)`;   | <small/>_condition_ is true |
| <small/>`ASSERT_FALSE(`_condition_`)`; | <small/>`EXPECT_FALSE(`_condition_`)`;  | <small/>_condition_ is false |

--

## Binary Comparison 


| <small/>**Fatal assertion** | <small/>**Nonfatal assertion** | <small/>**Verifies** |
|:--------------------|:-----------------------|:-------------|
|<small/>`ASSERT_EQ(`_val1_`, `_val2_`);`|<small/>`EXPECT_EQ(`_val1_`, `_val2_`);`|<small/> _val1_ `==` _val2_ |
|<small/>`ASSERT_NE(`_val1_`, `_val2_`);`|<small/>`EXPECT_NE(`_val1_`, `_val2_`);`|<small/> _val1_ `!=` _val2_ |
|<small/>`ASSERT_LT(`_val1_`, `_val2_`);`|<small/>`EXPECT_LT(`_val1_`, `_val2_`);`|<small/> _val1_ `<` _val2_ |
|<small/>`ASSERT_LE(`_val1_`, `_val2_`);`|<small/>`EXPECT_LE(`_val1_`, `_val2_`);`|<small/> _val1_ `<=` _val2_ |
|<small/>`ASSERT_GT(`_val1_`, `_val2_`);`|<small/>`EXPECT_GT(`_val1_`, `_val2_`);`|<small/> _val1_ `>` _val2_ |
|<small/>`ASSERT_GE(`_val1_`, `_val2_`);`|<small/>`EXPECT_GE(`_val1_`, `_val2_`);`|<small/> _val1_ `>=` _val2_ |

-In the event of a failure, Google Test prints both _val1_ and _val2_.

--

## String Comparison 

- <small/>The assertions in this group compare two **C strings**. If you want to compare two `std::string` objects, use `EXPECT_EQ`, `EXPECT_NE`, and etc instead.

| <small/>**Fatal assertion** | <small/>**Nonfatal assertion** | <small/>**Verifies** |
|:--------------------|:-----------------------|:-------------|
| <small/>`ASSERT_STREQ(`_str1_`, `_str2_`);`    | <small/>`EXPECT_STREQ(`_str1_`, `_str_2`);`     | <small/>the two C strings have the same content |
| <small/>`ASSERT_STRNE(`_str1_`, `_str2_`);`    | <small/>`EXPECT_STRNE(`_str1_`, `_str2_`);`     | <small/>the two C strings have different content |
| <small/>`ASSERT_STRCASEEQ(`_str1_`, `_str2_`);`| <small/>`EXPECT_STRCASEEQ(`_str1_`, `_str2_`);` | <small/>the two C strings have the same content, ignoring case |
| <small/>`ASSERT_STRCASENE(`_str1_`, `_str2_`);`| <small/>`EXPECT_STRCASENE(`_str1_`, `_str2_`);` | <small/>the two C strings have different content, ignoring case |

- Note that "CASE" in an assertion name means that case is ignored.


--

## ASSERT_DOUBLE_EQ
- gtest provides functions to test equality with normal values as well as floating point values
- full details are [here](https://github.com/google/googletest/blob/master/googletest/docs/AdvancedGuide.md#floating-point-comparison)

| <small/>**Fatal assertion** |  <small/>**Nonfatal assertion** |  <small/>**Verifies** |
|:--------------------|:-----------------------|:-------------|
|  <small/>`ASSERT_FLOAT_EQ(`_val1, val2_`);`  |  <small/>`EXPECT_FLOAT_EQ(`_val1, val2_`);` |  <small/>the two `float` values are almost equal |
|  <small/>`ASSERT_DOUBLE_EQ(`_val1, val2_`);` |  <small/>`EXPECT_DOUBLE_EQ(`_val1, val2_`);` |  <small/>the two `double` values are almost equal |

--

## ASSERT_NEAR 

-The following assertions allow you to choose the acceptable error bound:

|  <small/>**Fatal assertion** |  <small/>**Nonfatal assertion** |  <small/>**Verifies** |
|:--------------------|:-----------------------|:-------------|
|  <small/>`ASSERT_NEAR(`_val1, val2, abs\_error_`);` |  <small/>`EXPECT_NEAR`_(val1, val2, abs\_error_`);` |  <small/>the difference between _val1_ and _val2_ doesn't exceed the given absolute error |


--


## Exception Assertions ##

- These are for verifying that a piece of code throws (or does not throw) an exception of the given type:

| <small/>**Fatal assertion** | <small/>**Nonfatal assertion** | <small/>**Verifies** |
|:--------------------|:-----------------------|:-------------|
| <small/>`ASSERT_THROW(`_statement_, _exception\_type_`);`  | <small/>`EXPECT_THROW(`_statement_, _exception\_type_`);`  | <small/>_statement_ throws an exception of the given type  |
| <small/>`ASSERT_ANY_THROW(`_statement_`);`                | <small/>`EXPECT_ANY_THROW(`_statement_`);`                | <small/>_statement_ throws an exception of any type        |
| <small/>`ASSERT_NO_THROW(`_statement_`);`                 | <small/>`EXPECT_NO_THROW(`_statement_`);`                 |<small/> _statement_ doesn't throw any exception            |

--

## [example](https://github.com/NCCA/TestingLecture/tree/master/gtestAssert)

```
bool stringToDouble(const std::string &_str, double &io_result)
{
  io_result = std::stod(_str); // will throw std::invalid_argument if not valid
  return true;
}
```

```
TEST(str2Double,whitespace)
{
  double value;
  ASSERT_THROW(stringToDouble(" ", value),std::invalid_argument);
}
```



---

## Stub and Mock Objects
- One popular technique to make your unit tests more stable and resilient to failures is to create test objects that can stand in for real objects in the system
- These stand-in objects will present the same interface as the real objects they simulate.
- Depending upon the type of object (i.e. inheritance / virtual etc etc) we need to use different approaches

--

## Terminology
- **Fake object** An object that has functional behavior but uses a simpler implementation to aid testing.
- **Stub object** An object that returns prepared or canned responses.
- **Mock object** An instrumented object that has a preprogrammed behavior and that performs verification on the calling sequence of its methods. 

--

## Mock Objects

> For example, a mock object (or simply a mock) can specify that a GetValue() function will return 10 the first two times it’s called and then 20 after that. It can also verify that the function was called, say, only three times or at least five times or that the functions in the class were called in a given order.

--

## Fake vs Mock Objects

- Fake objects have working implementations, but usually take some shortcut (perhaps to make the operations less expensive), which makes them not suitable for production. 
  - An in-memory file system would be an example of a fake.
- Mocks are objects pre-programmed with expectations, which form a specification of the calls they are expected to receive.

--

## Google Mock [(gmock)](https://github.com/google/googletest/blob/master/googlemock/docs/ForDummies.md)
- is a framework / library for generating mock classes
Using Google Mock involves three basic steps:

  1. Use some simple macros to describe the interface you want to mock, and they will expand to the implementation of your mock class;
  1. Create some mock objects and specify its expectations and behavior using an intuitive syntax;
  1. Exercise code that uses the mock objects. Google Mock will catch any violation of the expectations as soon as it arises.

--

## Why use mocking?
- "It is your friend if any of the following problems is bothering you" 
  -  You are stuck with a sub-optimal design and wish you had done more prototyping before it was too late, but prototyping in C++ is by no means "rapid".
  - Your tests are slow as they depend on too many libraries or use expensive resources (e.g. a database).
  - Your tests are brittle as some resources they use are unreliable (e.g. the network).


--

## Why use mocking?
  - You want to test how your code handles a failure (e.g. a file checksum error), but it's not easy to cause one.
  - You need to make sure that your module interacts with other modules in the right way, but it's hard to observe the interaction; therefore you resort to observing the side effects at the end of the action, which is awkward at best.
  - You want to "mock out" your dependencies, except that they don't have mock implementations yet; and, frankly, you aren't thrilled by some of those hand-written mocks.

--

## example :- A Case for Mock Turtles
- Suppose you are developing a graphics program that relies on a [LOGO](http://tinyurl.com/dxhendg)-like API for drawing. 
- How would you test that it does the right thing?

--


## [example](https://github.com/NCCA/TestingLecture/tree/master/gmock)
- We can use Dependency Injection, instead of having your application talk to the drawing API directly, wrap the API in an interface (say, `Turtle`) and code to that interface:

```
// based on example here https://github.com/google/googletest/blob/master/googlemock/docs/ForDummies.md

#ifndef TURTLE_H_
#define TURTLE_H_

class Turtle
{
  public :
   virtual ~Turtle() {}
   virtual void penUp(){}
   virtual void penDown() {}
   virtual void forward(int distance) {}
   virtual void turn(int degrees) { m_rot=degrees;}
   virtual void goTo(int x, int y) { m_x=x; m_y=y;}
   virtual int getX() const {return m_x;}
   virtual int getY() const {return m_y;}

  private :
   int m_x=0;
   int m_y=0;
   int m_rot;
};

#endif

```

--

## example

- Your program will normally use a real implementation of this interface. 
- In tests, you can use a mock implementation instead. 
- This allows you to easily check what drawing primitives your program is calling, with what arguments, and in which order. 
- Now test will be 
  - more robust 
  - easier to read and maintain 
  - and run _much, much faster_

--

## How to Define It 
- Using the `Turtle` interface as example, here are the simple steps you need to follow:

  1. Derive a class `MockTurtle` from `Turtle`.
  1. Take a _virtual_ function of `Turtle`  and count how many arguments it has.
  1. In the `public:` section of the child class, write `MOCK_METHODn();` (or `MOCK_CONST_METHODn();` if you are mocking a `const` method), where `n` is the number of the arguments
  1. (while it's possible to [mock non-virtual methods using templates](https://github.com/google/googletest/blob/master/googlemock/docs/CookBook.md#mocking-nonvirtual-methods), it's much more involved).

--

## How to Define It 

- you take the function signature, cut-and-paste the _function name_ as the _first_ argument to the macro, and leave what's left as the _second_ argument (in case you're curious, this is the _type of the function_).
- repeat until all virtual functions you want to mock are done.

--

## example

```
#ifndef MOCKTURTLE_H_
#define MOCKTURTLE_H_
#include "Turtle.h"
#include <gmock/gmock.h>

class MockTurtle : public Turtle
{
 public:
  MOCK_METHOD0(penUp, void());
  MOCK_METHOD0(penDown, void());
  MOCK_METHOD1(forward, void(int distance));
  MOCK_METHOD1(turn, void(int degrees));
  MOCK_METHOD2(goTo, void(int x, int y));
  MOCK_CONST_METHOD0(getX, int());
  MOCK_CONST_METHOD0(getY, int());
};

```

--

## Using Mocks in Tests 
- The typical work flow is:

1. Create some mock objects.
1. Specify your expectations on them (How many times will a method be called? With what arguments? What should it do? etc.).
1. Exercise some code that uses the mocks; optionally, check the result using Google Test assertions. 
1. When a mock is destructed, Google Mock will automatically check whether all expectations on it have been satisfied.

--

## example painter

```
#include "Turtle.h"
#include <iostream>
class Painter
{
  public :
    Painter(Turtle *t) :m_turtle(t){;}
    bool drawCircle(int _x, int _y, int _r )
    {
      // made up routine to test
      m_turtle->penDown();
      m_turtle->goTo(_x,_y);
      m_turtle->turn(_r);
      m_turtle->forward(_r);
      return true;
    }

  private :
     Turtle *m_turtle;
};
```

--

## example test and mock

```
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "MockTurtle.h"
#include "Painter.h"
// based on example here https://github.com/google/googletest/blob/master/googlemock/docs/ForDummies.md

int main(int argc, char** argv)
{
  // The following line must be executed to initialize Google Mock
  // (and Google Test) before running the tests.
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(PainterTest, CanDrawSomething)
{
  using ::testing::AtLeast;
  using ::testing::_;
  MockTurtle turtle;
  EXPECT_CALL(turtle, penDown())
      .Times(AtLeast(1));
  EXPECT_CALL(turtle, goTo(_,_))
      .Times(AtLeast(1));
  EXPECT_CALL(turtle, forward(_))
      .Times(AtLeast(1));

  EXPECT_CALL(turtle, turn(_))
      .Times(AtLeast(1));


  Painter painter(&turtle);
  // Note test and mock together!
  EXPECT_TRUE(painter.drawCircle(0, 0, 10));
}


```

---


# References
- Martin Reddy. 2011. API Design for C++ (1st ed.). Morgan Kaufmann Publishers Inc., San Francisco, CA, USA.
- Steve McConnell. 2004. Code Complete, Second Edition. Microsoft Press, Redmond, WA, USA.
