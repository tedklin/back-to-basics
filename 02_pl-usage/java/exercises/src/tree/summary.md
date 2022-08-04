# Tree problems

[//]: # (reference-style links)
[Q100]: https://github.com/tedklin/back-to-basics/tree/master/02_pl-usage/java/exercises/src/tree/a_basic/Q100_SameTree
[Q104]: https://github.com/tedklin/back-to-basics/tree/master/02_pl-usage/java/exercises/src/tree/a_basic/Q104_MaxDepthBinaryTree
[Q112]: https://github.com/tedklin/back-to-basics/tree/master/02_pl-usage/java/exercises/src/tree/a_basic/Q112_PathSum
[Q144]: https://github.com/tedklin/back-to-basics/tree/master/02_pl-usage/java/exercises/src/tree/_traversals/Q144_BinaryTreePreorderTraversal
[Q226]: https://github.com/tedklin/back-to-basics/tree/master/02_pl-usage/java/exercises/src/tree/a_basic/Q226_InvertBinaryTree
[Q250]: https://github.com/tedklin/back-to-basics/tree/master/02_pl-usage/java/exercises/src/tree/b_nontrivial/Q250_CountUnivalueSubtrees

## Takeaways

### General process for designing a recursive solution
1. Figuring out the recursive step
    - Assume you can already get the solution for smaller subsets of the input. How can you combine those solutions to solve the problem for the input node itself?
        - For trees, the "smaller subsets of input" are usually the subtrees rooted at the input node's direct children.
    - e.g. for [Q104 Max Depth Binary Tree][Q104]: Given the max depth of its left subtree and the max depth of its right subtree, how can you solve for the max depth of the input node itself?
2. Designing the recursive function signature
    - Inputs:
        - Usually need at least one `TreeNode node` to recurse over the input tree.
        - What other auxiliary information did we need to recombine/solve the problem at the input node?
            - This potentially includes non-local data.
                - Personally, if I need data to be accessible/shared by multiple recursive helper calls, I would instantiate the shared objects in the function that spawns the first call to the recursive helper, and add extra parameters in the recursive helper signature to pass along pointers to the shared objects. The objects themselves may result in higher memory usage, but practically speaking, if you doing recursion in Java you probably value modularity/readability more than memory usage anyways. E.g. see [Q250 Count Univalue Subtrees][Q250].
    - Outputs:
        - What information did we need to obtain from recursing on the children?
    - If the resulting recursive function signature is different than the provided one, that indicates that you need a helper!
        - You may need multiple helpers if you break the original problem down into a sequence of discrete steps, each of which can be solved recursively. E.g. for tries, `public List collectAllKeysWithPrefix()` can be broken down into `private Node searchForKey(String s)` then `private void collectAllKeysRootedAt(Node n, List result)`.
    - The question "What *side effects* should we observe from recursing on the children?" is important to keep in mind for the overall solution, but is usually irrelevant to designing the recursive function *signature*. E.g. see [Q226 Invert Binary Tree][Q226].
3. Figuring out the base cases
    - Common base cases to try:
        - If the input node is null.
        - If the input node is a leaf.
            - Usually not desired because it can lead to messy "arms-length recursion" code (e.g. the naive solution in the code for [Q104 Max Depth Binary Tree][Q104]).
            - Sometimes needed, e.g. when all possible solutions **must** stop at a leaf (e.g. [Q112 Path Sum][Q112]).

### Obvious but important reminders
- **Check for nulls!!**
    - In recursive base cases.
    - On **every** insertion (`add`/`push`/`insert`) of an object (reference) into a (library) data structure.
- Pay attention to the inputs and outputs of each function.
- Pay attention to the type arguments you pass into generic declarations.

### Runtime and memory analysis
- Common candidates for worst/best cases:
    - Shape of input tree
        - Fully balanced.
        - Linked list ("stringy").
        - Lopsided, i.e. left subtree has one node and right subtree has many (e.g. [Q112 Path Sum][Q112]).
    - Behavior of function
        - When the condition that we're checking for is satisfied or violated ASAP (e.g. [Q112 Path Sum][Q112]).
        - When we need to traverse the entire tree to verify that the condition that we're checking for is satisfied or violated.
- Memory usage analysis will often depend on the input tree's height.
    - See analysis in [Q104 Max Depth Binary Tree][Q104] for reasoning.
- To make the worst/best-case analysis clearer (especially when they depend on factors other than height) we can include variables to represent height.
    - e.g. for memory usage analysis of [Q100 Same Tree][Q100].

### Converting tree recursion to iteration
- Pay attention to the order in which you add nodes to the stack.
    - e.g. for [Q144 Binary Tree Preorder Traversal][Q144].

### Useful traversal properties
- [A preorder or postorder traversal that explicitly includes null elements can uniquely identify a tree. A preorder or postorder traversal that does not explicitly include null elements cannot uniquely identify a tree.](https://stackoverflow.com/questions/45871284/uniqueness-of-inorder-preorder-and-postorder-traversal-with-null-elements)
- [A postorder traversal is equivalent to the reverse of the preorder traversal of the reversed (mirrored) tree.](https://github.com/tedklin/back-to-basics/blob/master/02_pl-usage/java/exercises/src/tree/_traversals/Q145_BinaryTreePostorderTraversal/notes.md#followup-from-recursion-to-iteration-two-stacks)


## TODO

### Blind 75

- Binary Tree Maximum Path Sum - https://leetcode.com/problems/binary-tree-maximum-path-sum/
- Serialize and Deserialize Binary Tree - https://leetcode.com/problems/serialize-and-deserialize-binary-tree/
- Construct Binary Tree from Preorder and Inorder Traversal - https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
- Validate Binary Search Tree - https://leetcode.com/problems/validate-binary-search-tree/
- Kth Smallest Element in a BST - https://leetcode.com/problems/kth-smallest-element-in-a-bst/
- Lowest Common Ancestor of BST - https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/
- Implement Trie (Prefix Tree) - https://leetcode.com/problems/implement-trie-prefix-tree/
- Add and Search Word - https://leetcode.com/problems/add-and-search-word-data-structure-design/
- Word Search II - https://leetcode.com/problems/word-search-ii/

### Other

- Convert Sorted Array to Binary Search Tree - https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/
