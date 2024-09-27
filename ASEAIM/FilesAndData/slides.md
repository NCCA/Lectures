# Lecture 3
## Files and Data

<p/>Jon Macey <br/>

<p/>jmacey@bournemouth.ac.uk

---

# Outline 

- We are going to look at how to read and write files today as well as how to generate stand alone programs
- By the end of the lecture we should have a good understanding of the concepts of
  - stream based file I/O
  - Command Line Arguments
  - Python Modules

---

## Making executables

- Under mac and linux we can make the python script runnable using [chmod](https://www.gnu.org/software/coreutils/manual/html_node/chmod-invocation.html#chmod-invocation)

```
chmod +x myscript.py
```

- we also need to tell the shell which interpreter to use.

```
#!/usr/bin/python
```

- This is know as a "Shebang" or "hash bang"

--

## [#!](https://en.wikipedia.org/wiki/Shebang_%28Unix%29)

- This is the first line of the script and informs the shell which interpreter to use.
- There are a few variants, but we usually use either

```
#!/usr/bin/env python
```

or 

```
#!/usr/bin/python
```

- If you have several versions of Python installed ```/usr/bin/env``` will ensure the interpreter used is the first one on your environment ```$PATH```

--

## Windows

- Under windows the situation is a little different
- Usually to run a python script we need to invoke it using the python.exe command

```
python myScript.py
python.exe myScipt.py
```

- It is possible to generate python executables under windows however this requires 3rd party tools such as [pyinstaler](http://www.pyinstaller.org/) which also work under linux and mac.

---

## Environment Variables
- Environment variables are global system variables available to all processes (i.e. programs)
- Most operating systems have a number of default values set which programs can query to set the way things operate.
- Users can also se their own environment variables to customise how things work.
- It is not uncommon for software packages to install their own environment variables when the program is installed.

--

## Environment Variables
- The PATH environment variable allows us to set a directory where the OS will look for scripts and programs
- We can add a local directory to our system which contains user scripts which can be executed by the user
- The configuration is different for both Windows and Unix

--

## Unix Environment variables

- The default shell used in the linux studios is the bash shell (Bourne again Shell)
- To set environment variable in this shell we use a file called .bashrc which is hidden in the home directory
- if you type ```code ~/.bashrc``` you can access it 

```bash
export PATH=$PATH:$HOME/scripts
```
- if you re-open the shell this will be made permanent
- Now any program placed in this directory may be found and executed

--

## The [os](https://docs.python.org/3/library/os.html) module
 
- The ```import os```  module provides a portable way of using operating system dependent functionality
- This includes opening files, accessing and manipulating paths

```python
#!/usr/bin/env python

import os

for (var,value) in os.environ.items() :
  print('Key {} : Value {}'.format(var,value))
```

--

## [PYTHONPATH](https://docs.python.org/3/using/cmdline.html?highlight=pythonpath#environment-variables)

- Python uses a number of environment variables to help it work
- PYTHONPATH is used to set the default search directories for python modules
  - this is where the ```import``` statement searches
- We can add to this in a number of ways


```python
#!/usr/bin/env python
import os
import sys

print(sys.path)
sys.path.append(os.getenv("HOME") + "/scripts")

print(sys.path)
```

--

## Modules and packages

- A module is a single .py file with Python code
- A package is a directory that can contains multiple Python modules
- there are different ways of loading in modules as show in the next examples each does the same thing.

--

## Modules and packages

```python
import random
random.randint(0,10)
```


```python
from random import randint
randint(0,10)
```

```python
from random import *
randint(0,10)
```

```python
from random import randint as ri
ri(0,10)
```

--

## [Modules and packages](https://docs.python.org/3/reference/simple_stmts.html#the-import-statement)

- ```from module import *``` is generally frowned upon as it imports everything into the current namespace
- ```import math``` for example will import all the math module code into the module but will need to be prefixed with math
- If this becomes problematic import the elements that are needed.

```python
from math import pi,cos,sin
cos(2*pi)+sin(2*pi)
```


--

## The main function

- The main function is a special function for most programming languages 
- It is the first function to be executed and is the entry point for most programs
- The main function is usually passed a set of global system variables called arguments
- These are available through the life of the program and are a good way of passing values to a program

--

## Python main


``` python
#!/usr/bin/env python
import sys


def aFunction(argv=None):
    print("in a function")
    print(f"my name is {__name__}")


if __name__ == "__main__":
    sys.exit(aFunction())

```
```python
#!/usr/bin/python
import sys
import aFunction

def main(argv=None):
	print ("in main function")
	print (f"{__name__}")
	aFunction.aFunction()

if __name__ == "__main__":
    sys.exit(main())
```

--


## Command Line arguments

- When a program is executed form the command line the whole line typed is passed to the program using the variable argv
- argv is a text string array split based on white space
- The following program show how we can print these values out

--


## arguments

```python
#!/usr/bin/env python
import sys


def main(argv=None):
    if argv is None:
        argv = sys.argv
    for index, args in enumerate(argv):
        print(f"{index} : {args}")


if __name__ == "__main__":
    sys.exit(main())

```

--

## getopt
- The getopt function is used to process a list of arguments in the form 
- -l or -vfx will be split into -v -f -x
- -f [optional argument]
- --help (know as a long option)
- The programmer passes a list of these options and the getopt function will split them (any additional command line values will be ignored)
- This is quite an old function and similar to the C library function of the same name

--

## The [argparse](https://docs.python.org/2.7/library/argparse.html) module

- The argparse module makes it easy to write user friendly command-line interfaces. 
- The program defines what arguments it requires, and argparse will figure out how to parse those out of sys.argv. 
- The argparse module also automatically generates help and usage messages and issues errors when users give the program invalid arguments.

--

## argparse example

- I use this in all my renderman examples

```python
#!/usr/bin/python

import sys
import argparse
import inspect

def main(shadingrate=10,pixelvar=0.1,
         fov=48.0,width=1024,height=720,
         integrator='PxrPathTracer',integratorParams={}
        ) :
    args, _, _, _ = inspect.getargvalues(inspect.currentframe()) 
    for arg in args: 
        print (arg , locals()[arg])


if __name__ == '__main__':
    parser=argparse.ArgumentParser()
    parser = argparse.ArgumentParser(description='Modify render parameters')

    parser.add_argument('--shadingrate', '-s', nargs='?', 
                                            const=10.0, default=10.0, type=float,
                                            help='modify the shading rate default to 10')

    parser.add_argument('--pixelvar', '-p' ,nargs='?', 
                                            const=0.1, default=0.1,type=float,
                                            help='modify the pixel variance default  0.1')
    parser.add_argument('--fov', '-f' ,nargs='?', 
                                            const=48.0, default=48.0,type=float,
                                            help='projection fov default 48.0')
    parser.add_argument('--width' , '-wd' ,nargs='?', 
                                            const=1024, default=1024,type=int,
                                            help='width of image default 1024')
    parser.add_argument('--height', '-ht' ,nargs='?', 
                                            const=720, default=720,type=int,
                                            help='height of image default 720')

    parser.add_argument('--rib', '-r' , action='count',help='render to rib not framebuffer')
    parser.add_argument('--default', '-d' , action='count',help='use PxrDefault')
    parser.add_argument('--vcm', '-v' , action='count',help='use PxrVCM')
    parser.add_argument('--direct', '-t' , action='count',help='use PxrDirect')
    parser.add_argument('--wire', '-w' , action='count',help='use PxrVisualizer with wireframe shaded')
    parser.add_argument('--normals', '-n' , action='count',help='use PxrVisualizer with wireframe and Normals')
    parser.add_argument('--st', '-u' , action='count',help='use PxrVisualizer with wireframe and ST')

    args = parser.parse_args()
    if args.rib :
        filename = 'rgb.rib' 
    else :
        filename='__render'

    integratorParams={}
    integrator='PxrPathTracer'
    if args.default :
        integrator='PxrDefault'
    if args.vcm :
        integrator='PxrVCM'
    if args.direct :
        integrator='PxrDirectLighting'
    if args.wire :
        integrator='PxrVisualizer'
        integratorParams={'int wireframe' : [1], 'string style' : ['shaded']}
    if args.normals :
        integrator='PxrVisualizer'
        integratorParams={'int wireframe' : [1], 'string style' : ['normals']}
    if args.st :
        integrator='PxrVisualizer'
        integratorParams={'int wireframe' : [1], 'string style' : ['st']}


    main(args.shadingrate,args.pixelvar,args.fov,args.width,args.height,integrator,integratorParams)```


---

## Accessing the Filesystem
- The python [os module](https://docs.python.org/3/library/os.html) contains a number of functions which allow us to access the file system
- This module allows us to create files and directories
- Change directories
- List the contents of a directory
- and much more 

--

## A Note about filesystems

- Filesystems are complex
    - different platforms work in different ways (case sensitive)
- Windows has Drives (C:\) linux does not
- the ```\``` has meaning in programming languages (it is know as an escape character)
    - quite often need to use ```\\``` which means ```\```  in scripts
- Linux / Mac OSX uses ```/``` for paths and no drive letter
- And don't get me started on the use of spaces in filenames! 

--

## simple example

```python
#!/usr/bin/env python

import os

cwd = os.getcwd()
print(f"Current directory is {cwd}")
try:
    os.mkdir("testdir")
except FileExistsError:
    print("directory testdir already exists")
    pass

os.chdir("testdir")
new_dir = os.getcwd()
print(f"Current directory is {new_dir}")

try:
    os.chdir(cwd)
    os.rmdir(new_dir)
except FileNotFoundError:
    print("can't remove the specified directory")


```

--

## Directory traversal

- python has a number of different functions to allow the traversal of directories in the filesystem
- to grab just the filenames we can use the function ```os.listdir()``` as follows

```python
#!/usr/bin/env python

import os

for item in os.listdir() :
    print(item)
```

--

## ```os.scandir()```

- ```scandir()``` is a directory iteration function like ```os.listdir()```
- unlike ```os.listdir()``` it gives us a ```DirEntry``` objects that include file type and stat information along with the name

```python
#!/usr/bin/env python

import os

with os.scandir('.') as it:
    for entry in it:
        if not entry.name.startswith('.') and entry.is_file():
            print(f'Name {entry.name} path {entry.path} \nStat : {entry.stat()}')

```


--

## [```with```](https://www.python.org/dev/peps/pep-0343/)

- The with statement is a form of [RAII](https://en.cppreference.com/w/cpp/language/raii)
>The with statement is used to wrap the execution of a block with methods defined by a context manager.  This allows common ```try…except…finally``` usage patterns to be encapsulated for convenient reuse.

- [see here](https://docs.python.org/3/reference/compound_stmts.html#the-with-statement)
- This is used a lot in file opening and other i/o idioms

--

## [```os.walk()```](https://docs.python.org/3/library/os.html#os.walk)

- the walk function allows us to traverse the full directory tree

```
#!/usr/bin/env python

import os

for root, dirs, files in os.walk(".", topdown=True):
    print(f"Root :{root}\n\tDirectories : {dirs}\n\tFiles {files}")

```

--

## [pathlib](https://docs.python.org/3/library/pathlib.html)

- One of the main issues with low level file system operations is the different OS have different commands
- To overcome this there are different libraries to help with this

```python
#!/usr/bin/env python
import pathlib

path = pathlib.Path.cwd()
print(path)
print(f"name is {path.name}")
Windows = pathlib.PureWindowsPath(r"C:\Users\jmacey/test.py")
print(Windows, type(Windows))
for p in pathlib.PurePosixPath(Windows).parts:
    print(p)

print(f"name is {Windows.name}")
print(f"suffixes {Windows.suffixes}")

# Join is useful

folder = pathlib.Path.home().joinpath("scripts", "test.py")
print(folder)

```


--

## [shutil](https://docs.python.org/3/library/shutil.html)

- high level operations on files and collections of files. 
- functions are provided which support file copying and removal. 
- Some meta-data is not copied (depending on FS)

```python
#!/usr/bin/env python

import os
import shutil

os.system("tar vfxz BaseMayaProject.tgz")

shutil.copytree("BaseMayaProject", "NewMayaProject")
shutil.rmtree("BaseMayaProject")
```

---

## Files
- One of the simplest way of communicating between different packages and different programs is by the use of text files.
- Reading and writing files in python is very simple and allows us to very quickly output elements from one software package to another in an easily readable hence debuggable way.

--

## Stream I/O

- When a file is opened a file descriptor is returned and this file descriptor is used for each subsequent I/O operation, when any operation is carried out on the file descriptor its is known as a stream.
- When a stream is opened the stream object created is used for all subsequent file operations not the file name.

--

## [The open function](https://docs.python.org/2/library/functions.html#open)

```python
# open a file for reading
FILE=open('test.txt','r')

# open a file for writing
FILE=open('text.txt',''w')
```
- The open function takes two parameters
  - The first is a String for the name of the file to open
  - The 2nd  is the open mode 'r' for reading from a file 'w' for writing to a file

--

## The close method

``` python
FILE.close()
```

- Once a file has been finished with it must be closed.
- This is especially important if we are writing to a file as the OS may be storing these values in memory.
- The close function actually forces the OS to flush the file to disk and closes thing properly

--

## Errors and Exceptions

- the open function will throw an exception if 
    - The file is not found ```FileNotFoundError``` (python 2 ```IOError```)
    - ```PermissionError``` or python 2 ```IOError``` if permission is denied
- because of this it is good practice to use the with clause, this also has the bonus effect of closing the file when finished

--

## readFile.py

```
#!/usr/bin/env python

import os
import sys


def main(argv=None):
    if argv is None:
        argv = sys.argv[1:]  # skip first arg

    for name in argv:
        with open(name) as file:
            lines = file.readlines()
            for i, line in enumerate(lines):
                print(f"{i:04d}: {line}", end="")
        print("-" * 80)


if __name__ == "__main__":
    sys.exit(main())
```

--

## writing files

- to write to a file we can use similar processes to printing
- first we must open the file for writing, to do this we use

```
file = open('filename','w')
```

- next we use the write method (along with usual formatting processes) as shown in the following example

--

## Random Points on a sphere

```
#!/usr/bin/env python

import argparse
import math
import random


def randomPointOnSphere(radius=1):
    phi = random.uniform(0, 2 * math.pi)
    costheta = random.uniform(-1, 1)
    u = random.uniform(0, 1)
    theta = math.acos(costheta)
    # note we could use np.cbrt to calculate cube root
    cbrt = lambda x: x ** (1.0 / 3.0) if 0 <= x else -((-x) ** (1.0 / 3.0))

    r = radius * cbrt(u)
    x = r * math.sin(theta) * math.cos(phi)
    y = r * math.sin(theta) * math.sin(phi)
    z = r * math.cos(theta)
    return x, y, z


def main(numPoints, filename, radius):
    with open(filename, "w") as file:
        for i in range(0, numPoints):
            x, y, z = randomPointOnSphere(radius)
            file.write(f"{x} {y} {z}\n")


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser = argparse.ArgumentParser(description="generate random points on a sphere")
    parser.add_argument(
        "--num",
        "-n",
        nargs="?",
        const=10,
        default=10,
        type=int,
        help="number of points to generate default 10",
    )
    parser.add_argument(
        "--radius",
        "-r",
        nargs="?",
        const=1.0,
        default=1.0,
        type=float,
        help="radius of sphere default 1.0",
    )
    parser.add_argument("--file", "-f", type=str, required=True)
    args = parser.parse_args()
    main(args.num, args.file, args.radius)
```

--

## Loading files

- the data stored in this file will be text
- it will need to be converted to float

```

#!/usr/bin/env python
import argparse


def main(file_name):
    with open(file_name, "r") as file:
        lines = file.readlines()
        for line in lines:
            numbers = line.split(" ")
            print(numbers)
            if len(numbers) == 3:
                try:
                    x = float(numbers[0])
                    y = float(numbers[1])
                    z = float(numbers[2])
                    print(f"{x} {y} {z}")

                except ValueError:
                    print("unable to convert value to float")


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser = argparse.ArgumentParser(description="parse points file")

    parser.add_argument("--file", "-f", type=str, required=True)
    args = parser.parse_args()
    main(args.file)

        
```

---


## JSON 

- JSON is a text format for storing data
  - **J**ava**S**cript **O**bject **N**otation
- Fairly ubiquitous in web and other formats, frequently used for config and setting files
-  It is a "data only" format (so not comments!)
-  A JSON object is a Key Value format

--

## JSON example

```json
{
  "first_name" : "Jon",
  "last_name" : "Macey",
  "office_number" : 246,
  "online" : false
}
```
- JSON has a few data types 

--

## Data types

- strings
- numbers
- objects
- arrays
- Booleans (true or false)
- null
- These map well to python data types and can also be combined to create more complex objects

--

## Designing Formats

- With json it is our job to design the format
  - this can take some time to design and understand 
- We can generate quite complex formats 
- These can be specified using a [schema](https://json-schema.org/draft/2020-12/json-schema-validation.html)

--

## Simple Example 

<iframe src="https://www.jsonschemavalidator.net/s/YDXUPhSr" width="100%" height="500" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>

--

## Simple example

```json
{
  "$schema": "http://json-schema.org/draft-04/schema#",
  "title": "MyFileFormat",
  "description": "The format for my program",
  "type": "object",
  "properties": {
    "width": {
      "description": "The width of the map",
      "type": "integer"
    },
    "height": {
      "description": "the height of the map",
      "type": "integer"
    },
    "map_contents": {
      "description": "The map data",
      "type": "array",
      "items": {
        "type": "object",
        "properties": {
          "x_pos": {
            "description": "the xposition",
            "type": "integer"
          },
          "y_pos": {
            "description": "the yposition",
            "type": "integer"
          },
          "value ": {
            "description": "the value on the map",
            "type": "number"
          }
        }
      }
    }
  },
  "required": [
    "width",
    "height"
  ]
}
```

```
{
	"width" : 10,
    "height" : 10,
      "map_contents" : [
        {
      	  "x_pos" : 2,
          "y_pos" :3,
          "value" : 2.2
        },
        {
      	  "x_pos" : 3,
          "y_pos" :4,
          "value" : 22.2
        }
      ]
}
```


--

## Using Python Json

- python has a json module as on of the built in modules
- The following example shows this in action

```python
#!/usr/bin/env python
import json
from pprint import pprint

with open("data.json", "r") as json_file:
    data = json.load(json_file)
    pprint(data)
    print(f"{data['width']=}")
    print(f"{data['height']=}")
    for values in data["map_contents"]:
        print(f"{values['x_pos']=}")
        print(f"{values['y_pos']=}")
        print(f"{values['value']=}")
        print("-" * 30)

```

--

## Writing JSON

- The simplest method to write json is to place it into a python dictionary

```python
#!/usr/bin/env python
import json
import random

json_data = dict()  # create a dictionary
json_data["width"] = 200
json_data["height"] = 200
map_data = list()
for i in range(100):
    x_pos = random.randint(0, 100)
    y_pos = random.randint(0, 100)
    value = random.uniform(0.0, 20.0)
    map_data.append({"x_pos": x_pos, "y_pos": y_pos, "value": value})

json_data["map_contents"] = map_data

json_object = json.dumps(json_data, indent=4)
# Writing to sample.json
with open("map_data.json", "w") as json_file:
    json_file.write(json_object)

```

---

## [CSV](https://en.wikipedia.org/wiki/Comma-separated_values) (Comma Separated Values)

- CSV data is a simple format with commas (or other delimiters) used to separate data items
- Particularly used for tabular data (excel) 
- used a lot in data analysis tools ([pandas](https://pandas.pydata.org/)) 

--

## [csv module](https://docs.python.org/3/library/csv.html)

- built in to python

```python
#!/usr/bin/env python
import csv
import random

header = ["x_pos", "y_pos", "size"]
with open("csv_data.csv", "w") as csv_file:
    csv_writer = csv.writer(csv_file)
    csv_writer.writerow(header)
    for i in range(100):
        x_pos = random.randint(0, 200)
        y_pos = random.randint(0, 200)
        size = random.randint(0, 10)
        csv_writer.writerow([x_pos, y_pos, size])
```

- can also write multiple rows at a time

--

## reading CSV

```python
#!/usr/bin/env python

import csv

with open("csv_data.csv", newline="") as csv_file:
    contents = csv.reader(csv_file)
    for row in contents:
        print(",".join(row))
```

--

## Be wary

- not all CSV parsers are fault tolerant
  - so errors can propagate over lines.
- Sometimes easier to write your own and split to convert to numeric types
- If using Pandas use [pandas.read_csv¶](https://pandas.pydata.org/docs/reference/api/pandas.read_csv.html#pandas-read-csv) rather than the built in csv module


---

## [Pickle](https://docs.python.org/3/library/pickle.html)

- Pickle is a module use for python object serialization
- Can be used for build in python types as well as classes
- We will look at this in more detail in another lecture

--

## Simple Example

```python
#!/usr/bin/env python
import pickle
import random

a = random.sample(range(100), 20)
print(a)

with open("test.pickle", "wb") as file:
    pickle.dump(a, file, protocol=pickle.HIGHEST_PROTOCOL)

with open("test.pickle", "rb") as file:
    b = pickle.load(file)
print(b)
print(a == b)

```

---




## References

- [http://en.wikipedia.org/wiki/Environment_variable](http://en.wikipedia.org/wiki/Environment_variable)
- [http://en.wikipedia.org/wiki/Main_function_(programming)](http://en.wikipedia.org/wiki/Main_function_(programming))
- [http://docs.python.org/library/shutil.html](http://docs.python.org/library/shutil.html)
- [http://www.devshed.com/c/a/Python/String-Manipulation/](http://www.devshed.com/c/a/Python/String-Manipulation/)
- [http://docs.python.org/library/string.html](http://docs.python.org/library/string.html)
- [http://www.rafekettler.com/magicmethods.html](http://www.rafekettler.com/magicmethods.html)

