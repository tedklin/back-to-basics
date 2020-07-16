# graphlib

This is my attempt at implementing a graph library completely from scratch,
based on concepts in *Skiena* but using different underlying data structures from STL.

My primary goal is to be as intuitive as possible, at the potential
expense of space overhead.

The project setup for this library was created based on [my CMake template](https://github.com/tedklin/cmake_sandbox).

**Note: *Skiena* has a list of [acknowledged errors](http://www3.cs.stonybrook.edu/~skiena/algorist/book/errata). While most errors seem to be regarding word choice, others are significant mistakes that result in implementation incorrectness. I double checked everything I implemented based on the book's pseudocode against this error list, but there is a chance I didn't catch all of them.**
