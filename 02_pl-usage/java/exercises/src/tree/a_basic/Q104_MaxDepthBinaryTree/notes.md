## Max Depth of Binary Tree (Q104)

### Clarifying questions to ask

| Question | Reason |
| --- | --- |
| ... | ... |

### Standard solution with recursion

See code. Note that this is essentially an augmented post-order traversal (finish visiting both child subtrees, then aggregate results to return).

**Runtime:**

Each node "gets visited" (calculates its own depth) exactly once, so total is Theta(N), where N is number of nodes in tree.

**Memory:**

At any given step, the recursive call stack resembles a single path down the tree, because for each node n we only start recursing on the right subtree of n after we're completely finished recursing on the left subtree of n (i.e. we never have both children on the call stack at the same time). So the max amount of space needed at any given step is *~height* to store the entire recursive call stack from the root to the lowest leaf.

Theta(height = N) in the worst case where the tree is a linked list. Theta(height = log N) in the best case where the tree is fully balanced.


### Followup: Iterative solution

Do BFS with each iteration of the while loop processing the entire queue (so every iteration we process one "wave" and increment the depth).

**Runtime:**

Same as BFS: Theta(N), where N is number of nodes in the tree.

**Memory:**

Same as BFS: The max amount of space needed at any given step is *~maxWidth* to store the entire queue at the widest level of nodes. Theta(N) in the worst case where the tree is fully balanced and the leaf level is ~N/2 nodes wide. Theta(1) in the best case where the tree is a linked list.
