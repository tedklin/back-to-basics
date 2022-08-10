# Recursion

**Reminder to self: these notes attempt to use precise/consistent/not-overloaded definitions, so during review don't skip the first few sections!**

A good summary of recursion (modified/extended from snippets of MIT 6.005):

A recursive function is defined in terms of one or more "base cases" and one (or more but rarely for our purposes) "recursive step".
- In a "base case", we compute the result immediately given the inputs to the function call.
    - Base cases...
        - are the simplest/smallest instances of the problem, that can’t be decomposed recursively any further.
        - often correspond to "emptiness" – the empty string, the empty list, the empty set, the empty tree, zero, etc.
- In a "recursive step", we compute the result with the help of one or more recursive calls to this same function definition, but with the inputs somehow reduced in size or complexity, bringing us closer to a base case.
    - A recursive step **decomposes** a larger instance of the problem into one or more simpler/smaller instances that can be solved by recursive calls, and **then combines** the results of those subproblems to produce the solution to the original problem.
        - Note the term "divide-and-conquer" usually refers to a more specific pattern, where the decomposing *divides* the problem into subproblems with no overlap (e.g. quicksort).
        - However, "decomposing" as used above is more general - it can also refer to e.g.:
            - one "difference-wise smaller" subproblem (e.g. factorial)
            - two or more "difference-wise smaller" subproblems (e.g. Nth fibonacci).
            - one "ratio-wise" smaller subproblem (e.g. binary search on a balanced binary search tree).


## Basic definitions (in addition to terms defined above)

- Say we have a problem (e.g. "find the kth largest element in a given array").
    - We define a "problem instance" as: an instantiation of the problem with *fully-specified* input *values*.
        - e.g. "find the kth largest element in a given array, where k=3 and the array is [61, 70, 127, 170]".
    - Given an "original" problem instance, we define a "subproblem" as: a problem instance where the size or complexity of the inputs are <= that of the inputs in the original problem.
        - Equality included (i.e. the original problem instance is a subproblem of itself) for consistency/convenience.
    - A subproblem can be "queried" in two primary ways: using a recursive function call, or using a cache (memoization / dynamic programming).

- Say we have a recursive function `func`.
    - We define a "call to `func`" as: a single invocation of `func` with *fully-specified* input *values*.
        - Note that (without memoization) we may make multiple recursive calls with the same input values. This corresponds to multiple queryings of one subproblem.


## The "shape" of recursion

Prelude: directed trees vs directed acyclic graphs (DAGs)
- Note that in most discussions of recursion, "trees" are implicitly directed. The rest of this document follows that convention.
- The primary difference to keep in mind between trees and DAGs:
    - each vertex in a tree has exactly one parent (except for the root which has zero parents).
    - each vertex in a DAG can have any number of parents.

It is often useful to visualize recursion in terms of

- a *recursive call tree* (or forest), with each recursive call as a vertex with an edge *from* its origin-call.
    - i.e. edges go from "spawner-call / parent" to "spawned-call / child".
    - "top-down" but no memoization (memoization would give a DAG).
    - useful for analysis of divide-and-conquer algorithms (e.g. mergesort) where there is no repeated querying of the same subproblem.
        - also prevalent as a pedagogical device in intro CS courses.

- a *subproblem DAG*, with each simpler/smaller subproblem as a vertex with an edge *to* the bigger subproblem it helps solve.
    - there is exactly one vertex per subproblem (as opposed to a recursive call tree where there could be multiple vertices/calls for one subproblem)
    - encodes the structure of (bottom-up) dynamic programming.
    - reversing the direction of edges gives the structure of (top-down) memoization.


## Designing recursive solutions

This is a crucial (and often the most difficult) piece of the puzzle when solving problems ranging from [manipulation of linked-lists/trees] to [general optimization/counting with dynamic programming].

### A basic framework for finding recursive structure

I've found myself going through a similar subconscious thought process for every new problem that looks like a candidate for recursion / dynamic programming.

