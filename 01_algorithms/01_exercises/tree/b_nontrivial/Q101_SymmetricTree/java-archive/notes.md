## Symmetric Tree (Q101)

Problem statement: https://leetcode.com/problems/symmetric-tree/

### Clarifying questions to ask

| Question | Reason |
| --- | --- |
| ... | ... |

### Standard solution with recursion

We want to do two traversals at the same time so we can compare for reflection. This suggests our recursive function should have two node parameters - one for the left reflection and one for the right reflection. Since this is different from the function signature provided, we make a recursive helper function. The implementation follows naturally.

**Runtime:**

Theta(N) in the worst case where the tree is symmetric and we visit every node exactly once. Theta(1) in the best case where all of the nodes are on one side of the root.

**Memory:**

Theta(H) for the recursive call stack in the worst case mentioned above. (H is the height of the input tree.) Theta(1) for the recursive call stack in the best case mentioned above.

H itself is bounded by Theta(N) in the worst case where the input tree looks like a linked list mirrored about the root (creating a perfect upside down V). H itself is bounded by Theta(log N) in the best case where the input tree is fully balanced.


### Followup: Iterative solution

Do BFS or DFS but with careful ordering of enqueues/pushes and dequeues/pops such that any mirrored node locations are adjacent in the queue/stack and can be dequeued/popped together for comparison.

**Runtime:**

Theta(N) in the worst case where the tree is symmetric and we visit every node exactly once. Theta(1) in the best case where all of the nodes are on one side of the root (returns immediately).

**Memory:**

For the DFS version, the max amount of space needed at any given step is *~height* to store the stack from the root to the lowest leaf.
- Theta(height = N) in the worst case where the tree looks like a linked list mirrored about the root (creating a perfect upside down V). Theta(1) in the best case where all of the nodes are on one side of the root (returns immediately).

For the BFS version, the max amount of space needed at any given step is *~maxWidth* to store the queue at the widest level of nodes.
- Theta(N) in the worst case where the tree is fully balanced and the leaf level is ~N/2 nodes wide. Theta(1) in the best case where the tree is a linked list.
