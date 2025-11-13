#include <gtest/gtest.h>
#include "../include/Hex.h"

TEST(HexTest, Addition) {
    Hex a("1A");
    Hex b("10");
    Hex c = a.add(b);
    EXPECT_TRUE(c.equal(Hex("2A")));
}

TEST(HexTest, Subtraction) {
    Hex d("FFB");
    Hex e("1A");
    Hex f = d.remove(e);
    EXPECT_TRUE(f.equal(Hex("FE1")));
}

TEST(HexTest, Equality) {
    Hex f("FE1");
    Hex g("FE1");
    EXPECT_TRUE(g.equal(f));
}

TEST(HexTest, Comparison) {
    Hex h("10");
    Hex d("FFB");
    Hex g("FE1");

    EXPECT_TRUE(h.lessThen(d));
    EXPECT_TRUE(g.biggerThen(h));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
