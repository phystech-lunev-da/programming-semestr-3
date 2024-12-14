
#include <gtest/gtest.h>

#include "skiplist.hpp"

class TestSkipList : public ::testing::Test {
protected:
    unsigned seed;
    SkipList<int>* skiplist;
    void SetUp() {
        skiplist = new SkipList<int>(1000);
    }
    void TearDown() {
        delete skiplist;
    }
};

