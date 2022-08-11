# Recursion

**These notes attempt to use precise/consistent/not-overloaded terminology definitions, so during review don't skip the first few sections!**

## Terminology definitions

- Say we have a problem, e.g. "find the Kth largest element in a given array".
    - We define a "problem instance" as: an instantiation of the problem with fully-specified or manipulable input values.
        - e.g. "find the Kth largest element in a given array, where K=3 and the array is [61, 70, 127, 170]".
        - e.g. "find the Kth largest element in a given array, where K=`k` and the array is `arr`".
            - We can manipulate `k` with e.g. `k-1` or `k/2`, and `arr` with e.g. `arr[:-1]`.
            - Similar in spirit to Prof Srivastava's proof approach of "putting tangible things on the table".
    - Given an "original problem instance", we define a "subproblem" as: a problem instance where the size or complexity of the input values are <= that of the input values in the original problem instance.
        - Equality included (i.e. the original problem instance is a subproblem of itself) for consistency/convenience.
    - A "query" of a subproblem returns the "solution-value" for that subproblem.
        - A subproblem can be queried in two primary ways: using a recursive function call, or using a cache if its solution-value was already found earlier (memoization / dynamic programming).

- Say we have a recursive function `func`.
    - We define a "call to `func`" as: a single invocation of `func` with fully-specified or manipulable input values.
        - e.g. `findKthLargest(k=3, arr=[61, 70, 127, 170])`
        - e.g. `findKthLargest(k=k, arr=arr)`
    - Note that (without memoization) we may make multiple recursive calls with the same input values. This corresponds to multiple queryings of one subproblem.

- Say we have some "original problem" (semantically different from "original problem instance" above) whose corresponding function signature is difficult/impossible to recurse on directly.
    - Then we might define a new "helper problem", whose corresponding "recursive helper function" signature is straightforward to recurse on directly.
    - For more detail, see step 2 of the section *A basic framework for finding recursive structure*.


## A summary of recursion (with some more terminology definitions)

(Note the following paragraph contains some direct snippets from MIT 6.005.)

A recursive function is defined in terms of one or more "base cases" and one "recursive step".
- In a "base case", we compute the result immediately.
    - Base cases...
        - are the simplest/smallest instances of the problem, that can’t be decomposed recursively any further.
        - often correspond to *emptiness* – the empty string, the empty list, the empty set, the empty tree, zero, etc.
- In the "recursive step" (reminiscent of the "inductive step" in proofs), we compute the result with the help of querying one or more subproblems.
    - The recursive step **decomposes** a larger instance of the problem into one or more smaller/simpler problem instances in a way such that it can then **combine** the solution-values of those subproblems to produce the solution-value of the original problem instance.
        - We define "the decomposition" in this context as *what we literally see written in the function definition*, i.e. the subproblem queries made **directly** by one call, **not including the subproblem queries made at any deeper levels of recursive execution**.


## Design of recursive algorithms (TODO: add relative links to 01_exercises?)

This is a crucial (and often the most difficult) piece of the puzzle when solving problems ranging from [manipulation of linked-lists/trees] to [general optimization/counting with dynamic programming].

