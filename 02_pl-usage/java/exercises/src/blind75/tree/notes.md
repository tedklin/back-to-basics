

---


## Same Tree (Q100)

### Clarifying questions to ask

| Question | Reason |
| --- | --- |
| ... | ... |
| ... | ... |

### Naive solution

....

### ... solution

....

### Followup: ...

....

### Takeaways

....


---


## Level Order Traversal (Q102)

### Clarifying questions to ask

| Question | Reason |
| --- | --- |
| ... | ... |
| ... | ... |

### Naive solution

....

### ... solution

....

### Followup: ...

....

### Takeaways

....


---


## Max Depth of Binary Tree (Q104)

### Clarifying questions to ask

| Question | Reason |
| --- | --- |
| ... | ... |
| ... | ... |

### Naive solution

....

### ... solution

....

### Followup: ...

....

### Takeaways

....


---


## Invert Binary Tree (Q226)

### Clarifying questions to ask

| Question | Reason |
| --- | --- |
| ... | ... |
| ... | ... |

### Naive solution

....

### ... solution

....

### Followup: ...

....

### Takeaways

....


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

Running time of our solution is O(k + H), where H is the height of the tree. Where does the "+ H" come from? Consider the case where k=1 and the tree is a string of nodes all leaning to the left. Once we find the 1st smallest element (the leftmost node, which is also the node at the "end" of the left-leaning string of nodes), then we still have to travel back up and "process" the nodes that we touched on the way down and are still on the recursive call stack (though at this point we aren't doing any more meaningful work). Since we take care to not start any more node visits once the solution is found, we get O(k + H).

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

### Takeaways

....


---


## Subtree of Another Tree (Q572)

### Clarifying questions to ask

| Question | Reason |
| --- | --- |
| ... | ... |
| ... | ... |

### Naive solution

....

### ... solution

....

### Followup: ...

....

### Takeaways

....


---
