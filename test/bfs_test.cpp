#include "sealib/iterator/bfs.h"
#include <gtest/gtest.h>
#include <stdio.h>
#include "sealib/_types.h"
#include "sealib/graph/graph.h"
#include "sealib/graph/graphcreator.h"

using namespace Sealib;  // NOLINT

static uint64_t c1 = 0, c2 = 0;
static void incr1(uint64_t) { c1++; }
static void incr2(uint64_t, uint64_t) { c2++; }

static uint64_t GRAPHCOUNT = 4, order = 500, degree = 20;
static std::vector<DirectedGraph> makeGraphs() {
    std::vector<DirectedGraph> g;
    for (uint64_t c = 0; c < GRAPHCOUNT; c++) {
        g.emplace_back(GraphCreator::kOutdegree(order, degree));
    }
    return g;
}

class BFSTest : public ::testing::TestWithParam<DirectedGraph> {
 protected:
    virtual void SetUp() { c1 = c2 = 0; }
};

INSTANTIATE_TEST_CASE_P(ParamTests, BFSTest, ::testing::ValuesIn(makeGraphs()),
                        /**/);

TEST_P(BFSTest, userproc) {
    DirectedGraph g = GetParam();
    BFS bfs(g, incr1, incr2);
    EXPECT_EQ(bfs.more(), false);
    EXPECT_THROW(bfs.next(), NoMoreGrayNodes);
    bfs.init();
    bfs.forEach([](std::pair<uint64_t, uint64_t>) {});
    EXPECT_EQ(c1, order);
    EXPECT_EQ(c2, order * degree);
}

TEST(BFSTest, nextComponent) {
    c1 = c2 = 0;
    DirectedGraph g = GraphCreator::kOutdegree(order, 0);
    BFS bfs(g, incr1, incr2);
    uint64_t rc = 0;
    bfs.init();
    bfs.forEach([&](std::pair<uint64_t, uint64_t>) { rc++; });
    EXPECT_EQ(rc, order);
    EXPECT_EQ(c1, order);
    EXPECT_EQ(c2, 0);
}
