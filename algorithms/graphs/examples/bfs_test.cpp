#include "bfs.hpp"
#include "graph.hpp"

#include <iostream>

void start_error_check() {
  Vertex v1("A"), v2("B"), v3("C");
  Graph graph({v1, v2, v3}, false);

  std::cout << "Not expecting error...\n\n";
  bfs(&graph, v1, nullptr, nullptr, nullptr);

  std::cout << "Not expecting error...\n\n";
  bfs(&graph, Vertex("A"), nullptr, nullptr, nullptr);

  std::cout << "Expecting error...\n";
  bfs(&graph, Vertex("D"), nullptr, nullptr, nullptr);
}

void full_bfs_check() {
  Vertex A("A"), B("B"), C("C"), D("D"), E("E");
  Graph::InputUnweightedAL input_al = {
      {A, {D, E}}, {B, {}}, {C, {}}, {D, {E}}, {E, {C}}};
  Graph graph(input_al, false);

  std::cout << "Untraversed graph " << graph.vertex_set_str() << "\n\n";

  bfs(&graph, A, print_vertex, nullptr, nullptr);

  // Here we're expecting that all vertices are in state PROCESSED (2).
  std::cout << "Traversed graph " << graph.vertex_set_str() << "\n\n";
}

int main() {
  start_error_check();
  full_bfs_check();
}
