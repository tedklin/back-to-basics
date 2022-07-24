

---


## Binary Tree Preorder Traversal (Q144)

### Clarifying questions to ask

| Question | Reason |
| --- | --- |
| Can the input root be null? If so, do we handle that case by returning null or returning an empty List? | Correctness. |

### Recursive solution

See code.

**Runtime**

We visit each node exactly once, so Theta(N) where N = number of nodes in tree.

**Space**

For a given tree, the amount of space needed at any given step is O(height) to store the entire recursive call stack to the lowest leaf. So best case is fully bushy tree with O(height = log N) and worst case is linked list with O(height = N).

### Followup: iteration instead of recursion

See code.

**Runtime**

We push, pop, and add to res each node exactly once, so Theta(N) where N = number of nodes in tree.

**Space**

For a given tree, the amount of space needed at any given step is O(height) to store the entire stack to the lowest leaf. So best case is fully bushy tree with O(height = log N) and worst case is linked list with O(height = N).

### Takeaways

- Obvious but important reminders:
  - **Check for nulls!!**
    - In recursive base cases.
    - On **every** insertion (`add`/`push`/`insert`) of an object (reference) into a data structure.
  - Pay attention to what you pass into / return from each function.
  - Pay attention to the type arguments you pass into generic declarations.


---


## Binary Tree Inorder Traversal (Q094)

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


## Binary Tree Postorder Traversal (Q145)

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


## Binary Tree Level Order Traversal (Q102)

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
