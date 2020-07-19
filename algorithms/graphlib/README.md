# graphlib

This is my attempt at creating a library based on the fundamental graph theory taught in *Skiena* and *Sedgewick*. Compared to the published code in the aforementioned books, the implementations here aim to be more flexible and use more intuitive data structures.

The project setup for this library loosely follows my [CMake template](https://github.com/tedklin/cmake_sandbox).

## Notes

- *Skiena* has a list of [acknowledged errors](http://www3.cs.stonybrook.edu/~skiena/algorist/book/errata). While many errors seem to be regarding word choice, others are bugs that result in implementation incorrectness. I double checked everything I implemented from this book against this error list, but there is a chance I didn't catch all of them.
- I haven't yet fully digested the DFS algorithms related to connectivity (biconnectivity and strong components). My implementations of those remain untested, but I plan to revisit them later.
- I haven't gone too deep into the relationships between different graph algorithms; I treated most of the algorithms as distinct solutions to different problems, as they were presented in my study material. However, it seems like a lot of the more complex algorithms might boil down to BFS or DFS at its core (for example, Dijkstra's shortest paths seems analogous to BFS with a priority queue). I haven't effectively explored this yet and plan to later.
