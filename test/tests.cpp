#include <gtest/gtest.h>
#include "../include/LRUCache.hpp"

TEST(LRUCacheSimpleTests, create) {
    LRUCache<int, int> cache(10);
}

TEST(LRUCacheSimpleTests, capacity) {
    LRUCache<int, int> cache(10);
    EXPECT_EQ(10, cache.get_capacity());
}

TEST(LRUCacheSimpleTests, get_from_empty) {
    LRUCache<int, int> cache(10);
    EXPECT_EQ(0, cache.get_size());
    EXPECT_EQ(nullptr, cache.get(0));
}

TEST(LRUCacheSimpleTests, put_one_element) {
    LRUCache<int, int> cache(10);
    EXPECT_EQ(0, cache.get_size());
    cache.put(0, 10);
    EXPECT_EQ(1, cache.get_size());
    EXPECT_EQ(10, *cache.get(0));
}

TEST(LRUCacheSimpleTests, put_elements) {
    size_t capacity = 10;
    LRUCache<int, int> cache(capacity);
    EXPECT_EQ(0, cache.get_size());
    for (int i = 0; i < capacity; i++) {
        cache.put(i, i + 1);
        EXPECT_EQ(i + 1, cache.get_size());
    }
    cache.put(10, 11);
    EXPECT_EQ(nullptr, cache.get(0));
}

TEST(LRUCacheSimpleTests, try_to_rewrite_exist_element) {
    size_t capacity = 10;
    LRUCache<int, int> cache(capacity);
    EXPECT_EQ(0, cache.get_size());
    for (int i = 0; i < capacity; i++) {
        cache.put(i, i + 1);
        EXPECT_EQ(i + 1, cache.get_size());
    }
    EXPECT_EXIT(cache.put(9, 11),::testing::KilledBySignal(SIGABRT), "Assertion failed:");
    EXPECT_EQ(10, *cache.get(9));
}

TEST(LRUCacheGeneratedTests, put_more_elements_than_capacity) {
    size_t n = random() % 1000000;
    int *arr = new int[n];
    size_t capacity = (random() % 25) * 1000;
    LRUCache<int, int> cache(capacity);
    for (size_t id = 0; id < n; id++) {
        arr[id] = random();
        cache.put(id, arr[id]);
    }
    EXPECT_EQ(arr[n-1], *cache.get(n-1));
    EXPECT_EQ(arr[n-capacity], *cache.get(n-capacity));
}

GTEST_API_ int main(int argc, char ** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
