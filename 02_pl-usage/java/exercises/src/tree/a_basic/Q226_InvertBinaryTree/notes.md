## Invert Binary Tree (Q226)

Problem statement: https://leetcode.com/problems/invert-binary-tree/

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

Theta(H) for the recursive call stack.

H itself is bounded by Theta(N) in the worst case where the input tree is a linked-list. H itself is bounded by Theta(log N) in the best case where the input tree is fully balanced.


### Followup: From recursion to iteration

We just need to visit each node exactly once to flip its left and right pointers. So we can use any traversal (preorder and level-order are easiest iteratively).
