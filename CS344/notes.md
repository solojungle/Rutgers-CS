# January 23, 2019

## Lecture 1

Bahman Kalantari

8 lectures until exam,
24 total lectures

Linear Programming
Convex Hall/Set

Polynomial Time Algorithms

Computational Time Geometry

# January 28, 2019

## Lecture 2

cs.rutgers.edu/~kalantar
kalantari@cs.rutgers.edu

Growth of Function Asymptotic Notations

Suppose f,g : N -> R<sub>&ge;0</sub>

f(n) = O(g(n))
(f is big-oh of g)
if there exists a constant c > 0
such that f(n) &le; c\*g(n),
for all n &ge; n<sub>0</sub>, for some number n<sub>0</sub>

examples:

f(n) = n, g(n) = n

- c = 1, n<sub>0</sub> = 1

f(n) = n, g(n) = n/7

- c = 7, n<sub>0</sub> = 1

f(n) = 1000n, g(n) = n<sup>2</sup>

- c = 1000, n<sub>0</sub> = 1

When f(n) = O(g(n))

- f is dominated by g from some point (n<sub>0</sub>) on line

Example:

- f(n) = 5n<sup>4</sup> - 7n<sup>3</sup> + 2n - 1
- g(n) = 1/2 n<sup>5</sup> - 1000n<sup>4</sup> + 7
- f(n) = O(g(n))

Example:

- f(n) = n<sup>k</sup>
- g(n) = 2<sup>n</sup>
- n<sup>k</sup> &le; 2<sup>n</sup>
- Take log<sub>2</sub> of both sides
- k log<sub>2</sub> = n
- k &le; n/log<sub>2</sub>(n)
- Suppose k = 10, If n = 128, log<sub>2</sub>(n) = 7

### Defintion

f(n) = Omega(g(n))
if there exists c > 0, such that
f(n) &ge; c\*g(n), for all n

f(n) = Theta(g(n)), if there exists c<sub>1</sub>, c<sub>2</sub> > 0 such that
c1\*g(n) &le; f(n) &le; c2\*g(n) for all n >= n<sub>0</sub>

f is sandwitched between two positive constant multiples

f(n) = 5n<sup>4</sup>-7n<sup>3</sup>+2n-1
g(n) = n<sup>4</sup>

- f(n) <= 5n<sup>4</sup> + 2n <= 7n<sup>4</sup>
- f(n) >= 4n<sup>4</sup> for some n(0)
- why?
- 4n<sup>4</sup>&le; f(n)&le; 7n<sup>4</sup>
- for all n &ge; n<sub>0</sub>

f(n) = Little Oh(g(n))

if the limit as n approaches infinity is f(n)/g(n) = 0

- Little Oh conveys more information than Big Oh, stronger proof

Two polynomials of the same degree cant be little oh of eachother

- If the limit as n apporaches infinity f(n)/g(n) = c,
- c a constant &ge; 0,
- then f(n) = O(g(n))
- Pf. There exists n<sub>0</sub> such that for all n &ge; n<sub>0</sub>
- |f(n)/g(n)-c| &le; epsilon
- \- epsilon &le; f(n)/g(n) - c &le; epsilon

L'Hopitals Rules

- If the limit as n approaches infinity is f(n) = the limit as n approaches infinity = g(n)

- ln(n) = little oh(n<sup>2</sup>)
- Pf. lim(ln(n)/n<sup>2</sup>) = lim((1/n)/alpha\*n<sup>alpha-1</sup>)
- = lim(1/alpha\*n<sup>alpha</sup>) = 0

Theorem

- n<sup>k</sup> = little oh(2<sup>n</sup>) for any k > 0
- lim(n<sup>k</sup>/2<sup>n</sup>) = ?
- if u(x) = x<sup>k</sup>
- u`(x) = kx<sup>k-1</sup>
- w(x) = 2<sup>x</sup> = e<sup>ln2<sup>x</sup></sup> = e<sup>xln2</sup>
- w`(x) = ln2e<sup>xln2</sup> = ln2\*2
- so lim(n<sup>k</sup>/2<sup>n</sup>) = lim(kn<sup>k-1</sup>/ln2\*2<sup>2</sup>)

### Properties of O, Omega, Theta

1. If f=O(g), g=O(h), f=O(h)
2. f=O(g) iff g=Omega(f)
3. f=Theta(g) iff g=Theta(f)
4. - O(f+g) = O(max{f,g})
   - Omega(f+g) = Omega(max{f,g})
   - Theta(f+g) = Theta(max{f,g})

