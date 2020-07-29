/*
Let the following be an undirected, unweighted graph with vertices
{A, B, C, D, E}:

      A       B
      |\
      | \
      |  \
      D---E---C

The corresponding adjacency list would be:

      A -> {D, E}
      B -> {}
      C -> {E}
      D -> {A, E}
      E -> {A, C, D}

===============================================================================

The "Vertex" class represents a vertex with a string name and an optional
floating point weight. Note that "vertex weights" are a separate concept from
"edge weights", which we will see below.

The "Graph" class defines two typenames, "VertexSet" and "AdjacentSet", for
internal use as the underlying data structure.

The "VertexSet" typename (map<Vertex, AdjacentSet>), represents the set of all
Vertex instances contained in a Graph. It also maps each Vertex of a graph to a
corresponding "AdjacentSet" type.

The "AdjacentSet" typename (map<const Vertex*, double>) represents the set of
neighboring vertices to an arbitrary "source" vertex (the "source" vertex is
defined by the VertexSet key to which an AdjacentSet is bound). The
AdjacentSet type maps each neighboring vertex with a floating point "edge
weight". Altogether, an VertexSet key, AdjacentSet key, and floating point
edge weight represent the concept of one edge in a graph.

There exists an auxiliary "Edge" class, which also represents the concept of an
edge in a graph, but this is only used for specific algorithms (like finding
MSTs) and not for defining Graphs themselves.

===============================================================================

To support intuitive usage, the typenames "InputUnweightedAL" and
"InputWeightedAL" are defined for users to pass into Graph constructors.

The adjacency list in the example above could be thought of as the following
literal (of type "InputUnweightedAL"):

  rep1 = {
      {A, {D, E}},
      {B, {}},
      {C, {E}},
      {D, {A, E}},
      {E, {A, C, D}}
  }

With explicit edge weights, the adjacency list could also be thought of as the
following literal (of type "InputWeightedAL"):

  rep2 = {
      {A, {{D, 1}, {E, 1}}},
      {B, {}},
      {C, {{E, 1}}},
      {D, {{A, 1}, {E, 1}}},
      {E, {{A, 1}, {C, 1}, {D, 1}}}
  }

Note that the example is an undirected graph (i.e. existence of edge {A, D}
implies edge {D, A}). The "Graph" class automatically adds reverse edges in
undirected graphs. Thus, the following literal of type "InputUnweightedAL" would
also result in the same Graph as the above.

  rep3 = {
      {A, {D, E}},
      {B, {}},
      {D, {E}},
      {E, {C}}
  }

See the "example" function in test.cpp for verification that this works.
*/

#pragma once

#include <map>
#include <memory>
#include <set>
#include <string>

namespace graphlib {

struct Vertex {
  enum class State { UNDISCOVERED, DISCOVERED, PROCESSED };

  Vertex(const std::string& name, double weight = 1)
      : name_(name), weight_(weight) {}

  // TODO: make these const? might have to introduce explicit copy control.
  std::string name_;
  double weight_;

  // Since the underlying implementation of Graph relies on pointers to const
  // Vertex, any Vertex data member we want to be able to modify through the
  // Graph needs to be of mutable type. This shouldn't create undefined behavior
  // because the overloaded comparison operators and hash functions we define
  // only use the name of the Vertex as the value.
  mutable State state_ = State::UNDISCOVERED;        // search state
  mutable const Vertex* parent_ = nullptr;           // search tree parent
  mutable int color_ = 0;                            // two-coloring (bipartite)
  mutable int entry_time_ = 0, exit_time_ = 0;       // dfs time intervals
  mutable const Vertex* reachable_ancestor_ = this;  // dfs earliest ancestor
  mutable int tree_out_degree_ = 0;  // dfs search tree out degree

