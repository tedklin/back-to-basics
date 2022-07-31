## Best Time to Buy and Sell Stock (Q121)

### Clarifying questions

| Question | Reason |
| --- | --- |
| Will the input always produce a valid answer? If no, then what should we return if there is no valid answer? | Correctness. |

### Naive solution

The naive solution would be to check every combination of days and return the maximum difference in price.

```
int maxProfit = 0;
for (int i = 0; i < prices.length; i++) {
    for (int j = i + 1; j < prices.length; j++) {
        maxProfit = Math.max(maxProfit, prices[j] - prices[i]);
    }
}
return maxProfit;
```

**Runtime:**

This is *(N-1) + (N-2)... + 2 + 1 = (N-1) * (N-2) / 2*, which means the running time of this solution would be O(N^2), where N is the size of the input *prices* array.

**Memory:**

Memory usage doesn't depend on the size of *prices* (no data structures were added), so space complexity is O(1).


### Single pass solution.

Note that for any day *i*, we only need the min price seen before day *i* to calculate the local max profit with *i* as the "sell" point.

We can iterate from day 0 to day N-1 in a single pass, updating the global max profit seen so far while simultaneously updating the min price seen so far.

**Runtime:**

Theta(N).

**Memory:**

O(1).

**Notes:**

This approach is related to Kadane's algorithm for the [Maximum Subarray (Q053)](#maximum-subarray-(q053)) problem. The uniting idea is that during a single pass through the input array, we can calculate a local max with the current index as the "stopping" point, while updating some information about what we've seen so far that will help the next index calculate its local max. The global max (the final answer) is then just the max of all the local max's.


### Followup: ...

....
