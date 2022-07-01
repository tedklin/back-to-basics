

---


## Design Circular Queue (Q622)

### Clarifying questions to ask

| Question | Reason |
| --- | --- |
| Do we need to handle resizing? | Correctness. |
| What makes an operation not "successful"? Is it just enqueue on a full queue and dequeue on an empty queue?  | Correctness. |

### Solution

Use an underlying array to hold the data, and keep track of the "head" and "tail" indices.

Details in code.

### Followup: ...

....

### Takeaways

- Draw diagrams!
- Explicitly noting what each member variable represents helps with reasoning about the implementation.
- Preconditions and postconditions help with reasoning about the coherence of a data structure.


---


## Question Name (Q001)

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