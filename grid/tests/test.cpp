
#include <gtest/gtest.h>

class TestAdd : public ::testing::Test {
protected:
    void SetUp() {}
    void TearDown() {}
};

TEST_F(TestAdd, TwoPlusTwo) { ASSERT_EQ(4, 2 + 2); }

TEST_F(TestAdd, TwoPlusThree) { ASSERT_NE(4, 2 + 3); }
TEST_F(TestAdd, OnePlusOne) { ASSERT_EQ(3, 1 + 1); }

// int main(int argc, char* argv[]) {
//     testing::InitGoogleTest(&argc, argv);
//     RUN_ALL_TESTS();
//     std::cin.get();
//     return 0;
// }