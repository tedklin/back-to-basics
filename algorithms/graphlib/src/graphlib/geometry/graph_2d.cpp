#include "graphlib/geometry/graph_2d.hpp"

namespace graphlib {

Graph2d::Graph2d(bool is_directed) : Graph(is_directed) {}

Graph2d::Graph2d(const InputVertexSet& vertex_set, bool is_directed)
    : Graph(vertex_set, is_directed) {}

Graph2d::Graph2d(const Input2dAL& al, bool is_directed) : Graph(is_directed) {
  for (const auto& v : al) {
    Vertex2d source = v.first;
    AddVertex(source);
    for (const Vertex2d& dest : v.second) {
      AddEdge(source, dest);
    }
  }
}

void Graph2d::AddEdge(const Vertex2d& source, const Vertex2d& dest) {
  AddVertex(source);
  AddVertex(dest);

  double edge_weight = distance_2d(source, dest);
  vertex_map_[source][GetInternalVertexPtr(dest)] = edge_weight;
  if (!is_directed_) {
    vertex_map_[dest][GetInternalVertexPtr(source)] = edge_weight;
  }
}

double Graph2d::EdgeWeight(const Vertex2d& source, const Vertex2d& dest) {
  return distance_2d(source, dest);
}

}  // namespace graphlib