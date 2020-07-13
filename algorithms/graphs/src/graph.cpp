// Graph class member implementations

#include "graph.hpp"

Graph::Graph(bool is_directed) : is_directed_(is_directed) {}

Graph::Graph(const InputVertexSet& vertex_set, bool is_directed)
    : is_directed_(is_directed) {
  for (const Vertex& v : vertex_set) {
    add_vertex(v);
  }
}

Graph::Graph(InputUnweightedAL unweighted_al, bool is_directed)
    : is_directed_(is_directed) {
  for (const auto& p : unweighted_al) {
    Vertex source = p.first;
    add_vertex(source);
    for (const Vertex& dest : p.second) {
      add_edge(source, dest);
    }
  }
}

Graph::Graph(AdjacencyList adjacency_list, bool is_directed)
    : adjacency_list_(adjacency_list), is_directed_(is_directed) {}

inline void Graph::add_vertex(const Vertex& v) { adjacency_list_[v]; }

void Graph::add_edge(const Vertex& source, const Vertex& dest,
                     double edge_weight) {
  add_vertex(source);
  add_vertex(dest);

  adjacency_list_[source][dest] = edge_weight;
  if (!is_directed_) {
    adjacency_list_[dest][source] = edge_weight;
  }
}

std::string Graph::vertex_set_str() const {
  std::string s("Vertex set:\n");
  for (const auto& p : adjacency_list_) {
    s += p.first.name_ + " | ";
  }
  s += '\n';
  return s;
}

std::string Graph::adjacency_list_str() const {
  std::string s("Adjacency list:\n");
  for (const auto& p : adjacency_list_) {
    s += p.first.name_ + " -> ";
    for (const auto& e : p.second) {
      // recall e.second is weight
      s += e.first.name_ + "(" + std::to_string(e.second) + ") | ";
    }
    s += '\n';
  }
  s += '\n';
  return s;
}
