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
  std::cout << "(expecting cycle error) Finding topological sort...\n";
  s = graphlib::topological_sort(&dcg);
}

void print_strong_components() {
  // Sedgewick p.589
  Vertex v0("0"), v1("1"), v2("2"), v3("3"), v4("4"), v5("5"), v6("6"), v7("7"),
      v8("8"), v9("9"), v10("10"), v11("11"), v12("12");
  Graph::InputUnweightedAL directed_al = {
      {v0, {v2, v6}},      {v1, {v0}},          {v2, {v3, v4}}, {v3, {v2, v4}},
      {v4, {v5, v6, v11}}, {v5, {v0, v3}},      {v6, {v7}},     {v7, {v8}},
      {v8, {v7}},          {v9, {v6, v8, v12}}, {v10, {v9}},    {v11, {v9}},
      {v12, {v10, v11}}};
  Graph directed_graph(directed_al, true);
  std::cout << "Finding connected components...\n";
  std::vector<std::set<const Vertex*>> components =
      graphlib::strong_components(&directed_graph);
  int counter = 1;
  for (const auto& component : components) {
    std::cout << "Component " << counter++ << ": ";
    for (const Vertex* v : component) {
      std::cout << v->name_ << " | ";
    }
    std::cout << '\n';
  }
}

int main() {
  std::cout << "============\n";
  std::cout << "CYCLE_DETECTION_CHECK\n\n";
  cycle_detection_check();

  std::cout << "============\n";
  std::cout << "PRINT_TOP_SORT\n\n";
  print_top_sort();

  std::cout << "============\n";
  std::cout << "PRINT_STRONG_COMPONENTS\n\n";
  print_strong_components();
}
