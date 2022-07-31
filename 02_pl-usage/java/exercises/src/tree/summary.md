# Tree problems

## Takeaways

### Obvious but important reminders
- **Check for nulls!!**
    - In recursive base cases.
    - On **every** insertion (`add`/`push`/`insert`) of an object (reference) into a (library) data structure.
- Pay attention to the inputs and outputs of each function.
- Pay attention to the type arguments you pass into generic declarations.

### Converting tree recursion to iteration
- pay attention to the order in which you add nodes to the stack.

### Arms-length recursion
- Usually not desired because it can lead to messy code (e.g. the naive solution in the code for Q104 Max Depth Binary Tree).
- Sometimes needed, e.g. when the base case is a leaf (e.g. Q112 Path Sum).

### Common candidates for best/worst cases for runtime and memory:
- Shape of input tree
    - Fully balanced.
    - Linked list ("stringy").
    - Lopsided, i.e. left subtree has one node and right subtree has many (e.g. Q112 Path Sum).
- Behavior of function
    - When the condition that we're checking for is satisfied or violated ASAP (e.g. Q112 Path Sum).
    - When we need to traverse the entire tree to verify that the condition that we're checking for is satisfied or violated.


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

- Construct Binary Tree from Sorted Array
