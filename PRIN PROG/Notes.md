# January 24, 2019

## Lecture 2

### Synatax and Semantics

How does a program get read?

characters -> lexer -> tokens -> parser -> data-structure

data-structure known as "intermediate representation"

#

x = 23 + y;

As tokens:

    <VAR, x>
    <ASSIGN>
    <CONST, 23>
    <PLUS>
    <VAR, y>
    <SEMICOLON>

#

### Regular Expressions

    concatenation - ab mean a followed by b
    alternation - a|b mean either a or b
    Kleene star - a* means 0 or more copies of a
    Parentheses - grouping


    (0|1)* - all binary string (including null string)
    (01) - sequences of 01 including null string
    1(0|1)*1 - all binary string starting and ending with 1
    aa* - all strings of a's (excluding null)

    Square bracket notation:
    [a-zA-Z][a-zA-Z0-9]*

#

### Context-free grammar

#### Backus-Naur form (BNF):

non-terminal symbol are similar to verbs/nouns/adverbs, and are placed within angle brackets.

Can we parse "2 + 3"

    expr => expr + expr
         => 2 + expr
         => 2 + 3

How about "10 - 3 - 2"

```
   expr => expr - expr
       => 10 - expr
       => 10 - expr - expr
       => 10 - 3 - expr
       => 10 - 3 - 2
```

#

### Parse Tree

2 + 3

```
           expr
         /  |  \
      expr  +  expr
        |       |
        2       3
```

**10 - (3 - 2)** V.S. **(10 - 3) - 2**

A grammar is ambiguous when, for some example input:

- there is more than one possible parse tree, or
- theres more than one possible derivation (using the same order of expansion)

The following is sufficient to prove ambiguity

```
   expr => expr - expr
        => 10 - expr
        => 10 - expr - expr
        => 10 - 3 - expr
        => 10 - 3 - 2

   expr => expr - expr
        => expr - expr - expr
        => 10 - expr - expr
        => 10 - 3 - expr
        => 10 - 3 - 2
```

#

### Abstract syntax trees (AST)s

Parse trees are _concrete_.

But usually we don't care about the full derivation:

```
Parse Tree:
    stmt
     |
    assn
    /|\
 var = expr
  |   / | \
  x   | + |
    expr expr
      |    |
      23  var
           |
           y
Abstract syntax trees:
   =
  / \
 x   +
    / \
   23  y
```

AST's remove the non-terminal symbols.

Very different languages may have the same AST!

#

### Semantics

If syntactically valid, what does the program mean?

```
Presedent
---------
Consequent
```

#

### Compilers \& Interpreters

Languages can be executed in a couple of ways:

- compiled
- interpreted

# January 29, 2019

## Lecture 3

### Paradigms (What this course is really about)

Paradigms

- Imperative
  - Procedural
  - Object-oriented
- Declarative
  - Functional
  - Logic

#

Real Examples:

- Imperative, procedural: C, Pascal
- Imperative, object-oriented: C++, Java, C#, Python
- Functional: Haskell, OCaml, F#, Scheme
- Logic: Prolog

#

- Imperative (Do this, do that)
- Declarative (I want this, you figure it out)

#

```
           | Static   Dynamic |
           +------------------+
Imperative | C, Java | Python |
Functional | Haskell | Scheme |
```

#

What is imperative programming?

- Program = series of statements that change state
- Assignment used to change values stored in memory

Closely matches execution of underlying hardware.

#

Common features in imperative languages:

- Procedures
- Loops
- Blocks
- Conditional branches
- Unconditional branches

#

C overview

#

### Python

```python
print('Hello World')
```

Python can be run interactively in a read-eval-print loop (REPL)

Python doesn't require a main function, but it's common to use one:

```python
#!/usr/bin/env python3

def main():
   print('Hello World')

if __name__ == '__main__':
   main()
```

#

### Lists and Tuples

Tuple is immutable

### List comprehensionss

