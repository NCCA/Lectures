# A Technical Introduction to Maya

Jon Macey

---

### Maya as a scripting Engine

- at it's simplest maya is a scripting engine that can run MEL language scripts.
- When maya starts up it executes multiple scripts located in the directory 

``` $MAYA_LOCATION/scripts/startup/ ```

- This makes it possible to fully customize the look and feel of maya.

--

# goMaya

- When we run maya in the labs we use the goMaya script 
- this sets up the environment and plugin paths for everything we need.
- However this includes everything for the University build and can be slow

--

## Speeding up startup

- to help speedup maya when launching we can disable any plugins we don't need.
- to do this we use the plugin manager

![](images/plugin1.png)


--

## Disable plugins

- By default I disable the following plugins

	1. Bifrost
	2. MASH
	3. xGen

---


## The Maya Environment

- When maya starts up it reads a file called Maya.env this contains a number of environment variables for Maya.
- Under Linux ```~/maya/version/```
- Under Windows ```%HOMEDRIVE%\%HOMEPATH%\Documents\maya\[version]```
- On a mac this is located in ```~/Library/Preferences/Autodesk/maya/[Version]```
- We are going to use this to setup some directories to use for the next few weeks Lectures

--

## Basic Setup

```
cd $HOME
mkdir MayaScripts
mkdir MayaPlugs
```

- Add this to the Maya.env (you may need both versions of Maya)

``` 
MAYA_PLUG_IN_PATH=/home/jmacey/MayaPlugs
MAYA_SCRIPT_PATH=/home/jmacey/MayaScripts
MAYA_DISABLE_CLIC_IPM=1
MAYA_DISABLE_CER=1
```
- Note the last too can speed up maya start / restart which you will need __a lot__

--

## A simple Mel Script Test

```
global proc helloMel()
{
  print("hello from Mel\n");
}
```
- Save the file in the scripts directory as hello.mel
- in the Mel window source ```hello.mel```
- then call helloMel()

--


## Python Paths

- maya will use the global python path which you can set as usual
- it is also possible to setup some default python behaviors using a file called ```userSetup.py```
- this lives in the default maya user directory as follows
```
# Windows
%HOMEDRIVE%\%HOMEPATH%\Documents\maya\[version]\scripts
# Linux 
~/maya/[version]/scripts
# Mac OSX
~/Library/Preferences/Autodesk/maya/[version]/scripts
```

--

## userSetup.py

- to add to the path in the userSetup.py file we can do the following

```
import sys
sys.path.append('yourpath')
```

- it is quite common to add global python imports here such as 

```
from __future__ import print_function,division
import maya.cmds as cmds
```

--

## A Simple Python Script

```
def helloPy() :
  print ('hello from python ')
```
- Again save this script as helloPy.py in the Scripts directory
- We need to import the module before we use it so the following is needed

```
from helloPy import helloPy
helloPy()
```

--

## [reload](https://docs.python.org/2/library/functions.html#reload)
- To help the development cycle, we can easily modify the script and call 
```
import helloPy
# make changes to source.
reload (helloPy)
```

- to reload the module from the source file, otherwise this will be the same module for the whole of the session.
- Also note that each tab of the script editor is also a different instance so each module is unique to the tab imported

---


## MEL (Maya Embedded Language)

>As a language, MEL is descended from UNIX shell scripting. This means MEL is strongly based on executing commands to accomplish things (like executing commands in a UNIX shell), rather than manipulating data structures, calling functions, or using object oriented methods as in other languages.

--

# [MEL](https://knowledge.autodesk.com/support/maya/learn-explore/caas/CloudHelp/cloudhelp/2018/ENU/Maya-Scripting/files/GUID-60178D44-9990-45B4-8B43-9429D54DF70E-htm.html)

- Maya’s user interface is created primarily using MEL, and MEL provides an easy way to extend the functionality of Maya. 
- Everything you can do using Maya’s graphical interface can be automated and extended using MEL. 
- Familiarity with MEL can deepen your understanding of and expertise with Maya.
- it’s easy to perform a task in the graphical interface, then drag the resulting commands from the Script Editor to the shelf to create a button. 

--

## Assignment

- Mel is a strongly typed language, however it allows implicit declaration and typing in most instances. 
- When you declare a variable you also declare its type and can optionally assign an initial value.
- Variable names start with a $, followed by a letter, then any combination of letters, numbers, and underscores. 

- a variable's type cannot be redefined once it is created, however standard scoping rules are still applicable.


--

## Assignment

```
int $a = 5;
float $b = 3.456;
vector $v = <<1.2, 3.4, 6.5>>;
float $ar[] = {1.2, 3.4, 4.5}; // An array of floats
matrix $mtx[3][2]; // A 3x2 matrix of floats
```

```
int $a=1;
int $b=1;
// Error: int $b=1; // 
// Error: Line 2.7: Invalid redeclaration of variable "$b" as a different type. // 
```

- In this example the variables are effectively global.

--

## Assignment

- A variable must go out of scope before it can be declared as a different type. 
- Best to always use scope when writing simple expressions and tests

```
{
	$s1 = "hello";
	$s2 = " Mel Scripting";
	print( $s1 + $s2);
}
print($s1);
```