1. Brainstorm ways to decompose the problem input(s).
    - It may help to first mentally fix a particular problem instance in the general case (NOT the base/edge cases).
    - **Naturally-recursive input structures** are pretty straightforward to decompose.
        - Linked-list / path-in-graph
            - Consider shrinking the problem by advancing the **"tail-endpoint"** of the input **towards a base case**.
                - e.g. (DP) longestPathInDag(G, **endNode**) = max { (longestPathInDag(G, **parentNode**) + weight(parentNode, endNode)), for all parentNodes such that (parentNode, endNode) is an edge in G }
        - Tree
            - Consider shrinking the problem by recursing on subtrees rooted at (direct) children.
                - e.g. (D&C) maxDepthBinaryTreeRootedAt(node) = 1 + max { maxDepthBinaryTreeRootedAt(node.left), maxDepthBinaryTreeRootedAt(node.right) }
        - Graph
            - (TODO) e.g. Bellman-Ford
    - **Linear input structures** (e.g. array, string, range of integers) can be trickier.
        - 1) Consider shrinking its **range**:
            - a) from one end. Decrease the `j` in `input[:j]`.
                - e.g. (DP) "Edit Distance" separately shrinks the range of input string 1 from the right end and the range of input string 2 from the right end.
                - e.g. (DP) "Knapsack Unbounded" shrinks the range of allowed weight from the high end.
                - e.g. (DP) "Knapsack 0-1" separately shrinks the range of allowed items from the high end and the range of allowed weight from the high end.
            - b) from both ends. Decrease the `j` and/or increase the `i` in `input[i:j]`.
            - c) by partitioning. Choose some `k` between `i,j`, and create partitions `input[i:k]` and `input[(k+1):j]`.
                - e.g. (D&C) Quicksort shrinks the range of array-to-sort by partitioning around a single choice of `k` (where `input[k]` is approximately / probabilistically-expected-to-be the median).
                    - (D&C) Mergesort is similar, but `k` (chosen to be the midpoint of `i` and `j`) is included in one of the partitions (i.e. the partitions are `input[i:(k+1)]` and `input[(k+1):j]`).
                - e.g. (D&C) "Construct BST from Sorted Array" shrinks the range of array-to-convert-to-tree by partitioning around the median (found directly since input is sorted).
                - e.g. (DP) "Matrix Chain Multiplication" shrinks the range of matrices-to-multiply by partitioning around the last-executed pairwise-multiplication `k`.
                    - Since we a-priori don't know the last-executed pairwise-multiplication that maximizes our objective, we try all possible values (`(i:j)`) for `k` (hence DP).
                - e.g. (DP) "Burst Balloons" shrinks the range of balloons-to-pop by partitioning around the last-popped balloon `k`.
                    - Since we a-priori don't know the last-popped balloon that maximizes our objective, we try all possible values (`(i:j)`) for `k` (hence DP).
        - 2) Consider finding some other **naturally-recursive nonlinear *sub*structure**
            - e.g. *Increasing subsequences* are reminiscent of paths in a graph ("Longest Increasing Subsequence" reduces to "Longest Path in DAG").

2. Trial-and-error to find an appropriate recursive step.
    - 1) Based on above brainstorm and intuition, choose a particular way to decompose the problem input(s).
        - This might involve the following (both of which are (separate) reasons to need "recursive helper functions" during implementation):
            - adding additional input variables to keep track of what (sub)range each subproblem is looking at.
                - e.g. `low, high` in binary search.
            - defining a new "helper problem" that can take advantage of naturally-recursive substructure
                - A "good" helper problem is one where:
                    - a) it's a problem that is straightforward to recurse on.
                    - b) we can find the solution-value to an instance of the *original problem* by a simple (non-recursive) combination/aggregation of queries to helper problem instances.
                - e.g. Let "Longest Path in DAG" be our original problem. Since paths are a naturally-recursive substructure of graphs, we try defining the helper problem "Longest Path in DAG ending at `endNode`".
                    - This turns out to be a "good" helper problem since:
                        - a) it's a problem that is straightforward to recurse on.
                        - b) we can solve any instance of the *original problem* by querying the helper problem instance for every possible `endNode` then simply (non-recursively) taking the maximum over those solution-values.
        - Examples of intuition:
            - e.g. In "Knapsack Unbounded", we know that our optimum is *only* bounded by our allowed weight. In "Knapsack 0-1", we know that our optimum is bounded by *both* our allowed weight and which items we can choose from.
            - e.g. *Increasing subsequences* are reminiscent of paths in a graph.
    - 2) Consider an instance "I" of the (helper) problem with general (NOT base/edge) input values (e.g. `x: int, lst: [int], node: TreeNode`).
    - 3) **Assume we *already know*** the **solution-values** for **all** subproblems of I {e.g. all combinations of (`(x-1)`..`0`, `lst[:-1]`..`lst[:1]`, `root.left`/`root.right`/`root.left.left`/etc)}. How can we use/combine some subset of that knowledge to obtain the solution-value for I? Is it even possible or do we need more knowledge?
    - **Rinse and repeat until something works!**
    - Example: (Length of) Longest Increasing Subsequence
        - Design iteration #1:
            - 1) Start with the most basic decomposition: recursing directly on the original problem by shrinking the *range* of the input array.
            - 2) Consider the general-case input `nums = [5, 6, 2, 1, 3, 4]`.
            - 3) Assuming we already know the subproblem solution-values `lenLIS(nums[:1]) = 1`, `lenLIS(nums[:2]) = 2`, `lenLIS(nums[:3]) = 2`, `lenLIS(nums[:4]) = 2`, `lenLIS(nums[:5]) = 2`, how can we obtain `lenLIS(nums[:6]) = 3`?
                    - It is impossible. We don't know what value the LIS in each shrunken range ends on, so we can't determine whether the current `nums[j]` can create a better (longer) LIS.
                        - Even if we did know what value the LIS in each shrunken range ends on, figuring out whether that value needs to be updated for our current range would take non-constant computational work. E.g. consider `lenLIS(nums[:5])` as our current range - we *can* write a subroutine that determines that we need to update the LIS from `5, 6` to `1, 3` (the value 3 < the value 6, hence is "easier" to continue building an IS on), but running that subroutine on every input range just devolves into brute-force inefficiency overall.
        - Design iteration #2:
            - 1) Notice that the problem has a naturally-recursive nonlinear substructure. Define the helper problem `lenLisEndingAt(nums, i)`. Note that `lenLisEndingAt` is a good helper since:
                - a) `lenLisEndingAt(nums, i)` is straightforward to recurse on.
                - b) `lenLIS(nums)` = max { `lenLisEndingAt(nums, i)` for all i }
            - 2) Consider the general-case input `nums`.
            - 3) Assuming we already know the subproblem solution-values of `lenLisEndingAt(nums, k)` for all `k=(1:i)`, how can we obtain `lenLisEndingAt(nums, i)`?
                - `lenLisEndingAt(nums, i)` = 1 + max { `lenLisEndingAt(nums, j)` for all j < i where nums[j] < nums[i] }
            - Done!

