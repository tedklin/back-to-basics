---


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


---