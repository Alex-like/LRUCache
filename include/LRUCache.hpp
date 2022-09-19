//
// Created by Alex Shchelochkov on 19.09.2022.
//

#ifndef LRUCACHE_HPP
#define LRUCACHE_HPP

#include <unordered_map>

template<typename K, typename V>
class LRUCache {
private:
    struct node {
        K key;
        V value;
        node *prev = nullptr, *next = nullptr;
    };

    size_t capacity = 0, size = 0;
    node *head, *tail;
    std::unordered_map<K, node*> hash_map;

public:
    explicit LRUCache(size_t capacity = 100);
    size_t getCapacity() const;
    size_t getSize() const;
    V* get(K key);
};

template<typename K, typename V>
LRUCache<K, V>::LRUCache(const size_t capacity) {
    this->size = 0;
    this->capacity = capacity;
    this->hash_map = std::unordered_map<K, node*>();
    this->tail = nullptr;
    this->head = tail;
}

template<typename K, typename V>
size_t LRUCache<K, V>::getCapacity() const {
    return capacity;
}

template<typename K, typename V>
size_t LRUCache<K, V>::getSize() const {
    return size;
}

template<typename K, typename V>
V* LRUCache<K, V>::get(K key) {
    if (hash_map.find(key) == hash_map.end())
        return nullptr;
    return &(hash_map[key]->value);
}


#endif //LRUCACHE_HPP
