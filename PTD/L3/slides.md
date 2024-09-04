## Lecture 3 Why Python?
Jon Macey

jmacey@bournemouth.ac.uk

---

## Introduction

- A brief history of scripting in DCC tools
- Why did python become the core language?
- Software lifecycle for DCC and Pipelines
  - Install, develop, test , deploy (repeat / maintain)

---

## A (brief) History of DCC programming

- Very early days of computer animation used analog computers
- Not until the 80's that digital computers we used
  - Whilst this was the beginning of home computers most computers were [mini / mainframes](https://en.wikipedia.org/wiki/VAX) in an academic environment.
- Mainly running a Unix like OS

--

## Early Animation Systems

- Early animation systems were usually small programs piped together
  - intermediate representations fed into the pipeline to generate input for renderer
  - Standard Unix tools used to modify (sed / awk)
- Most programs written in C 

--

## No off the shelf 1990's

- There were no off the shelf tools so most were developed in house 
  - NCCA had it's own CGAL (needed to program to use)
- Power Animator was the Industry standard but needed IRIX / SGI machines and £7K a seat!

--

## Coding Animation
<div id="mySlideLeftCode">
<iframe src="sphere.html" ></iframe>
</div>
<div id="mySlideRightCode">
```
SCRIPT 1 TO 150 DO
  BEGIN
    FROM 1 TO 100 EVERY 25 LOOP 10 DO
      RZ [ball] 1.5;
      .....
  END;
```
</div>
- This generates 150 frames of animation 
  - makes the object ```[ball]``` rotate around the z axis by 1.5 degrees in loops of 10 frames every 25 
  - i.e. 1-10  26-35 51-60 76-85

--

## Enter the tools

- via various mergers animation tools began to appear
- Early tools started to be packaged into GUI systems 
  - but the underlying systems are still scripts 
- Most GUI tools are just glued together with scripts

--

## Scripting Languages

- MEL (Maya Embedded Language) based on [Perl](https://www.perl.org/) and [TCL](https://www.tcl.tk/about/language.html)
- HScript Houdini scripting language
- XSI used Python, Perl, JavaScript and VB Script
- Python started in Maya 8.5 
- [Lua](https://www.lua.org/) quite common in pipelines and bespoke tools

---

## Why python?

- In recent years python has become the core language
  - it is easy to embed and use in DCC tools
- Good support for GUI (PyQt / PySide)
- Easy to learn (to start with!) Easy to abuse too!

--

## Python in Pipeline and DCC's

- VFX reference platform mandates 3.9.x (ucs4) but we still have 2.7 floating around!
  - maya 2019 still in use by us.
```
import sys
print (sys.maxunicode)
1114111
```

--

## Embeding and extending

- (C)Python is very easy to extend and embed
  - Extending is adding new compiled libraries with python bindings
- Embedding is the opposite where we extend our app with scripting
- There are many 3rd party tools to enable the generation of python bindings 
- We will explore these later.

--

## How is python embedded

- The core power of python is the interpreter can be embedded in our own apps
  - https://docs.python.org/3/extending/embedding.html
- when you extend Python, the main program of the application is still the Python interpreter
- when you embed Python, the main program may have nothing to do with Python 
- instead, some parts of the application occasionally call the Python interpreter to run some Python code. 

--

## [Simple Embed](https://github.com/NCCA/PipelineAndTD/tree/main/Lecture3Python/Embed1)

```
// g++ embed.cpp `python-config --cflags --ldflags --libs --embed`
// from https://docs.python.org/3/extending/embedding.html
#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[])
{
wchar_t *program = Py_DecodeLocale(argv[0], NULL);
if (program == NULL) 
{
  std::cerr<<"Fatal error: cannot decode argv[0]\n";
  exit(EXIT_FAILURE);
}

Py_SetProgramName(program);  /* optional but recommended */
Py_Initialize();
PyRun_SimpleString("from time import time,ctime\n"
                    "print('Today is', ctime(time()))\n");
if (Py_FinalizeEx() < 0) 
{
  std::cerr<<"Failed to exit python\n";
  // 120 is used by python not sure why!
  exit(120);
}
PyMem_RawFree(program);
return EXIT_SUCCESS;
}
```

```
g++ embed.cpp `python-config --cflags --ldflags --libs --embed`
```

--

## Building 

- we need to build against the interpreter / libraries we use
- Packaging is fun!
- In the previous example we use python-config which is set from pyenv
- May clash with other version / libs
- Hence why each DCC packages and ships own libs / python

--

## Building

- cmake has a [FindPython3](https://cmake.org/cmake/help/git-stage/module/FindPython3.html) module

```
cmake_minimum_required(VERSION 3.12)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE AND DEFINED ENV{CMAKE_TOOLCHAIN_FILE})
   set(CMAKE_TOOLCHAIN_FILE $ENV{CMAKE_TOOLCHAIN_FILE})
endif()

project(EmbedPythonBuild)
# This is the name of the Exe change this and it will change everywhere
set(TargetName EmbedPython)
find_package (Python COMPONENTS Interpreter Development)



add_executable(${TargetName})

target_sources(${TargetName} PRIVATE ${PROJECT_SOURCE_DIR}/embed.cpp)
target_link_libraries(${TargetName} PRIVATE Python::Python)
```

--

## cmake

- sometimes have to specify the python interpreter on the command line
  - for example with virtual env

```
cmake -DPython_ROOT_DIR=~/.pyenv/shims ..
```

--

## [distutils](https://docs.python.org/3/library/distutils.html) 

- now being deprecated but in until 3.12 then use [setuptools](https://pypi.org/project/setuptools/)
```python
import distutils.sysconfig as sysconfig
print(sysconfig.get_config_var('LDLIBRARY'))
print(sysconfig.get_python_inc())
print(sysconfig.get_config_var('LIBDIR'))
```

```
'libpython3.9.a'
'/Users/jmacey/.pyenv/versions/3.9.7/include/python3.9'
'/Users/jmacey/.pyenv/versions/3.9.7/lib'
```

--

## [From file](https://github.com/NCCA/PipelineAndTD/tree/main/Lecture3Python/File)

- The following example uses PyRun_SimpleFile to execute files from the filesystem

```
// g++ file.cpp `python-config --cflags --ldflags --libs --embed`
// from https://docs.python.org/3/extending/embedding.html
#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <cstdlib>
#include <iostream>
#include <filesystem>
#include <vector>

int main(int argc, char **argv)
{
  if (argc == 1)
  {
    std::cout<<"Please pass file(s) to view on command line\n";
    exit(EXIT_FAILURE);
  }
  std::vector<std::string> files;
  namespace fs = std::filesystem;

  for(int i=1; i<argc; ++i)
  {
    if(fs::exists(argv[i]))
    {
      files.push_back(argv[i]);
    }
  }
  
  Py_Initialize();
  for(auto f : files)
  {
    std::cout<<"__________________________________________\n";
    std::cout<<"running "<<f<<'\n';
    auto fp = fopen(f.c_str(), "r");
    if (fp)
    {
        PyRun_SimpleFile(fp, f.c_str());
        fclose(fp);
    }
  }
  if (Py_FinalizeEx() < 0) 
  {
    std::cerr<<"Failed to exit python\n";
    // 120 is used by python examples not sure why!
    exit(120);
  }
  return EXIT_SUCCESS;
}
```

---

## Beyond Very High Level Embedding

- The previous examples actually run python but don't communicate with the C/C++ program
- To access data in our program we need to use lower level calls
  - This means more C/C++ code but does add more flexibility

--

## Embedding vs extending
- When extending
  1. Convert data values from Python to C,
  2. Perform a function call to a C routine using the converted values
  3. Convert the data values from the call from C to Python.

- When embedding Python, the interface code does
  1. Convert data values from C to Python,
  2. Perform a function call to a Python interface routine using the converted values
  3. Convert the data values from the call from Python to C.


--

## [A simple extend](https://github.com/NCCA/PipelineAndTD/tree/main/Lecture3Python/Extend1)

```c++
// https://docs.python.org/3/extending/embedding.html
#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <iostream>

int main(int argc, char *argv[])
{
    PyObject *pName, *pModule, *pFunc;
    PyObject *pArgs, *pValue;
    int i;

    if (argc < 3) 
    {
        std::cerr<<"Usage: call pythonfile funcname [args]\n";
        return EXIT_FAILURE;
    }

    Py_Initialize();
    pName = PyUnicode_DecodeFSDefault(argv[1]);
    /* Error checking of pName left out */

    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) 
    {
        pFunc = PyObject_GetAttrString(pModule, argv[2]);
        /* pFunc is a new reference */

        if (pFunc && PyCallable_Check(pFunc)) 
        {
            pArgs = PyTuple_New(argc - 3);
            for (i = 0; i < argc - 3; ++i) 
            {
                pValue = PyLong_FromLong(atoi(argv[i + 3]));
                if (!pValue) 
                {
                    Py_DECREF(pArgs);
                    Py_DECREF(pModule);
                    std::cerr<<"Cannot convert argument\n";
                    return EXIT_FAILURE;
                }
                /* pValue reference stolen here: */
                PyTuple_SetItem(pArgs, i, pValue);
            }
            pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);
            if (pValue != NULL) 
            {
                std::cout<<"Result of call: "<< PyLong_AsLong(pValue)<<'\n';
                Py_DECREF(pValue);
            }
            else 
            {
                Py_DECREF(pFunc);
                Py_DECREF(pModule);
                PyErr_Print();
                std::cerr<<"Call failed\n";
                return EXIT_FAILURE;
            }
        }
        else 
        {
            if (PyErr_Occurred())
                PyErr_Print();
            std::cerr<<"Cannot find function "<<argv[2]<<'\n';
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    }
    else 
    {
        PyErr_Print();
        std::cerr<<"Failed to load"<<argv[1]<<'\n';
        return EXIT_FAILURE;
    }
    if (Py_FinalizeEx() < 0) 
    {

        return 120;
    }
    return EXIT_SUCCESS;
}
```

--

## pure embedding

- The first program aims to execute a function in a Python script. 
```
 ./Extend mult multiply 3 5
Will compute 3 times 5
Result of call: 15
```
- Most of the code is for data conversion from args to python objects


--

## [A more complex Example](https://github.com/NCCA/EmbedPython)

- When our program starts it grabs ```__main__``` and the global dictionary
- these are passed to a class called Agent which exposes some of it's attributes to a python script
  - position, direction and speed (ngl::Vec3 -> Python List[3])
- A python script is loaded as a string into the agent which will be the string to run.
- Each frame we map the variables from Agent to the python script
- This updates them and then they are copied back to our application

---

## Building Python Modules

- It is possible to build python modules from C/C++ code by hand
- This is quite tedious so it is better to use a generator
- The main options for C/C++ are
  - [PyBind11](https://github.com/pybind/pybind11) which is a port of [boost::python](https://www.boost.org/doc/libs/1_64_0/libs/python/doc/html/index.html)
  - [SWIG](http://www.swig.org/) which can bind to many languages
  - [shiboken](https://doc.qt.io/qtforpython/shiboken2/) used for PyQt

--

## Binding Generators

- Most binding generators need input from the user
- SWIG requires less but can generate very un-pythonic code
- PyBind11 needs more user input / code generation but we can ensure we generate more pythonic code
- There are tools to [help](https://cppbinder.readthedocs.io/en/latest/)

--

## [Example PoissonDisk Sampling](https://www.cs.ubc.ca/~rbridson/docs/bridson-siggraph07-poissondisk.pdf)

<image src="images/disk.png" width=80%>

--

## [Example PoissonDisk Sampling](https://www.cs.ubc.ca/~rbridson/docs/bridson-siggraph07-poissondisk.pdf)



> [it is often useful to obtain a sample of random points such that no one point is closer than some pre-determined distance from any other point, in order to avoid this clustering effect.](https://scipython.com/blog/poisson-disc-sampling-in-python/)

--

## [Original Python Version](https://github.com/NCCA/PipelineAndTD/tree/main/Lecture3Python/DiskSampling/01OriginalPython)

- The python version is a simple class with a constructor and sample methods to return a list of 2d Points
- [Matplotlib](https://matplotlib.org/) is used for simple visualization

```
 ./scatter.py -wd 400 -ht 400 -r 3.2 -k 20 --seed=12345
construction took 2 ms
sample took 3259 ms for 9711 points
```
- as we increase the size and decrease the radius calling sample gets slower
- in part this is due to it being written in python.

--

## [A C++ version](https://github.com/NCCA/PipelineAndTD/tree/main/Lecture3Python/DiskSampling/02CPPVersion)

- The C++ version is a translation of the python version to C++
- There were a few gotcha's
  1. Cells initialised to ```None``` then return index
  2. Dictionaries used for coordinate lookup
  3. How to do this in C++?

```python
if not (0 <= neighbour_coords[0] < self.nx and 
        0 <= neighbour_coords[1] < self.ny):

// C++
if( !((current.x >= 0) && (current.x < m_nx) && 
      (current.y >= 0) && (current.y < m_ny)))
```

--

## C++ Version

```c++
#ifndef POSSIONDISK_H_
#define POSSIONDISK_H_

#include <vector>

struct Point2
{
  Point2(float _x, float _y) : x{_x},y{_y}{}
  Point2()=default;
  float x,y;
};

struct Index
{
    Index(int _x, int _y) : x{_x},y{_y}{}
    Index operator+(const Index &_rhs)const ;
    int x;
    int y; 
};

class PoissonDisk
{
  public :
    PoissonDisk(int _width=50, int _height=50, float _r=1.0, int _k=30, int _seed=1234);
    void reset(bool _reseed=true);
    std::vector<Point2> sample();

  private :
    Index getCellCoords(Point2 _xy);
    std::vector<int> getNeighbours(Index  _cords);
    bool pointValid(Point2 _pt);
    // return true if found and fill in o_found as the point
    bool getPoint(Point2 _pt, Point2 &o_found);
    int getIndex(Index _i);
    int m_width=50;
    int m_height=50;
    float m_r=1.0f;
    int m_k=30;
    float m_a=0.0f;
    std::vector<Point2> m_samples;    
    // cell index values, set to -1 for None
    std::vector<int> m_cells;
    // Number of cells in the x- and y-directions of the grid
    int m_nx;
    int m_ny;

};

#endif
```

--

## Output to Python

- to ensure that I could visualize the data I decided the simplest way was to generate a python program from the data points. 
- As you can see this version is much faster

```
 ./Poisson -w 400 -h 400 -r 3.2 -k 20 --seed 12345
Construction took 0[ms]
sample took 378[ms]
Number of Points 9684
```

--

## A Python Module

- The previous example works well but it is not directly accessible in python
- To do this we need to generate a python module and interface to the C++ code
- typically this is a shared library of the C++ code with extra python interface code added
- We need to build against the version of python we are using and this needs to be reflected in the CMake file 

---

## [PyBind11 example](https://github.com/NCCA/PipelineAndTD/tree/main/Lecture3Python/DiskSampling/03PyBind11)

- When using PyBind11 we create an extra c++ file(s) which contains a module definition
- Within this file we write code to wrap the classes we need 
  - in most cases this is just pointing to the method by name
- However if we have default parameter values we need extra code
- Also certain STL containers and operators require more code
- Pybind 11 is header only but installed in the labs via vcpkg

--

## [PythonBindings.cpp](https://github.com/NCCA/PipelineAndTD/blob/main/Lecture3Python/DiskSampling/03PyBind11/src/PythonBindings.cpp)

```c++
#include "PoissonDisk.h"
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <pybind11/cast.h>
#include <pybind11/stl_bind.h>
#include <pybind11/pytypes.h>
#include <pybind11/complex.h>

namespace py = pybind11;

PYBIND11_MAKE_OPAQUE(std::vector<Point2>);

PYBIND11_MODULE(PoissonDisk,m)
{
  m.doc()="pyngl module to use NGL in python";

  py::class_<Point2>(m,"Point2")
      .def(py::init<>())
       .def("__repr__",
        [](const Point2 &p) {
                      return "("+std::to_string(p.x)+","+
                          std::to_string(p.y)+"]";})
          .def_readwrite("x", &Point2::x)
          .def_readwrite("y", &Point2::y)
      ;
  py::class_<PoissonDisk>(m, "PoissonDisk")
      .def(py::init<int, int, float , int , int >(),
      py::arg("_width") = 50,
      py::arg("_height") = 50,
      py::arg("_r") = 1.0f,
      py::arg("_k") = 30,
      py::arg("_seed") = 1234
      )

      .def("reset",&PoissonDisk::reset)
      .def("sample",&PoissonDisk::sample)
  ;

  py::bind_vector<std::vector<Point2>>(m,"VectorPoint2")
  .def("__iter__", [](std::vector<Point2> &v) 
  {
    return py::make_iterator(std::begin(v),std::end(v));
  }, py::keep_alive<0, 1>()) /* Keep vector alive while iterator is used */
    ;

}
```

--

## [Python Demo](https://github.com/NCCA/PipelineAndTD/blob/main/Lecture3Python/DiskSampling/03PyBind11/test.py)

```python
#!/usr/bin/env python
from PoissonDisk import PoissonDisk
import matplotlib.pyplot as plt
from datetime import datetime
import numpy as np
import argparse
import faulthandler

def plot(width = 400,height=400,r=3.5,k=20,seed=1234) :
    start = datetime.now()
    p=PoissonDisk(width,height,r,k,seed)
    end = datetime.now()
    delta = end-start

    print('construction took {} ms'.format(int(delta.total_seconds() * 1000)))

    start = datetime.now()
    faulthandler.enable()
    points=p.sample()
    end = datetime.now()
    delta = end-start
    print('sample took {} ms size {}'.format(int(delta.total_seconds() * 1000),len(points)))
    plt.title("Poisson disk sampling")
    p2=[]
    for t in points :
        p2.append((t.x,t.y))
    plt.scatter(*zip(*p2),s=1.3)
    plt.show()

if __name__ == '__main__' :
    parser = argparse.ArgumentParser(description='Plot params')

    parser.add_argument('--radius', '-r', nargs='?', 
						const=3.5, default=3.5, 
                        type=float,help='radius')

    parser.add_argument('--width' , '-wd' ,nargs='?', 
						const=400, default=400,
                        type=int,help='width of sim')
    parser.add_argument('--height', '-ht' ,nargs='?', 
						const=400, default=400,
                        type=int,help='height of sim')
    parser.add_argument('--simcount', '-k' ,nargs='?', 
						const=40, default=40,
                        type=int,help='sim steps')
    parser.add_argument('--seed', '-s' ,nargs='?', 
						const=1234, default=1234,
                        type=int,help='rand seed')
    args = parser.parse_args()


    plot(args.width,args.height,args.radius,args.simcount,args.seed)
```
```
 python test.py -wd 400 -ht 400 -r 3.2 -k 20 --seed 12345
construction took 0 ms
sample took 401 ms size 9633
```

---

## [SWIG Version](https://github.com/NCCA/PipelineAndTD/tree/main/Lecture3Python/DiskSampling/04Swig)

- Swig is a tool that generates a cxx file to be bound with our project
- This will need to be added to your path before use
```
export PATH="/home/jmacey/.pyenv/shims:${PATH}:/public/devel/2021/swig/bin/"
```
- It then reads an interface file (part of the build process) to generate the files
- CMake has good support for SWIG, however I did have issues with the python config

--

## [Interface File](https://github.com/NCCA/PipelineAndTD/blob/main/Lecture3Python/DiskSampling/04Swig/src/PoissonDisk.i)

```
%module PoissonDisk

%{
#define SWIG_FILE_WITH_INIT
#include "PoissonDisk.h"
%}

%include "std_vector.i"
namespace std {
    %template(VectorPoint2)  std::vector<Point2>;
}


// Include the header file with above prototypes
%include "PoissonDisk.h"

```

--

## SWIG output

- SWIG generates a python (.py) file as well as a .so library file
- The python file is used for the import of the .so

```
❯ python test.py -wd 400 -ht 400 -r 3.2 -k 20 --seed 12345
construction took 0 ms
sample took 372 ms size 9643
```

---

## Conclusions

- As you can see the modules both have comparable speed
  - SWIG is slightly faster 
- At present neither return value (```std::vector<Point2>```) wrapped is very pythonic 
  - ideally we need to write this to return a list of tuples or numpy array

--

## Conclusions

- For a more indepth example of python bindings it is worth looking at the pyNGL code
- This uses lots of different files as functions to generate the bindings (which is quicker)
- It also manages a lot of strange edge cases
- Still not 100% pythonic but ok for OpenGL use

---

## References

- https://www.computerhistory.org/timeline/graphics-games/#169ebbe2ad45559efbc6eb357207c7ce
- https://en.wikipedia.org/wiki/The_Advanced_Visualizer
- https://devguide.python.org/exploring/
- https://docs.python.org/3/c-api/index.html#c-api-index
- https://scipython.com/blog/poisson-disc-sampling-in-python/