Floor of n/2 + Ceiling of n/2 = n

### Properties of logs

# January 30, 2019

## Lecture 3

Was 15 mins late.

#

### Probability

- Sample space S = set of all element outcomes of an experiment
- Event = any subset of S
- Probability function = P: S -> Realnumbers such that:

1. P(A) &ge; 0, forall A in S
2. P(S) = 1
3. P(AvB) = P(A) + P(B) if A∧B = null set

#

Random variable X: S -> R

- X=x means {a in S: X(a) = x}
- Probability density function: f<sub>x</sub>(x) = P(X=x)
- Expectation: E(x) = SUM(XP(X=x))

#

### Binary Search

- searching for a key in a sorted list:
- L[1],L[2],...,L[n]
- x = key
- Compare x with middle of list + deleete half of list

#

### Worst case

- W(n) = 1 + W(floor(N/2))
- we take n = 2<sup>k</sup>
- W(2<sup>k</sup>) = 1 + W(2<sup>k-1</sup>)
- = 1 + 1 + W(2<sup>k-2</sup>)
- = k + W(2<sup>k-k</sup>)
- = k + W(1)
- = k + 1
- W(n) = floor(log<sub>n</sub>) + 1

#

### Average case

- Let A(n) be the average number of comparisons of binary seach on a list of n distinct numbers.
  What is A(n)?

#

- Suppose n = 3
- If the key is in the list there are boviously 2 comparisons in the worst case:
- 2 | 1 | 2
- But the key may also not be in the list.

#

- There are actually 4 gaps between all numbers (n = 3)
- 2 (2) 2 (1) 2 (2) 2
- () = actual number in list
- There is 3 + 4 = 7 spots.
- So average is (6x2+1)/7 = 13/7

#

- Now let n = 2<sup>k</sup>-1 for some k
- Worst-case is: W(n) = floor(logn) + 1 = k
- Let S<sub>t</sub> = # of positions that would require t comparisons to determine correct location of key

#

There are n + (n+1) = 2n+1 positions

- S<sub>t</sub> = 2<sup>t-1</sup>
- when t = 1,2,...,k-1
- What is S<sub>k</sub>?
- S<sub>1</sub> + S<sub>2</sub> + ... + S<sub>k-1</sub> + S<sub>k</sub> = 2n+1

- So S<sub>k</sub> = 2n+1 -2<sup>k</sup>

#

### Average

A(n) = SUM(tS<sub>t</sub>)

- A(n) ~= k - 1/2
- k = floor(lg(n))

#

### Lower bound (Optimality):

- Binary search has optimal complexity among all algorithms that use comparison.
- How to prove this?
- A decision tree on n nodes is a binary tree.

#

Image of node tree with depth of 4

#

Lemma: A binary tree on n nodes has depth at least floor(lg(n))

Theorem: Any comparison based algorithm for binary search must do at least floor(lg(n)) + 1 comparisons for some input. (must check a path from root to a leaf)

#

### Recurrence Relations

Example:

```
T(n) = {|Theta(1), n = 1     }
       {|2T(n/2) + Theta(n)  }

       Theta(1) means a constant
T(1) = Theta(1) is called initial condition
```

Why are we interested in asymptotic solutions

- Some methods:
  1. Iteration
  2. Substitution

Ex.

- T(n) = 2T(n/2) + n
- T(1) = 1
- In reality T(n) = T(Floor(n/2)) + T(Ceiling(n/2)) + n

T(n) = 2T(n/2) + n

Iteration: k

- Let n = n^k for some k
- so
- T(n) = T(2^k) = 2T(2^k-1) + 2^k = 2(2T(2^k-2) + 2^k-1) + 2^k =
- 2^2T(2^k-2)+2^k+2^k

- 2^2\*T(2^k-2) + 2\*2^k =
- 2^2(2T(2^k-3) + 2^k-2) + 2\*2^k =
- 2^3T(2^k-3) + 2^k + 2\*2^k =
- 2^3T(2^k-3)+ 3\*2^k =
- 2^kT(2^0) + k\*2^k =
- 2^kT(1) + k\*2^k =
- n + nlog(n)

#

- So T(n) = Big Oh(nlogn)
- Solving by substitution:
- We guess an answer then prove it by induction

-Example:

- T(n) = 2T(n/2) + n
- T(1) = 1
- We claim T(n) &le; c\*nlog(n) for some positive constant c

