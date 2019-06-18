#Structured Programming

Jon Macey

---

##Structured Programming
- Structured programming is an attempt to formalize the process of program development.
- There are several basis for a theorem of structured programming, some of which go back the mid 1940’s such as the following papers :-
- ["Flow Diagrams, Turing Machines and Languages with Only Two Formation Rules"](https://nccastaff.bournemouth.ac.uk/jmacey/PPP/papers/FlowDiagramsBohm.pdf) Bohm and Jacopini (1966)
- [“Flow chart techniques for structured programming”](https://nccastaff.bournemouth.ac.uk/jmacey/PPP/papers/nassi-shneidermandiagrams.pdf) Nassi and Shneiderman 1973

--

##Structured Programming Theorem
- The structured programming theorem states that any [computable function](https://en.wikipedia.org/wiki/Computable_function) may be built from three building blocks :-
  - sequences of operations.
  - selections ( executing one of two operations based on a boolean value).
  - iteration (repetition) repeating an operation until some sentinel value is reached.

--

##Sequence
<image src='images/FlowSequence.png' style='width:20%;height:auto;'></br>
- A sequence is a linear execution of program commands </p>
- The sequence of the two commands A and B makes sure that after entering the sequence A is always followed by B and the exit can only be reached by doing this sequence </p>

--

## Selections
- At it’s simplest selection asks a question and will execute a sequence if the answer to the question is true
- This is know as a monadic selection  <!-- .element: class="popupHoverElement" -->
<div id="two" class="popupBox">(Philosophy / Logic) (Mathematics) Logic Maths (of an operator, predicate, etc.) having only a single argument place  </div>
- It is also possible to execute different sequences depending upon the answer (true / false)
- This is know as a dyadic (2) selection. <!-- .element: class="popupHoverElement" -->
<div id="two" class="popupBox">(Philosophy / Logic) Logic Maths (of a relation, predicate, etc.) relating two terms;  Compare monadic, polyadic </div>

--

## Monadic Selection

<image src='images/monadic.png' style='width:40%;height:auto;'></br>
- Here we check a condition and if true execute A else continue

--

## dyadic Selection

<image src='images/dyadic.png' style='width:40%;height:auto;'></br>
- In this version we execute A if the condition is true else we execute B

--

## multiple selection
<image src='images/multselect.png' style='width:40%;height:auto;'></br>

- Depending upon the programming language there are different methods for doing multiple selection.
- Some of these methods are language constructs, whilst some are the nesting of if / else clauses

--

##iteration (loop execution)

- We can break iteration into 3 different categories
  - iterative (head controlled loop)
  - repetitive (foot controlled loop)
  - continuous (never ending loop)
- We can also use a technique called [recursion](https://en.wikipedia.org/wiki/Recursion) (which we will look at later in the year)

--

## Head controlled loop
<image src='images/headloop.png' style='width:20%;height:auto;'></br>
- This loop structure will check the condition first and then execute the function
- To enter this structure the exit condition must be true in the first place.
- Once this is complete the condition is checked again and repeated until the condition is false
- This is know as a do-while loop

--

## foot controlled loop
<image src='images/footloop.png' style='width:20%;height:auto;'></br>
- This loop structure will check the condition first and then execute the function
- To enter this structure the exit condition must be true in the first place.
- Once this is complete the condition is checked again and repeated until the condition is false
- This is know as a do-while loop

--

##continuous loop
<image src='images/conloop.png' style='width:20%;height:auto;'></br>
- A continuous loop has an entrance but no exit condition or check.
- These kinds of loops can be useful for systems that need to run forever without interruption (embedded systems)
- However they may also be problematic and can be caused by bugs in code.

--


##continuous with exit(s)
- It is possible to construct loops with multiple exit conditions
- Whilst these are common, there are sometimes issues with maintenance / debugging using these constructs.

--

##Structured Programming

- We will return to these constructs soon, and see how we can build them in different programming languages.
- But first we are going to introduce notational technique to help describe the syntax of programming languages.
- This will aid us in explaining the programming constructs in a more formal way before jumping into specific programming language syntax

---

##BNF (Backus–Naur Form)
- In the 1950’s both [John Backus](https://en.wikipedia.org/wiki/John_Backus) and [Noam Chomsky](https://en.wikipedia.org/wiki/Noam_Chomsky) invented the same notation which has become widely used to describe programming language syntax.
- [Chomsky](https://chomsky.info/) is a linguist and never intended to apply this work to computers
- Backus however was involved in the specification for a programming language called [ALGO](https://en.wikipedia.org/wiki/ALGO) and used this context free grammar to describe syntax which he called [BNF](https://en.wikipedia.org/wiki/Backus%E2%80%93Naur_Form). 
- It was only later that the connection between the two systems were made

--

##Meta-languages
- A meta-language is a language to describe another language. 
- BNF uses abstractions for syntactic structures.
- A BNF is a set of rules written like this 
``` 
<symbol> ::= __expression__ 
```
- symbol is a syntactic variable (or non-terminal) meaning a variable that can be replaced
- The expression is what the symbol is representing and is usually a finite combination of other symbols

--

## alternatives
- In BNF alternatives may be separated by the vertical bar
```bash
<digit>:== "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
```
- In this case we state that a digit can be any of the numbers 0 through 9

--

##(E)xtended- BNF
- E-BNF has a different syntax from the previous BNF, notation but has a number of advantages of basic BNF.

###BNF
```bash
<digit>:== "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
```
###E-BNF
```bash
digit excluding zero =  "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9";
digit = "0" | digit excluding zero;
```
- Note the use of the ; in this version and the lack of < >

--

##E-BNF , rule
- A comma indicates a concatenation for example
```bash
eleven = "1","1";
one hundred and eleven = eleven,"1";
```
- or perhaps
```bash
eleven = "1","1";
one hundred and eleven = "1",eleven;
```

--

## E-BNF {}
- Expressions that may be omitted or repeated can be represented through curly braces

```bash
digit excluding zero =  "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9";
digit = "0" | digit excluding zero;

natural number = digit excluding zero, {digit};
```

--

## <small/>[More E-BNF](https://en.wikipedia.org/wiki/Extended_Backus%E2%80%93Naur_Form)
| Usage          | Notation        |                 
|----------------|-----------------|
| definition     | ```=```         |
| concatenation  | ```,```         |
| termination    | ```;```         |
| alternation    | ``` :```        |
| option         | ```[...]```     |
| repetition     | ```{....}```    |
| grouping       | ```()```        |
| terminal string| ```“.....”```   |
| comment        | ```(*......*)```|
| exception      | ```-```         |

---

##[Integers](https://en.wikipedia.org/wiki/Integer)
- In computing the integer data type is used to represent the whole numbers (including zero)
- We can further refine the definition by stating if they are signed or unsigned

```bash
digit excluding zero =  "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9";
digit = "0" | digit excluding zero;

unsigned integer=digit, { digit};
signed integer = unsigned integer   | + unsigned integer  | - unsigned integer
```

--

## variable declarations in C
- In C we can declare variables ([identifiers](http://en.cppreference.com/w/c/language/identifier#Reserved_identifiers)) using the syntax

```bash
<variable type> <variable identifier>;
<variable type> <var1>,<var2> ... <var n>;
```
- Where variable type indicates one of the C data types 
- identifier is a valid name for a variable 

--

## [valid variable names]()

- The following rules must be applied to C variable names
- must not begin with a number
- spaces are not allowed in names
- Only letters digits and _ are valid characters
- C keywords are not allowed 

```bash
digit = "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9";

letter = "a"|"b"|"c"|"d"|"e"|"f"|"g"|"h"|"i"|"j"|"k"|"l"|"m"|"n"|"o"|"p"|"q"|"r"|"s"|"t"|"u"|"v"|"w"|"x"|"y"|"z"|
         "A"|"B"|"C"|"D"|"E"|"F"|"G"|"H"|"I"|"J"|"K"|"L"|"M"|"N"|"O"|"P"|"Q"|"R"|"S"|"T"|"U"|"V"|"W"|"X"|"Y"|"Z";
         

start char = "letter" | "_";

variable name = start char , {digit} | {start char};
```


[full C BNF](https://cs.wmich.edu/~gupta/teaching/cs4850/sumII06/The%20syntax%20of%20C%20in%20Backus-Naur%20form.htm)

--

## C reserved words
<table class="wikitable">

<tr>
<td>
<p><a href="http://en.cppreference.com/w/c/keyword/auto" title="c/keyword/auto"><code>auto</code></a><br />
<a href="http://en.cppreference.com/w/c/keyword/break" title="c/keyword/break"><code>break</code></a><br />
<a href="http://en.cppreference.com/w/c/keyword/case" title="c/keyword/case"><code>case</code></a><br />
<a href="http://en.cppreference.com/w/c/keyword/char" title="c/keyword/char"><code>char</code></a><br />
<a href="http://en.cppreference.com/w/c/keyword/const" title="c/keyword/const"><code>const</code></a><br />
<a href="http://en.cppreference.com/w/c/keyword/continue" title="c/keyword/continue"><code>continue</code></a><br />
<a href="http://en.cppreference.com/w/c/keyword/default" title="c/keyword/default"><code>default</code></a><br />
<a href="http://en.cppreference.com/w/c/keyword/do" title="c/keyword/do"><code>do</code></a><br />
<a href="http://en.cppreference.com/w/c/keyword/double" title="c/keyword/double"><code>double</code></a><br />
<a href="http://en.cppreference.com/w/c/keyword/else" title="c/keyword/else"><code>else</code></a><br />
<a href="http://en.cppreference.com/w/c/keyword/enum" title="c/keyword/enum"><code>enum</code></a><br />
<a href="http://en.cppreference.com/w/c/keyword/extern" title="c/keyword/extern"><code>extern</code></a>
</p>
</td>
<td>
<p><a href="http://en.cppreference.com/w/c/keyword/float" title="c/keyword/float"><code>float</code></a><br />
<a href="http://en.cppreference.com/w/c/keyword/for" title="c/keyword/for"><code>for</code></a><br />
<a href="http://en.cppreference.com/w/c/keyword/goto" title="c/keyword/goto"><code>goto</code></a><br />
<a href="http://en.cppreference.com/w/c/keyword/if" title="c/keyword/if"><code>if</code></a><br />
<a href="http://en.cppreference.com/w/c/keyword/inline" title="c/keyword/inline"><code>inline</code></a> <span class="t-mark-rev t-since-c99">(since C99)</span><br />
<a href="http://en.cppreference.com/w/c/keyword/int" title="c/keyword/int"><code>int</code></a><br />
<a href="http://en.cppreference.com/w/c/keyword/long" title="c/keyword/long"><code>long</code></a><br />
<a href="http://en.cppreference.com/w/c/keyword/register" title="c/keyword/register"><code>register</code></a><br />
<a href="http://en.cppreference.com/w/c/keyword/restrict" title="c/keyword/restrict"><code>restrict</code></a> <span class="t-mark-rev t-since-c99">(since C99)</span><br />
<a href="http://en.cppreference.com/w/c/keyword/return" title="c/keyword/return"><code>return</code></a><br />
<a href="http://en.cppreference.com/w/c/keyword/short" title="c/keyword/short"><code>short</code></a>
</p>
</td>
<td>
<p><a href="http://en.cppreference.com/w/c/keyword/signed" title="c/keyword/signed"><code>signed</code></a><br />
<a href="http://en.cppreference.com/w/c/keyword/sizeof" title="c/keyword/sizeof"><code>sizeof</code></a><br />
<a href="http://en.cppreference.com/w/c/keyword/static" title="c/keyword/static"><code>static</code></a><br />
<a href="http://en.cppreference.com/w/c/keyword/struct" title="c/keyword/struct"><code>struct</code></a><br />
<a href="http://en.cppreference.com/w/c/keyword/switch" title="c/keyword/switch"><code>switch</code></a><br />
<a href="http://en.cppreference.com/w/c/keyword/typedef" title="c/keyword/typedef"><code>typedef</code></a><br />
<a href="http://en.cppreference.com/w/c/keyword/union" title="c/keyword/union"><code>union</code></a><br />
<a href="http://en.cppreference.com/w/c/keyword/unsigned" title="c/keyword/unsigned"><code>unsigned</code></a><br />
<a href="http://en.cppreference.com/w/c/keyword/void" title="c/keyword/void"><code>void</code></a><br />
<a href="http://en.cppreference.com/w/c/keyword/volatile" title="c/keyword/volatile"><code>volatile</code></a><br />
<a href="http://en.cppreference.com/w/c/keyword/while" title="c/keyword/while"><code>while</code></a>
</p>
</td>
</tr></table>

--

##integer data type

- In C / C++ we can specify an integer using the int keyword.
- The range of an integer is dependant upon the machine architecture but is usually a whole 16, 32 or 64-bit (2, 4 or 8 bytes, respectively) addressable word.
- By default the int data type is signed (can be positive or negative)
- Typical range is −2147483648 to +2147483647

--

##[example](https://github.com/NCCA/PPPLectureCode/blob/master/Lecture2/integer.c)

```c
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int a=10;
	int b=20;
	printf("a+b = %d \n",a+b);

	 unsigned int aBigNumber = 4294967295;
	int one= 2;

	printf("aBigNumber+one = %d \n",aBigNumber+one);


	return EXIT_SUCCESS;
}

```

--

## [ordinal data types](https://en.wikipedia.org/wiki/Ordinal_data_type)

- The ordinal data types in C can be either signed or unsigned. 
- C gives the programmer the following ordinal data types
- char, short int, long int
- each can be pre-fixed with the keyword unsigned

--

## ordinal data types

| Type            | Description                                                    |
|-----------------|----------------------------------------------------------------|
| ```char```      | Small data type only needs 1 byte / 8 bits of memory to store. |
| ```short int``` | Integer data type half the size of an integer |
| ```int```       | Integer data type, size dependent upon platform using it |
| ```long int```  |	Integer data type twice the size of the int data type |

--

## [sizeof()](https://en.wikipedia.org/wiki/Sizeof)
- In C/C++ sizeof is a unary operator that must be implemented by the developer of the compiler
- it appears as a C/C++ function when we use it but will return the size in bytes of the data type passed to it.
- The following program demonstrates sizeof

--


## [sizeof.c](https://github.com/NCCA/PPPLectureCode/blob/master/Lecture2/sizeof.c)
```c
#include <stdio.h>
#include <stdlib.h>

int main()
{
  printf("sizeof(char)= %ld \n",sizeof(char));
  printf("sizeof(short int)= %ld \n",sizeof(short int));
  printf("sizeof(int)= %ld \n",sizeof(int));
  printf("sizeof(long int)= %ld \n",sizeof(long int));
  printf("sizeof(float)= %ld \n",sizeof(float));
  printf("sizeof(double)= %ld \n",sizeof(double));

  printf("unsigned versions\n");

  printf("sizeof(unsigned char)= %ld \n",sizeof(unsigned char));
  printf("sizeof(unsigned short int)= %ld \n",sizeof(unsigned short int));
  printf("sizeof(unsigned int)= %ld \n",sizeof(unsigned int));
  printf("sizeof(unsigned long int)= %ld \n",sizeof(unsigned long int));

  return EXIT_SUCCESS;
}
```

--

## output 

```
$ clang -Wall -g sizeof.c -o sizeof
$./sizeof
sizeof(char)= 1
sizeof(short int)= 2
sizeof(int)= 4
sizeof(long int)= 8
sizeof(float)= 4
sizeof(double)= 8
unsigned versions
sizeof(unsigned char)= 1
sizeof(unsigned short int)= 2
sizeof(unsigned int)= 4
sizeof(unsigned long int)= 8
```

--

##[char](http://en.cppreference.com/w/c/language/arithmetic_types#Character_types)


- The char data type is useful for representing ASCII characters
- It usually takes up 1 byte and can represent either 0 to +255 (unsigned) or -128 to +128 (signed)
- Whilst this is used to store numeric values we can use the convenience single quote method to assign a char from a character as shown in the next program

--

## [Example](https://github.com/NCCA/PPPLectureCode/blob/master/Lecture2/char.c)
```c
#include <stdio.h>
#include <stdlib.h>

int main()
{
	char a='a';
	printf("%c \n",a);
	a=65; 
	printf("%c \n",a);
  for( unsigned char c=0; c<255; ++c)
  {
    printf("%c",c);
	}
  return EXIT_SUCCESS;
}
```

```
$clang -Wall -g char.c -o char
$./char
a
A



 !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~�������������������������������������������������������������������������������������������������������������������������������
```

--


## [ASCII](https://en.wikipedia.org/wiki/ASCII)

<image src='images/ASCII_Code_Chart.svg' style='width:100%;height:auto;'></br>

### [source](http://upload.wikimedia.org/wikipedia/commons/4/4f/ASCII_Code_Chart.svg)


--

## unsigned bytes

<div class="stretch">
<iframe src="bytes.html" style="border:0px #FFFFFF solid;" name="code" scrolling="yes" frameborder="1" marginheight="0px" marginwidth="0px" height="100%" width="100%"></iframe>
</div>

--

## signed bytes

<div class="stretch">
<iframe src="signedbyte.html" style="border:0px #FFFFFF solid;" name="code" scrolling="yes" frameborder="1" marginheight="0px" marginwidth="0px" height="100%" width="100%"></iframe>
</div>

--

##real numbers

- In computing we use floating point data types to represent real numbers (numbers with a fractional part)
- These numbers are always approximations as we have to move the decimal.
- Numbers are, in general, represented approximately to a fixed number of significant digits  and scaled using an exponent.
$$ \text{Significant digits} \times base^{exponent} $$

--

##real numbers in C

- C has two real data types float and double
- the long prefix may be used with double to increase the precision

<image src='images/floats.png' style='width:100%;height:auto;'></br>

--

## [example](https://github.com/NCCA/PPPLectureCode/blob/master/Lecture2/float.c)

```c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{

	float a=2.5f;
	double b=0.0000034;
	long double c=123213213.343433434320;
  
	printf("%f \n",a);
	printf("%.8lf \n",b);
	printf("%Lf \n",c);
  

	return EXIT_SUCCESS;
}
```

```bash
$clang -g -Wall float.c -o float
$./float
2.500000
0.00000340
123213213.343433
```

---

## Arithmetic operations
- Most programs are algorithmic in nature which means we have to do some maths
- The table below shows the available arithmetic operators
<image src='images/arithmetic.png' style='width:80%;height:auto;'></br>

--

##The / Operator
- When applied to two positive integers the division operator computes the integral part of the result dividing its first operand by its second
- For example
```c
7.0 / 2.0;      // is 3.5 
7 / 2;          // is 3
299.0 / 100.0;  // is 2.99 (double value)
299 / 100;      // is 2  (integer value)
```

- If the / Operator is used with a negative and positive integer, the results vary from one C implementation to another
- For this reason you should avoid division by -ve integers

--

## [More on /](https://github.com/NCCA/PPPLectureCode/blob/master/Lecture2/divByZero.c)
- It is also important not to do division by 0 as the program may crash, some modern compilers will try to warn of this.
- see the following
  - [http://mathworld.wolfram.com/DivisionbyZero.html](http://mathworld.wolfram.com/DivisionbyZero.html)
  - [https://www.khanacademy.org/math/algebra/introduction-to-algebra/division-by-zero/v/why-dividing-by-zero-is-undefined](https://www.khanacademy.org/math/algebra/introduction-to-algebra/division-by-zero/v/why-dividing-by-zero-is-undefined)
  - [https://en.wikipedia.org/wiki/Division_by_zero](https://en.wikipedia.org/wiki/Division_by_zero)

--

## [More on /](https://github.com/NCCA/PPPLectureCode/blob/master/Lecture2/divByZero.c)

```
#include <stdio.h>
#include <stdlib.h>

int main()
{
  printf("3/15 %d\n",3/15);
  printf("15/3 %d\n",15/3);
  printf("16/3 %d\n",16/3);
  printf("17/3 %d\n",17/3);
  printf("18/3 %d\n",18/3);
  printf("16/-3 %d\n",16/-3);
  printf("4/0 %d\n",4/0);

  printf("0/4 %d\n",0/4);

  return EXIT_SUCCESS;
}
```

```
$clang -g -Wall divByZero.c -odiv
divByZero.c:12:22: warning: division by zero is undefined [-Wdivision-by-zero]
  printf("4/0 %d\n",4/0);
                     ^~
1 warning generated.
$./div
3/15 0
15/3 5
16/3 5
17/3 5
18/3 6
16/-3 -5
4/0 73832
0/4 0
```

--

## The % (modulus) Operator
- The remainder operator (%) returns the integer remainder of the result of dividing the first operand with the second
- For example the value of ```7 % 2 is 1 ```
- The magnitude of m % n must always be lest than the division n

<image src='images/mod.png' style='width:70%;height:auto;'></br>

--

## [example](https://github.com/NCCA/PPPLectureCode/blob/master/Lecture2/modulus.c)

```c 
#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("3 %% 5=%d\n",3%5);
	printf("5 %% 3=%d\n",5%3);
	printf("4 %% 5=%d\n",4%5);
	printf("5 %% 4=%d\n",5%4);
	printf("5 %% 5=%d\n",5%5);
	printf("15 %% 5=%d\n",15%5);
	printf("6 %% 5=%d\n",6%5);
	printf("15 %% 6=%d\n",15%6);
	printf("7 %% 5=%d\n",7%5);
	printf("15 %% -7=%d\n",15%-7);
	printf("8 %% 5=%d\n",8%5);
	printf("15 %% 0=%d\n",15%0);

	return EXIT_SUCCESS;
}
```

```
$clang -g -Wall modulus.c -o modulus
modulus.c:17:26: warning: remainder by zero is undefined [-Wdivision-by-zero]
        printf("15 %% 0=%d\n",15%0);
                                ^~
1 warning generated.
$./modulus
3 % 5=3
5 % 3=2
4 % 5=4
5 % 4=1
5 % 5=0
15 % 5=0
6 % 5=1
15 % 6=3
7 % 5=2
15 % -7=1
8 % 5=3
15 % 0=73832
```

--

## Data type of an expression
- There are certain rules to define the results of mixing data types
- For example
```c
int a=10;
int b=10;
int c;
c=a+b; //will result in an integer value
```

- However if we mix the types we will get different results depending upon the receiving variables data type

```
double x;
int n;
x=9*0.5; // will result in x=4.5
n=9*0.5; // will result in n=4
```

--

## [Expressions with Multiple Operators](https://en.wikipedia.org/wiki/Order_of_operations)
- There are rules as to how expressions are evaluated
- Parentheses Rule 
  - All expressions in parentheses must be evaluated separately. 
  - Nested parenthesised expressions must be evaluated from the inside out, with the innermost expression evaluated first.
- Operator precedence rule : 
  - Operators in the same expression are evaluated in the following order.
```
unary +, -    first
*, /, %       next
binary +,-    last
```

--

## [Expressions with Multiple Operators](https://en.wikipedia.org/wiki/Order_of_operations)
- Associativity Rule : Unary operators in the same sub-expression and at the same precedence levels (such as + and -) are evaluated right to left. 
- Binary operators in the same sub-expression and the same precedence level (such as + and -) are evaluated left to right.
- To help avoid problems with the order of evaluation it is best to use parenthesis

```
x * y * z + a / b -c * d;

can be written

(x * y * z) + (a / b) - (c * d);
```

--

## <small>Mathematical Formulas as C/C++ expressions </small>

|Mathematical Formula    | C Expression      |
|------------------------|-------------------|
| $$  b^2-4ac $$         |  ```(b*b)-4*a*c```|
| $$ a+b-c  $$           |  ``` a+b-c```     |
| $$ \frac{a+b}{c+d} $$  | ```(a+b)/(c+d)``` |
| $$ \frac{1}{1+x^2} $$  | ```1/(1+x*x)```   |
| $$ a \times -(b+c) $$  | ``` a* -(b+c)```  |

--


## Powers
- note that most programming languages don't have the ability to express powers such as $ x^2 $
- in C/C++ we can use ```x*x``` for a square and ```x*x*x``` for a cube.
- there is a generic [ pow function](http://www.cplusplus.com/reference/cmath/pow/) ```a=pow(x,5);``` 
- in python we can also use the ```**``` operator such as ``` a=x**5 ```
- for more maths functions see [``` #include <math.h>```](http://www.cplusplus.com/reference/cmath/)

---


## Further reading
- [http://en.wikipedia.org/wiki/Floating_point](http://en.wikipedia.org/wiki/Floating_point)
- [http://en.wikipedia.org/wiki/C_syntax](http://en.wikipedia.org/wiki/C_syntax)
- [https://en.wikipedia.org/wiki/C_mathematical_functions](https://en.wikipedia.org/wiki/C_mathematical_functions)
- [https://en.wikibooks.org/wiki/C_Programming/Simple_math](https://en.wikibooks.org/wiki/C_Programming/Simple_math)
- [http://www.sanfoundry.com/c-programming-examples-mathematical-functions/](http://www.sanfoundry.com/c-programming-examples-mathematical-functions/)
- [http://hplgit.github.io/primer.html/doc/pub/half/book.pdf](http://hplgit.github.io/primer.html/doc/pub/half/book.pdf)
- [http://numerical.recipes/](http://numerical.recipes/)

--

## References
- Cornelia M. Yoder and Marilyn L. Schrag. 1978. Nassi-Shneiderman charts an alternative to flowcharts for design. SIGSOFT Softw. Eng. Notes 3, 5 (January 1978), 79-86.
- I. Nassi and B. Shneiderman. 1973. Flowchart techniques for structured programming. SIGPLAN Not. 8, 8 (August 1973), 12-26.
- Anderson Eike F.  2002-2005 Computer Programming in ANCI C Lecture notes NCCA
- Sebesta R. W. 2002, Concepts of Programming Languages, 5th edition, Addison Wesley, International Ed

--

## References

- Daniel D. McCracken and Edwin D. Reilly. 2003. Backus-Naur form (BNF). In Encyclopedia of Computer Science (4th ed.), Anthony Ralston, Edwin D. Reilly, and David Hemmendinger (Eds.). John Wiley and Sons Ltd., Chichester, UK 129-131.
- Hanly. J. R Koffman E. B. 1999, Problem Solving & Program Design in C, 3rd Edition, Addison Wesley, International Ed
