## Summary of takeaways

- 


---


## Two Sum (Q001)

### Clarifying questions to ask

| Question | Reason |
| --- | --- |
| Will the input always produce a valid answer? If no, then what should we return if there is no valid answer? | Correctness. |
| Can there be multiple answers from the input? If there are multiple answers, will we need to return all of them or just one? | If we don't need to return all answers if there are multiple, then we can return as soon as we find *an* answer. If we need to return all answers if there are multiple, our bound becomes Theta() instead of O(), because we would need to check every element regardless of how soon we come across the "first" answer. |
| Are repeated indices allowed? (i.e. Is [0,0] a valid answer if *nums=[3, 2, 4]* and *target=6*) | Correctness. |

### Naive solution

The naive solution would be to check every combination of two integers in the input *nums* array. 

**Runtime:**

This is *(N choose 2) = N * (N-1) / 2*, which means the running time of this solution would be O(N^2), where N is the size of *nums*.

**Memory:**

Memory usage doesn't depend on the size of *nums* (no data structures were added), so space complexity is O(1).

Be mindful of whether repeated indices are allowed (note initialization of inner loop index).

```
for (int i = 0; i < nums.length; i++) {
    for (int j = i + 1; j < nums.length; j++) {
        if (nums[i] + nums[j] == target) {
            return new int[]{i, j};
        }
    }
}
return null;
```


### Caching map solution

Note that a particular index *i* is part of the solution iff the rest of *nums* contains *i*'s "complement" value *target - nums[i]*.

As we loop through *nums*, we can build a set of elements we've seen so far. We can use this set of seen elements to check for the current element's complement. In the case that the current element's complement actually exists but we haven't seen it yet (i.e. it's located further along *nums*), the set of seen elements will contain the current element when we eventually reach the complement later on in the loop.

**Runtime:**

A hash set gives us amortized O(1) "contains" and "put" operations. Doing one "contains" and one "add" per element in *nums* gives us a O(N) running time.

Once we find a valid pair, we would need the complement's index to return the answer. So we can make the hash set into a hash map, mapping seen values to their respective indices.

**Memory:**

The hash map takes O(N) space.


### Followup: ...

....


---


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


---


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

Note the connection between Kadane's algorithm and the solution to the [Best Time to Buy and Sell Stock (Q121)](#best-time-to-buy-and-sell-stock-(q121)) problem. The uniting idea is that during a single pass through the input array, we can calculate a local max with the current index as the "stopping" point, while updating some information about what we've seen so far that will help the next index calculate its local max. The global max (the final answer) is then just the max of all the local max's.

### Followup: ...

....


---


## Maximum Product Subarray (Q152)

### Clarifying questions

| Question | Reason |
| --- | --- |
| ... | ... |

### Naive solution

The naive solution would be to check every subarray possible for the one with the maximum product.

**Runtime:**

**Memory:**


### ... solution

....

**Runtime:**

**Memory:**


### Followup: ...

....


---
