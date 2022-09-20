#include <gtest/gtest.h>
#include "../include/LRUCache.hpp"

class LRUCacheSimpleTest : public ::testing::Test {
protected:
    size_t capacity = 0;
    LRUCache<int, int> *cache = nullptr;

    void SetUp() override {
        capacity = 10;
        cache = new LRUCache<int, int> (capacity);
    }
};

TEST_F(LRUCacheSimpleTest, create) {
    EXPECT_NE(nullptr, cache);
}

TEST_F(LRUCacheSimpleTest, capacity) {
    EXPECT_EQ(10, cache->get_capacity());
}

TEST_F(LRUCacheSimpleTest, get_from_empty) {
    EXPECT_EQ(0, cache->get_size());
    EXPECT_EQ(nullptr, cache->get(0));
}

TEST_F(LRUCacheSimpleTest, put_one_element) {
    EXPECT_EQ(0, cache->get_size());
    cache->put(0, 10);
    EXPECT_EQ(1, cache->get_size());
    EXPECT_EQ(10, *cache->get(0));
}

TEST_F(LRUCacheSimpleTest, put_elements) {
    EXPECT_EQ(0, cache->get_size());
    for (int i = 0; i < capacity; i++) {
        cache->put(i, i + 1);
        EXPECT_EQ(i + 1, cache->get_size());
    }
    cache->put(10, 11);
    EXPECT_EQ(nullptr, cache->get(0));
}

TEST_F(LRUCacheSimpleTest, try_to_rewrite_exist_element) {
    EXPECT_EQ(0, cache->get_size());
    for (int i = 0; i < capacity; i++) {
        cache->put(i, i + 1);
        EXPECT_EQ(i + 1, cache->get_size());
    }
    EXPECT_EXIT(cache->put(9, 11),::testing::KilledBySignal(SIGABRT), "Assertion failed:");
    EXPECT_EQ(10, *cache->get(9));
}

TEST_F(LRUCacheSimpleTest, update_head) {
    EXPECT_EQ(0, cache->get_size());
    for (int i = 0; i < capacity; i++) {
        cache->put(i, i + 1);
        EXPECT_EQ(i + 1, cache->get_size());
    }
    EXPECT_EQ(1, *cache->get(0));
    cache->put(10, 11);
    EXPECT_EQ(1, *cache->get(0));
    EXPECT_EQ(nullptr, cache->get(1));
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
