#include <string>
#include <unordered_map>
#include <unordered_set>

/**
 * This is my attempt at defining a graph class type from scratch, based on
 * concepts in Skiena but using different underlying data structures. The
 * primary goal is to be as intuitive as possible, possibly at the expense of
 * space overhead.
 *
 * The concept of weights is supported but optional. Unweighted graphs simply
 * use implicit default values of 1.
 */

/*
  Let the following be an undirected, unweighted graph with vertices
  {A, B, C, D, E}:

        A       B
        |\
        | \
        |  \
        D---E---C


  The corresponding adjacency list would be:

        A -> D, E
        B -> (none)
        C -> E
        D -> A, E
        E -> A, D, C

  =============================================================================

  The "Vertex" class represents a vertex with a string name and an optional
  floating point weight. Note that vertex weights are a separate concept from
  edge weights, which we will see below.

  The "Graph" class defines an "AdjacencyList" typename (unordered_map<Vertex,
  EdgeSet>), which maps each vertex of a graph to a corresponding "EdgeSet"
  type. Note that the set of keys in the "AdjacencyList" represents the set of
  all vertices in the graph.

  The "Graph" class also defines the "EdgeSet" typename (unordered_map<Vertex,
  double>), which represents the set of neighboring vertices with edges to an
  arbitrary "source" vertex (the "source" vertex is defined by the AdjacencyList
  key to which an EdgeSet is bound). The underlying data structure for the
  EdgeSet type is a map to support associating edges with floating point
  weights.

  Thus, the adjacency list in the example above could be thought of abstractly
  as the following literal:

    {
        {A, {D, E}},
        {B, {}},
        {C, {E}},
        {D, {A, E}},
        {E, {A, D, C}}
    }

  The actual underlying AdjacencyList structure stored by the class (includes
  implicit weights of 1 for an unweighted graph) would have a literal
  representation of:

    {
        {A, {{D, 1}, {E, 1}}},
        {B, {}},
        {C, {{E, 1}}},
        {D, {{A, 1}, {E, 1}}},
        {E, {{A, 1}, {D, 1}, {C, 1}}}
    }

  Both can be passed in as a literal initializers for the "Graph" class, with
  the first implicitly resulting in an unweighted graph with the second
  underlying structure.

 */

class Vertex {
 public:
  enum State { UNDISCOVERED, DISCOVERED, PROCESSED };

  Vertex(const std::string& name, double weight = 1)
      : name_(name), weight_(weight) {}

  bool operator==(const Vertex& rhs) { return (name_ == rhs.name_); }
  bool operator!=(const Vertex& rhs) { return !operator==(rhs); }

  std::string name_;
  double weight_;
  State state_ = State::UNDISCOVERED;
};

// Overload std::hash for our self-defined Vertex type.
// https://en.cppreference.com/w/cpp/container/unordered_map/unordered_map
namespace std {
template <>
struct hash<Vertex> {
  std::size_t operator()(const Vertex& f) const {
    return std::hash<std::string>{}(f.name_);
  }
};
}  // namespace std

class Graph {
 public:
  using EdgeSet = std::unordered_map<Vertex, double>;
  using AdjacencyList = std::unordered_map<Vertex, EdgeSet>;

  Graph(bool is_directed) : is_directed_(is_directed) {}

  // Creates a graph given only a set of vertices, no edges.
  Graph(std::unordered_set<Vertex> vertex_set, bool is_directed)
      : is_directed_(is_directed) {}

  // Creates a graph without specified edge weights.
  Graph(std::unordered_map<Vertex, std::unordered_set<Vertex>> unweighted_al,
        bool is_directed)
      : is_directed_(is_directed) {}

  Graph(AdjacencyList adjacency_list, bool is_directed)
      : adjacency_list_(adjacency_list), is_directed_(is_directed) {}

  void add_edge(const Vertex& start, const Vertex& end,
                double edge_weight = 1) {}

  void add_vertex(const Vertex& v, double vertex_weight = 1) {}

 private:
  AdjacencyList adjacency_list_;
  bool is_directed_;
};
