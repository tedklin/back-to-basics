## Invert Binary Tree (Q226)

### Clarifying questions to ask

| Question | Reason |
| --- | --- |
| ... | ... |
| ... | ... |


### Standard recursive solution

See code.

**Runtime:**

Theta(N) since we recurse on every node exactly once.

**Memory:**

Theta(N) for the recursive call stack in the worst case where the tree is a linked-list. Theta(log N) for the recursive call stack in the best case where the tree is fully balanced.


### Followup: From recursion to iteration

We just need to visit each node exactly once to flip its left and right pointers. So we can use any traversal (preorder and level-order are easiest iteratively).