1. Brainstorm ways to shrink the problem input(s).
    - It may help to first mentally fix a particular problem instance in the most general case (NOT the base/edge cases).
    - **Naturally-recursive input structures** are often straightforward to decompose.
        - Linked-list / path-in-graph
            - Consider shrinking the input by advancing the **"tail-endpoint"** of the input **towards a base case**.
                - TODO: different linked-list example
                - e.g. (DP) longest_path_in_dag_ending_at(G, **end_node**) = max { ( longest_path_in_dag_ending_at(G, **parent_node**) + weight(parent_node, end_node) ), **for all parent_nodes** such that (parent_node, end_node) is an edge in G }
        - Tree
            - Consider shrinking the input by recursing on subtrees rooted at (direct) children of the current root.
                - e.g. (D&C) max_depth_binary_tree_rooted_at(node) = 1 + max { max_depth_binary_tree_rooted_at(node.left), max_depth_binary_tree_rooted_at(node.right) }
    - **Array-like input structures** (e.g. array, string, range of integers) can be trickier.
        - 1) Consider shrinking the input's **range**:
            - a) from one end. Decrease the `j` in `input[:j]`.
                - e.g. (DP) "Edit Distance" separately shrinks the range of input string 1 from the right end and the range of input string 2 from the right end.
                - e.g. (DP) "Knapsack Unbounded" shrinks the range of allowed weight from the high end.
                - e.g. (DP) "Knapsack 0-1" separately shrinks the range of allowed items from the high end and the range of allowed weight from the high end.
            - b) from both/either ends. Decrease the `j` and/or increase the `i` in `input[i:j]`.
                - e.g. Binary Search (on a sorted array) shrinks the range that can possibly contain the desired key.
                - TODO: find a DP example for this category (this category was mentioned in DPV Ch6 pg178, but I couldn't find a concrete example of it).
            - c) by partitioning. Choose some `k` between `i,j`, and create partitions `input[i:k]` and `input[(k+1):j]`.
                - e.g. (D&C) Quicksort shrinks the range of array-to-sort by partitioning around a single choice of `k` (where `input[k]` is approximately / probabilistically-expected-to-be the median).
                    - (D&C) Mergesort is similar, but `k` (always chosen to be the midpoint of `i` and `j`) is included in one of the partitions (i.e. the partitioning is `input[i:(k+1)]` and `input[(k+1):j]`).
                    - Note that the decomposition step for both Quicksort and Mergesort is a *single* partitioning, hence these are "divide-and-conquer" algorithms (as opposed to "Matrix Chain Multiplication" below).
                - e.g. (D&C) "Construct BST from Sorted Array" shrinks the range of array-to-convert-to-tree by partitioning around the median (found directly since input is sorted).
                - e.g. (DP) "Matrix Chain Multiplication" shrinks the range of matrices-to-multiply by partitioning around the pairwise-multiplication-operation-to-execute-last `k`.
                    - Note that since we a-priori don't know the pairwise-multiplication-operation-to-execute-last that maximizes our objective, the decomposition step tries the partitioning `input[i:k]` and `input[(k+1):j]` for *all* possible values ( `(i:j)` ) of `k`. Different partitionings (with different values of `k`) "partially overlap" (e.g. (`input[0:1]`,`input[2:10]`) and (`input[0:8]`,`input[9:10]`) overlap at indices `(2:8)`), which means that deeper in the *unmemoized* recursive call tree there will be many repeated subproblem queries, hence a dynamic programming algorithm is appropriate (as opposed to Quicksort/Mergesort above).
                - e.g. (DP) "Burst Balloons" shrinks the range of balloons-to-pop by partitioning around the balloon-to-pop-last `k`.
                    - This is a dynamic programming algorithm for similar reasoning as "Matrix Chain Multiplication" above.
        - 2) Consider finding some other **naturally-recursive nonlinear *sub*structure** in the problem:
            - e.g. *Increasing subsequences* are essentially paths in a DAG (e.g. "Longest Increasing Subsequence" reduces to "Longest Path in DAG").
    - Another possible axis on which we can classify ways to shrink is "difference-wise" vs "ratio-wise".
        - "Difference-wise"
            - e.g. "Nth Factorial", "Nth Fibonacci", "Edit Distance", "(Uncached) Length of Linked List", "Longest Path in DAG (Ending At)".
            - often good candidates for dynamic programming.
        - "Ratio-wise":
            - e.g. "Binary Search", "Max Depth of (Balanced) Binary Tree", Mergesort.
                - Quicksort can also be thought of as "ratio-wise" in the probabilistic sense.
            - often results in efficiency analyses with a `log(N)` factor.
        - But keep in mind not all problems *cleanly* fit into exactly one of these classifications.
            - e.g. "Matrix Chain Multiplication" feels like it is "ratio-wise" because it involves partitioning (until we realize we need to try all possible values of `k`), and it is not clearly "difference-wise" yet is a dynamic programming algorithm (but perhaps we can view it as "difference-wise" wrt `k`).

