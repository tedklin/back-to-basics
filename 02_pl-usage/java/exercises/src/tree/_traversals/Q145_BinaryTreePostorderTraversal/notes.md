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
