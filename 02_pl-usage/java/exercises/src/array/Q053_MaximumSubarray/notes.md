## Maximum Subarray (Q053)

### Clarifying questions

| Question | Reason |
| --- | --- |
| What to return if the input array elements are all negative? | There are two sensible answers for this case: you can simply return the "empty subarray" with sum 0, or you can disallow the "empty subarray" and return the single largest input array element. Which one you choose has virtually no affect on performance. |

### Naive solution

The naive solution would be to check every subarray possible for the one with the maximum sum.

```
int maxSum = Integer.MIN_VALUE;
for (int i = 0; i < nums.length; i++) {
    int currentSum = 0;
    for (int j = i; j < nums.length; j++) {
        currentSum = currentSum + nums[j];
        maxSum = Math.max(maxSum, currentSum);
    }
}
return maxSum;
```

**Runtime:**

This is *(N) + (N-1)... + 2 + 1 = (N) * (N-1) / 2*, which means the running time of this solution would be O(N^2), where N is the size of the input *nums* array.

**Memory:**

Memory usage doesn't depend on the size of *nums* (no data structures were added), so space complexity is O(1).


### Kadane's algorithm solution

Note that for any index *i*, the maximum subarray ending with index *i* is either:

1) itself: ( *[ nums[i] ]* )
2) itself concatenated with the maximum subarray ending with index *i-1*: ( *[ [localMaxSubarray(i-1)], nums[i] ]* )

We can iterate *i* from 0 to N-1 in a single pass, updating the maximum subarray of each index by taking the max of the two options above.

Along the way, we can update the global maximum subarray as the maximum of the local maximums we've seen.

**Runtime:**

Theta(N)

**Memory:**

O(1).

**Notes:**

Note the connection between Kadane's algorithm and the solution to Q121 Best Time to Buy and Sell Stock. The uniting idea is that during a single pass through the input array, we can calculate a local max with the current index as the "stopping" point, while updating some information about what we've seen so far that will help the next index calculate its local max. The global max (the final answer) is then just the max of all the local max's.

### Followup: ...

....
