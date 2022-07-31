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


---


## Binary Tree Inorder Traversal (Q094)

### Clarifying questions to ask

| Question | Reason |
| --- | --- |
| ... | ... |


### Naive solution

....

**Runtime:**

**Memory:**


### ... solution

....

**Runtime:**

**Memory:**


### Followup: ...

....


---


## Binary Tree Postorder Traversal (Q145)

### Clarifying questions to ask

| Question | Reason |
| --- | --- |
| ... | ... |
| ... | ... |

### Naive solution

....

**Runtime:**

**Memory:**


### ... solution

....

**Runtime:**

**Memory:**


### Followup: From recursion to iteration (two stacks)

The key observation is: for a binary tree (not sure if this works for general trees), doing a pre-order traversal where the order in which you recurse on a node's children is flipped will yield the reverse post-order. You can draw out an example (bounding blob trace) to see this.

So augment the iterative pre-order code by
- switching the order of pushing each node's children onto the stack.
- for the pre-order "visit" of each node, push that node onto **another stack**.

After the pre-order traversal is complete, the other stack can pop the nodes in post-order.


### Followup: From recursion to iteration (one stack)

[Reference.](https://www.geeksforgeeks.org/iterative-postorder-traversal-using-stack/)


---


## Binary Tree Level Order Traversal (Q102)

### Clarifying questions to ask

| Question | Reason |
| --- | --- |
| ... | ... |
| ... | ... |

### Naive solution

....

**Runtime:**

Theta(N), where N is number of nodes in the tree.

**Memory:**

The max amount of space needed at any given step is *~maxWidth* to store the queue at the widest level of nodes.

Theta(N) in the worst case where the tree is fully balanced and the leaf level is ~N/2 nodes wide. Theta(1) in the best case where the tree is a linked list.


### ... solution

....

**Runtime:**

**Memory:**


### Followup: ...

....


---