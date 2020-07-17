// Quick ad-hoc tests for DFS-related graph algorithms.

#include "dfs.hpp"

#include <iostream>

#include "graph.hpp"

using graphlib::Graph;
using graphlib::Vertex;

void cycle_detection_check() {
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
  std::cout << "Expecting not cyclic: " << graphlib::is_cyclic(&acyclic_graph)
            << "\n\n";
}

void print_top_sort() {
  // DAG with only one possible topological sort: G, A, B, C, F, E, D
  // as seen in Figure 5.15 (p.179) in Skiena.
  Vertex A("A"), B("B"), C("C"), D("D"), E("E"), F("F"), G("G");
  Graph::InputUnweightedAL dag_al = {{A, {B, C}}, {B, {C, D}}, {C, {E, F}},
                                     {D, {}},     {E, {D}},    {F, {E}},
                                     {G, {A, F}}};
  Graph dag(dag_al, true);
  std::cout << "Finding topological sort...\n";
  std::stack<const Vertex*> s = graphlib::topological_sort(&dag);
  while (!s.empty()) {
    std::cout << s.top()->name_ << " | ";
    s.pop();
  }
  std::cout << "\n\n";

  // Example above, but with edge G->F reversed, creating a cyclic graph.
  Graph::InputUnweightedAL dcg_al = {{A, {B, C}}, {B, {C, D}}, {C, {E, F}},
                                     {D, {}},     {E, {D}},    {F, {E, G}},
                                     {G, {A}}};
  Graph dcg(dcg_al, true);
  std::cout << "Finding topological sort...\n";
  s = graphlib::topological_sort(&dcg);
}

int main() {
  std::cout << "============\n";
  std::cout << "CYCLE_DETECTION_CHECK\n\n";
  cycle_detection_check();

  std::cout << "============\n";
  std::cout << "PRINT_TOP_SORT\n\n";
  print_top_sort();
}
