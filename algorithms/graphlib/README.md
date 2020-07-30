# graphlib

Graph theory is known as one of the most foundational topics in computer science. I can't count how many times I've been pleasantly surprised to find connections between graph theory and everyday tools / technologies. Indeed, everything from makefiles to git, from social networks to robot path planning, all can be modeled as graph problems.

This is a library for fundamental graph algorithms taught in *Skiena* and *Sedgewick*. The implementations here aim to be as flexible and intuitive as possible by taking full advantage of the C++ language and STL.

As noted in the top-level README of this repo, this is mostly meant to be a place for me to familiarize myself with / get my hands dirty with graph theory concepts. There are likely other graph libraries out there with more rigorous performance optimization, testing, and documentation.


## Notes

- The project setup for this library loosely follows my [CMake template](https://github.com/tedklin/cmake_sandbox).
- I needed several global helper variables to circumvent inability to pass capturing lambdas as function pointers. These global variables are prefixed with "g_".
- A few of my implementations are untested; these are marked with "UNTESTED!" comments in both header and source files.
- *Skiena* has a list of [acknowledged errors](http://www3.cs.stonybrook.edu/~skiena/algorist/book/errata). While many errors seem to be regarding word choice, others are bugs that result in implementation incorrectness. There is a chance I didn't catch all of them.