### Dictionaries

#

Shallow vs Deep copies

# January 31, 2019

## Lecture 4

First assignment tomorrow-ish

### More Python Features:

- Dynamic typing
- Classes

`__init__` is basically the contructor in python

`self` is equal to this, must be explicity provided to every function in a class

```C
typedef strut Person {
   char* name;
   int age;
} Person;

void growOlder(Person* p) {
   p -> age += 1;
}

// Replacing p with 'this', makes it start to look a lot more like java
void growOlder(Person* this) {
   this -> age += 1;
}

// Python's case
void growOlder(Person* self) {
   self -> age += 1;
}
```

```python
// Note the explicit declaration of self.
class Person:
   def __init__(self, name, age):
      self.name = name
      self.age = age;
      self.occupation = 'unemployed'

   def hello(self ):
      print(self.name + ' says hello')
```

### Namespaces

```python
# A.py
# ------
x = 42
y = 43
z = 44

# B.py
# ------
import A
print(A.x)
```

### Duck Typing

"If it walks like a duck and it quacks like a duck, then it must be a duck"

Obviously must contain the correct attribute (function)

```python
class Duck:
   def fly(self):
      print('Duck Flying')

class Airplane:
   def fly(self):
      print('Airplane Flying')

def lift_off(entity):
   entity.fly()

duck = Duck()
airplane = Airplane()

lift_off(duck)       # prints 'Duck Flying'
lift_off(airplane)   # prints 'Airplane Flying'
```

### Anonymous functions

```python
def dbl(x):
   return x * 2

dbl(10)

dbl = lambda x: x * 2

dbl(10)
```

### Program state

```python
x = 10

def f():
# Must call explicitly
   global x
   x = 20

print(x)
f()
print(x)
```

### Debugging Can Be Tricky

- Var typos are hard to find
- Class typos are also hard to find, because you can add attributes on the fly

### Unit Testing

Built-in unit test library

### Overriding default behavior

```python
class Foo:
   def __init__(self):
      self.x = 10

   def __str__(self):
      return 'This Object has x = ' + str(self.x)

f = foo()
print(f)
```

Python3 classes implicitly extend super classes

```python
class Attrs:
   def __getattribute__(self, a):
      print(f'Getting {a}')
      return object.__getattribute__(self,a)

   def __setattr__(self, k, v):
      print(f'Setting {k} to {v}')
      object.__setattr__(self, k, v)

attr = Attrs()
attr.x = 10
print(attr.x)
```

### Performance

- Python isn't that fast, the way to get around this is to use C for high performance code snippets
- Compile C as a shared library
- ctypes will allow you to load library on runtime

### Interactive Environment

- Jupyter

# February 5, 2019

## Lecture 5

# Feb 7, 2019

## Lecture 6

cat test.txt | python program.py

### Lambda Calculus

Racket (Lisp Variant)

Lambda Calculus is Aligators

- variables
- functions (abstractions)
- applications

#### Functions (Abstractions)

f(x) = x + 5 (named func.)
x -> x + 5 (anon. func.)

#

We apply functions by providing an argument:

(Lambda\*x.x)y

#

- Lambda\*x.x is a function with parameter x and body x.
- Replace every occurance of the parameter in the body with the actual argument(y)
- Replace every x in x with y
- y

#

What does (Lambda\x.yxyzxz)w mean?

- Lamba\*x.yxyzxz is a function with parameter x and body yzyzaz
- Replace every occurance of the parameter in the body with the actual argument (w).
- Replace every x ... (went too fast)

#

# February 8, 2019

## Recitation

- Deterministic FA (DFA)
  - At most one transition for any state/character pair
  - Every transition consumes on input character
- Nondeterministic FA (NFA)

  - For some state/character: more than one transition and / or
  - epsilon moves: transition that does not consume a character
  - NFA accepts a string if ANY sequence of allowed choices ends in an accepting state

#

DFA is no less powerful than an NFA
