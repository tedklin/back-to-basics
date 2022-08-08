## Longest Increasing Subsequence (Q300)

Problem statement: https://leetcode.com/problems/longest-increasing-subsequence/

### Clarifying questions to ask

| Question | Reason |
| --- | --- |
| ... | ... |
| ... | ... |

### Naive recursive solution

1. Conceptual formulation

Recursive step:
```
lenLisEndingAt(nums, i)
    = 1 + max (for all j < i where nums[j] < nums[i]) { lenLisEndingAt(nums, j) }
```
Recursive base cases:
```
if i < 0, then return 0
```
Main function (initialization / aggregation):
```
lengthOfLIS(nums) = max (for all i) { lenLisEndingAt(nums, i) }
```

**Runtime:**

Exponential.

**Memory:**

Exponential.


### Memoized recursive solution

Add a memoization table for storing the solutions to lenLisEndingAt(nums, i) for all `i=0..N`.

**Runtime:**

There are N possibilities for the recursive step input (`i=0..N`), so there are O(N) recursive calls (with memoization no recursive calls are repeated). Each recursive call does O(i) work, so total runtime is O(0+1+2+..+(N-1)+N) = O(N^2).

**Memory:**

Theta(N) for the memoization table.


### Dynamic programming solution

Bottom-up ordering: `i=0..N`. Note that since each subproblem needs to look at *all* previous subproblems, we can't do any memory saving.

**Runtime:**

Theta(N^2).

**Memory:**

Theta(N).
