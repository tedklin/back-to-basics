// Quick ad-hoc tests for weighted shortest path graph algorithms.

#include "graphlib/algo/weighted_paths.hpp"

#include <iostream>

#include "graphlib/graph.hpp"

using graphlib::Graph;
using graphlib::Vertex;

void tiny_ewd_dijkstras() {
  // "tiny_ewd" graph example provided in Sedgewick.
  // See expected results in Sedgewick (p.653)
  Vertex v0("0"), v1("1"), v2("2"), v3("3"), v4("4"), v5("5"), v6("6"), v7("7");
  Graph::InputWeightedAL al = {{v0, {{v4, 0.38}, {v2, 0.26}}},
                               {v1, {{v3, 0.29}}},
                               {v2, {{v7, 0.34}}},
                               {v3, {{v6, 0.52}}},
                               {v4, {{v5, 0.35}, {v7, 0.37}}},
                               {v5, {{v4, 0.35}, {v7, 0.28}, {v1, 0.32}}},
                               {v6, {{v2, 0.4}, {v0, 0.58}, {v4, 0.93}}},
                               {v7, {{v5, 0.28}, {v3, 0.39}}}};
  Graph tiny_ewd(al, true);

  std::cout << "Shortest paths parent tree:\n";
  std::cout << "search root: " << v0.name_ << '\n';
  graphlib::dijkstra(&tiny_ewd, tiny_ewd.GetInternalVertexPtr(v0));
  for (const auto& v : tiny_ewd.GetVertexMap()) {
    if (v.first != v0) {
      std::cout << v.first.name_ << " parent: " << v.first.parent_->name_
                << '\n';
    }
  }
  std::cout << '\n';

  std::cout << "Shortest weighted path from 0 to 1:\n";
  std::stack<const Vertex*> path = graphlib::shortest_pos_weight_path(
      &tiny_ewd, tiny_ewd.GetInternalVertexPtr(v0),
      tiny_ewd.GetInternalVertexPtr(v1));
  if (!path.empty()) {
    while (path.size() > 1) {
      std::cout << path.top()->name_ << " -> ";
      path.pop();
    }
    std::cout << path.top()->name_ << '\n';
  }
  std::cout << '\n';

  std::cout << "Shortest weighted path from 0 to 3:\n";
  path = graphlib::shortest_pos_weight_path(&tiny_ewd,
                                            tiny_ewd.GetInternalVertexPtr(v0),
                                            tiny_ewd.GetInternalVertexPtr(v3));
  if (!path.empty()) {
    while (path.size() > 1) {
      std::cout << path.top()->name_ << " -> ";
      path.pop();
    }
    std::cout << path.top()->name_ << '\n';
  }
  std::cout << '\n';

  std::cout << "Shortest weighted path from 0 to 6:\n";
  path = graphlib::shortest_pos_weight_path(&tiny_ewd,
                                            tiny_ewd.GetInternalVertexPtr(v0),
                                            tiny_ewd.GetInternalVertexPtr(v6));
  if (!path.empty()) {
    while (path.size() > 1) {
      std::cout << path.top()->name_ << " -> ";
      path.pop();
    }
    std::cout << path.top()->name_ << '\n';
  }
  std::cout << '\n';
}

void tiny_ewdn_bellman() {
  // "tiny_ewdn" graph example provided in Sedgewick.
  // See expected results in Sedgewick (p.676)
  Vertex v0("0"), v1("1"), v2("2"), v3("3"), v4("4"), v5("5"), v6("6"), v7("7");
  Graph::InputWeightedAL al = {{v0, {{v4, 0.38}, {v2, 0.26}}},
                               {v1, {{v3, 0.29}}},
                               {v2, {{v7, 0.34}}},
                               {v3, {{v6, 0.52}}},
                               {v4, {{v5, 0.35}, {v7, 0.37}}},
                               {v5, {{v4, 0.35}, {v7, 0.28}, {v1, 0.32}}},
                               {v6, {{v2, -1.2}, {v0, -1.4}, {v4, -1.25}}},
                               {v7, {{v5, 0.28}, {v3, 0.39}}}};
  Graph tiny_ewdn(al, true);

  std::cout << "Shortest paths parent tree:\n";
  std::cout << "search root: " << v0.name_ << '\n';
  graphlib::bellman_ford(&tiny_ewdn, tiny_ewdn.GetInternalVertexPtr(v0));
  for (const auto& v : tiny_ewdn.GetVertexMap()) {
    if (v.first != v0) {
      std::cout << v.first.name_ << " parent: " << v.first.parent_->name_
                << '\n';
    }
  }
  std::cout << '\n';

  std::cout << "Shortest weighted path from 0 to 1:\n";
  std::stack<const Vertex*> path = graphlib::shortest_weighted_path(
      &tiny_ewdn, tiny_ewdn.GetInternalVertexPtr(v0),
      tiny_ewdn.GetInternalVertexPtr(v1));
  if (!path.empty()) {
    while (path.size() > 1) {
      std::cout << path.top()->name_ << " -> ";
      path.pop();
    }
    std::cout << path.top()->name_ << '\n';
  }
  std::cout << '\n';
}

void floyd_warshall_test() {
  // Example provided here:
  // http://web.eecs.utk.edu/~jplank/plank/classes/cs494/494/notes/Floyd/index.html
  Vertex v1("1"), v2("2"), v3("3"), v4("4");
  Graph::InputWeightedAL al = {{v1, {{v3, -2}}},
                               {v2, {{v1, 4}, {v3, 3}}},
                               {v3, {{v4, 2}}},
                               {v4, {{v2, -1}}}};
  Graph graph(al, true);
  auto dist_matrix = graphlib::floyd_warshall(&graph);

  std::cout << "  1  2  3  4\n";
  std::cout << "  ==========\n";

  for (const auto& i : dist_matrix) {
    std::cout << i.first->name_ << "|";
    for (const auto& j : i.second) {
      std::cout << j.second << " ";
    }
    std::cout << '\n';
  }
  std::cout << '\n';
}

int main() {
  std::cout << "=============\n";
  std::cout << "TINY_EWD_DIJKSTRAS\n\n";
  tiny_ewd_dijkstras();

  std::cout << "=============\n";
  std::cout << "TINY_EWDN_BELLMAN\n\n";
  tiny_ewdn_bellman();

  std::cout << "=============\n";
  std::cout << "FLOYD_WARSHALL_TEST\n\n";
  floyd_warshall_test();
}
