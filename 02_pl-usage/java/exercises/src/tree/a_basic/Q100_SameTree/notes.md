## Same Tree (Q100)

### Clarifying questions to ask

| Question | Reason |
| --- | --- |
| ... | ... |
| ... | ... |

### Standard recursive solution

See code.

**Runtime:**

Theta(N) in the worst case where the trees are the same and every node is visited. Theta(1) in the best case where the first node checked is already not the same.

**Memory:**

Theta(N) for the recursive call stack in the worst case where the trees are the same and every node is visited, and the trees are both linked lists. Theta(1) for the recursive call stack in the best case where the first node checked is already not the same.

Note that in the case where the trees are the same, but both trees are fully balanced, the recursive call stack takes Theta(logN).


### Followup: From recursion to iteration

Use a stack for each input tree and iteratively traverse them in sync to check for sameness.
