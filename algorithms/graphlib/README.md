# graphlib

This is a library for fundamental graph algorithms taught in *Skiena* and *Sedgewick*. Compared to the published code in the aforementioned books, the implementations here aim to be more flexible and intuitive by taking full advantage of the C++ language and STL.

The project setup for this library loosely follows my [CMake template](https://github.com/tedklin/cmake_sandbox).

## Notes

- *Skiena* has a list of [acknowledged errors](http://www3.cs.stonybrook.edu/~skiena/algorist/book/errata). While many errors seem to be regarding word choice, others are bugs that result in implementation incorrectness. I double checked everything I implemented from this book against this error list, but there is a chance I didn't catch all of them.
- I needed several global helper variables to circumvent inability to pass capturing lambdas as function pointers. These global variables are prefixed with "g_".
- My implementation for finding articulation vertices (and biconnectivity) is untested.
- I haven't gone too deep into the relationships between different graph algorithms; I treated most of the algorithms as distinct solutions to different problems, as they were presented in my study material. However, it seems like a lot of the more complex algorithms boil down to BFS or DFS at its core (for example, Dijkstra's shortest paths seems analogous to BFS with a priority queue). I haven't effectively explored this yet and plan to later.
