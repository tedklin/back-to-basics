## Binary Tree Preorder Traversal (Q144)

### Clarifying questions to ask

| Question | Reason |
| --- | --- |
| Can the input root be null? If so, do we handle that case by returning null or returning an empty List? | Correctness. |

### Standard solution with recursion

See code.

**Runtime:**

We visit each node exactly once, so Theta(N) where N = number of nodes in tree.

**Memory:**

The max amount of space needed at any given step is *~height* to store the recursive call stack from the root to the lowest leaf.

Theta(height = N) in the worst case where the tree is a linked list. Theta(height = log N) in the best case where the tree is fully balanced.


### Followup: From recursion to iteration

See code.

**Runtime:**

We push, pop, and add to result each node exactly once, so Theta(N) where N = number of nodes in tree.

**Memory:**

The max amount of space needed at any given step is *~height* to store the stack from the root to the lowest leaf.

Theta(height = N) in the worst case where the tree is a linked list. Theta(height = log N) in the best case where the tree is fully balanced.
