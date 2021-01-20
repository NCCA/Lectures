# Lecture 2 
## Control Structures in Python

<p/>Jon Macey <br/>

<p/>jmacey@bournemouth.ac.uk

---

## What are control Structures?

- Most programming tasks can be split into a combination of the following elements
  - Sequences
  - Selection
  - Iteration
- Whenever I learn a new language I see how these are represented syntactically as this makes learning the language easier.

--

## Sequences

- As the name suggest a sequence is a fixed set of instructions 
- They are always carried out in the same order
- With the use of functions we can bundle other sequences together to make programs easier to read / maintain
- The following example shows this in action

--

## Sequences

<iframe src="https://trinket.io/embed/python/d986b1a5fb" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>

--

## Let's make this more visual

- Python has a module called "Turtle" which allows for simple 2D drawing

> Turtle graphics is a popular way for introducing programming to kids. It was part of the original Logo programming language developed by Wally Feurzeig, Seymour Papert and Cynthia Solomon in 1967.

- I learnt a lot of programming from this.

--

## Let's make this more visual

> Imagine a robotic turtle starting at (0, 0) in the x-y plane. After an import turtle, give it the command turtle.forward(15), and it moves (on-screen!) 15 pixels in the direction it is facing, drawing a line as it moves. Give it the command turtle.right(25), and it rotates in-place 25 degrees clockwise.


--

## A Sequence

<iframe src="https://trinket.io/embed/python/d7e9c4e7f7" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>

--

## Two Squares

<iframe src="https://trinket.io/embed/python/b67ab452a3" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>

--

## Problems

