//
// Created by Alex Shchelochkov on 19.09.2022.
//

#ifndef LRUCACHE_HPP
#define LRUCACHE_HPP

#include <unordered_map>

template<typename K, typename V>
class LRUCache {
protected:
    struct node {
        K key;
        V value;
        node *prev = nullptr, *next = nullptr;
    };

    size_t capacity = 0, size = 0;
    node *head, *tail;
    std::unordered_map<K, node*> hash_map;

    void update_head(node *new_head);
    void remove_tail();

public:
    explicit LRUCache(size_t capacity = 100);
    size_t getCapacity() const;
    size_t getSize() const;
    V* get(K key);
    void put(K key, V value);
};


template<typename K, typename V>
void LRUCache<K, V>::update_head(LRUCache::node *new_head) {
    if (head == nullptr) {
        head = new_head;
        tail = new_head;
        return;
    }
    new_head->prev = head;
    head->next = new_head;
    head = new_head;
}

template<typename K, typename V>
void LRUCache<K, V>::remove_tail() {
    if (tail == nullptr) return;
    if (tail->next != nullptr) {
        hash_map.erase(tail->key);
        tail->next->prev = nullptr;
        tail = tail->next;
    }
    hash_map.erase(tail->key);
    tail = nullptr;
    head = nullptr;
}

template<typename K, typename V>
LRUCache<K, V>::LRUCache(const size_t capacity) {
    this->size = 0;
    this->capacity = capacity;
    this->hash_map = std::unordered_map<K, node*>();
    this->tail = nullptr;
    this->head = nullptr;
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
    if (hash_map[key]->next != nullptr)
        hash_map[key]->next->prev = hash_map[key]->prev;
    hash_map[key]->next = nullptr;
    update_head(hash_map[key]);
    return &(hash_map[key]->value);
}

template<typename K, typename V>
void LRUCache<K, V>::put(K key, V value) {
    if (hash_map.find(key) != hash_map.end()) {
        hash_map[key]->value = value;
        if (hash_map[key]->next != nullptr)
            hash_map[key]->next->prev = hash_map[key]->prev;
        hash_map[key]->next = nullptr;
        update_head(hash_map[key]);
        return;
    }
    if (size < capacity)
        size++;
    else
        remove_tail();
    node *new_node = new node();
    new_node->key = key;
    new_node->value = value;
    new_node->next = nullptr;
    update_head(new_node);
    hash_map[key] = new_node;
}

#endif //LRUCACHE_HPP
