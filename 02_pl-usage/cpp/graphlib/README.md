# graphlib

Graph theory is known as one of the most foundational topics in computer science. I can't count how many times I've been pleasantly surprised to find connections between graph theory and everyday tools / technologies. Indeed, everything from makefiles to git, from social networks to robot path planning, all can be modeled as graph problems.

There are a multitude of graph representations in code found in educational texts and online tutorials. But nearly all of them have the sole purpose of teaching algorithm concepts, so idioms like simply using integers to represent vertices is common.

This is my attempt at defining a more useful/extensible code representation of general graphs. Using this representation, I also implemented some of the graph algorithms taught in *Skiena* and *Sedgewick*. My primary goal is to be as flexible, expressive, and safe as I could by taking full advantage of the C++ language and STL. Keeping memory and performance overhead low is secondary.

As noted in the [top-level README](https://github.com/tedklin/back-to-basics) of this repo, this was mostly meant to be a place for me to build intuition for various concepts from the ground up. There are likely other formal graph libraries out there with more functionality, better performance, and complete testing.


## Notes

- The project setup for graphlib loosely follows my [CMake template](https://github.com/tedklin/cmake_sandbox).
- The [examples](https://github.com/tedklin/back-to-basics/tree/master/cpp/graphlib/examples) double as ad-hoc tests. A few of the algorithms implemented are untested; these are marked with "UNTESTED!" comments in both header and source files.
- I followed Skiena's method of passing function pointers to build algorithms off of common traversal patterns. However, I needed several global helper variables to circumvent inability to pass capturing lambdas as function pointers. These global variables are prefixed with "g_".
    - Note that these are cleared automatically by the functions that use them, but **information encoded in Vertices are not reset automatically**. This is to support the possibility of performing multiple algorithms in succession.
- Defining an extensible graph representation took more iteration than I expected. For example, an [early version](https://github.com/tedklin/back-to-basics/tree/graphlib-old/algorithms/graphlib) could not support polymorphism due to a basic oversight on my part (I was used to Java, for which polymorphism is natural because all object variables are already pointers).
