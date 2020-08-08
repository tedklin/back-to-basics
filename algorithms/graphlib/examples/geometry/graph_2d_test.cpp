// Quick ad-hoc checks to make sure algorithms can run on the 2d geometric
// extensions of core Vertex and Graph types. Currently does NOT test for
// correctness of algorithm logic itself! (See tests for algorithm correctness
// using core Graph types in "examples/algo/")

#include "graphlib/geometry/graph_2d.hpp"

#include <iostream>
#include <random>

#include "graphlib/algo/mst.hpp"
#include "graphlib/algo/weighted_paths.hpp"
#include "graphlib/graph.hpp"

using graphlib::Edge;
using graphlib::Graph2d;
using graphlib::Vertex;
using graphlib::Vertex2d;

void distance_test() {
  Vertex2d v1(3, 0), v2(0, 4);
  std::cout << "distance between " + v1.name_ + " and " + v2.name_ + ": " +
                   std::to_string(graphlib::distance_2d(v1, v2)) + "\n\n";
}

void mst_check() {
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_real_distribution<double> distribution(-10, 10);

  Vertex2d v1(distribution(mt), distribution(mt)),
      v2(distribution(mt), distribution(mt)),
      v3(distribution(mt), distribution(mt)),
      v4(distribution(mt), distribution(mt)),
      v5(distribution(mt), distribution(mt));

  Graph2d graph({{v1, {v2, v3}}, {v2, {v4, v5}}, {v3, {v4, v5}}, {v4, {v5}}},
                false);

  std::cout << "MST found by Prim's algorithm:\n";
  std::vector<Edge> prims_output = graphlib::prim_mst(&graph);
  for (const auto& e : prims_output) {
    std::cout << graphlib::to_string(e);
  }
  std::cout << '\n';

  std::cout << "MST found by Kruskal's algorithm:\n";
  graph.ResetState();
  std::vector<Edge> kruskals_output = graphlib::kruskal_mst(&graph);
  for (const auto& e : kruskals_output) {
    std::cout << graphlib::to_string(e);
  }
  std::cout << '\n';
}

void dijkstras_check() {
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_real_distribution<double> distribution(-10, 10);

  Vertex2d v0(distribution(mt), distribution(mt)),
      v1(distribution(mt), distribution(mt)),
      v2(distribution(mt), distribution(mt)),
      v3(distribution(mt), distribution(mt)),
      v4(distribution(mt), distribution(mt)),
      v5(distribution(mt), distribution(mt)),
      v6(distribution(mt), distribution(mt)),
      v7(distribution(mt), distribution(mt));

  Graph2d::Input2dAL al = {
      {v0, {v4, v2}}, {v1, {v3}},         {v2, {v7}},         {v3, {v6}},
      {v4, {v5, v7}}, {v5, {v4, v7, v1}}, {v6, {v2, v0, v4}}, {v7, {v5, v3}}};
  Graph2d graph(al, true);

  std::cout << "Shortest paths parent tree:\n";
  std::cout << "search root: " << v0.name_ << '\n';
  graphlib::dijkstra(&graph, graph.GetVertexPtr(v0));
  for (const auto& v : graph.GetVertexMap()) {
    if (v.first != graph.GetVertexPtr(v0)) {
      std::cout << v.first->name_ << " parent: " << v.first->parent_->name_
                << '\n';
    }
  }
  std::cout << '\n';

  std::cout << "Shortest weighted path from 0 to 1:\n";
  std::stack<std::shared_ptr<const Vertex>> path =
      graphlib::shortest_pos_weight_path(&graph, graph.GetVertexPtr(v0),
                                         graph.GetVertexPtr(v1));
  if (!path.empty()) {
    while (path.size() > 1) {
      std::cout << path.top()->name_ << " -> ";
      path.pop();
    }
    std::cout << path.top()->name_ << '\n';
  }
  std::cout << '\n';

  std::cout << "Shortest weighted path from 0 to 3:\n";
  path = graphlib::shortest_pos_weight_path(&graph, graph.GetVertexPtr(v0),
                                            graph.GetVertexPtr(v3));
  if (!path.empty()) {
    while (path.size() > 1) {
      std::cout << path.top()->name_ << " -> ";
      path.pop();
    }
    std::cout << path.top()->name_ << '\n';
  }
  std::cout << '\n';

  std::cout << "Shortest weighted path from 0 to 6:\n";
  path = graphlib::shortest_pos_weight_path(&graph, graph.GetVertexPtr(v0),
                                            graph.GetVertexPtr(v6));
  if (!path.empty()) {
    while (path.size() > 1) {
      std::cout << path.top()->name_ << " -> ";
      path.pop();
    }
    std::cout << path.top()->name_ << '\n';
  }
  std::cout << '\n';
}

int main() {
  std::cout << "=============\n";
  std::cout << "DISTANCE_TEST\n\n";
  distance_test();

  std::cout << "=============\n";
  std::cout << "MST_CHECK\n\n";
  mst_check();

  std::cout << "=============\n";
  std::cout << "DIJKSTRAS_CHECK\n\n";
  dijkstras_check();
}
