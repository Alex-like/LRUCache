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

TEST(LRUCacheTests, put_one_element) {
    LRUCache<int, int> cache(10);
    EXPECT_EQ(0, cache.getSize());
    cache.put(0, 10);
    EXPECT_EQ(1, cache.getSize());
    EXPECT_EQ(10, *cache.get(0));
}

TEST(LRUCacheTests, put_elements) {
    size_t capacity = 10;
    LRUCache<int, int> cache(capacity);
    EXPECT_EQ(0, cache.getSize());
    for (int i = 0; i < capacity; i++) {
        cache.put(i, i + 1);
        EXPECT_EQ(i + 1, cache.getSize());
    }
    cache.put(10, 11);
    EXPECT_EQ(nullptr, cache.get(0));
}

TEST(LRUCacheTests, rewrite_exist_element) {
    size_t capacity = 10;
    LRUCache<int, int> cache(capacity);
    EXPECT_EQ(0, cache.getSize());
    for (int i = 0; i < capacity; i++) {
        cache.put(i, i + 1);
        EXPECT_EQ(i + 1, cache.getSize());
    }
    cache.put(9, 11);
    EXPECT_EQ(11, *cache.get(9));
}

GTEST_API_ int main(int argc, char ** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
