# Lecture 7 : PyTorch and Tensors
Jon Macey

jmacey@bournemouth.ac.uk

---

## What is PyTorch

- PyTorch is an open-source deep learning framework primarily developed by Facebook’s AI Research lab (FAIR)
- It allow us to build and train neural networks as well as other machine learning models
- It has a number of extra modules to help with data loading, image processing and other common tasks
- In this lecture we will explore some of these features and how to use them.


--

## Overview

- The first part of this lecture will look at the overall features of PyTorch
- New we will look at how to install and get started (this will differ per platform)
- Next we will look at some of the core modules.
- The final part of this lecture and the following onces will use Jupyter Notebooks to explore some of the features of PyTorch in more detail.

---

## Tensor Based Computing

- at it's core pytorch is a tensor based computing library
- Tensors are similar to numpy arrays but with some key differences in particular they can be used on both the CPU and GPU
  - Note with Numpy 2.x we can now also use the GPU
- Tensors are the core data structure in PyTorch and are used to store data and perform operations on the data

--

## But what is a Tensor?

- A tensor is a generalization of a matrix 
  - it is a fundamental data structure in machine learning, especially in frameworks like PyTorch and TensorFlow.
- Think of them as a way of encapsulating data that can be represented as an array of numbers.
- In simpler terms, a tensor is a multi-dimensional array that can hold data similar to how vectors and matrices do, but in more dimensions. 

--

## Tensor properties

- A tensor is defined by three key attributes:
  - Number of dimensions (rank)
  - Shape
  - Data type

--

## [Tensor Rank](https://mathworld.wolfram.com/TensorRank.html)

| Rank | Math Entity | 
|------|-------------|
| 0    | Scalar      |
| 1    | Vector      | 
| 2    | N x M Matrix |
| >= 3    | Tensor    | 

--

## Tensor Rank

- Dimensionality: Tensors can have different numbers of dimensions (also called ranks):
  - 0D Tensor: A scalar, a single number. Example: 5.
  - 1D Tensor: A vector, like an array of numbers. Example: [1, 2, 3].
  - 2D Tensor: A matrix, like a table or grid of numbers. Example: a 2D array or list of lists.
  - 3D Tensor: A cube or a series of 2D matrices stacked together. Example: a color image with height, width, and three color channels (RGB).

--

## Higher dimesional Tensors

- Higher dimensions: Tensors can extend beyond three dimensions, with each additional dimension representing more complex data structures.

- for example 
  - 4D Tensor: A collection of matrices. Example: a collection of color images.
  - 5D Tensor: A collection of 3D volumes. Example: a collection of video sequences.
  - and so on...

---

## Tensor Shape

- The shape of a tensor describes the size of each dimension. 
- For example, a tensor with a shape of (3, 4) would have 3 rows and 4 columns (a 2D tensor).
- This is similar to the shape of a matrix in linear algebra or the shape of a numpy array.
- The shape of a tensor is important as it will determine the number of elements in the tensor.

--

## Tensor Data Type

- The data type of a tensor describes the type of data stored in the tensor.
- Common data types include integers, floats, and booleans.
- The data type of a tensor is important as it will determine the precision of the data stored in the tensor.
- PyTorch supports a wide range of data types, including 32-bit and 64-bit floating point numbers, 8-bit and 16-bit integers, and boolean values.

---

## Operations

- PyTorch provides a wide range of operations for working with tensors.
  - These operations include arithmetic operations (addition, subtraction, multiplication, division)
  - matrix operations (matrix multiplication, matrix inversion)
  - and other operations (transposing, indexing, slicing).

- These operations can be used to perform a wide range of tasks, from simple arithmetic to complex machine learning algorithms.

--

## CPU vs GPU

- One of the key features of PyTorch is its support for running computations on both the CPU and GPU.
- This is know as the device and we can move tensors between the CPU and GPU using the `.to()` method.
- If there is no GPU present most operations will default to the CPU.
- This is a key feature as it allows us to take advantage of the parallel processing power of the GPU to speed up computations.

--

## Types of GPU 

