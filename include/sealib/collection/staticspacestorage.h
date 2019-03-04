#ifndef SEALIB_COLLECTION_STATICSPACESTORAGE_H_
#define SEALIB_COLLECTION_STATICSPACESTORAGE_H_
#include <vector>
#include "sealib/_types.h"
#include "sealib/collection/bitset.h"
#include "sealib/collection/sequence.h"
#include "sealib/dictionary/rankselect.h"
#include "sealib/graph/graph.h"

namespace Sealib {
/**
 * Data storage created by static space allocation. N bits of data are allocated
 * according to a bit pattern of n+N bits, where the i-th set bit is the start
 * of the i-th entry. The data is handled in a separate array with the size and
 * offset specified by the bit pattern.
 * EFFICIENCY: O(n+N) bits
 */
class StaticSpaceStorage : public Sequence<uint64_t> {
 public:
    /**
     * @param i index of the storage array
     * @return value stored in element i
     */
    uint64_t get(uint64_t i) const;

    /**
     * @param i index of the storage array
     * @param v value to insert
     */
    void insert(uint64_t i, uint64_t v);

    /**
     * Create a new storage from a bit vector.
     * @param bits bit pattern that shows the position and size of entries. The
     * bits reserved for an entry must NOT exceed 64.
     *  Example:
     *      10001001100
     *      => 4 data packs: size 3, 2, 0 and 2 bits
     */
    explicit StaticSpaceStorage(const std::vector<bool> &bits);

    /**
     * Create a new storage with O(log(deg(u)) bits for each node u in the graph
     * G.
     * @param g graph G=(V,E) to create a storage for
     */
    explicit StaticSpaceStorage(Graph const &g);

    /**
     * Convenience method to create a bit pattern from a vector of sizes
     * @param sizes a vector that holds sizes of each entry (e.g. {2,3,6,2})
     * @return bit pattern corresponding to the input vector (e.g.
     * 10010001000000100)
     */
    static std::vector<bool> makeBitVector(std::vector<uint64_t> const &sizes);

 private:
    const uint64_t n;
    const Bitset<uint8_t> pattern;
    const RankSelect rankSelect;
    std::vector<uint64_t> storage;
    static const uint64_t WORD_SIZE = sizeof(uint64_t) * 8;
    static const uint64_t one = 1;

    /**
     * Gets the bit past the end of sequence A_k.
     * @param k Number of the sequence (0,...,n-1)
     * @return Index of first bit of A_{k+1}
     */
    uint64_t getEnd(uint64_t k) const {
        return (k < n - 1) ? rankSelect.select(k + 2) : pattern.size();
    }

    /**
     * Gets the size of bit sequence A_k.
     * @param k Number of the sequence (0,...,n-1)
     * @return Size of sequence A_k
     */
    uint64_t getSize(uint64_t k) const {
        return getEnd(k) - rankSelect.select(k + 1) - 1;
    }
};
}  // namespace Sealib
#endif  // SEALIB_COLLECTION_STATICSPACESTORAGE_H_
