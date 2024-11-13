# Lecture 5 Into to Numpy
Jon Macey

jmacey@bournemouth.ac.uk

---

## What is Numpy

- Numpy (Numerical Python) is an Open Source library used for numerical computing in Python.
- It provides support for large, multi-dimensional arrays and matrices, 
  - along with a collection of mathematical functions to operate on these arrays efficiently. 
- NumPy is widely used in scientific computing, data analysis, machine learning, and other domains requiring fast numerical computations.
- It has recently been updated to version [2.0.0](https://numpy.org/doc/stable/release/2.0.0-notes.html) however not all packages have been updated to use this version.

--

## Arrays

- The core of NumPy is the `ndarray` (n-dimensional array) object for representing arrays.
- it fast and efficient operations for large datasets. 
- It is similar to Python lists but optimized for numerical operations and more flexible in terms of dimensions.


--

## Broadcasting

- broadcasting is the process of applying operation on arrays of different shapes.
- NumPy automatically broadcasts the smaller array over the larger array so that they have compatible shapes.
- This eliminates the need for explicit loops and makes the code more readable and faster.

--

## Mathematical Functions

- NumPy comes with a wide range of mathematical functions like trigonometric, statistical, and algebraic operations that can be applied directly to arrays.
- These functions are optimized for performance and can be used to perform complex operations on large datasets efficiently.

--

## Linear Algebra

- NumPy provides efficient linear algebra operations such as matrix multiplication, determinants, eigenvalue computations, and more, often used in machine learning and scientific computations.
- This is basically the core of many machine learning algorithms and scientific computations, we will be doing these with both Numpy and PyTorch.

--

## Random Number Generation

- It has tools for generating random numbers, which are used in simulations, probabilistic models, and other applications.
- NumPy provides a variety of random number generators for different distributions, as well as tools for shuffling and sampling data.
- This is useful for generating synthetic data, bootstrapping, and other statistical applications.


---

## Installation

- NumPy is included in the Anaconda distribution, which is the recommended way to install it for machine learning
- You can also install it using pip by running the following command:

```bash
pip install numpy
```

--

## version

- We can test which version of Numpy we have installed by running the following code:

```python
import numpy as np
print(np.__version__)
```

```bash
1.26.4
```
- We are going to use this rather than 2.0.0 as not all packages have been updated to use this version.


---

## Numpy Reference

- The core help for numpy can be found here https://numpy.org/doc/1.26/reference/index.html
- The rest of this lecture will be hosted in an interactive Jupyter notebook [here](https://github.com/NCCA/SEForMedia/blob/main/Lecture5/IntroductionToNumpy.ipynb)

---


