// Quick ad-hoc tests for DFS-related graph algorithms.

#include "dfs.hpp"

#include <iostream>

#include "graph.hpp"

using graphlib::Graph;
using graphlib::Vertex;

void cycle_detection() {
  // Example seen in comment at the top of graph.hpp
  // (A-D-E form a cycle)
  Vertex A("A"), B("B"), C("C"), D("D"), E("E");
  Graph::InputUnweightedAL cyclic_al = {
      {A, {D, E}}, {B, {}}, {D, {E}}, {E, {C}}};
  Graph cyclic_graph(cyclic_al, false);
  std::cout << "Expecting cyclic: " << graphlib::is_cyclic(&cyclic_graph)
            << '\n';

  // Example above, but without the edge connecting A and D.
  Graph::InputUnweightedAL acyclic_al = {{A, {E}}, {B, {}}, {D, {E}}, {E, {C}}};
  Graph acyclic_graph(acyclic_al, false);
  std::cout << "Expecting cyclic: " << graphlib::is_cyclic(&acyclic_graph)
            << "\n\n";
}

int main() {
  std::cout << "============\n";
  std::cout << "CYCLE_DETECTION\n\n";
  cycle_detection();
}
