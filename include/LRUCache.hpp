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

        node(const K key, const V value);
    };

    size_t capacity = 0;
    node *head, *tail;
    std::unordered_map<K, node*> hash_map;

    void update_head(node *new_head);
    void remove_tail();

public:
    explicit LRUCache(size_t capacity = 100);
    size_t get_capacity() const;
    size_t get_size() const;
    V* get(K key);
    void put(K key, V value);
};

template<typename K, typename V>
LRUCache<K, V>::node::node(const K key, const V value) {
    this->key = key;
    this->value = value;
}


template<typename K, typename V>
void LRUCache<K, V>::update_head(LRUCache::node *new_head) {
    assert(new_head != nullptr);
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
    assert(capacity > 0);
    this->capacity = capacity;
    this->hash_map = std::unordered_map<K, node*>();
    this->tail = nullptr;
    this->head = nullptr;
}

template<typename K, typename V>
size_t LRUCache<K, V>::get_capacity() const {
    return capacity;
}

template<typename K, typename V>
size_t LRUCache<K, V>::get_size() const {
    return hash_map.size();
}

template<typename K, typename V>
V* LRUCache<K, V>::get(K key) {
    if (hash_map.find(key) == hash_map.end())
        return nullptr;
    if (hash_map[key] == tail) {
        head->next = tail->next;
        tail->prev = head->prev;
        head->prev = nullptr;
        tail->next = nullptr;
        std::swap(head, tail);
    }
    if (hash_map[key]->next != nullptr)
        hash_map[key]->next->prev = hash_map[key]->prev;
    hash_map[key]->next = nullptr;
    update_head(hash_map[key]);
    assert(head == hash_map[key]);
    return &(hash_map[key]->value);
}

template<typename K, typename V>
void LRUCache<K, V>::put(K key, V value) {
    assert(hash_map.find(key) == hash_map.end());
    if (hash_map.size() == capacity)
        remove_tail();
    node *new_node = new node(key, value);
    new_node->key = key;
    new_node->value = value;
    new_node->next = nullptr;
    update_head(new_node);
    hash_map[key] = new_node;
    assert(head == hash_map[key]);
}

#endif //LRUCACHE_HPP
