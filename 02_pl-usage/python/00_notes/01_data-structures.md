# Common data structures in Python

Note that when we say "analogous to", we are discussing simplified classic mental models of the actual implementation (e.g. even though the actual implementation of Python Lists use a more advanced resizing policy, thinking of them as geometrically resizing arrays is accurate enough for our purposes).

References:
- *Data Structures and Algorithms in Python* by Goodrich, Tamassia, Goldwasser
- [Common Python Data Structures ](https://realpython.com/python-data-structures/)
- [How to deal with lack of built-in TreeMap in Python](https://algo.monster/problems/python-treemap)


### List

- Analogous to: geometrically resizing array.
    - e.g. Java ArrayList,  C++ vector.

| Operation | Time | Space | Description |
| --- | --- | --- | --- |
| `len(lst)` | O(1) | O(1) | Get length of `lst` via cached integer. |
| `lst[i]` | O(1) | - | Read or write `i`th element of `lst`. |