#

- T(2) = 2T(1) + 2 = 4
- 4 = c2log2 = 2c
- so we pick c = 2
- want to prove T(n) &le; 2nlogn, for all n &ge; 2

Proof:

- T(2) = 4 = 2\*2log(2)
- assume true for all k<n
- T(n) = 2T(n/2) + n &le; 2\*c\*n/2\*ln(n/2) + n = ...
- 2c(n/2)log(n/2)+n =
- c\*n(log(n)-log(2)) + n
- = c\*n\*log(n)-c\*n+n
- = 2\*n\*log(n)-2\*n+n
- &le; 2\*n\*log(n)

# February 4, 2019

## Lecture 4

- T(n) = 2T(n/2) + (n-1), n > 1
- T(1) = 0

Relation that stands for any n greater than 1

- What happens if n is odd
- We should replace with floor or celing to get whole number
- We can assume n is a proper power
- Solve by iteration (assume the right power)

#

Recurrence Relations

How would this differ from previous example?

Let n = 2<sup>k</sup>

- T(2<sup>k</sup>) = 2T(2<sup>k-1</sup>) + 2<sup>k</sup> - 1
- 2(2T(2<sup>k-2</sup>)+2<sup>k-1</sup> - 1) = 2<sup>k</sup> - 1
- I have picture of rest.

- Cleanup and iterate until we find the pattern
- Theta of nlogn-n+1 => nlog(n)

#

Sometimes we can gain by using change of variable

- T(N) = 2T(floor(sqrt(n)))+lg(n)
- Try n = 2<sup>m</sup>
- sqrt(n) = 2<sup>m/2</sup>
- lgn = m
- T(2<sup>m</sup>) = 2T(2\*(m/2)) + m

#

- Suppose we call T(2<sup>m</sup>) to be S(m)
- Then S(m) = 2S(m/2) + m
- But we know S(m) = O(mlogm)
- So T(n) = O(log(n)log(log(n)))

#

### Divide-and-Conquer

    Many algorithms are recursive. They call themselves one or more times and follow a divide-and-conquer approach

    Divide: divide a big problem into smaller ubproblems

    Conquer: Solve the subproblems recursively. If subproblems are small solve in straight forward way

    Combine: combines olution of subproblems into solution for original problem

#

Example: Mergesort

- Divide: into two n/2 element sets
- Conquer: sort teh two subsets recursively using merge sort
- Combine: into sorted list

#

- Merge sort example (You will be asked for exact number of comparisons)
- 5 2 4 6 1 3 2 6
- | 5 2 4 6 | 1 3 2 6 |
- | 5 2 | 4 6 | 1 3 | 2 6 |
- | 2 5 | 4 6 | 1 3 | 2 6 |
- | 2 4 5 6 | 1 2 3 6 |
- | 1 2 2 3 4 5 6 6 |

#

What is the complexity of mergesort?

- Merging two sorted lists of size n/2 takes n-1 comparisons
- So if T(n) = complexity of mergesort then
- T(n) = 2T(n/2) + n - 1
- T(1) = 0, but we solved this!

#

General divide-and-conquer gives rise to recurrence relation:

T(n) = bT(n/c)+t(n)
b: number of subproblems
n/c: size of subproblems

- T(n) = c<sub>0</sub>, a constant when n&le;n<sub>0</sub>
- T(n) = running time on size n
- b = # of subproblems
- n/c = size of subproblems
- t(n) = time for dividing and conquer algorithm

#

Fast multiplication

Let x \* y be two n bit numbers

Take n = 2<sup>k</sup> for some k.

