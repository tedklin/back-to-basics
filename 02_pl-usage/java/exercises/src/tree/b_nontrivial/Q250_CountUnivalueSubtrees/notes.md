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
