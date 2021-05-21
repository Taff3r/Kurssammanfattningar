# Explain what O(n), Omega(n), and Theta(n) means.
All are measures of how much an algorithm scales time, memory, comparisons etc with growing input.

These are not exact, because that would not be useful since a program also depends on the programming language, compiler, and hardware.
* O(n)
    - Defines the upper bound of the algorithm, i.e. it can't get worse than that.
    - Also called *Asymptotic complexity*, because of the following definition:
        + O(f(n)) = {g(n) : g(n) < c * f(n), n > n0} 
        "The function f(n) belongs in the set of functions O, if there exists a function g(n) which is strictly less than some constant c multiplied by f(n), where n is some value in the function, greater than some lower value."
 