3. Figure out the base cases.
    - Although this is expected to be the easiest part of the process, it's also the part where I've most frequently made (avoidable) errors, so **be careful and thorough**!

4. If necessary, figure out the main function (initialization before / aggregation after executing recursive helpers).


## A general procedure for *analysis* of recursive algorithms (without memoization)

Before proceeding, review the above sections: *Basic definitions* and *The "shape" of recursion*. 

1. Consider *one* call to `func`. Analyze the work done by this call in terms of its input, **excluding work done *inside* any *new* recursive calls directly spawned by this call**.
    - More specifically, we only account for new recursive calls *directly spawned by this call*, and we **treat them as constant-time operations** (we only take into account the work to *spawn* the new calls and **ignore** any work done *inside* the new calls).
    - A simple concrete way to go about this is to look at the written-out definition (i.e. code in the body) of `func`, and mentally replace every recursive call to `func` you see in the code with a constant-time operation.
    - Note that we can apply asymptotic equivalences to simplify the final result of this step.

2. Draw out the recursive call tree rooted at the initial call(s) to `func`.
    - A simple concrete way to go about this:
        - For every call, we will draw a box containing:
            - (a) the actual values / relevant characteristics of the input.
                - For example, if `func` had parameters `(x: int, lst: [int])`, we might have
                    - "`x` = N, size of `lst` = M" for the root call.
                    - "`x` = N-1, size of `lst` = M/2" for some subsequent recursive call.
            - (b) the work done by the call, as calculated in step 1, but now with actual values plugged in.
                - Continuing with the above example, if in step 1 we found the work done by `func` to be Theta(`x * len(lst)**2`), then we would have:
                    - "work done = N * M^2" for the root call.
                    - "work done = (N-1) * M^2 / 4" for the subsequent recursive call.
                        - **Notice we do NOT use asymptotic equivalences to simplify here.** We can safely simplify in step 1 to get the general formula, but further simplifying at each recursive call could result in exponential errors when we later (in step 3) characterize *total* work done.
        - Start with the root(s) at the top and grow the tree downwards. The goal is to get a general sense of the "shape" of the work done throughout the tree, so only draw as many calls as you need (usually a few rows near the root + one or two rows at the leaves is sufficient) and use ellipses generously.
            - **Make sure to draw / pay careful attention to what happens near the leaves of the tree** (when the recursion hits its base cases).

3. Finally, calculate the *total* work done by summing the work done by all calls.
    - This step is a simple sum because of the way we approached step 1 :)
    - Note that we can apply asymptotic equivalences to simplify the final result of this step.

### Example: (TODO)

