// Quick ad-hoc tests for core functionality

#include "graph.hpp"

#include <iostream>

void equality_op_overload() {
  Vertex v1("A");
  Vertex v2("B");
  Vertex v1_again("A");

  std::cout << (v1 == v2) << '\n';
  std::cout << (v1 == v1_again) << "\n\n";
}

void hash_overload() {
  Vertex v1("A");
  Vertex v2("B");
  Vertex v1_again("A");

  std::cout << std::hash<Vertex>{}(v1) << '\n';
  std::cout << std::hash<Vertex>{}(v2) << '\n';
  std::cout << std::hash<Vertex>{}(v1_again) << "\n\n";
}

void vertex_set_initializer() {
  Vertex v1("A"), v2("B"), v3("C");
  Graph::InputVertexSet vertex_set({v1, v2, v3});

  // TODO: why doesn't this work? isn't there an implicit conversion from string
  // to Vertex, as defined by the Vertex constructor?
  // Graph::InputVertexSet vertex_set_conv({"A", "B", "C"});

  Graph graph(vertex_set, false);
  std::cout << graph.vertex_set_str() << "\n\n";
}

void unweighted_al_initializer() {
  Vertex v1("A"), v2("B"), v3("C");

  // These two adjacency lists should be the same when the graph is undirected,
  // but different when the graph is directed.
  Graph::InputUnweightedAL unweighted_al_full(
      {{v1, {v2, v3}}, {v2, {v1, v3}}, {v3, {v1, v2}}});
  Graph::InputUnweightedAL unweighted_al_min({{v1, {v2, v3}}, {v2, {v3}}});

  Graph graph_undirected_1(unweighted_al_full, false);
  Graph graph_undirected_2(unweighted_al_min, false);
  std::cout << "full undirected\n"
            << graph_undirected_1.adjacency_list_str() << '\n';
  std::cout << "min undirected\n"
            << graph_undirected_2.adjacency_list_str() << '\n';

  Graph graph_directed_1(unweighted_al_full, true);
  Graph graph_directed_2(unweighted_al_min, true);
  std::cout << "full directed\n"
            << graph_directed_1.adjacency_list_str() << '\n';
  std::cout << "min directed\n"
            << graph_directed_2.adjacency_list_str() << '\n';
}

// The example as seen in the comment at the top of graph.hpp.
// All three literal representations should result in the same unweighted,
// undirected graph.
void example_initializer() {
  Vertex A("A"), B("B"), C("C"), D("D"), E("E");

  Graph::InputUnweightedAL rep1 = {
      {A, {D, E}}, {B, {}}, {C, {E}}, {D, {A, E}}, {E, {A, C, D}}};

  Graph::AdjacencyList rep2 = {{A, {{D, 1}, {E, 1}}},
                               {B, {}},
                               {C, {{E, 1}}},
                               {D, {{A, 1}, {E, 1}}},
                               {E, {{A, 1}, {C, 1}, {D, 1}}}};

  Graph::InputUnweightedAL rep3 = {
      {A, {D, E}}, {B, {}}, {C, {}}, {D, {E}}, {E, {C}}};

  Graph graph1(rep1, false), graph2(rep2, false), graph3(rep3, false);

  std::cout << "rep1\n" << graph1.adjacency_list_str() << '\n';
  std::cout << "rep2\n" << graph2.adjacency_list_str() << '\n';
  std::cout << "rep3\n" << graph3.adjacency_list_str() << '\n';
}

int main() {
  // equality_op_overload();
  // hash_overload();
  // vertex_set_initializer();
  // unweighted_al_initializer();
  example_initializer();
}
