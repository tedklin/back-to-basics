## Edit Distance (Q072)

Problem statement: https://leetcode.com/problems/edit-distance/


### Clarifying questions to ask

| Question | Reason |
| --- | --- |
| ... | ... |
| ... | ... |


### Naive recursive solution

1. Conceptual formulation

Recursive step:
```
minDistance(word1, word2)
    = min {
        1 + minDistance(word1[:-2], word2);     // delete one char
        1 + minDistance(word1, word2[:-2]);     // insert one char
        if word1[-1] == word2[-1], then consider minDistance(word1[:-2], word2[:-2])    // no edit
            else consider 1 + minDistance(word1[:-2], word2[:-2]);      // replace one char
    }
```

Recursive base cases:
```
if word1.length == 0, then return word2.length;     // insert all that's left of word2
if word2.length == 0, then return word1.length;     // delete all that's left of word1
```

2. Implementation with simple optimizations

Avoid string copying by letting `i, j := current word1, word2 substring lengths`.
- Note that letting `i, j := current word1, word2 indices being considered` results in messier base cases.

Recursive step:
```
minDistance(word1, word2, i, j)
    = min {
        1 + minDistance(word1, word2, i-1, j);     (deletion)
        1 + minDistance(word1, word2, i, j-1);     (insertion)
        if word1[i-1] == word2[j-1], then consider minDistance(word1, word2, i-1, j-1)      (no-edit)
            else consider 1 + minDistance(word1, word2, i-1, j-1);      (replacement)
    }
```

Recursive base cases:
```
if i == 0, then return j;     // insert all that's left of word2
if j == 0, then return i;     // insert all that's left of word1
```

**Runtime:**

Exponential.

**Memory:**

Exponential.


### Memoized recursive solution

See code.

**Runtime:**

There are N\*M possibilities for the recursive step input (`i=0..N`, `j=0..M`), so there are O(N\*M) recursive calls (with memoization no recursive calls are repeated). Each recursive call does constant work, so total runtime is O(N\*M).

**Memory:**

O(N\*M) for the memoization table.


### Dynamic programming solution

Draw out the underlying recursive dependency DAG for this problem. (For an example **(reverse)** dependency DAG for this problem, see [DPV Ch6 p177](https://people.eecs.berkeley.edu/~vazirani/algorithms/chap6.pdf)).

Note that each non-base-case subproblem has three dependencies: `up 1`, `left 1`, and `up-left 1`. A few possible bottom-up orderings are:
1. row by row, left to right.
    - The current subproblem **directly** depends on only the current row (for `left 1`) and the previous row (for `up 1` and `up-left 1`). Theta(M) space.
2. column by column, top to bottom.
    - The current subproblem **directly** depends on only the current column (for `up 1`) and the previous column (for `left 1` and `up-left 1`). Theta(N) space.
3. in the order of BFS starting from i=0, j=0 on the **(reverse)** dependency DAG.
    - The current subproblem **directly** depends on only the current BFS wave and the previous BFS wave (visually each BFS wave is an ⅃ shape centered at i=0, j=0). Theta(N+M) space (for the final and biggest BFS wave).

**Runtime:**

Each subproblem takes constant time, and there is exactly one subproblem for every combination of `i, j`, so total runtime is Theta(N*M).

**Memory:**

Our implementation goes row by row, left to right, so space is Theta(M).
