## Subtree of Another Tree (Q572)

Problem statement: https://leetcode.com/problems/subtree-of-another-tree/

### Clarifying questions to ask

| Question | Reason |
| --- | --- |
| ... | ... |
| ... | ... |

### Naive solution

See code. Note the usage of the solution to [Q100 Same Tree](https://github.com/tedklin/back-to-basics/tree/master/02_pl-usage/java/exercises/src/tree/a_basic/Q100_SameTree).

**Runtime:**

Let N = the size of the `root` tree, M = the size of the `subRoot` tree, H = the height of the `root` tree, and J = the height of the `subRoot` tree.

Theta(NM) in the worst case where all subtrees of size M in the `root` tree nearly match the `subRoot` tree (the only difference being the bottom right node for all of them). For any node in the `root` tree, we need to do M work before we can determine that it's not a matching subtree. We need to do this for each of the N nodes in the `root` tree since there are no matching subtrees overall.

Theta((H - J) + M) in the best case where there is a matching subtree in the bottom left of the `root` tree, and all other nodes in the `root` tree are different from the root of the `subRoot` tree (so the match-checking process takes M time for the matching subtree and constant time for all other nodes). The (H - J) is the time spent following the left child pointers down from `root` to the matching subtree.

**Memory:**

Theta(H). It is Theta(H) in the worst case even while processing the leaf level of the `root` tree because as soon as `isSameTree` hits a null, it stops exploring further and goes back up the call stack.


### Preorder traversal solution

[Reference.](https://leetcode.com/problems/subtree-of-another-tree/discuss/474425/JavaPython-2-solutions%3A-Naive-Serialize-in-Preorder-then-KMP-O(M%2BN)-Clean-and-Concise)



### Followup: ...

....
