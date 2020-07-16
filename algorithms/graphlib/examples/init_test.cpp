// Quick ad-hoc tests for Graph type initialization and other core
// functionality.

#include "graph.hpp"

#include <iostream>

using graphlib::Graph;
using graphlib::Vertex;

void equality_op_overload() {
  Vertex v1("A"), v2("B"), v1_again("A");

  std::cout << (v1 == v2) << '\n';
  std::cout << (v1 == v1_again) << "\n\n";
}

void hash_overload() {
  Vertex v1("A"), v2("B"), v1_again("A");

  std::cout << std::hash<Vertex>{}(v1) << '\n';
  std::cout << std::hash<Vertex>{}(v2) << '\n';
  std::cout << std::hash<Vertex>{}(v1_again) << "\n\n";
}

void vertex_set_initializer() {
  Vertex v1("A"), v2("B"), v3("C"), v1_again("A"), v2_again("B");

  // Initial states should be reset to UNDISCOVERED when passed into a graph.
  v2.state_ = Vertex::State::PROCESSED;
  v3.state_ = Vertex::State::DISCOVERED;

  // v1_again should be ignored.
  Graph graph({v1, v2, v3, v1_again}, false);

  // v2_again should be ignored.
  graph.add_vertex(v2_again);

  // Check that only A, B, and C exist in the graph, all with state UNDISCOVERED
  // (0).
  std::cout << graph.vertex_set_str() << "\n";
}

void unweighted_al_initializer() {
  Vertex v1("A"), v2("B"), v3("C");

  // These two adjacency lists should be the same when the graph is undirected,
  // but different when the graph is directed.
  Graph::InputUnweightedAL unweighted_al_full(
      {{v1, {v2, v3}}, {v2, {v1, v3}}, {v3, {v1, v2}}});
  Graph::InputUnweightedAL unweighted_al_min({{v1, {v2, v3}}, {v2, {v3}}});

  Graph graph_undirected_1(unweighted_al_full, false);  // also tests dup edges!
  Graph graph_undirected_2(unweighted_al_min, false);
  std::cout << "full undirected\n"
            << graphlib::to_string(graph_undirected_1) << '\n';
  std::cout << "min undirected\n"
            << graphlib::to_string(graph_undirected_2) << '\n';

  Graph graph_directed_1(unweighted_al_full, true);
  Graph graph_directed_2(unweighted_al_min, true);
  std::cout << "full directed\n"
            << graphlib::to_string(graph_directed_1) << '\n';
  std::cout << "min directed\n"
            << graphlib::to_string(graph_directed_2) << '\n';
}

// The example as seen in the comment at the top of graph.hpp.
// All three literal representations should result in the same unweighted,
// undirected graph.
void example_initializer() {
  Vertex A("A"), B("B"), C("C"), D("D"), E("E");

  Graph::InputUnweightedAL rep1 = {
      {A, {D, E}}, {B, {}}, {C, {E}}, {D, {A, E}}, {E, {A, C, D}}};

  Graph::InputWeightedAL rep2 = {{A, {{D, 1}, {E, 1}}},
                                 {B, {}},
                                 {C, {{E, 1}}},
                                 {D, {{A, 1}, {E, 1}}},
                                 {E, {{A, 1}, {C, 1}, {D, 1}}}};

  Graph::InputUnweightedAL rep3 = {{A, {D, E}}, {B, {}}, {D, {E}}, {E, {C}}};

  Graph graph1(rep1, false), graph2(rep2, false), graph3(rep3, false);

  std::cout << "rep1\n" << graphlib::to_string(graph1) << '\n';
  std::cout << "rep2\n" << graphlib::to_string(graph2) << '\n';
  std::cout << "rep3\n" << graphlib::to_string(graph3) << '\n';
}

int main() {
  std::cout << "=============\n";
  std::cout << "EQUALITY_OP_OVERLOAD\n\n";
  equality_op_overload();

  std::cout << "=============\n";
  std::cout << "HASH_OVERLOAD\n\n";
  hash_overload();

  std::cout << "=============\n";
  std::cout << "VERTEX_SET_INITIALIZER\n\n";
  vertex_set_initializer();

  std::cout << "=============\n";
  std::cout << "UNWEIGHTED_AL_INITIALIZER\n\n";
  unweighted_al_initializer();

  std::cout << "=============\n";
  std::cout << "EXAMPLE_INITIALIZER\n\n";
  example_initializer();
}
