# Tree problems

## Takeaways

### General process for designing a recursive solution
1. Figuring out the recursive step
   - Assume you can already get the solution for smaller subsets of the input. How can you combine those solutions to solve the problem for the input node itself?
     - For trees, the "smaller subsets of input" are usually the subtrees rooted at the input node's direct children.
   - e.g. for Q104 Max Depth Binary Tree: Given the max depth of its left subtree and the max depth of its right subtree, how can you solve for the max depth of the input node itself?
2. Designing the recursive function signature
   - Inputs:
     - Usually need (at least one) `TreeNode node` since we're recursing on a tree.
     - What other auxiliary information did we need to recombine/solve the problem at the input node?
       - This includes potential non-local data like the set in Q250 Count Univalue Subtrees.
   - Outputs:
     - What information did we need to obtain from recursing on the children?
3. Figuring out the base cases
   - Common base cases to try:
     - If the input node is null.
     - If the input node is a leaf.
       - Usually not desired because it can lead to messy "arms-length recursion" code (e.g. the naive solution in the 
         code for Q104 Max Depth Binary Tree).
       - Sometimes needed, e.g. when possible solutions must stop at a leaf (e.g. Q112 Path Sum).

### Obvious but important reminders
- **Check for nulls!!**
    - In recursive base cases.
    - On **every** insertion (`add`/`push`/`insert`) of an object (reference) into a (library) data structure.
- Pay attention to the inputs and outputs of each function.
- Pay attention to the type arguments you pass into generic declarations.

### Common candidates for best/worst cases for runtime and memory
- Shape of input tree
    - Fully balanced.
    - Linked list ("stringy").
    - Lopsided, i.e. left subtree has one node and right subtree has many (e.g. Q112 Path Sum).
- Behavior of function
    - When the condition that we're checking for is satisfied or violated ASAP (e.g. Q112 Path Sum).
    - When we need to traverse the entire tree to verify that the condition that we're checking for is satisfied or violated.

### Converting tree recursion to iteration
- Pay attention to the order in which you add nodes to the stack.


## TODO

### Blind 75

- Binary Tree Maximum Path Sum - https://leetcode.com/problems/binary-tree-maximum-path-sum/
- Serialize and Deserialize Binary Tree - https://leetcode.com/problems/serialize-and-deserialize-binary-tree/
- Subtree of Another Tree - https://leetcode.com/problems/subtree-of-another-tree/
- Construct Binary Tree from Preorder and Inorder Traversal - https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
- Validate Binary Search Tree - https://leetcode.com/problems/validate-binary-search-tree/
- Kth Smallest Element in a BST - https://leetcode.com/problems/kth-smallest-element-in-a-bst/
- Lowest Common Ancestor of BST - https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/
- Implement Trie (Prefix Tree) - https://leetcode.com/problems/implement-trie-prefix-tree/
- Add and Search Word - https://leetcode.com/problems/add-and-search-word-data-structure-design/
- Word Search II - https://leetcode.com/problems/word-search-ii/

### Other

- Convert Sorted Array to Binary Search Tree - https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/
