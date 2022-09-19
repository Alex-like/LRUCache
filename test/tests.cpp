#include <iostream>
#include <gtest/gtest.h>
#include "../include/LRUCache.hpp"

TEST(LRUCacheTests, create) {
    LRUCache<int, int> cache(10);
}

TEST(LRUCacheTests, capacity) {
    LRUCache<int, int> cache(10);
    EXPECT_EQ(10, cache.getCapacity());
}

TEST(LRUCacheTests, get_from_empty) {
    LRUCache<int, int> cache(10);
    EXPECT_EQ(0, cache.getSize());
    EXPECT_EQ(nullptr, cache.get(0));
}

GTEST_API_ int main(int argc, char ** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
