**IMPORTANT NOTE: The implementation of graphlib here (on the graphlib-old-2 branch of this repo) is outdated. An updated version of graphlib with better ownership semantics can be found on the master branch of this repo). Please refer to that version.

# graphlib

Graph theory is known as one of the most foundational topics in computer science. I can't count how many times I've been pleasantly surprised to find connections between graph theory and everyday tools / technologies. Indeed, everything from makefiles to git, from social networks to robot path planning, all can be modeled as graph problems.

This is a library for fundamental graph algorithms taught in *Skiena* and *Sedgewick*. The implementations here aim to be as flexible and intuitive as possible by taking full advantage of the C++ language and STL.

As noted in the [top-level README](https://github.com/tedklin/back-to-basics/tree/graphlib-dev) of this repo, this was mostly meant to be a place for me to build intuition for various concepts from the ground up. There are likely other formal graph libraries out there with more functionality, better performance, and complete testing.


## Notes

- The project setup for this library loosely follows my [CMake template](https://github.com/tedklin/cmake_sandbox).
- I have yet to optimize my usage of shared_ptr. If in need for speed, consider finding appropriate places where shared_ptr can be safely passed by reference instead of by value, and/or change shared_ptrs to raw pointers where lifetime can be safely ignored (e.g. intermediate steps in algorithms).
    - There are most likely many other types of optimizations I missed, but this is the most glaring one I can think of.
- I needed several global helper variables to circumvent inability to pass capturing lambdas as function pointers. These global variables are prefixed with "g_".
    - Note that these are cleared automatically by the functions that use them, but **information encoded in Vertices are not reset automatically**. This is to support the possibility of performing multiple algorithms in succession.
- A few of my implementations are untested; these are marked with "UNTESTED!" comments in both header and source files.
