# Explain what O(n), Omega(n), and Theta(n) means.
All are measures of how much an algorithm scales time, memory, comparisons etc with growing input.

These are not exact, because that would not be useful since a program also depends on the programming language, compiler, and hardware.

* O(n)
    - Defines the _upper_ bound of the algorithm, i.e. it can't get worse than that.
    - Also called *Asymptotic complexity*, because of the following definition:
        + O(f(n)) = {g(n) : g(n) <= c * f(n), n > n0} 
        "The function f(n) belongs in the set of functions O, if there exists a function g(n) which is strictly less than some constant c multiplied by f(n), where n is some value in the function, greater than some lower value."
    - This means all functions in the set O(n) belongs in O(n^3) 
* Omega(n)
    - Defines the _lower_ bound of the algorithm, i.e. it can't get better than that.
    - Also an *Asymptotic complexity*, but for the lower bound instead.
        + Omega(f(n)) = {g(n): g(n) * c <= f(n), n > n0}
* Theta(n)
    - When both Omega(n) and O(n) are determined we can find the "exact" time complexity, defined as Theta(n).


# Suppose you gave invented a greedy algorithm that finds an optimal solution to a problem. Explain two approaches to proves its output is really optimal.

There are two common approaches to proving that a greedy algorithm is optimal.
* Proving that the greedy algorithm is always atleast as good as the optimal algorithm,
* Or by transforming the output of the optimal algorithm, without changing its quality, to the output of the greedy algotihm.

These methods are referred to as *staying ahead*, and by an *exchange argument*. In both cases we are not comparing the algorithms, but only their output.

# Explain what is meant by a divide-and-conquer algorithm (söndra-och-härska).

Divide and conquer algorithms are algorithms which split the problem into more easily solved subproblems and then combining the results of the subproblems in (often) linear time to get a result.

# Explain what is meant by dynamic programming (dynamisk programmering)
Dynamic programming is about taking a problem which is expresed as the solution of several smaller subproblems, such as printing the fibonnaci sequence. We cache the intermediate results so that once they have been calculated they can be found in constant time and "bubble up" their results.
In contrast to divide-and-conquer algorithms these problems are dependent on each other, while in divide-and-conquer they are independant.

# Explain what the Master Theorem is about.

The Master Theorem is about finding the complexity of a divide and conquer algorithm. A simplification of The Master Theorem can be applied if and only if the function in its original form is polynomial. ( `f(n) = n^s, s > 0, s is in R)`)
It states the following system of equations:
    * T(1) = 1
    * T(n) = aT(n/b) + n^s
Depending on a, b, and s we get three cases of closed formulas. 
These are the following:

* T(n) = O(n^s), when s > logb(a)
* T(n) = O(n^s * logn), when s = logb(a)
* T(n) = O(n^(logb(a))), when s < logb(a)


# Explain how hollow heaps work. Focus on the simplest version with multiple root nodes.