- The GPU is a powerful parallel processor that can perform thousands of computations simultaneously.
- PyTorch supports running computations on both NVIDIA and AMD GPUs. 
- There is also support for Metal for Apple devices, however not all features are supported.
- PyTorch also supports running computations on multiple GPUs in parallel, allowing you to scale up your computations to take advantage of the power of multiple GPUs.


--

## GPU

- we need to keep track of where our tensors are stored
- we can use the `.device` attribute to check where a tensor is stored
- In a lot of cases we will generate our data on the CPU then move it to the GPU for training
  - once this is done we can move the data back to the CPU for further processing

--

## Tensors in Machine Learning:

- in Machine Learning, we use tensors to store and manipulate data.
  - **Input Data:**  : a batch of images can be represented as a 4D tensor of shape (batch_size, channels, height, width).
  - **Model Parameters** :  Neural network weights and biases are stored as tensors, which are updated during training.
  - **Outputs** : The output of a neural network is also a tensor, which can be used to make predictions.



---

## PyTorch Installation

- PyTorch can be installed using pip or conda however we need to be careful to install the correct version for our system.
- In particular we need to make sure we have the correct version of CUDA installed if we want to use the GPU.
- in the labs we are using nvidia GPUs with CUDA 12 so we need to get this version.

--

## Installing PyTorch

- the web page give use a good tool to select the correct version for our machine https://pytorch.org/get-started/locally/ 
- We can determine which version of CUDA we have installed by running `nvidia-smi` in a terminal

```
nvidia-smi
Fri Oct 18 11:53:32 2024
+-----------------------------------------------------------------------------------------+
| NVIDIA-SMI 555.42.02              Driver Version: 555.42.02      CUDA Version: 12.5     |
|-----------------------------------------+------------------------+----------------------+
| GPU  Name                 Persistence-M | Bus-Id          Disp.A | Volatile Uncorr. ECC |
| Fan  Temp   Perf          Pwr:Usage/Cap |           Memory-Usage | GPU-Util  Compute M. |
|                                         |                        |               MIG M. |
|=========================================+========================+======================|
|   0  NVIDIA GeForce RTX 4080        Off |   00000000:01:00.0  On |                  N/A |
| 30%   26C    P8             12W /  320W |     225MiB /  16376MiB |      0%      Default |
|                                         |                        |                  N/A |
+-----------------------------------------+------------------------+----------------------+

+-----------------------------------------------------------------------------------------+
| Processes:                                                                              |
|  GPU   GI   CI        PID   Type   Process name                              GPU Memory |
|        ID   ID                                                               Usage      |
|=========================================================================================|
|    0   N/A  N/A      3159      G   /usr/libexec/Xorg                              97MiB |
|    0   N/A  N/A     22140      G   ...7de10227491fe7420e399875a4ffe4fa5ff         26MiB |
|    0   N/A  N/A    171331      G   /usr/bin/gnome-shell                           69MiB |
+-----------------------------------------------------------------------------------------+

```

--


## Lab install

- whilst we have CUDA 12.5 in the lab we will install the latest version of PyTorch as this will work with the older version of CUDA 12.4 
- we can install PyTorch using the following command

```
pip3 install torch torchvision torchaudio --index-url https://download.pytorch.org/whl/cu124
```

- we can test by running the following code

```python
import torch
torch.cuda.is_available()
```

--

## Mac Version

- On a mac you can build the mps (metal) version of pytorch as long as you have apple silicon (M1) chip or later
- The instructions are on the pytorch web page https://pytorch.org/get-started/locally/

```python
import torch
torch.backends.mps.is_available()
```

--

## AMD Version

- I don't have access to an AMD GPU but you can follow instructions here if you do have one.
  - https://pytorch.org/blog/pytorch-for-amd-rocm-platform-now-available-as-python-package/
- Once this is done it should work the same as the standard cuda versions. 




---


## Which Device

- We can check which device a tensor is stored on using the `.device` attribute
- If we want to write code to determine what devices we have available we can do the following

```
def get_device() -> torch.device:
    """
    Returns the appropriate device for the current environment.
    """
    if torch.cuda.is_available():
        return torch.device('cuda')
    elif torch.backends.mps.is_available(): # mac metal backend
        return torch.device('mps')
    else:
        return torch.device('cpu')

```