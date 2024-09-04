## Documentation and Deployment

Jon Macey

jmacey@bournemouth.ac.uk

---

## Documentation

- Requirements documents are usually written before development
- Code should be documented when written (most people don't)
- Technical Documents (API / Design / Architecture) written as you go (with examples)
- End User (i.e. user manuals) written towards the end of the production

--


## Deployment

- Deployment is usually the last stage of the development cycle
  - it ensures that the product works on the target devices.
- It is part of the DevOps cycle which involves Testing, Packaging and Releasing
- Releases could be either internal or to 3rd parties (sometimes daily release)

--

## Tool Support

- Both deployment and documentation can be automated to some extent with tools
- This helps with consistency and automation of the processes
- We will investigate a few of the tools available to us.
- Many companies have in house tools for both.


---

## Documentation

- For this part of the unit we are only going to look at software / API documentation
- This is similar to the Qt Docs or ReadTheDocs style
- We will look at [Doxygen](https://www.doxygen.nl/) and [Sphinx](https://www.sphinx-doc.org/en/master/)
  - In particular Doxygen is good for C like languages
  - Sphinx for Python (but can use other languages) 

--

## Documentation

- Most documentation tool use special comment flags to process and document tools
- It can be done as part of the build process
- Most python documentation tools take the standard docstrings and produce documentation

--

## Doxygen

- Doxygen tags usually begin with on of the following comment blocks

```c++
/**
 * ... text ...
 */

/*!
 * ... text ...
 */

///
/// ... text ...
///

//!
//!... text ...
//!

```

--

## Where to put comments

- We can put comments in either the .cpp file or .h file. 
- I usually prefer to put it in the header files
  - because as you add and remove methods it is easy to change comments etc
- Putting in .cpp can hide stuff when deploying an API

--

## Header Comments

```c++
/// @file Vec3.h
/// @brief encapsulates a 3 float object like glsl vec3 but not maths
/// use the Vec3 class for maths and the asVec3 to return a vec3
/// @author Jonathan Macey
/// @version 1.0
/// @date 20/6/11 initial version
```

--

### Method / Function comments

```c++
/// @brief return this dotted with _b
/// @param[in]  _b vector to dot current vector with
/// @returns  the dot product
float dot(const Vec3 &_b  )const noexcept;

```

--

## Doxyfile

- Doxygen uses a file called the Doxyfile to generate the documentation
- We can use Doxygen to create an empty file for us

```
doxygen -s -g 
```

- This file will need to be edited to configure options (read the manual)

```
doxygen 
```

---

## Sphinx

- We need to install Sphinx before we start

```
pip install sphinx
pip install sphinx-rtd-theme
```

--

## initial setup

- we can use sphinx-quickstart to create our initial setup

```python
sphinx-quickstart docs
```
- answer y to the seperate source and build dirs
- this will allow us to version config but not build

--

## docs/source/conf.py

- next we edit the conf file to add themes and extensions
- in particular we modify paths to ensure we can find modules when running  autodoc

```python

import os
import sys
sys.path.insert(0, ("../Math"))

extensions = ["sphinx.ext.autodoc", "sphinx.ext.napoleon"]
html_theme = "sphinx_rtd_theme"
napoleon_include_special_with_doc = True
```

--

## Generate Autodocs

- next we can use the apidoc tools to generate documents from the source code

```python
cd docs
sphinx-apidoc --append-syspath  -o source ../*
```

--

## Finally build the docs

```
make clean;
make html
```

- we can also use

```
 sphinx-build -b html source/ build/html

```


---

## Deployment

- deployment is a difficult task, and depends upon many factors
- At it's simplest level we could just distribute source code an let the user build
  - This requires some level of skill from the user
- we could tar.gz the build tool but would require we have certain libraries installed
- Typically packaging and deployment will be combined

--

### In house vs customer

- Usually in house deployment is easier, we know the systems and what they are
- We can test on a known base and install as required
- Customer deployment harder, unknown systems and installs
  - May need to deploy other runtime tools (libraries etc)
- Either way good support will be needed

--

## [PyInstaller](https://pyinstaller.org/en/stable/)

- This is the easiest tool if you are using python 3.7 or above
- Due to the way we have previously installed pyenv we need to do some extra work as pyenv needs dynamic python libraries.

```
env PYTHON_CONFIGURE_OPTS="--enable-shared" pyenv install 3.9.7
pip install pyinstaller
```

--

## PyInstaller

- we can now install the package. As an example we will use the LayoutTool developed in the lab
- This needs the python modules as well as the forms/ directory and assestDatabase.db
- In the Layout tool folder we run the following

```
pyinstaller --add-data="./forms/*:./forms/" --add-data="./assetDatabase.db:./" LayoutTool.py
```

--

## PyInstaller

- This will create a dist folder with a subfolder the name of the source file (LayoutTool)
- Within this is an executable LayoutTool and all the required libraries
- This folder can be compressed and distributed as a package 

--

## PyInstaller

- This works well but will require a build per OS / Variant
- Can become complex to package but still one of the simplest tools
- For windows [Py2Exe](https://www.py2exe.org/) can be used
- See also
  - [Nukita](https://nuitka.net/) [PyOxidizer](https://github.com/indygreg/PyOxidizer) 

---

## PyPi 

- We can publish a package to pypi to allow users to pip install our packages
- You will need an account to publish a module to PyPi however you can create a wheel package for distribution by other means
- This takes quite a lot of setup and more details can be found [here](https://packaging.python.org/en/latest/tutorials/packaging-projects/)

---

## C++ Deployment

- There are a number of tools to deploy C++ applications again it can depend upon OS
- Qt has a good [installer framework](https://doc.qt.io/qtinstallerframework/) but again requires work
- Visual Studio on Windows has [project templates](https://docs.microsoft.com/en-us/cpp/ide/walkthrough-deploying-your-program-cpp?view=msvc-170)

- You can also use tools like [vcpkg](https://vcpkg.readthedocs.io/en/latest/examples/installing-and-using-packages/) or [conan](https://docs.conan.io/en/latest/devtools/running_packages.html)

---

## Final thoughts

- we need to think about relocatability 
  - Software may need to be on different paths / drives 
  - Environment variables are good for this (set a APP_ROOT)
- Limiting deployment targets make it easier
- Deployment is hard usually a department will deal with it


