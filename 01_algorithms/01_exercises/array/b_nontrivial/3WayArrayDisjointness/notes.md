# Three-way array disjointness

Problem statement: Goodrich & Tamassia 3.3.3.

"The three-way set disjointness problem is to determine if the intersection of three sequences is empty, namely, that there is no element x such that x ∈ A, x ∈ B, and x ∈ C."


## 1. Fully understand the problem statement, including asking clarifying questions and listing out possible inputs / expected outputs (basic functionality and a couple edge cases).

**Metanotes:**
- **During this step, avoid thinking about possible solutions already.**
- **For the sake of time, don't actually code up the tests unless explicitly asked to.**
- Delete the example rows below to avoid getting confused.

| Clarifying question | Answer | Reason for asking |
| --- | --- | --- |
| Are the input sequences already sorted? | No. | Input structure - sorting at the start would incur additional cost. |
| Can there be duplicate elements within an individual input sequence? | No. | Input structure: Might open / close opportunities to use hashsets/maps or to actively prune search space. |
| Given multiple collections, can we assume they are of same length? |  Yes. | Input structure: Affects efficiency analysis and possible solutions / implementation details. |
| Is in-place modification of the input allowed? | No. | Problem semantics: Affects additional-memory analysis and possible solutions / implementation details. |
| ... | ... | ... |

| Input | Expected output | Description |
| --- | --- | --- |
| `A=[1, 2], B=[3, 4], C=[5, 6]` | `True` | Basic functionality. |
| `A=[1, 2], B=[2, 3], C=[3, 4]` | `True` | Basic functionality. |
| `A=[1, 2], B=[2, 3], C=[4, 2]` | `False` (x=2) | Basic functionality. |
| At least one of the lists is empty. | `True` | Edge case. |
| ... | ... | ... |


## 2. Brainstorm - quick name-listing of ANY possibly relevant solution directions (techniques, data structures, simplifying-transformations of input like sorting/mapping, etc.).

**Metanotes:**
- **Don't spend too much time on the first-pass brainstorm - this list is meant to be revisited and heavily pruned / added to throughout the process.**
    - **Don't worry about correctness / fully fleshing out the solution directions that come to mind - just list them out first.**

- Sorting each sequence then traversing all 3 together, vaguely resembling a [3-way mergesort merge](https://leetcode.com/discuss/interview-question/568482/facebook-phone-merge-3-sorted-arrays).
- Throw all elements in a Counter-style map and check if any count is 3.
- ....
- ....
- ....


## 3. Implementation and analysis

### Solution 1: naive/brute-force

```
def is_disjoint(A: list[int], B: list[int], C: list[int]) -> bool:
    for a in A:
        for b in B:
            for c in C:
                if a == b == c:
                    return False
    return True
```

**Runtime:**

Let N = the length of each input list.

Worst case: Theta(N^3) when there is no three-way common element.

Best case: Theta(1) when the first element of each input list is the same.

Overall: O(N^3)

**Additional memory:**

None.


### Solution 2: sort then traverse together

A similar problem: https://leetcode.com/problems/intersection-of-three-sorted-arrays/description/

```
def is_disjoint(A: list[int], B: list[int], C: list[int]) -> bool:
    # Takes NlogN time and N additional memory.
    sorted_A = sorted(A)
    sorted_B = sorted(B)
    sorted_C = sorted(C)

    idx_a, idx_b, idx_c = 0, 0, 0
    while idx_a < len(sorted_A) and idx_b < len(sorted_B) and idx_c < len(sorted_C):
        val_a = sorted_A[idx_a]
        val_b = sorted_B[idx_b]
        val_c = sorted_C[idx_c]

        if val_a == val_b == val_c:
            return False

        min_val = min(val_a, val_b, val_c)
        if val_a == min_val:
            idx_a += 1
        if val_b == min_val:
            idx_b += 1
        if val_c == min_val:
            idx_c += 1

    return True
```

**Runtime:**

Overall Theta(NlogN). Dominated by initial sorting.
- Note that the while loop runs in Theta(N) time.
    - On every iteration of the while loop, at least one index gets incremented, which means the while loop iterates no more than 3N times, with each iteration taking constant time.
    - OTOH in the best case, all three indices get incremented on every iteration, which means the while loop iterates N times, with each iteration taking constant time.

**Additional memory:**

Overall Theta(N). For sorted lists.


### Solution 3: throw all elements in Counter-style map

```
def is_disjoint(A: list[int], B: list[int], C: list[int]) -> bool:
    counts = {}
    def add_elems_to_counts(lst: list[int]) -> None:
        nonlocal counts
        for elem in lst:
            if elem in counts:
                counts[elem] += 1
            else:
                counts[elem] = 1
    add_elems_to_counts(A)
    add_elems_to_counts(B)
    add_elems_to_counts(C)
    for count in counts.values():
        if count == 3:
            return False
    return True
```

**Runtime:**

Overall Theta(N).

**Additional memory:**

Overall Theta(N). For counts map.


### Solution 4: solution from textbook (suboptimal runtime, but important example of runtime analysis / using problem assumptions)

Realize that instead of checking both conditions (two equalities) at once on all possible *triples*, we can check equality of one *pair* at a time and actively prune our search space (reminiscent of short-circuit evaluation). The efficiency improvement might not be immediately obvious, but after implementation we can see that efficiency improvement is guaranteed because of the assumption that there are no duplicate elements within an individual input sequence.

```
def is_disjoint(A: list[int], B: list[int], C: list[int]) -> bool:
    for a in A:
        for b in B:
            if a == b:  # this check occurs O(N^2) times.
                # the check passes *at most* N times because of the uniqueness assumption above.
                for c in C:
                    if c == a:
                        return False
    return True
```

**Runtime:**

Overall O(N^2).

**Additional memory:**

None.


## 4. Misc notes / possible followup questions

....
