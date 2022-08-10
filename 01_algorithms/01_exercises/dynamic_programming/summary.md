# Dynamic programming problems

[//]: # (reference-style links)
[Q104]: https://github.com/tedklin/back-to-basics/tree/master/02_pl-usage/java/exercises/src/tree/a_basic/Q104_MaxDepthBinaryTree

## Takeaways

### Fundamental approach

Dynamic programming / memoization is a very general **optimization** (i.e. finding max/min) and **counting** (e.g. Nth fibonacci) technique for discrete problems. It boils down to **efficiently enumerating** a large potential solution space to find the optimal solution.

- Memoization ("top-down"):
    - Main idea: Augment a recursive solution with a lookup-table / cache for already-solved subproblems, so we don't do any repeated work.
        - Memoization (and, by extension, dynamic programming) helps the most for recursion where the same subproblems are repeatedly called a significant number of times / the problem size only shrinks slightly (e.g. by an additive constant) every call. If we didn't memoize this type of recursion, the full recursive execution tree will generally have an exponential number of calls ([DPV Ch6 p173](https://people.eecs.berkeley.edu/~vazirani/algorithms/chap6.pdf)).
            - Memoization generally doesn't help on a divide-and-conquer algorithm like mergesort since subproblems aren't repeated / the problem size shrinks significantly (e.g. by a multiplicative factor) every call.
    - Compared to dynamic programming, memoization can *sometimes* be more efficient because "dynamic programming solves every subproblem that could conceivably be needed, while memoization only ends up solving the ones that are actually used" ([DPV p183](https://people.eecs.berkeley.edu/~vazirani/algorithms/chap6.pdf)).

- Dynamic programming ("bottom-up"):
    - Main idea: Iteratively solve subproblems in an order such that by the time we consider the current subproblem, we already have the solutions to the subproblems that the current subproblem directly depends on.
        - i.e. solve subproblems in reverse topological order of the underlying recursive dependency DAG (where an edge A->B indicates subproblem A directly depends on the solution to subproblem B).
    - Compared to memoization, dynamic programming can often be more space-efficient because we are allowed to forget the parts of history that are no longer relevant. At any given step, we only need to keep the solutions to past subproblems that at least one current/future subproblem **directly** depends on. Once a past subproblem is no longer **directly** depended-on by any current/future subproblem, we are allowed to "forget" that past subproblem's solution.
        - e.g. in the context of computing Fibonacci numbers:
            - The subproblem `fibonacci(i)` **directly** depends on the solutions to the subproblems `fibonacci(i-1)` and `fibonacci(i-2)`.
            - To solve `fibonacci(N)`, we iteratively solve `fibonacci(i)` in a bottom-up ordering `i=0,1,...,N-1,N`. For any value of i, the solution to `fibonacci(i-2)` (and the solution to any prior subproblem `fibonacci(anything < i-2)`) isn't directly needed for any future subproblem `fibonacci(anything > i)`. So once we finish using the solution to `fibonacci(i-2)` to solve `fibonacci(i)`, we are allowed to "forget" the solution to `fibonacci(i-2)`.
                - This means that at any given step of solving `fibonacci(N)`, we only need to store 2 subproblem solutions instead of O(N).

- References:
    - [Jelani Nelson's Sp20 CS170 lectures](https://youtu.be/a7qNN-OQ2zs?t=2744)
    - [DPV Ch6](https://people.eecs.berkeley.edu/~vazirani/algorithms/chap6.pdf)


### Finding the correct recursive subproblem definition (TODO: remove this section - moved to 01_algorithms/00_preliminaries/01_recursion.md)

Finding the correct recursive subproblem definition is often the most difficult step.

I've found myself going through a similar subconscious thought process for every new problem:

1. Focus on a particular instance of the problem input(s) in the most general case (i.e. NOT the base/edge cases).
2. List out ways to shrink input(s).
    - What exact attributes of each input can we shrink?
        - In what specific ways can we do the shrinking of each attribute?
3. Prototype possibilities for recursive step.
    - Try defining the problem w.r.t. a selection of the original problem inputs - e.g. for Knapsack, try defining the problem w.r.t the available weight alone (this ends up being the solution to Knapsack Unbounded), or w.r.t. the allowed items alone, or w.r.t. the available weight and the allowed items both (this ends up being the solution to Knapsack 0-1).
        - Try different possibilities for the recursive step by considering what we listed out in step 2 for each selected input.
            - Assuming we have the solutions to the problem for all shrunken inputs, can we solve the problem for the original input?
    - If nothing works, consider defining a different problem that is simpler to recurse on than the original problem definition and whose results can be combined/aggregated to solve the original problem.
4. Refine recursive step.
    - Does our recursive step work for all general (non-base-case, non-edge-case) inputs?
5. Figure out recursive base cases.
    - Although this should be the easiest part of the process, it's also the part where I've made the most errors, so watch out!
6. If necessary, figure out the main function (initialization before / aggregation after recursion).

#### Step 2 details

- Consider shrinking the **range** of the input.
    - For a linear input structure (e.g. array, String, range of integers), consider shrinking its range
        - from one end. Decrease the `j` in `input[..j]`.
            - Edit Distance separately shrinks the range of input String 1 from the right end and the range of input String 2 from the right end.
            - Knapsack Unbounded shrinks the range of allowed weight from the high end.
            - Knapsack 0-1 separately shrinks the range of allowed items from the high end and the range of allowed weight from the high end.
        - from both ends. Decrease the `j` and/or increase the `i` in `input[i..j]`.
        - by partitioning. Choose some `k` between `i,j`, and create partitions `input[i..k]` and `input[(k+1)..j]`.
            - Matrix Chain Multiplication shrinks the range of matrices-to-multiply by partitioning.
            - Burst Balloons shrinks the range of balloons-to-pop by partitioning.
            - (As an aside, this also applies to non-DP problems like "Construct BST from Sorted Array".)
    - For a nonlinear input structure (e.g. graph, tree), consider (TODO)
- Consider shrinking the problem by moving forward the **"endpoint"** of the input.
    - longestPathInDAG(G, endNode) = max { longestPathInDAG(G, parentNode) for all {parentNode, endNode} is an edge in G }
    - lenLISEndingAt(nums, i) = 1 + max { lenLISEndingAt(nums, j) for all j < i where nums[j] < nums[i] }
        - LIS = Longest Increasing Subsequence

#### Step 3 details

- Example: Edit Distance
    - Assuming we have the correct Edit Distance for all shrunken ranges of input Strings 1 and 2, can we solve the problem for the original input Strings 1 and 2?
        - Yes!

- Example: (Length of) Longest Increasing Subsequence
    - Assuming we have the correct Length of Longest Increasing Subsequence (lenLIS) for all shrunken **ranges** of the input array, can we solve the problem for the original input array?
        - Consider the input `nums = {5, 6, 2, 1, 3, 4}`. From `lenLIS(nums[..1]) = 1`, `lenLIS(nums[..2]) = 2`, `lenLIS(nums[..3]) = 2`, `lenLIS(nums[..4]) = 2`, `lenLIS(nums[..5]) = 2`, can we obtain `lenLIS(nums[..6]) = 3`? **No**. We don't know what value the LIS in each shrunken range ends on, so we can't determine whether the current nums[j] can create a better (longer) LIS.
            - Even if we did know what value the LIS in each shrunken range ends on, figuring out whether that value needs to be updated for our current range would take non-constant computational work. E.g. consider `lenLIS(nums[..5])` as our current range - we *can* write a subroutine that determines that we need to update the LIS from `5, 6` to `1, 3` (the value 3 < the value 6, hence is "easier" to continue building an IS on), but running that subroutine on every input range just devolves into brute-force inefficiency overall.
        - Can we define a stronger (more specific) or different problem that is simpler to recurse on than the original problem definition (i.e. design a recursive helper)?
            - Yes! Instead of recursing on lenLIS, recurse on lenLISEndingAt. To get lenLIS, take the max of all lenLISEndingAt solutions.

### Other

- https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm
