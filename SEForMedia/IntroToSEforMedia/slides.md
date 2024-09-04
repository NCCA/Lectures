
## Software Engineering for Media 
## Introduction 
### MSc AIM
Jon Macey

jmacey@bournemouth.ac.uk

---

## Teaching Team

- **Jon Macey** *jmacey@bournemouth.ac.uk* Unit Leader
- **Dr Hammadi Nait-Charif**  *<hncharif@bournemouth.ac.uk>*


--

###  Intended Learning Outcomes

-  demonstrate an ability to write complex programs using a high-level programming language and deep learning frameworks
-  apply various data augmentation techniques on a range of multimedia data.
- apply Test Driven Development to the design and implementation of a major software artefact informed by industry best practice.
- display proficiency in applying modern deep-learning techniques to multimedia data
- develop proficiency in setting up development environments.

--

## Outline of Unit

- This unit is one of the foundations of the course, and is designed to give you the technical programming skills to apply the Machine Learning and AI models to areas of your choice
-  It further adds practical computing and software engineering techniques to enable in depth understanding of the areas of AI / ML and media.

--

## Outline of Unit

- Introduction to Software Engineering principles
  - Python, Test Driven Development, OO concepts, Version Control, Design Patterns 
- Using Jupyter Notebooks
  - Pandas, NumPy, Dataframes
- Data collection and processing
  - Finding an appropriate data source.
  - Analysing your data
  - Data cleaning and augmentation techniques.

--

## Outline of Unit 

- Model architectures - Neural network layers 
- (Convolutional, Linear, LSTM, etc.), Activation Functions, Normalisation (Batch-norm).
- Training loop - Optimisers, Loss function, forward and backwards pass (backpropagation). Plotting loss and analysing for overfitting.
- Train-Test-Validation 
  - The importance of testing and validating your model.
- Deployment 
  - offline and online.

---

## What we will use

