## Knapsack 0-1 (no item repetition allowed)

Problem statement: [DPV Ch6 p181](https://people.eecs.berkeley.edu/~vazirani/algorithms/chap6.pdf)

### Clarifying questions to ask

| Question | Reason |
| --- | --- |
| ... | ... |
| ... | ... |

### Naive recursive solution

Recursive step:
```
// max total value given allowedWeight and allowed items 0..j including j.
maxTotalValue(int allowedWeight, int j)
    = max {
        itemValues[j] + maxTotalValue(allowedWeight - itemWeights[j], j-1) (only consider this if allowedWeight - itemWeights[j] >= 0),
        maxTotalValue(allowedWeight, j-1)
    }
```

Recursive base cases:
```
if allowedWeight == 0, then return 0  // the if condition in the recursive step guarantees allowedWeight will never go below 0.
if j == -1, then return 0  // since j always decreases by exactly 1, j will never go below -1.
```

**Runtime:**

Exponential.

**Memory:**

Exponential.


### Memoized recursive solution

Add a memoization table for storing the solutions for all `allowedWeight=1..W`, `j=0..N`.

**Runtime:**

There are W\*N possibilities for the recursive step input (`allowedWeight=1..W`, `j=0..N`), so there are O(W\*N) recursive calls (with memoization no recursive calls are repeated). Each recursive call does constant work, so total runtime is O(W\*N).

**Memory:**

O(W\*N) for memoization table.


### Dynamic programming solution

Any subproblems that the current subproblem directly depends on is in the previous row (j-1). Bottom-up ordering: if each j is a row and each allowedWeight is a column, go row by row, left to right in each row. We only need to save the current and previous row.

**Runtime:**

Theta(W\*N). Each element in the table takes constant work.

**Memory:**

Theta(W).


### Followup: ...

....
