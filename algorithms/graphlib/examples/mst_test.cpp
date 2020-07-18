#include "mst.hpp"

#include <iostream>

#include "graph.hpp"

using graphlib::Edge;
using graphlib::Graph;
using graphlib::Vertex;

// Example graph provided in Sedgewick.
void prims_tiny_ewg() {
  Vertex v0("0"), v1("1"), v2("2"), v3("3"), v4("4"), v5("5"), v6("6"), v7("7");
  Graph::InputWeightedAL al = {
      {v0, {{v7, 0.16}, {v4, 0.38}, {v2, 0.26}}},
      {v1, {{v5, 0.32}, {v7, 0.19}, {v2, 0.36}, {v3, 0.29}}},
      {v2, {{v3, 0.17}, {v7, 0.34}}},
      {v3, {{v6, 0.52}}},
      {v4, {{v5, 0.35}, {v7, 0.37}}},
      {v5, {{v7, 0.28}}},
      {v6, {{v2, 0.4}, {v0, 0.58}, {v4, 0.93}}}};
  Graph graph(al, false);

  std::vector<Edge> vec = graphlib::prim_mst(&graph);
  for (const auto& e : vec) {
    std::cout << graphlib::to_string(e);
  }
  std::cout << '\n';
}

int main() {
  std::cout << "=============\n";
  std::cout << "TINY_EWG\n\n";
  prims_tiny_ewg();
}
