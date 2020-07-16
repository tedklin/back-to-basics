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

The "Graph" class defines two typenames, "AdjacencyList" and "AdjacentSet", for
internal use as the underlying data structure.

The "AdjacencyList" typename (map<Vertex, AdjacentSet>), represents a map from
each Vertex of a graph to a corresponding "AdjacentSet" type. Note that the set
of keys in the "AdjacencyList" represents the set of all vertices in the graph.

The "AdjacentSet" typename (map<const Vertex*, double>) represents the set of
neighboring vertices to an arbitrary "source" vertex (the "source" vertex is
defined by the AdjacencyList key to which an AdjacentSet is bound). The
AdjacentSet type maps each neighboring vertex with a floating point "edge
weight". Altogether, an AdjacencyList key, AdjacentSet key, and floating point
edge weight represent the concept of one edge in a graph.

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

  // TODO: do more research on if mutable is appropriate here.
  // Since the underlying implementation of Graph relies on pointers to const
  // Vertex, any Vertex data member we want to be able to modify through the
  // Graph needs to be of mutable type. This shouldn't create undefined behavior
  // because the overloaded comparison operators and hash functions we define
  // only use the name of the Vertex as the value.
  mutable State state_ = State::UNDISCOVERED;   // search state
  mutable const Vertex* parent_ = nullptr;      // search tree parent
  mutable int entry_time_ = 0, exit_time_ = 0;  // dfs
  mutable int color_ = 0;                       // bipartiteness

  // TODO: removing the const qualifier here makes it so that any const Vertex
  // object can't call reset (see add_vertex in Graph.cpp). is there a better
  // way to do this that doesn't create confusion over intention?
  void reset() const {
    state_ = State::UNDISCOVERED;
    parent_ = nullptr;
    entry_time_ = 0;
    exit_time_ = 0;
    color_ = 0;
  }
};

inline bool operator<(const Vertex& lhs, const Vertex& rhs) {
  return (lhs.name_ < rhs.name_);
}

inline bool operator==(const Vertex& lhs, const Vertex& rhs) {
  return (lhs.name_ == rhs.name_);
}

inline bool operator!=(const Vertex& lhs, const Vertex& rhs) {
  return !operator==(lhs, rhs);
}

// There is no string conversion for scoped enum members, so we define our own.
inline std::string to_string(const Vertex::State& state);

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
  // AdjacentSet depends on the pointer itself, not the pointed-to Vertex.
  // If the same edge is added more than once performance loss may occur.
  using AdjacentSet = std::map<const Vertex*, double>;
  using AdjacencyList = std::map<Vertex, AdjacentSet>;

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

  void add_vertex(const Vertex& v);

  // Obtain a pointer to a Vertex within this Graph instance. If you don't use
  // this, you are likely going to accidentally use a copy of Vertex when your
  // intention was to access the singular Vertex instance stored by this Graph
  // (i.e. the keyset of adjacency_list_).
  const Vertex* internal_vertex_ptr(const Vertex& v) const;

  void add_edge(const Vertex& source, const Vertex& dest,
                double edge_weight = 1);

  // Reset the state, color, etc, of all Vertices in this Graph instance.
  void reset_state();

  std::string vertex_set_str() const;

  std::string adjacency_list_str() const;

  const AdjacencyList& adjacency_list() const { return adjacency_list_; }

  AdjacencyList& mutable_adjacency_list() { return adjacency_list_; }

  const AdjacentSet& adjacent_set(const Vertex& source) const {
    return adjacency_list_.at(source);
  }

  AdjacentSet& mutable_adjacent_set(const Vertex& source) {
    return adjacency_list_.at(source);
  }

  bool is_directed() { return is_directed_; }

 private:
  // The keyset of adjacency_list_ represents the only copy of Vertices this
  // Graph stores.
  AdjacencyList adjacency_list_;

  bool is_directed_;
};

}  // namespace graphlib
