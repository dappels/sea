#ifndef SEALIB_GRAPH_GRAPH_H_
#define SEALIB_GRAPH_GRAPH_H_
#include <sealib/_types.h>

namespace Sealib {
/**
 * Graph is a virtual class that provides an interface for graph traversing
 * algorithms.
 * @Author Simon Schniedenharn
 */
class Graph {
 public:
    /**
    * Returns the degree of the node that v points at.
    * @param v Vertex v
    * @return Returns d that is the degree of node v.
    */
    virtual uint64_t deg(uint64_t v) const = 0;

    /**
    * Returns the vertex v that u points at with its k-th edge.
    * @param u Vertex u
    * @param k index in the adjacency vector of node u
    * @return Returns v that is the k-th neighbor of u.
    */
    virtual uint64_t head(uint64_t u, uint64_t k) const = 0;

    /**
    * @return Returns the order of the graph, i.e, the total number of vertices.
    */
    virtual uint64_t getOrder() const = 0;

 protected:
    Graph() = default;
    Graph(Graph const &) = default;
    Graph &operator=(Graph const &) = default;
    Graph(Graph &&) = default;
    Graph &operator=(Graph &&) = default;
    virtual ~Graph() = default;
};
}  // namespace Sealib
#endif  // SEALIB_GRAPH_GRAPH_H_
