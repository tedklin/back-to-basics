// Quick ad-hoc tests for BFS-related graph algorithms.

#include "bfs.hpp"
#include "graph.hpp"

#include <iostream>
#include <map>
#include <stack>

using graphlib::Graph;
using graphlib::Vertex;

void start_error_check() {
  Vertex v1("A"), v2("B"), v3("C");
  Graph graph({v1, v2, v3}, false);

  std::cout << "Not expecting error...\n\n";
  graphlib::bfs(&graph, graph.internal_vertex_ptr(v1));

  std::cout << "Not expecting error...\n\n";
  graphlib::bfs(&graph, graph.internal_vertex_ptr(Vertex("A")));

  std::cout << "Expecting error...\n";
  try {
    graphlib::bfs(&graph, graph.internal_vertex_ptr(Vertex("D")));
  } catch (std::runtime_error e) {
    std::cout << "Caught runtime exception:\n" << e.what() << '\n';
  }
}

void bfs_traverse_check() {
  // Example seen in comment at the top of graph.hpp
  Vertex A("A"), B("B"), C("C"), D("D"), E("E");
  Graph::InputUnweightedAL input_al = {
      {A, {D, E}}, {B, {}}, {D, {E}}, {E, {C}}};
  Graph graph(input_al, false);

  std::cout << "Untraversed graph\n" << graph.vertex_set_str() << "\n";

  graphlib::bfs(&graph, graph.internal_vertex_ptr(A), graphlib::print_vertex,
                nullptr, nullptr);

  // Here we're expecting all vertices connected to Vertex A to be in state
  // PROCESSED (2).
  std::cout << "\nTraversed graph\n" << graph.vertex_set_str() << "\n\n";
}

void print_shortest_path() {
  // Example seen in comment at the top of graph.hpp
  Vertex A("A"), B("B"), C("C"), D("D"), E("E");
  Graph::InputUnweightedAL input_al = {
      {A, {D, E}}, {B, {}}, {D, {E}}, {E, {C}}};
  Graph graph(input_al, false);

  std::cout << "Shortest path from A to C:\n";
  std::stack<const Vertex*> path = graphlib::shortest_path(
      &graph, graph.internal_vertex_ptr(A), graph.internal_vertex_ptr(C));
  if (!path.empty()) {
    while (path.size() > 1) {
      std::cout << path.top()->name_ << " -> ";
      path.pop();
    }
    std::cout << path.top()->name_ << "\n\n";
  }

  std::cout << "Shortest path from A to B:\n";
  path = graphlib::shortest_path(&graph, graph.internal_vertex_ptr(A),
                                 graph.internal_vertex_ptr(B));
  if (!path.empty()) {
    while (path.size() > 1) {
      std::cout << path.top()->name_ << " -> ";
      path.pop();
    }
    std::cout << path.top()->name_ << "\n\n";
  }
}

void print_connected_components() {
  // Example seen in comment at the top of graph.hpp,
  // but with added vertex F connected to B to create two connected components.
  Vertex A("A"), B("B"), C("C"), D("D"), E("E"), F("F");
  Graph::InputUnweightedAL input_al = {
      {A, {D, E}}, {B, {F}}, {D, {E}}, {E, {C}}};
  Graph graph(input_al, false);

  auto components = graphlib::connected_components(&graph);
  int i = 1;
  for (auto component : components) {
    std::cout << "Component " << i << ":\n";
    for (Vertex v : component) {
      std::cout << v.name_ << " | ";
    }
    std::cout << '\n';
    ++i;
  }
  std::cout << '\n';
}

void bipartite_check() {
  // Bipartite undirected graph example:
  //    A---B
  //    |   |
  //    C---D
  Vertex A("A"), B("B"), C("C"), D("D");
  Graph::InputUnweightedAL bipartite_al = {{A, {B, C}}, {D, {B, C}}};
  Graph bipartite_graph(bipartite_al, false);
  std::cout << "expecting bipartite:\n"
            << graphlib::is_bipartite(&bipartite_graph) << "\n\n";

  // Non bipartite undirected graph example:
  //    A---B
  //    | \ |
  //    C---D
  Graph::InputUnweightedAL nonbipartite_al = {{A, {B, C, D}}, {D, {B, C}}};
  Graph nonbipartite_graph(nonbipartite_al, false);
  std::cout << "expecting non bipartite:\n"
            << graphlib::is_bipartite(&nonbipartite_graph) << "\n\n";
}

int main() {
  std::cout << "============\n";
  std::cout << "START_ERROR_CHECK\n\n";
  start_error_check();

  std::cout << "============\n";
  std::cout << "BFS_TRAVERSE_CHECK\n\n";
  bfs_traverse_check();

  std::cout << "============\n";
  std::cout << "PRINT_SHORTEST_PATH\n\n";
  print_shortest_path();

  std::cout << "============\n";
  std::cout << "PRINT_CONNECTED_COMPONENTS\n\n";
  print_connected_components();

  std::cout << "============\n";
  std::cout << "BIPARTITE_CHECK\n\n";
  bipartite_check();
}
