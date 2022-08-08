## Knapsack Unbounded (repetition allowed)

Problem statement: [DPV Ch6 p181](https://people.eecs.berkeley.edu/~vazirani/algorithms/chap6.pdf)

### Clarifying questions to ask

| Question | Reason |
| --- | --- |
| ... | ... |
| ... | ... |

### Naive recursive solution

Recursive step:
```
maxTotalValue(int allowedWeight)
    = max (for all i where itemWeights[i] <= allowedWeight) {
        itemValues[i] + maxTotalValue(allowedWeight - itemWeights[i])
    }
```

Recursive base case:
```
if no items within allowedWeight, then return 0
```

**Runtime:**

Exponential in W.

**Memory:**

Exponential in W.


### Memoized recursive solution

Add a memoization table for storing the solutions to maxTotalValue(allowedWeight) for all `allowedWeight=1..W`.

**Runtime:**

There are W possibilities for the recursive step input (`allowedWeight=1..W`), so there are O(W) recursive calls (with memoization no recursive calls are repeated). Each recursive call does O(N) work, so total runtime is O(W\*N).

**Memory:**

O(W) for memoization table.


### Dynamic programming solution

Bottom-up ordering: `allowedWeight=1..W`. Note that since each subproblem may need to look at any of the previous subproblems, we can't do any memory saving.

**Runtime:**

O(N*W).

**Memory:**

O(W).


### Followup: ...

....