  // Note: removing the const qualifier here makes it so that any const Vertex
  // object can't call Reset (see AddVertex in Graph.cpp).
  void Reset() const {
    state_ = State::UNDISCOVERED;
    parent_ = nullptr;
    color_ = 0;
    entry_time_ = 0;
    exit_time_ = 0;
    reachable_ancestor_ = this;
    tree_out_degree_ = 0;
  }
};

// Provides ordering for storage in Graph.
inline bool operator<(const Vertex& lhs, const Vertex& rhs) {
  return (lhs.name_ < rhs.name_);
}

inline bool operator==(const Vertex& lhs, const Vertex& rhs) {
  return (lhs.name_ == rhs.name_);
}

inline bool operator!=(const Vertex& lhs, const Vertex& rhs) {
  return !operator==(lhs, rhs);
}

std::string to_string(const Vertex::State& state);

}  // namespace graphlib

// To use std::unordered_map with our self-defined Vertex type, we must overload
// std::hash.
// https://en.cppreference.com/w/cpp/container/unordered_map/unordered_map
namespace std {
template <>
struct hash<graphlib::Vertex> {
  std::size_t operator()(const graphlib::Vertex& f) const {
    return std::hash<std::string>{}(f.name_);
  }
};
}  // namespace std

namespace graphlib {

class Graph {
 private:
  // Underlying data structure types. Well-tuned unordered maps should also work
  // here if we need a performance boost. Keep in mind the ordering of the
  // AdjacentSet has no significance (it depends on the pointer itself, not the
  // pointed-to Vertex).
  using AdjacentSet = std::map<const Vertex*, double>;
  using VertexSet = std::map<Vertex, AdjacentSet>;

 public:
  // Convenience typenames used for user input; not actual underlying types.
  using InputUnweightedAL = std::map<Vertex, std::set<Vertex>>;
  using InputWeightedAL = std::map<Vertex, std::map<Vertex, double>>;
  using InputVertexSet = std::set<Vertex>;

  // Constructs an empty graph.
  Graph(bool is_directed);

  // Constructs a graph given only a set of vertices, no edges.
  Graph(const InputVertexSet& vertex_set, bool is_directed);

  // Constructs a fully specified unweighted graph.
  Graph(InputUnweightedAL unweighted_al, bool is_directed);

  // Constructs a fully specified weighted graph.
  Graph(InputWeightedAL adjacency_list, bool is_directed);

  void AddVertex(const Vertex& v);

  // Given a Vertex, obtain a pointer to the singular instance of that Vertex
  // within this Graph object (i.e. in the keyset of vertex_set_).
  const Vertex* GetInternalVertexPtr(const Vertex& v) const;

  void AddEdge(const Vertex& source, const Vertex& dest,
               double edge_weight = 1);

  // Reset the state, color, etc, of all Vertices in this Graph object.
  // This is intended for direct user usage and is *not* automatically called at
  // the start of algorithmic functions present in this library.
  void ResetState();

  // Return a new copy of this Graph, but with all edges reversed. Note that
  // this naturally only makes sense for directed graphs.
  std::shared_ptr<Graph> GetReverseGraph() const;

  std::string GetVertexSetStr() const;

  const VertexSet& GetVertexSet() const { return vertex_set_; }

  const AdjacentSet& GetAdjacentSet(const Vertex& source) const {
    return vertex_set_.at(source);
  }

  AdjacentSet& GetMutableAdjacentSet(const Vertex& source) {
    return vertex_set_.at(source);
  }

  bool IsDirected() { return is_directed_; }

 private:
  // The keyset of vertex_set_ represents the only copy of Vertices this Graph
  // stores.
  VertexSet vertex_set_;

  bool is_directed_;
};

// For a given graph, return a string displaying all vertices and corresponding
// adjacency sets.
std::string to_string(const Graph& graph);

// An auxiliary Edge class.
struct Edge {
  Edge(const Vertex* v1, const Vertex* v2, double weight)
      : v1_(v1), v2_(v2), weight_(weight) {}

  const Vertex* v1_ = nullptr;
  const Vertex* v2_ = nullptr;
  double weight_ = 0;
};

// Provides ordering for Edge min-heaps.
inline bool operator>(const Edge& lhs, const Edge& rhs) {
  return (lhs.weight_ > rhs.weight_);
}

inline std::string to_string(const Edge& edge) {
  return edge.v1_->name_ + " -> " + edge.v2_->name_ + " (" +
         std::to_string(edge.weight_) + ")\n";
}

}  // namespace graphlib
