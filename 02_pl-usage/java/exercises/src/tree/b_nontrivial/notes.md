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

The max amount of space needed at any given step is *~height* to store the recursive call stack from the root to the lowest leaf.

Theta(height = N) in the worst case where the tree looks like a linked list mirrored about the root (creating a perfect upside down V). Theta(1) in the best case where all of the nodes are on one side of the root (returns immediately).


### Followup: Iterative solution

Do BFS or DFS but with careful ordering of enqueues/pushes and dequeues/pops such that any mirrored node locations are adjacent in the queue/stack and can be dequeued/popped together for comparison.

**Runtime:**

Theta(N) in the worst case where the tree is symmetric and we visit every node exactly once. Theta(1) in the best case where all of the nodes are on one side of the root (returns immediately).

**Memory:**

For the DFS version, the max amount of space needed at any given step is *~height* to store the stack from the root to the lowest leaf.
- Theta(height = N) in the worst case where the tree looks like a linked list mirrored about the root (creating a perfect upside down V). Theta(1) in the best case where all of the nodes are on one side of the root (returns immediately).

For the BFS version, the max amount of space needed at any given step is *~maxWidth* to store the queue at the widest level of nodes.
- Theta(N) in the worst case where the tree is fully balanced and the leaf level is ~N/2 nodes wide. Theta(1) in the best case where the tree is a linked list.


---


## Kth Smallest Element of a BST (Q230)

### Clarifying questions to ask

| Question | Reason |
| --- | --- |
| Is k zero-indexed or 1-indexed? | ... |
| Will the initial input tree always have at least one node? (i.e. Let *N* be the size of the initial input tree. Will *N >= 1* always hold?) | ... |
| Will k always be a valid query? (i.e. Will *1 <= k <= N* always hold?) | ... |

### Naive solution

Recall that the *inorder traversal* of a BST will process nodes in order from smallest to largest.

Therefore, a simple solution to this problem is: pick the element that appears Kth in the BST's inorder traversal.

To keep memory usage low, we use a single non-local variable *numNodesSeenSoFar* to keep track of the number of nodes processed so far by the inorder traversal. When *numNodesSeenSoFar* hits the input k, we know the node currently being processed is the kth node of the inorder traversal, and we store the node's value (the solution) in another non-local variable. To stop the ongoing traversal from visiting more nodes than it needs to, once we have found our solution, we make sure to not recursively visit any more nodes to the right of the nodes already on the call stack.

**Runtime:**

Running time of our solution is O(k + H), where H is the height of the tree. Where does the "+ H" come from? Consider the case where k=1 and the tree is a string of nodes all leaning to the left. Once we find the 1st smallest element (the leftmost node, which is also the node at the "end" of the left-leaning string of nodes), then we still have to travel back up and "process" the nodes that we touched on the way down and are still on the recursive call stack (though at this point we aren't doing any more meaningful work). Since we take care to not start any more node visits once the solution is found, we get O(k + H).

**Memory:**

Memory usage of our solution is O(1), which accounts for the two non-local variables we added. If we want to take into account the call stack memory used by recursion, then the memory usage would be O(H), since the recursion depth will never exceed the maximum depth of the tree.

### Followup: iterative inorder traversal

Be prepared to transform the recursive inorder traversal to an iterative one. This would improve our solution's memory usage, albeit only by a constant factor of memory due to the shift from recursive call stack to explicit stack.

### Followup: divide-and-conquer solution

If we design our BST data structure with this "Kth smallest element" operation in mind, we could do the following: for every node in the tree, keep track of the size of the subtree rooted at that node. (Note this requires slight modification of insert and delete operations.)

Then, we can run a recursive divide-and-conquer algorithm (NOTE: indices here may be off by one, adjust accordingly!):
- if *k < size of left subtree*, then the solution is in the left subtree, so recurse on the left subtree
- if *k == size of left subtree*, then the current node's value is the solution
- else, the solution is in the right subtree, so recurse on the right subtree
- note the value of k would have to change to *k - size of left subtree - 1* to maintain proper recursion

Running time of this solution is O(log N). This approach is reflective of the classic "search" operation on BSTs.


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