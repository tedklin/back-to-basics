## Generic data structures

### Collection

Basic interfaces: `List<T>`, `Set<T>`, `Queue<T>`, `Deque<T>`

`List<T>`: Holds elements the way that they were inserted. Provides, among other things, indexed `add`/`remove`/`get`/`set`, and `contains`/`indexOf`/`remove` given an element instance (according to the `equals` method defined for the element type).

- `ArrayList<T>` implementation
    - This is a resizing array.
    - Runtime:
        - `get`/`set` is constant-time. 
        - `add`/`remove` *at the tail end* is amortized constant-time. However, `add`/`remove` *not at the tail end* is O(N) time because all elements after the inserted/removed element need to be shifted one to the right/left.
        - `contains`/`indexOf`/`remove` given an element instance (according to `equals`) is O(N) time.
    - Memory usage: Very efficient.
    - Misc hardware details: Cache-friendly (good spatial locality).
- `LinkedList<T>` implementation
    - This is a doubly-linked list with stored pointers to both the first and last elements.
    - Runtime:
        - `add`/`remove`/`get`/`set` *at either end* is constant-time.
        - `add`/`remove`/`get`/`set` *not at either end* is O(N) time (need to traverse to the specified index).
        - (The primary benefit of LinkedList) `add`/`remove` an element *as the list is being iterated over* (i.e. you have an iterator already on the element where you want to `add`/`remove`) is constant-time. In contrast, this is O(N) time for ArrayList.
        - `contains`/`indexOf`/`remove` given an element instance (according to `equals`) is O(N) time.
    - Memory usage: Not as efficient as ArrayList (overhead of having a linked list node wrapper around each element).
    - Misc hardware details: Not cache-friendly (bad spatial locality).
