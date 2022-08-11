# Tree problems

[//]: # (reference-style links)
[Q100]: https://github.com/tedklin/back-to-basics/tree/master/02_pl-usage/java/exercises/src/tree/a_basic/Q100_SameTree
[Q104]: https://github.com/tedklin/back-to-basics/tree/master/02_pl-usage/java/exercises/src/tree/a_basic/Q104_MaxDepthBinaryTree
[Q112]: https://github.com/tedklin/back-to-basics/tree/master/02_pl-usage/java/exercises/src/tree/a_basic/Q112_PathSum
[Q144]: https://github.com/tedklin/back-to-basics/tree/master/02_pl-usage/java/exercises/src/tree/_traversals/Q144_BinaryTreePreorderTraversal
[Q226]: https://github.com/tedklin/back-to-basics/tree/master/02_pl-usage/java/exercises/src/tree/a_basic/Q226_InvertBinaryTree
[Q250]: https://github.com/tedklin/back-to-basics/tree/master/02_pl-usage/java/exercises/src/tree/b_nontrivial/Q250_CountUnivalueSubtrees


**Before continuing, review [01_recursion.md](../../00_preliminaries/01_recursion.md) for precise terminology definitions and context.**

## Runtime and memory analysis
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

## Converting tree recursion to iteration
- Pay attention to the order in which you add nodes to the stack.
    - e.g. for [Q144 Binary Tree Preorder Traversal][Q144].

## Useful traversal properties
- [A preorder or postorder traversal that explicitly includes null elements can uniquely identify a tree. A preorder or postorder traversal that does not explicitly include null elements cannot uniquely identify a tree.](https://stackoverflow.com/questions/45871284/uniqueness-of-inorder-preorder-and-postorder-traversal-with-null-elements)
- [A postorder traversal is equivalent to the reverse of the preorder traversal of the reversed (mirrored) tree.](https://github.com/tedklin/back-to-basics/blob/master/02_pl-usage/java/exercises/src/tree/_traversals/Q145_BinaryTreePostorderTraversal/notes.md#followup-from-recursion-to-iteration-two-stacks)


## TODO

- Convert Sorted Array to Binary Search Tree - https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/
