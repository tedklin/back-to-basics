# Dynamic programming / memoization

[//]: # (reference-style links)
[01_recursion.md]: https://github.com/tedklin/back-to-basics/tree/master/01_algorithms/00_preliminaries/01_recursion.md


## Fundamental approach

**Before continuing, review [01_recursion.md](../../00_preliminaries/01_recursion.md) for precise terminology definitions and context.**

Dynamic programming / memoization is a very general **optimization** (i.e. finding max/min) and **counting** (e.g. Nth Fibonacci) technique for discrete problems. It boils down to **efficiently enumerating** a large potential search space to find the (optimal) solution-value.

- Memoization ("top-down"):
    - Main idea: Augment a recursive algorithm with a lookup-table / cache for already-solved subproblems, so we don't do any repeated work.
        - Memoization (and, by extension, dynamic programming) helps the subset of recursive algorithms where if we didn't memoize, subproblems would be repeatedly queried a significant number of times (e.g. the full recursive call tree would have an exponential number of calls, as seen in [DPV Ch6 p173](https://people.eecs.berkeley.edu/~vazirani/algorithms/chap6.pdf)).
            - Memoization generally doesn't help on a divide-and-conquer algorithm like Mergesort since subproblems aren't repeated.
    - Compared to dynamic programming, memoization can *sometimes* be more efficient because "dynamic programming solves every subproblem that could conceivably be needed, while memoization only ends up solving the ones that are actually used" ([DPV p183](https://people.eecs.berkeley.edu/~vazirani/algorithms/chap6.pdf)).

- Dynamic programming ("bottom-up"):
    - Main idea: *Iteratively* solve subproblems in an ordering such that by the time we consider the current subproblem, we already have the solution-values of the (smaller/simpler) subproblems that the current (bigger) subproblem directly depends on.
        - i.e. solve subproblems in a topological ordering of the underlying *subproblem DAG* (as defined in [01_recursion.md](../../00_preliminaries/01_recursion.md)).
    - Compared to memoization, dynamic programming can often be more space-efficient because we are allowed to *forget* the parts of history that are no longer relevant. At any given step, we only need to keep the solution-values of past subproblems that at least one current/future subproblem **directly** depends on. Once a past subproblem is no longer **directly** depended-on by any current/future subproblem, we are allowed to forget that past subproblem's solution-value.
        - e.g. in the context of computing Fibonacci numbers:
            - The subproblem `fibonacci(i)` **directly** depends on the solution-values of the subproblems `fibonacci(i-1)` and `fibonacci(i-2)`.
            - To solve `fibonacci(N)`, we iteratively solve `fibonacci(i)` in a bottom-up ordering `i=0,1,...,N-1,N`. For any value of i, the solution-value of `fibonacci(i-2)` (and the solution-value of any prior subproblem `fibonacci(anything < i-2)`) isn't directly needed for any future subproblem `fibonacci(anything > i)`. So once we finish using the solution-value of `fibonacci(i-2)` to solve `fibonacci(i)`, we are allowed to "forget" the solution-value of `fibonacci(i-2)`.
                - This means that at any given step of solving `fibonacci(N)`, we only need to store 2 subproblem solution-values instead of O(N).

**Often the most difficult part of designing a memoized / dynamic programming algorithm is finding the underlying recursive structure. This is covered in [01_recursion.md](../../00_preliminaries/01_recursion.md).**

- References:
    - [Jelani Nelson's Sp20 CS170 lectures](https://youtu.be/a7qNN-OQ2zs?t=2744)
    - [DPV Ch6](https://people.eecs.berkeley.edu/~vazirani/algorithms/chap6.pdf)


### TODO

- https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm
