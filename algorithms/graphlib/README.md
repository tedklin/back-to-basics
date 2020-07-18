# graphlib

This is my attempt at creating a graph library based on the fundamental graph theory concepts taught in *Skiena* and *Sedgewick*. Compared to the published code in the aforementioned books, the implementations in this library aim to be more flexible and use more intuitive data structures, at the potential expense of space overhead.

The project setup for this library was created based on [my CMake template](https://github.com/tedklin/cmake_sandbox).

## Notes

- *Skiena* has a list of [acknowledged errors](http://www3.cs.stonybrook.edu/~skiena/algorist/book/errata). While many errors seem to be regarding word choice, others are bugs that result in implementation incorrectness. I double checked everything I implemented based on this book against this error list, but there is a chance I didn't catch all of them.
- I haven't fully digested the DFS algorithms related to connectivity (biconnectivity and strong components) yet. My implementations of those remain untested, and I plan to revisit them later.
