## Summary of takeaways

- Obvious but important reminders:
  - **Check for nulls!!**
    - In recursive base cases.
    - On **every** insertion (`add`/`push`/`insert`) of an object (reference) into a data structure.
  - Pay attention to the inputs and outputs of each function.
  - Pay attention to the type arguments you pass into generic declarations.

- When converting tree recursion to iteration, pay attention to the order in which you add nodes to the stack.

- Arms-length recursion:
    - Usually not desired because it can lead to messy code (e.g. the naive solution in the code for Q104 Max Depth Binary Tree).
    - Sometimes needed, e.g. when the base case is a leaf (e.g. Q112 Path Sum).


---


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

The max amount of space needed at any given step is *~height* to store the entire recursive call stack from the root to the lowest leaf.

Theta(height = N) in the worst case where the tree is a linked list. Theta(height = log N) in the best case where the tree is fully balanced.


### Followup: From recursion to iteration

See code.

**Runtime:**

We push, pop, and add to result each node exactly once, so Theta(N) where N = number of nodes in tree.

**Memory:**

The max amount of space needed at any given step is *~height* to store the entire stack from the root to the lowest leaf.

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

The max amount of space needed at any given step is *~maxWidth* to store the entire queue at the widest level of nodes.

Theta(N) in the worst case where the tree is fully balanced and the leaf level is ~N/2 nodes wide. Theta(1) in the best case where the tree is a linked list.


### ... solution

....

**Runtime:**

**Memory:**


### Followup: ...

....


---


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


---


## Symmetric Tree (Q101)

### Clarifying questions to ask

| Question | Reason |
| --- | --- |
| ... | ... |

### Standard solution with recursion

We want to do two traversals at the same time so we can compare for reflection. This suggests our recursive function should have two node parameters - one for the left reflection and one for the right reflection. Since this is different from the function signature provided, we make a recursive helper function. The implementation follows naturally.

**Runtime:**

Theta(N) in the worst case where the tree is symmetric and we visit every node exactly once. Theta(1) in the best case where all of the nodes are on one side of the root (returns immediately).

**Memory:**

The max amount of space needed at any given step is *~height* to store the entire stack from the root to the lowest leaf.

Theta(height = N) in the worst case where the tree looks like a linked list mirrored about the root (creating a perfect upside down V). Theta(1) in the best case where all of the nodes are on one side of the root (returns immediately).


### Followup: Iterative solution

Do BFS or DFS but with careful ordering of enqueues/pushes and dequeues/pops such that any mirrored node locations are adjacent in the queue/stack and can be dequeued/popped together for comparison.

**Runtime:**

Theta(N) in the worst case where the tree is symmetric and we visit every node exactly once. Theta(1) in the best case where all of the nodes are on one side of the root (returns immediately).

**Memory:**

For the DFS version, the max amount of space needed at any given step is *~height* to store the entire stack from the root to the lowest leaf.

Theta(height = N) in the worst case where the tree looks like a linked list mirrored about the root (creating a perfect upside down V). Theta(1) in the best case where all of the nodes are on one side of the root (returns immediately).

For the BFS version, the max amount of space needed at any given step is *~maxWidth* to store the entire queue at the widest level of nodes.

Theta(N) in the worst case where the tree is fully balanced and the leaf level is ~N/2 nodes wide. Theta(1) in the best case where the tree is a linked list.


---


## Path Sum (Q112)

### Clarifying questions to ask

| Question | Reason |
| --- | --- |
| ... | ... |

### Standard solution with recursion

See code. Note that the problem states **root-to-leaf** path, so the recursion is not as clean as [other tree problems](#max-depth-of-binary-tree-q104); we only trigger "path found" if the current node is a leaf, so arms-length recursion is actually needed here.

**Runtime:**

Theta(N) in the worst case where we traverse the entire tree and don't find any paths. Theta(1) in the best case where the root only has one node on the left that satisfies the path sum, and we can skip traversing all of the right subtree.

**Memory:**

Theta(N) for the recursive call stack in the worst case where the tree is a linked-list. Theta(1) for the recursive call stack in the best case mentioned above.

Note that in the case where the tree is fully balanced and we don't find any paths, memory usage will be Theta(log N) for the recursive call stack.


### Followup: From recursion to iteration

One stack for TreeNodes (like in regular iterative DFS) is not enough. I.e. you can't just have one targetSum variable, you need a separate targetSum variable associated with each TreeNode to properly mirror the recursive call stack. So have two stacks - one for TreeNodes and one for targetSums - and use them in sync. Or have one stack for {TreeNode, targetSum} pairs.


---


## Count Univalue Subtrees (Q250)

### Clarifying questions to ask

| Question | Reason |
| --- | --- |
| ... | ... |

### Standard recursive solution

There are two goals we need to accomplish: determine whether a subtree rooted at a given node is univalue, and determine the total number of univalue subtrees. Solving the first goal is a prerequisite for tackling the second goal.

A subtree rooted at node is a univalue subtree iff all of the node's non-null children are themselves univalue subtrees AND have the same value as node. (We define children to mean direct descendants, i.e. does not include grandchildren etc.).

Therefore we can solve the first goal using the recursive helper `boolean isSubtreeUnivalue(TreeNode node)`.
- A naive solution to solve the second goal with this helper is to call it on every node in the tree, which is inefficient (a lot of repeated work on the nodes farther away from the root).
- A second solution would be to use an integer, global to all recursive calls, that is incremented every time we confirm a univalue subtree. Then one call to the helper on the root would suffice.
    - An "integer global to all recursive calls" can be accomplished with a global variable (generally not the best practice), or with an extra parameter in the helper for a pointer to an integer instantiated in the initial caller of the helper (not naturally supported in Java).

An alternative approach (the one I ended up with) is to use a set, global to all recursive calls, that keeps track of all univalue-subtree-roots seen so far. Then traversing the tree in post-order will solve the first goal, and getting the size of the set at the end will solve the second goal.
- Since sets are objects, making a set global to all recursive calls can be naturally accomplished in Java with an extra parameter in the helper.
- Note that this results in higher memory usage (because of the set) and worse best-case-runtime (because no [short-circuit evaluation](https://en.wikipedia.org/wiki/Short-circuit_evaluation#Common_use)) than the second solution discussed above.


**Runtime:**

Theta(N) since it's always a complete post-order traversal.

**Memory:**

Theta(N) in the worst-cases where
- all subtrees are univalue and the set takes Theta(N) space.
- OR the tree is a linked-list and the recursive call stack takes Theta(N) space.

Theta(log N) in the best-case where
- no subtrees are univalue and the set takes Theta(1) space.
- AND the tree is fully balanced and the recursive call stack takes Theta(log N) space.


### ... solution

....

**Runtime:**

**Memory:**


### Followup: ...

....


---
