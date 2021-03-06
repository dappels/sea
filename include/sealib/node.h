#ifndef SEALIB_NODE_H_
#define SEALIB_NODE_H_

#include <sealib/adjacency.h>
#include <vector>

namespace Sealib {
/**
 * A Node object containing the nodes adjacencies and its degree.
 * @author Johannes Meintrup
 */
class Node {
 private:
    std::vector<Sealib::Adjacency> adj;

 public:
    /**
     * Creates a node out of its adjacencies.
     * @param _adj array of adjacencies.
     * @param _deg degree of this node.
    */
    Node(const Adjacency *adj_, unsigned long deg_);

    /**
     * Creates a node out of its adjacencies.
     * @param _adj vector of adjacencies.
    */
    explicit Node(const std::vector<Sealib::Adjacency> &adj_);

    Node() = default;

    /**
     * @return Returns a pointer to the adjacency array.
     */
    const std::vector<Adjacency> &getAdj() const;

    /**
     * @return Returns the degree of the node.
     */
    unsigned int getDegree() const;

    /**
     * Make a cross pointer from "this" to an "other" adjacency array
     * @param adjIndex index of endpoint in "this" adjacency array
     * @param crossIndex index of endpoint in the "other" adjacency array
     */
     void setCrossIndex(unsigned int adjIndex, unsigned int crossIndex);

     /**
      * Adds a new Adjacency.
      * @param vertex - vertex of the Adjacency.
      * Set the crossindex manually after adding a new adjacency
      */
      void addAdjacency(unsigned int vertex);
};
}  // namespace Sealib
#endif  // SEALIB_NODE_H_
