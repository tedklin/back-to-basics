#pragma once

#include "graph.hpp"

#include <vector>

namespace graphlib {

// Prim's algorithm ("lazy" version in Sedgewick). Assumes given graph is
// connected.
std::vector<Edge> prim_mst(Graph* graph);

}  // namespace graphlib
