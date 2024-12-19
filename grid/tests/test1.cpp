
#include "grid.hpp"
#include <cassert>
#include <gtest/gtest.h>

class FloatGridTest : public ::testing::Test {
protected:
    void SetUp() {
        g = new Grid<float>(3, 2, 0.0f);
    }
    void TearDown() {
        delete g;
    }

    Grid<float> *g;
};

class Vec2GridTest : public ::testing::Test {
protected:
    void SetUp() {
        g = new Grid<Vec2>(3, 2, Vec2(0.0f, 0.0f));
    }
    void TearDown() {
        delete g;
    }

    Grid<Vec2> *g;
};

TEST_F(FloatGridTest, floatgrid_xsize_is_3) {ASSERT_EQ(3, g->get_x_size());}
TEST_F(FloatGridTest, floatgrid_ysize_is_2) {ASSERT_EQ(2, g->get_y_size());}

TEST_F(Vec2GridTest, vecgrid_xsize_is_3) {ASSERT_EQ(3, g->get_x_size());}
TEST_F(Vec2GridTest, vecgrid_ysize_is_2) {ASSERT_EQ(2, g->get_y_size());}