- Further reference: [StackOverflow thread comparing ArrayList vs LinkedList](https://stackoverflow.com/questions/322715/when-to-use-linkedlist-over-arraylist-in-java)


`Set<T>`: No duplicate elements (according to the `equals` method defined for the element type). Basic operations are `add`/`remove`/`contains`.

- `HashSet<T>` implementation
    - This is a hash set with capacity (number of "buckets") that resizes when the set's load factor (number of elements / capacity) exceeds some specified threshold (default 0.75).
        - The element type must have a [well-defined `hashCode` method](https://docs.oracle.com/javase/8/docs/api/java/lang/Object.html#hashCode--) (in addition to a [well-defined `equals` method](https://docs.oracle.com/javase/8/docs/api/java/lang/Object.html#equals-java.lang.Object-)).
            - Since under-the-hood the "bucket index" is produced by further processing the value returned by `hashCode` (e.g. modulo current capacity of the set), there is no limit on the range of values `hashCode` is allowed to return.
            - `hashCode` doesn't need to return a unique value for every different object instance, but try to make it as uniformly distributed as possible for good performance.
    - Runtime: `add`/`remove`/`contains` is constant-time on average (assuming the element type has a good hashing scheme).
- `TreeSet<T>` implementation
    - This is a balanced search-tree, which means, in addition to the semantics defined by the Set interface, you can iterate over the elements in sorted order (sorted according to the element type's Comparable interface implementation or according to a Comparator object passed in as an argument to TreeSet's constructor).
    - Runtime: `add`/`remove`/`contains` is O(log n) time.
- `LinkedHashSet` implementation
    - This is basically `HashSet<T>`, but *insertion* order is maintained using extra pointers in the style of a doubly-linked list (so iterating through the set goes in insertion order).
    - Runtime: Same as `HashSet<T>` asymptotically, with constant overhead for maintaining the doubly-linked list.
    - Memory usage: Same as `HashSet<T>` asymptotically, with overhead proportional to number of elements (from pointers for the doubly-linked list).


`Queue<T>`: Produces contained elements (`add`/`remove`/`peek`) according to some queueing policy, e.g. priority (through the `PriorityQueue<T>` implementation) or FIFO (the default).

- `PriorityQueue<T>` implementation
    - This is a min-heap, which means `remove`/`peek` returns the element with the lowest priority value (as specified by the element type's Comparable interface implementation or according to a Comparator object passed in as an argument to PriorityQueue's constructor).
    - Runtime: `add`/`remove` is O(log n) time (to maintain heap structure). `peek` is constant-time.
- `ArrayDeque<T>` and `LinkedList<T>` implementations
    - `ArrayDeque<T>` is backed by a resizing array. `LinkedList<T>` is a doubly-linked list as described above.
    - Runtime: `ArrayDeque<T>` is almost always better than `LinkedList<T>` (similar reasoning to the comparison of ArrayList and LinkedList above).
    - `LinkedList<T>` supports null elements, whereas `ArrayDeque<T>` does not.
- `Deque<T>` *subinterface*
    - Use this if you want to specify LIFO/stack-like (`push`/`pop`/`peek`) behavior.
        - It is an imperfect specification because it exposes functions for FIFO/queue-like behavior (`add`), but it is a better specification than `Stack<T>` which inherits from `Vector<T>` and exposes functions for indexed access/insertion/deletion.
    - Implemented by `ArrayDeque<T>` and `LinkedList<T>`.


### Map

Basic interface: `Map<K, V>`

- Maps keys of type K to values of type V. Provides, among other things, `put(key, value)`/`get(key)`/`containsKey(key)`/`containsValue(value)` and `remove`/`replace`/`entrySet`/`keySet`/`values`.

- `HashMap<K, V>` implementation
    - Like a `HashSet<K>`, but each element (key) is associated with a value.
    - Key type must satisfy same requirements as `HashSet<K>`.
- `TreeMap<K, V>` implementation
    - Like a `TreeSet<K>`, but each element (key) is associated with a value.
    - Key type must satisfy same requirements as `TreeSet<K>`.
- `LinkedHashMap<K, V>` implementation
    - Like a `LinkedHashSet<K>`, but each element (key) is associated with a value.
    - Key type must satisfy same requirements as `LinkedHashSet<K>`.
    - In addition to the default of keeping elements in insertion order, there is the option to instead keep elements in least-recently-used (LRU) order (configured in constructor).
- `WeakHashMap<K, V>` implementation
    - Does not behave like a "normal" map; used for certain types of problems.


### General notes

- Reminder to take advantage of polymorphism! Say you have a piece of code that operates on a list (and only uses the methods specified by the List interface). Even if you are currently confident that an ArrayList will result in the best performance, use `List<T> l = new ArrayList<T>` instead of `ArrayList<T> l = new ArrayList<T>` for flexibility down the road.

- Any Collection/Map can be directly printed (they have well-defined `toString` methods).

- Iterating through a Collection:
    - Iterator example:
        ```
        List<T> list = new ArrayList<>(Arrays.asList(new T[]{a, b, c}));
        Iterator<T> iter = list.iterator();
        while (iter.hasNext()) {
            T item = iter.next();
            // do work per item.
            // remove item if it matches the object instance we are looking for.
            if (item.equals(objectToRemove)) {
                // according to the Iterable spec, "remove" removes the most recent element returned by this iterator.
                iter.remove();
            }
        }
        ```
        - Notice iterator usage is agnostic to the underlying Collection type; this is another mechanism for polymorphic-like behavior.
        - `ListIterator` is a more powerful subtype of `Iterator` that is only produced by classes implementing the `List` interface via the `listIterator` method.
    - For-each example:
        ```
        List<T> list = new ArrayList<>(Arrays.asList(new T[]{a, b, c}));
        for (T item : list) {
            // do work per item.
        }
        ```
        - The for-each syntax can be used on native arrays and any type that implements the `Iterable` interface (providing an `Iterator`), including all Collection types. **Note that Maps don't directly implement `Iterable`; instead Maps provide Collection-type views through `entrySet`/`keySet`/`values`.**

- Element types should have a [well-defined `equals` method](https://docs.oracle.com/javase/8/docs/api/java/lang/Object.html#equals-java.lang.Object-).
    - In general, if you override `equals` you should override `hashCode` too (see the `HashSet<T>` section for details). But if you're writing a tiny toy program not meant for real use under a time constraint (e.g. Leetcode) and you're not planning to use a HashSet/HashMap with this element/key type, you can probably get away with not overriding `hashCode`.

- Any Collection/Map that relies on ordering through the element type's Comparable interface implementation (e.g. TreeSet/TreeMap without a passed-in Comparator object) won't support holding null values.
    - From the Java docs for [Comparable](https://docs.oracle.com/javase/8/docs/api/java/lang/Comparable.html): "`null` is not an instance of any class, so `elem.compareTo(null)` throws a NullPointerException".

- In general, implementations of `compareTo` (Comparable interface) and `compare` (Comparator class) should return zero *if and only if* the two objects being compared are `equals` to each other.
    - Otherwise, a Collection/Map that interally maintains the ordering defined by the element type's Comparable interface implementation or a passed-in Comparator object (e.g. TreeSet/TreeMap) may exhibit unexpected behavior.
    <!-- - For further details, refer to the Java docs for [Comparable](https://docs.oracle.com/javase/8/docs/api/java/lang/Comparable.html) and [Comparator](https://docs.oracle.com/javase/8/docs/api/java/util/Comparator.html).
    - From the [Java docs for TreeSet](https://docs.oracle.com/javase/8/docs/api/java/util/TreeSet.html): "Note that the ordering maintained by a set (through the element type's Comparable interface implementation or the passed-in Comparator object) must be consistent with `equals` if it is to correctly implement the Set interface." -->

- `Collections.` [static utility methods](https://docs.oracle.com/javase/7/docs/api/java/util/Collections.html), e.g. reverse/sort/rotate/swap, unmodifiable, max/min/binarySearch.


## String

- [Java docs for `String`](https://docs.oracle.com/javase/8/docs/api/java/lang/String.html)

- `String`s are immutable.
    - Utility methods that "transform" a `String` actually just return a new one (the passed-in `String` never changes).

- Java overloads the `+` and `+=` operators to mean concatenation for `String`s.
    - Conceptually, under the hood, a [`StringBuilder`](https://docs.oracle.com/javase/8/docs/api/java/lang/StringBuilder.html) instance is created for each *statement* that `+` `String`s together. This means having `+` in the body of long loops may be inefficient (a new `StringBuilder` may be created on each iteration); alternatively you can explicitly create one `StringBuilder` instance outside the loop and use it to "build" the String inside the loop.

- Options for printing to output include `System.out.println` (normal) and `System.out.format` (C-style printing with format specifiers).


### Regex


### Scanner