x = 1542, y = 2736
xy = (1500+42)(2700+36)
= 15\*27\*10<sup>4</sup> + (15\*36+42 ... he skipped too fast

#

- x [a | b]
- y [c | d]
- x = 2<sup>n/2</sup>a + b
- x = 2<sup>n/2</sup>c + d
- x \* y = ac \* 2<sup>n</sup> + (ad + bc)2<sup>n/2</sup>+bd
- 4 multiplications of n/2-bit numbers
- 3 additions + shifts

#

### "get ready for some magic"

Let:

- w<sub>1</sub> = a + b
- w<sub>2</sub> = c + d
- u = w<sub>1</sub>w<sub>2</sub> = ac+ad+bc+bd
- v = ac
- w = bd

Then:

- x\*y = 2<sup>n</sup>v + (u-v-w)2<sup>n/2</sup>
- 3 multiplication of n/2-bit
- (n/2+1)-bit numbers (v, w, n)

Let T(n) be the # of operations to, multiply 2 n-bit numbers

- T(n) = 3T(n/2+1)+cn
- T(1) = 1 (how fast can u multiply 2 1-bit numbers, constant time)
- 3T(n/2)+cn

#### How to solve it

Let n = 2<sup>k</sup>
T(2<sup>k</sup>) = 3T(2<sup>k-1</sup>) + c2<sup>k</sup>

- = 3(3T(2<sup>k-2</sup>) + c2<sup>k-1</sup>) + c2<sup>k</sup>
- = 3<sup>2</sup>T(2<sup>k-2</sup>) + c\*3\*2<sup>k-1</sup>+c2<sup>k</sup>
- = 3<sup>3</sup>T(2<sup>k-3</sup>)+c\*3<sup>2</sup>2<sup>k-2</sup>+ ... too fast again

#

T(n) = O(n<sup>1.59</sup>)
= little Oh(n<sup>2</sup>)

#

### Master Theorem

Consider solving:

- T(n) = aT(ceiling(n/b)) + O(n<sup>d</sup>)
- where a>0, b > 1, d > 0
- a = # of subproblems
- n/b = size of subproblems
- T(1) a constant

#

- T(n) = O(n<sup>d</sup>), if d > log<sub>b</sub>a
- T(n) = O(n<sup>d</sup>log(n)), if d = log<sub>b</sub>a
- T(n) = O(n<sup>log<sub>b</sub>a</sup>), if d < log<sub>b</sub>a

So we only need to compare d with log<sub>b</sub>a

T(n) = 4T(n/2) + cn
T(n) = aT (n/b) + n<sup>d</sup>

a = 4
b = 2
d = 1

# February 6, 2019

## Lecture 5

- T(n) = 3T(n/2)+cn
- T(1) = 1, c > 0
- T(n) = O(n<sup>1.59</sup>)

### Master Theorem

- Given a divide-and-conquer
- We only need to compare d with log<sub>b</sub><sup>a</sup>

#

- For given example
- D = 1
- log<sub>2</sub><sup>3</sup>
- Third case

#

All we have to do is figure how to some relation up

#

Master theorem does not solve all cases

- T(n) = 2T(n/2) + nlogn
- T(1) = c, constant
- T(n) = Theta(nlog<sup>2</sup>n)

#

Divide and conquer is not a good technique for solving all recurrence relations:

- Fibonacci Sequence
- This takes exponential time

# Sorting

# February 11, 2019?

# February 13, 2019

Front \& Back Cheat Sheet

Til the last word on monday we will be responsible

#

### Finding Median:

X<sub>1</sub>, X<sub>2</sub>, X<sub>3</sub>, X<sub>4</sub>, X<sub>5</sub>

- Compare(X<sub>1</sub>, X<sub>2</sub>) X<sub>1</sub>\< X<sub>2</sub>
- Compare(X<sub>3</sub>, X<sub>4</sub>) X<sub>3</sub>\< X<sub>4</sub>
- Compare(X<sub>2</sub>, X<sub>4</sub>) X<sub>2</sub>\< X<sub>4</sub>

#

X<sub>4</sub> is larger than 3 indicies so X<sub>4</sub> is out

- Compare(X<sub>2</sub>, X<sub>5</sub>) X<sub>2</sub>\< X<sub>5</sub>
- X<sub>5</sub> is out
- X<sub>1</sub>\<X<sub>2</sub>
- X<sub>1</sub> is out
- Compare(X<sub>2</sub>, X<sub>3</sub>)

#

m\* is the median of medians

```
* * * ... * * *
       .
       .
       .
* * *  m* * * *
       .
       .
       .
* * * ... * * *
```

- S<sub>1</sub>=C Union {all elements in AuD that are < m\*}
- S<sub>2</sub>=B Union {all elements in AuD that are > m\*}

|S<sub>1</sub>|+1=k

#

- nlgn ? 16 n
- lgn = 16
- n = 2^16
- if n is less than 2^16 just sort with nlgn, if larger 16n

#

- W(n) = cn
- 0.9cn
- 1.6n + 0.9cn
- 0.1c = 1.6
- c = 16

#

Try it with groupings of 3 instead of 5

#

### Dynamic Programming

### Matrix Mult.

2n
= (2n)!/(n!n!)
n