2. Trial-and-error to find an appropriate recursive step.
    - 1) Based on the above brainstorm and some intuition, choose a particular way to decompose the problem instance into one or more subproblems.
        - This might involve the following (both of which are (separate) reasons to need "recursive helper functions" during implementation):
            - adding additional input variables to keep track of which portion of the original input each subproblem is looking at.
                - e.g. `low, high` in binary search, keeping track of which subrange each subproblem is looking at.
                - e.g. `node` in algorithms on tree data, keeping track of (the root of) which subtree each subproblem is looking at.
            - adding additional input variables for any auxiliary state that will be updated throughout the recursion execution.
                - e.g. the counter in "Count Univalue Subtrees".
                - e.g. (Trie definition) `result` in `collectAllKeysRootedAt(node: TrieNode, result: [str])`.
            - defining a new "helper problem" that can better take advantage of naturally-recursive substructure.
                - A helper problem is good when:
                    - a) it is straightforward to recurse on, i.e. its instances can be solved by combining solution-values of its subproblems.
                    - b) we can find the solution-value to an instance of the *original problem* by a simple (non-recursive) aggregation after querying helper problem instances.
                - e.g. Let "Longest Path in DAG" be our original problem. Since paths are a naturally-recursive substructure of graphs, we try defining the helper problem "Longest Path in DAG ending at `endNode`".
                    - This turns out to be a good helper problem since:
                        - a) it is straightforward to recurse on (see "naturally-recursive input structures").
                        - b) we can solve any instance of the *original problem* by querying the helper problem instance for every possible `endNode` then simply (non-recursively) taking the maximum over those solution-values.
                - You may need multiple helper problems if you break the original problem down into a sequence of discrete steps, each of which can be solved recursively.
                    - e.g. (Trie definition) `collectAllKeysWithPrefix() -> [str]` can be broken down into `searchForKey(s: str) -> TrieNode` then `collectAllKeysRootedAt(node: TrieNode, result: [str])`.
        - Examples of intuition:
            - e.g. In "Knapsack Unbounded", we know that our optimum is *only* bounded by our allowed weight. In "Knapsack 0-1", we know that our optimum is bounded by *both* our allowed weight and which items we can choose from.
                - These hint us toward the inputs we should define each respective problem in terms of.
            - e.g. *Increasing subsequences* are reminiscent of paths in a graph.
    - 2) Consider an instance "I" of the (helper) problem with general (NOT base/edge) input values (e.g. `x: int, lst: [int], node: TreeNode`).
    - 3) **Assume we *already know*** the **solution-values** for **all** subproblems of I {e.g. all combinations of (`(x-1)`..`0`, `lst[:-1]`..`lst[:1]`, `root.left`/`root.right`/`root.left.left`/etc)}. How can we use/combine some subset of that knowledge to obtain the solution-value for I? Is it even possible or do we need to keep track of more state / use a different decomposition (see notes under step 1)?
        - The assumption is "the recursive leap of faith" from [CS 61A](https://cs61a.org/).
    - **Rinse and repeat until something works!**
    - Example: (Length of) Longest Increasing Subsequence
        - Design iteration #1:
            - 1) Start with the most basic decomposition: recursing directly on the original problem by shrinking the *range* of the input array.
            - 2) Consider the general-case input `nums = [5, 6, 2, 1, 3, 4]`.
            - 3) Assuming we already know the subproblem solution-values `lenLIS(nums[:1]) = 1`, `lenLIS(nums[:2]) = 2`, `lenLIS(nums[:3]) = 2`, `lenLIS(nums[:4]) = 2`, `lenLIS(nums[:5]) = 2`, how can we obtain `lenLIS(nums[:6]) = 3`?
                    - It is impossible. We don't know what value the LIS in each shrunken range ends on, so we can't determine whether the current `nums[j]` can create a better (longer) LIS.
                        - Even if we did know what value the LIS in each shrunken range ends on, figuring out whether that value needs to be updated for our current range would take non-constant computational work. E.g. consider `lenLIS(nums[:5])` as our current range - we *can* write a subroutine that determines that we need to update the LIS from `5, 6` to `1, 3` (the value 3 < the value 6, hence is "easier" to continue building an IS on), but running that subroutine on every input range just devolves into brute-force inefficiency overall.
        - Design iteration #2:
            - 1) Notice that the problem has a naturally-recursive nonlinear substructure. Define the helper problem `lenLisEndingAt(nums, i)`. Note that this is a good helper since:
                - a) it is straightforward to recurse on.
                - b) `lenLIS(nums)` = max { `lenLisEndingAt(nums, i)` for all i }
            - 2) Consider the general-case input `nums`.
            - 3) Assuming we already know the subproblem solution-values of `lenLisEndingAt(nums, k)` for all `k=(0:i)`, how can we obtain `lenLisEndingAt(nums, i)`?
                - `lenLisEndingAt(nums, i)` = 1 + max { `lenLisEndingAt(nums, j)` for all j < i where nums[j] < nums[i] }
            - Done!

3. Figure out the base cases.
    - **Be careful and thorough!** Although this is supposed to be the easiest part of the process, it's also the part where I've most frequently made (avoidable) errors!
    - (Repeated from *A summary of recursion*) Base cases often correspond to *emptiness* – the empty string, the empty list, the empty set, the empty tree, zero, etc. **Always try these first!**
        - "Arms-length recursion" is an **anti**pattern where choosing base cases that are "too big" results in unnecessarily complicated case-checking.
            - e.g. [a naive solution for "Max Depth Binary Tree"](../01_exercises/tree/a_basic/Q104_MaxDepthBinaryTree/java-archive/Solution.java).
            - However, there are exceptions to this rule, e.g. ["Path Sum"](../01_exercises/tree/a_basic/Q112_PathSum/).


