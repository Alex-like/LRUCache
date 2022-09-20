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
    // head <- next <- ... <- next <- tail
    // head -> prev -> ... -> prev -> tail
    node *head, *tail;
    std::unordered_map<K, node*> hash_map;

    void update_head(node *new_head);

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
    if (new_head->next != nullptr && new_head->prev != nullptr) {
        new_head->next->prev = new_head->prev;
        new_head->prev->next = new_head->next;
    } else if (new_head->next != nullptr && new_head->prev == nullptr) {
        tail = tail->next;
    } else if (new_head->next == nullptr && new_head->prev == nullptr) {
        if (head == nullptr && tail == nullptr) {
            head = tail = new_head;
            return;
        }
    } else {
        assert(head == new_head);
        return;
    }
    head->next = new_head;
    new_head->prev = head;
    head = new_head;
    assert(head == new_head);
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
    update_head(hash_map[key]);
    assert(head == hash_map[key]);
    return &(hash_map[key]->value);
}

template<typename K, typename V>
void LRUCache<K, V>::put(K key, V value) {
    assert(hash_map.find(key) == hash_map.end());
    if (hash_map.size() >= capacity) {
        hash_map.erase(tail->key);
        tail = tail->next;
        if (tail != nullptr)
            tail->prev = nullptr;
    }
    node *new_node = new node(key, value);
    hash_map[key] = new_node;
    update_head(new_node);
    assert(head == hash_map[key]);
}

#endif //LRUCACHE_HPP
