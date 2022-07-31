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
