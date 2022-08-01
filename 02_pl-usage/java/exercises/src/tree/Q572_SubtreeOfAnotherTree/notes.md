## Subtree of Another Tree (Q572)

Problem statement: https://leetcode.com/problems/subtree-of-another-tree/

### Clarifying questions to ask

| Question | Reason |
| --- | --- |
| ... | ... |
| ... | ... |

### Naive solution

See code.

**Runtime:**

Theta(NM) in the worst case where there is no matching subtree. For each of the N nodes in the `root` tree, we need to do M work to compare the subtree rooted at that node to the tree rooted at `subRoot`.

**Memory:**

Theta(H) in the worst case where there is no matching subtree. (H is the height of the `root` tree, and J is the height of the `subRoot` tree.) It is Theta(H) even while processing the leaf level of the `root` tree because as soon as `isSameTree` hits a null, it stops exploring further and goes back up the call stack.


### ... solution

....

**Runtime:**

**Memory:**


### Followup: ...

....