- Python 3.x and [Anaconda](https://www.anaconda.com/download/) / J[upyter Notebooks](https://jupyter.org/)
- [PyTorch](https://pytorch.org/) for core ML however there are other tools such as [TensorFlow](https://www.tensorflow.org/) 
- [git](https://guides.github.com/activities/hello-world/) and [GitHub](https://github.com/) for versions control and code submission
- Various Python Tools and libraries ([Black](https://black.readthedocs.io/en/stable/index.html),[PyEnv](https://github.com/pyenv/pyenv),[numpy](https://numpy.org/), [pandas](https://pandas.pydata.org/))

---


### Citing Code in your Work

- A lot of programming / software engineering is about code re-use.
- It is important to cite your code when using 3rd party code
	- We have methods to do this that allow you to use / re-use what we call ["boiler plate code"](https://en.wikipedia.org/wiki/Boilerplate_code) 
	- This is very common practice in software engineering
- But not your projects must also contain original work as well!
 

--

### Citing code in your work

```python
"""
a simple Tensor Flow example
from :-
https://www.tensorflow.org/tutorials/quickstart/beginner
[Accessed 2022]. Avaliable from : <https://www.tensorflow.org/tutorials/quickstart/beginner>
"""
model = tf.keras.models.Sequential([
  tf.keras.layers.Flatten(input_shape=(28, 28)),
  tf.keras.layers.Dense(128, activation='relu'),
  tf.keras.layers.Dropout(0.2),
  tf.keras.layers.Dense(10)
])
```

--

## Citing Code
- The previous example was taken and modified from a website
- We need to cite this source in the code to avoid any notion of plagiarism.
- To do this we use the standard Harvard referencing format

--

### Citing a small section of code

- If you use a small section of code do the following
- Cite at the beginning of the code section
- at the end of the section mark as end of citation

```python
"""
The following section is from :-
Dan Sunday (2006) Intersections of Rays, Segments Planes and Triangles in 3D [online]
Accessed [2010] 
Avaliable from http://softsurfer.com/Archive/algorithm_0105/algorithm_0105.htm#intersect_RayTriangle()
"""
n=calcNormal(v0,v1,v2)
a = -n.dot(tvec)
b = n.dot(dir)
r=a/b;
# End Citation
```

---

## Coding Standards

- Most companies have coding standards, these guidelines help to make code conformant and easy to understand
- It helps with larger collaborations as all code is easy to locate and traverse
- We have an NCCA Coding standard for C++

--


## [NCCA Coding Standard](https://nccastaff.bournemouth.ac.uk/jmacey/NCCACodingStandard/index.html)
- The coding standard includes more details on how to cite code as well as other rules
- This helps us integrate code with existing projects
- Helps staff to understand code quicker when debugging and fixing problems
- Is good practice for the future (most companies use standards)
- We can also use tools to help with this.

--

## [Python Coding Standards](https://peps.python.org/pep-0008/)

- As python is a relatively new language it specified a coding standards very early (unlike C/C++)
- This was presented in the Python Enhancement Proposals 8 in 2001. (PEP-8) 
- We have tools that allow us to check our code and format to this standard
- If you are unsure check the PEP-8 guide, we expect you to be conformant with PEP-8 for all code

--

##  Tool Support

- We will use a number of tools to make it easier to format and conform our code
- We will install and set these up in the labs over the next few weeks.
  - [black](https://github.com/psf/black) 
  - [autopep8](https://pypi.org/project/autopep8/)
  - [isort](https://pycqa.github.io/isort/)
- Most of these will integrate into VSCode which will be the main editor for early development

--

##  Using AI for Code

- There are a number of "AI Coding Assistants" available to use. 
- It is fine to use them but you should use caution as the code is sometimes not what you need
	- I tend to use it as a better search system 
- If you do use code generated by co-pilot etc you must cite it as outlined in the coding standards.

---

## Python

- Python is a versatile programming language used for a wide range of applications. Here are some of the main uses:
		**Data Science and Machine Learning**
		**Web Development**
		**Automation and Scripting**
		**Cybersecurity**
		**Digital Content Creation (DCC) Tools and Pipelines***
		

--
## Why python?

- In recent years python has become a core language for Digital Content Creation
  - it is easy to embed and use in DCC tools
- Good support for GUI (PyQt / PySide)
- Machine Learning and AI tools support python
- Easy to learn (to start with!) Easy to abuse too!

--

## Python

- python is a very flexible programming language, it can be used in a number of different ways.
- Most of our animation packages allow for embedded python scripting
- We can also write complex programs which run stand alone, and if written correctly can run on all operating systems

--

## Python in Pipeline and DCC's

- [VFX reference platform](https://vfxplatform.com/) mandates 3.10.x  - 3.11 due to compatibility with other tools
  - maya 2019 still in use in some places still uses python 2.7 but this is rare.

--

## Embeding and extending

- (C)Python is very easy to extend and embed
  - Extending is adding new compiled libraries with python bindings
- Embedding is the opposite where we extend our app with scripting
- There are many 3rd party tools to enable the generation of python bindings
- Most machine learning tools are written in C++ with Python bindings.
- This is true of machine learning tools as well which are typically written in C++ / CUDA and have python as a front end.

--

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

<img style="border: 0;" src="https://imgs.xkcd.com/comics/python.png" width="40%">
- [python easter eggs](http://digitizor.com/easter-eggs-in-python/)

---

## Getting started
- At it’s simplest level python can be used as a simple command interpreter
- We type python into the terminal and we get a prompt which lets us enter commands
- This is know as the REPL [Read, Eval, Print, Loop](https://en.wikipedia.org/wiki/Read%E2%80%93eval%E2%80%93print_loop)
- If nothing else we can use this as a basic calculator
- It is also useful for trying simple bits of code which we wish to put into a larger system

--

## Python Implementations

- Standard python used by most people is CPython (this is also in the DCC tools)
- [iPython](https://ipython.org/) is another version used for many things, including the Jupyter Project
  - This can be installed using [anaconda](https://www.anaconda.com/)
- There are other [alternatives](https://www.python.org/download/alternatives/)

--

## References and Resources

- [Python Cheat Sheet](https://www.pythoncheatsheet.org/)