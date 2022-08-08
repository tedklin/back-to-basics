## Burst Balloons (Q312)

Problem statement: https://leetcode.com/problems/burst-balloons/

### Clarifying questions to ask

| Question | Reason |
| --- | --- |
| ... | ... |
| ... | ... |

### Naive recursive solution

Recursive step
```
// the max coins obtainable by popping balloons i..j (not including j)
// k represents the balloon popped LAST
maxCoins(nums, i, j)
    = max (for all k = i..j) {
        nums[i-1]*nums[k]*nums[j] + maxCoins(nums, i, k) + maxCoins(nums, k+1, j)
    }
```

Recursive base case
```
if j == i then return 0  // the recursive step guarantees j will never go below i.
```

Example base case: 3 is the only balloon
```
(1), 3, (1)
maxCoins(nums, i=0, j=1)
// only possible value of k is 0
= nums[-1]*nums[0]*nums[1] + maxCoins(nums, 0, 0) + maxCoins(nums, 1, 1)
= 3 + 0 + 0  // this is correct.
```

To handle the (1) balloons at the ends,
```
int[] numsAdjusted = new int[nums.length + 2];
numsAdjusted[0] = 1;
numsAdjusted[numsAdjusted.length-1] = 1;
System.arrayCopy()
```

**Runtime:**

Exponential in N

**Memory:**

Exponential in N.


### Memoized recursive solution

Add a memoization table for storing the solutions for all pairs of i, j (where i < j).

**Runtime:**

There are ~N^2 possibilities for the recursive step input (`i=0..N`, `j=0..N` where i < j), so there are O(N^2) recursive calls (with memoization no recursive calls are repeated). Each recursive call does O(N) work, so total runtime is O(N^3).

**Memory:**

O(N^2) for the memoization table.


### Dynamic programming solution

Bottom-up ordering: 
```
for i = 0..N:
    for j = i..N:
        ...
```

**Runtime:**

**Memory:**


### Followup: ...

....
