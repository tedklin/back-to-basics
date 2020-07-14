#include "bfs.hpp"
#include "graph.hpp"

#include <iostream>

void start_iter_check() {
  Vertex v1("A"), v2("B"), v3("C");
  Graph graph({v1, v2, v3}, false);

  std::cout << "Not expecting error...\n\n";
  bfs(&graph, v1, nullptr, nullptr, nullptr);

  std::cout << "Not expecting error...\n\n";
  bfs(&graph, Vertex("A"), nullptr, nullptr, nullptr);

  std::cout << "Expecting error...\n";
  bfs(&graph, Vertex("D"), nullptr, nullptr, nullptr);
}

int main() {
  start_iter_check();
  // more stuff
}
