## Count Univalue Subtrees (Q250)

Problem statement: https://leetcode.com/problems/count-univalue-subtrees/

### Clarifying questions to ask

| Question | Reason |
| --- | --- |
| ... | ... |

### Standard recursive solution

There are two goals we need to accomplish: determine whether a subtree rooted at a given node is univalue, and determine the total number of univalue subtrees. Solving the first goal is a prerequisite for tackling the second goal.

A subtree rooted at node is a univalue subtree iff all of the node's non-null children have the same value as node AND are themselves univalue subtrees. (We define children to mean direct descendants, i.e. does not include grandchildren etc.).

Therefore we can solve the first goal using the recursive helper `boolean isSubtreeUnivalue(TreeNode node)`.
- A naive solution to solve the second goal with this helper is to call it on every node in the tree, which is inefficient (a lot of repeated work on the nodes farther away from the root).
- A second solution would be to use an integer, accessible/shared by all recursive calls, that is incremented every time we confirm a univalue subtree. Then one call to the helper on the root would suffice.
    - An "integer accessible/shared by all recursive calls" can be accomplished with a class variable (generally not the best practice), or with an extra parameter in the helper for a pointer to an integer instantiated in the initial caller of the helper (not naturally supported in Java).

An alternative approach (the one I ended up with) is to use a set, accessible/shared by all recursive calls, that keeps track of all univalue-subtree-roots seen so far. Then processing the tree in post-order will solve the first goal, and getting the size of the set at the end will solve the second goal.
- Since sets are objects, making a set accessible/shared by all recursive calls can naturally be accomplished in Java with an extra parameter in the helper to pass along (pointers to) the set.
- Note that the use of a set results in higher worst-case memory usage than the second solution discussed above.


**Runtime:**

Theta(N) since it's always a complete post-order traversal.

**Memory:**

The set takes Theta(N) space in the worst case where all subtrees are univalue. The set takes Theta(1) space in the best case where no subtrees are univalue.

The recursive call stack takes Theta(H) space. H itself is Theta(N) in the worst case where the input tree is a linked-list. H itself is Theta(log N) in the best case where the input tree is fully balanced.

So overall Theta(N) in the worst-case and Theta(log N) in the best-case.


### ... solution

....

**Runtime:**

**Memory:**


### Followup: ...

....
