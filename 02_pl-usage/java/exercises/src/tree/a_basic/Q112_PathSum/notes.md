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