- There is a lot of repeated code
- It is hard to read and maintainability is low
- This is where [functions](https://www.w3schools.com/python/python_functions.asp) come into play


---

## Functions in Python

- A function is a block of code which only runs when it is called.
- You can pass data, known as parameters, into a function.
- A function can return data as a result.

--

##  ```def```

- The ```def``` keyword is used to define a function or method of a class.

```
def <function>(<params>):
    <body>
```

--

|Component	 | Meaning |
|------------|---------|
|```def```	| The keyword that informs Python that a function is being defined |
| ```<function_name>``` |	A valid Python identifier that names the function |
| ```<parameters>``` |	An optional, comma-separated list of parameters that may be passed to the function |
| ```:``` |	Punctuation that denotes the end of the Python function header (the name and parameter list) |
| ```<statement(s)>``` |	A block of valid Python statements |

--

## [indentation](https://www.python.org/dev/peps/pep-0008/)

- Python uses indentation to block code 
  - convention states we use 4 spaces for indentation (see PEP-8)
- This is unusual as most programming languages use {}
- This can lead to problem, especially when mixing tabs and spaces (python 3 doesn't allow this)
- I will show different examples of this as we go 
- usually this will follow a statement and the ```:``` operator to indicate the start of the block

--


## A simple [Function](https://realpython.com/defining-your-own-python-function/)

<iframe src="https://trinket.io/embed/python/0da890d686" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>

--

### What happens when I use a function?
<iframe width="800" height="500" frameborder="0" src="http://pythontutor.com/iframe-embed.html#code=def%20add%28a,b%29%20%3A%0A%20%20%20%20return%20a%2Bb%0A%0Ax%3D1%0Ay%3D2%0Aresult%3Dadd%28x,y%29%0Ax%3D%22hello%22%0Ay%3D%22world%22%0Aresult%3Dadd%28x,y%29%0A&codeDivHeight=400&codeDivWidth=350&cumulative=false&curInstr=0&heapPrimitives=nevernest&origin=opt-frontend.js&py=3&rawInputLstJSON=%5B%5D&textReferences=false"> </iframe>

--

## Functions in practice 

- A function needs to be declared before it is called
- These can be placed externally (in another file / module)
- Usually a function will have parameters and it can also return values

--

## Let's design a function

- In one of the earlier examples we used the turtle to draw two squares
- This is idea for a function so we can design one but what do we need?
  - a [name](https://en.wikipedia.org/wiki/Naming_convention_%28programming%29 )
  - useful parameters (and perhaps useful defaults)
  - possible return values

--

## How do we specify a Square?

- There are many ways to do this
  1. Top (x,y) Bottom (x,y)
  2. Start Pos (x,y) Width Height
  3. Center (x,y) Width / Height

- Which one to choose is a matter of design (the hard part)
- Pays to be consistent with other functions
- What other parameters could be add?

--

## Square Example 1

<iframe src="https://trinket.io/embed/python/35051ca01d" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>


--

## Not quite Rothko

<iframe src="https://trinket.io/embed/python/e921ea00c2" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>



--

## Is that all for Functions?

- There is a lot more to discuss
- We will look in more depth at other features as we progress
- for now we will continue with some more programming constructs

---

## Selection

- selections allow us to make choices
- most programming languages have at least the if else construct
  - some languages have more (switch case )
- The result of an if operation is a boolean (true / false) value and code is executed or not depending upon these value
- In python we use the following constructs


--


## simple if statement

<iframe src="https://trinket.io/embed/python/39713d2c94" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>


--

## Python Comparison Operators
<small>given ```a=10 b=20```</small>

| <small>Operators    </small>              | <small>Description               </small>                                                                 | <small>Example  </small>          |
|----------------------------|--------------------------------------------------------------------------------------------|--------------------|
| <small>```==```    </small>                | <small>equality operator returns true if values are the same </small>                                     | <small>(a==b) is not true  </small>|
| <small>```!=```  </small>                  | <small>not equal operator             </small>                                                            | <small>(a!=b) is true   </small>   |
| <small>```>```    </small>                 | <small>Checks if the value of left operand is greater than the value of right operand  </small>           |  <small>(a>b) is not true  </small> |
| <small>```<```    </small>                 |  <small>Checks if the value of left operand is less than the value of right operand   </small>              |  <small>(a>b) is true     </small>  |
| <small>```>=```    </small>                |  <small>Checks if the value of left operand is greater than or equal to the value of right operand  </small>| <small> (a>=b) is not true </small> |
| <small>```<=```    </small>                |  <small>Checks if the value of left operand is less than or equal to the value of right operand   </small>  | <small> (a<=) is true   </small>    |

--

<iframe src="https://trinket.io/embed/python/e2c242a4d7" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>

--


## Python Logical Operators

<small>given ```a=true b=False```</small>

| <small>Operators    </small>              | <small>Description               </small>                                                                 | <small>Example  </small>          |
|----------------------------|--------------------------------------------------------------------------------------------|--------------------|
| <small>```and```    </small>                | <small>Logical and </small>                                     | <small>a and b is False  </small>|
| <small>```or```  </small>                  | <small>Logical or             </small>                                                            | <small>a or b is True   </small>   |
| <small>```not```   </small>| <small>Logical not   </small>                                    | <small>not (a and b) is True  </small>   |

--

<iframe src="https://trinket.io/embed/python/e2d9dfb5e6" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>

--



## [and gates](https://en.wikipedia.org/wiki/AND_gate)

<div class="stretch">
<iframe src="../and.html" style="border:0px #FFFFFF solid;" name="code" scrolling="yes" frameborder="1" marginheight="0px" marginwidth="0px" height="100%" width="100%"></iframe>
</div>

<p/><small/>simcirjs from https://kazuhikoarase.github.io/simcirjs/

--

## [or gates](https://en.wikipedia.org/wiki/OR_gate)

<div class="stretch">
<iframe src="../or.html" style="border:0px #FFFFFF solid;" name="code" scrolling="yes" frameborder="1" marginheight="0px" marginwidth="0px" height="100%" width="100%"></iframe>
</div>

<p/><small/>simcirjs from https://kazuhikoarase.github.io/simcirjs/


--

# [not gate (invertor)](https://en.wikipedia.org/wiki/Inverter_(logic_gate)

<div class="stretch">
<iframe src="../not.html" style="border:0px #FFFFFF solid;" name="code" scrolling="yes" frameborder="1" marginheight="0px" marginwidth="0px" height="100%" width="100%"></iframe>
</div>
 
<p/><small/>simcirjs from https://kazuhikoarase.github.io/simcirjs/

--

## Selection

- selections can be embedded to create quite complex hierarchies of “questions”
- This can sometimes make reading code and maintenance hard especially with the python white space rules as code quite quickly becomes complex to read
- We usually prefer to put complex sequences in functions to make the code easier to read / maintain
- can also be simplified using set operators such as ```in```

---


## iteration

- iteration is the ability to repeat sections of code 
- python has two main looping constructs 
  - for each
  - while
- for-each loops operate on ranges of data 
- while loops repeat while a condition is met

--

## [for](https://docs.python.org/3/tutorial/controlflow.html#for-statements)

- A for loop is used for iterating over a sequence 
  - list, tuple, dictionary, set, string
- The iteration is always in the order that they appear in the sequence

--

## example

<iframe src="https://trinket.io/embed/python/ad7b258486" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>


--

## [```range```](https://docs.python.org/3/tutorial/controlflow.html#the-range-function)

- ```for``` loops are quite often used in conjunction with the ```range``` function
- we use range to generate a sequence and the for runs through each element of the range

```
range(start,stop,step)
```

- By default an integer range value is returned

--

## [```break```](https://docs.python.org/3/tutorial/controlflow.html#break-and-continue-statements-and-else-clauses-on-loops)

- The ```break``` clause allows us to jump out of a loop
- It is usually used in conjunction with an if statement

<iframe src="https://trinket.io/embed/python/f6d47d3f6d" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>


--

## [```continue```](https://docs.python.org/3/tutorial/controlflow.html#break-and-continue-statements-and-else-clauses-on-loops)

- continue will stop the current loop and jump to the next item

<iframe src="https://trinket.io/embed/python/98eff37dc4" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>


--

##  [```-```]()
- ```_``` can be used as a general purpose "throwaway" variable name

<iframe src="https://trinket.io/embed/python/9be5ad2635" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>


--

## for an dictionaries

- the dictionary ```items()``` method returns the key and the value, we could use just ```keys()``` or ```values()```

<iframe src="https://trinket.io/embed/python/635c786486" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>

---

## the [```while```]() statement

-  the while loop executes a set of statements as long as a condition is ```True``` 

<iframe src="https://trinket.io/embed/python/4ecccf600a" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>


--

## input validation

- while is useful for input validation 

<iframe src="https://trinket.io/embed/python/45117bc136" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>


--

## looping for x and y

- This example shows how we can loop from -10 in the x and y in increments of 0.5
- In C / C++ we would use a for loop
```c++
for(float y=-10.0f; y<10.0f; ++y)
{
    for(float x=-10.0f; x<10.0f; ++x)
    {
      std::cout<<x<<' '<<y<<'\n';
    }
}
```

--

## float loop

<iframe src="https://trinket.io/embed/python/a33d95720c" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>


--

## Generating values 

- it is quite common to generate values within a list constructor 

<iframe src="https://trinket.io/embed/python/3a23dd86b8" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>


--

## using [numpy](https://numpy.org/) for float values

- range only give integer values, we can get float values using the [```numpy.arange```](https://numpy.org/doc/stable/reference/generated/numpy.arange.html) function

<iframe src="https://trinket.io/embed/python/d84219882a" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>


--

## Recursion

- Recursion occurs when a thing is defined in terms of itself or of its type
- in programming this usually done by defining a function and call the same function within itself
- obviously we will need some way of escaping this else it will go on forever
- We use this quite a lot in graphics to traverse hierarchies.  

--

## Recursion 

<iframe src="https://trinket.io/embed/python/704181b38f" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>

--

## Recursion 2

<iframe src="https://trinket.io/embed/python/631a6e404a" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>

---

## Generator Functions and ```yield```

<iframe src="https://trinket.io/embed/python/7fe74b873b" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>







