# Algorithm analysis

The "efficiency" of an algorithm usually refers to
- its running time w.r.t. input (time complexity)
- the amount of memory it takes up w.r.t. input (space complexity).

Here we are focusing on the *basic asymptotic analysis* of algorithm efficiency. We make mathematical approximations where appropriate, and we intentionally ignore the details of underlying hardware, compilers, etc. This makes our analysis simpler and more general.


## General procedure for analyzing an algorithm's running time

The overarching question we want to answer through our analysis is: *how does a given algorithm's running time vary w.r.t. properties of its inputs?*

1. Define an input model. An input model = the input type (e.g. array, graph, sequence of requests, etc) + variable properties of the input that can significantly affect running time. Focus on properties related to input *size* (e.g. number of elements in the input array, number of vertices in the input graph, number of requests in the input sequence, etc).
    - For completeness, consider characteristics like the specific contents of the input (e.g. specific contents in input array or specific order of requests in input sequence). We usually default to setting these kinds of characteristics to be the worst possible case, in order to provide *absolute guarantees* about algorithm efficiency. But there are also many situations where we want to consider the average case and give *probabilistic guarantees* about algorithm efficiency (classic examples are [quicksort](https://en.wikipedia.org/wiki/Quicksort) and [hash tables](https://en.wikipedia.org/wiki/Hash_table)).

2. Define a cost model. A cost model = small snippets of the algorithm (usually single operations like memory accesses, comparisons, or function calls) whose frequency of execution captures the bulk of the algorithm's computation time. Focus on operations in the innermost loops or recursive calls.

3. Determine the number of times the operations in our cost model are executed w.r.t the properties identified in our input model. This serves as an approximate representation of the algorithm's running time.

4. Simplify the result of step 3 as follows to get the *order of growth* of the algorithm's running time. Use this order of growth as a baseline characterization of the algorithm's running time.
    - Throw away low-order terms. These generally become insignificant as input sizes grow large.
        - ```3N^2 + 61N + 162``` simplifies to ```3N^2```
    - Throw away constant scaling factors. These generally become insignificant (overpowered by differences in order of growth) as input sizes grow large. Furthermore, constant scaling factors can be dependent on machine-specific or input-specific characteristics, which complicates our models / analysis.
        - ```3N^2``` simplifies to ```N^2```
        - ```log base 2 of N``` simplifies to ```log(N)```

Note that this simplified analysis may hide many details about the true performance of the algorithm. Depending on the situation, certain simplifications (e.g. throwing away low-order terms with large constants) may sometimes lead to inconsistent or inexplicable analyses.

However, in general, this procedure serves as a nice easy way to reason about and compare algorithm efficiency.


### Examples of steps 1-3 of above procedure

(from *Sedgewick*, p184)

![procedure-example.png](assets/images/01_analysis/procedure-example.png)


## Visualizing orders of growth

(from *Sedgewick*, p188)

![visualizing-orders.png](assets/images/01_analysis/visualizing-orders.png)


## Formal notation for asymptotic analysis

[Explanation of Big Theta and Big O from CS61B](https://www.youtube.com/watch?v=CGdubALgQw4&list=PL8FaHk7qbOD4oAdQOZ765z6aeqyKs2593&index=8)

[Explanation of "Big O" vs "Worst case" from CS61B](https://www.youtube.com/watch?v=0SCtnf84QrI&list=PL8FaHk7qbOD41EHkD7CgQuRw1jpH_Fv7-&index=4)


## Some relevant math background

(from *Sedgewick*, p185)

![relevant-math.png](assets/images/01_analysis/relevant-math.png)


## Amortized analysis

[Methods for amortized analysis from Cornell's CS3110](https://www.cs.cornell.edu/courses/cs3110/2011sp/Lectures/lec20-amortized/amortized.htm)