## The shape of recursive execution (all levels, overall work done)

Before continuing, review the section: *Terminology definitions*.

Prelude: directed trees vs directed acyclic graphs (DAGs)
- Note that in most discussions related to recursion (including this document), "trees" are implicitly directed, i.e. edges either consistently go from "parent" to "child" (e.g. classic tree datatype from an intro CS course) or consistently go from "child" to "parent" (e.g. Git commit tree without merges).
- The primary difference to keep in mind between trees and DAGs:
    - each vertex in a tree has exactly one parent (except for the root which has zero parents).
    - each vertex in a DAG can have any number of parents.

It is often useful to visualize/analyze recursive execution (all levels, overall work done) by using:

- a *recursive call tree* (or forest), with each *recursive call* as a vertex with an edge *from* its origin-call.
    - i.e. edges go from "spawner-call / parent" to "spawned-call / child".
    - overall shows how calls are spawned "top-down".
    - useful for the analysis of unmemoized recursive algorithms.

- a *subproblem DAG*, with each *subproblem* as a vertex with edges *to* all the (bigger) subproblems that it *directly* helps solve (i.e. all the (bigger) subproblems that *directly* query it).
    - there is a one-to-one correspondence between vertices and subproblems.
        - as opposed to a recursive call tree, where there is a many-to-one correspondence between vertices and subproblems.
    - encodes the "bottom-up" view of dynamic programming execution (which is also the convention followed in DPV Ch6 figures).
        - reversing the direction of edges gives the "top-down" view of memoized recursive execution.
    - useful for the analysis of memoized recursive and dynamic programming algorithms.


## Analysis of recursive algorithms

Before continuing, review the section: *The shape of recursive execution*.

Note that the following process was written with unmemoized recursive algorithms in mind, but can also be applied to analysis of memoized recursive and dynamic programming algorithms.

1. Consider *one isolated* call to `func`. Analyze the work done by this one isolated call in terms of its input (in each case, for all general/base/edge cases), **ignoring any work done *inside* recursive calls made by this call**.
    - More specifically, we only look at recursive calls that are *directly spawned by this one isolated call* (i.e. literally written out in the definition of `func`), and we only take into account the work to *spawn* those direct recursive calls, **ignoring** any work done *inside* those direct recursive calls.
    - Note that we can apply asymptotic equivalences to simplify the final result of this step.

2. Draw out the recursive call tree rooted at the initial call(s) to `func`.
    - A simple concrete way to go about this:
        - For every call(/vertex), we will draw a box containing:
            - a) the actual values / relevant characteristics of the input.
                - For example, if `func` had parameters `(x: int, lst: [int])`, we might have
                    - "x = N, size of lst = M" for the root call.
                    - "x = N-1, size of lst = M/2" for some subsequent recursive call.
            - b) the work done by the call, as calculated in step 1, but now with actual values plugged into the input.
                - Continuing with the above example, if in step 1 we found the work done by `func` to be Theta(`x * len(lst)**2`), then we would have:
                    - "work done = N * M^2" for the root call.
                    - "work done = (N-1) * M^2 / 4" for the subsequent recursive call.
                        - **Notice we do NOT use asymptotic equivalences to simplify here.** We can safely simplify in step 1 to get the general formula, but further simplifying at each recursive call could result in exponential errors when we later (in step 3) characterize *total* work done.
        - Start with the root(s) at the top and grow the tree downwards. The goal is to get a general sense of the "shape" of the work done throughout the tree, so only draw as many calls as you need (usually a few rows near the root + one or two rows at the leaves is sufficient) and use ellipses generously.
            - **Make sure to draw / pay careful attention to what happens near the leaves of the tree** (when the recursion hits its base cases).

3. Finally, calculate the *total* work done by summing the work done by all calls.
    - This is a straightforward sum because we avoided double-counting in step 1 :)
    - A common way to simplify evaluation of the total sum is to find the intermediate sum amount of work done at *each level* of the recursive call tree (as a function of the "level index", often with "level 0" being the root), then add those intermediate sums up.
    - Note that we can apply asymptotic equivalences to simplify the final result of this step.

### TODO: example with visuals


## Additional references

[MIT 6.006 Sp20 Lecture 15](https://www.youtube.com/watch?v=r4-cftqTcdI)

