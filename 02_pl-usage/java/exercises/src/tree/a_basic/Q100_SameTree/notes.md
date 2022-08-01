## Same Tree (Q100)

Problem statement: https://leetcode.com/problems/same-tree/

### Clarifying questions to ask

| Question | Reason |
| --- | --- |
| ... | ... |
| ... | ... |

### Standard recursive solution

See code.

**Runtime:**

Theta(N) in the worst case where the input trees are the same and every node is visited. Theta(1) in the best case where the first node checked is already not the same.

**Memory:**

Theta(H) for the recursive call stack in the worst case mentioned above. (H is the height of the input trees.) Theta(1) for the recursive call stack in the best case mentioned above.

H itself is bounded by Theta(N) in the worst case where the input tree is a linked-list. H itself is bounded by Theta(log N) in the best case where the input tree is fully balanced.


### Followup: From recursion to iteration

Use a stack for each input tree and iteratively traverse them in sync to check for sameness.
