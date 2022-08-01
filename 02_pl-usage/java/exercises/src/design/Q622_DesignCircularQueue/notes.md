## Design Circular Queue (Q622)

Problem statement: https://leetcode.com/problems/design-circular-queue/

### Clarifying questions to ask

| Question | Reason |
| --- | --- |
| Do we need to handle resizing? | Correctness. |
| What makes an operation not "successful"? Is it just enqueue on a full queue and dequeue on an empty queue?  | Correctness. |

### Solution

Use an underlying array to hold the data, and keep track of the "head" and "tail" indices.

Details in code.

**Runtime:**

**Memory:**


### Followup: ...

....
