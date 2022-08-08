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

```
def is_disjoint(A: list[int], B: list[int], C: list[int]) -> bool:
    # Takes NlogN time and N additional memory.
    sorted_A = sorted(A)
    sorted_B = sorted(B)
    sorted_C = sorted(C)

    # TODO: check correctness and runtime analysis.
    # TODO: optimization - stop the search as soon as one of the lists is exhausted.
    idx_a, idx_b, idx_c = 0, 0, 0
    while idx_a <= len(sorted_A) or idx_b <= len(sorted_B) or idx_c <= len(sorted_C):
        while sorted_B[idx_b] < sorted_A[idx_a]:  # overall occurs between N and 2N times
            idx_b += 1                            # overall occurs N times
        while sorted_C[idx_c] < sorted_B[idx_b]:  # overall occurs between N and 2N times
            idx_c += 1                            # overall occurs N times
        assert(sorted_C[idx_c] >= sorted_B[idx_b] >= sorted_A[idx_a])
        if sorted_A[idx_a] == sorted_B[idx_b] == sorted_C[idx_c]:    # overall occurs between N and 2N times (see notes below)
            return False
        else:
            idx_a += 1                            # overall occurs N times
    return True
```

**Runtime:**

TODO: think through this more thoroughly.

How many times does the check `A[idx_a] == B[idx_b] == C[idx_c]` occur overall?
- Case 1: all a∈A < all b∈B < all c∈C
    - First, idx_a gets incremented until its end while idx_b and idx_c don't change. The check occurs N times.
    - Second, idx_b gets incremented until its end while idx_c doesn't change. The check occurs N times.
    - So overall 2N times.
- Case 2: all a∈A < all c∈C < all b∈B
    - On the first iteration of the outer loop, idx_c gets incremented until its end. The check occurs once.
    - idx_a gets incremented until its end while idx_b doesn't change. The check occurs N times.
    - So overall N times.
- Case 3: A=[1, 4, 7, ...], B=[2, 5, 8, ...], C=[3, 6, 9, ...]
    - The three indexes will essentially increment in lock step, and the check will occur on (idx_a, idx_b, idx_c) = (0,0,0), (1,1,1), (2,2,2), etc.
    - So overall N times.
- Case 4: everything else is a mix of the above extreme cases.

Overall Theta(NlogN). Dominated by initial sorting.

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
