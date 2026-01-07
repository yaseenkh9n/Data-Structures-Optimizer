#ifndef HASHMAP_H
#define HASHMAP_H

#include <iostream>
#include <string>
#include <functional>
#include <cmath>
#include <algorithm>
#include <stdexcept>

template<typename K, typename V>
class HashMap {
private:
    struct Node {
        K key;
        V value;
        Node* next;

        Node(const K& k, const V& v) : key(k), value(v), next(nullptr) {}
    };

    Node** buckets;
    int capacity;
    int size;
    double maxLoadFactor;

    int hash(const K& key) const {
        if constexpr (std::is_same_v<K, int>) {
            return std::abs(key) % capacity;
        }
        else if constexpr (std::is_same_v<K, std::string>) {
            unsigned long hashValue = 5381;
            for (char c : key) {
                hashValue = ((hashValue << 5) + hashValue) + c;
            }
            return hashValue % capacity;
        }
        else {
            return std::hash<K>{}(key) % capacity;
        }
    }

    void rehash() {
        int oldCapacity = capacity;
        Node** oldBuckets = buckets;

        capacity *= 2;
        buckets = new Node*[capacity]();
        size = 0;

        for (int i = 0; i < oldCapacity; i++) {
            Node* current = oldBuckets[i];
            while (current != nullptr) {
                insert(current->key, current->value);
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }

        delete[] oldBuckets;
    }

public:
    HashMap(int initialCapacity = 16, double loadFactor = 0.75)
        : capacity(initialCapacity), size(0), maxLoadFactor(loadFactor) {
        buckets = new Node*[capacity]();
    }

    ~HashMap() {
        clear();
        delete[] buckets;
    }

    void insert(const K& key, const V& value) {
        if (getLoadFactor() >= maxLoadFactor) {
            rehash();
        }

        int index = hash(key);
        Node* current = buckets[index];

        while (current != nullptr) {
            if (current->key == key) {
                current->value = value;
                return;
            }
            current = current->next;
        }

        Node* newNode = new Node(key, value);
        newNode->next = buckets[index];
        buckets[index] = newNode;
        size++;
    }

    V* search(const K& key) {
        int index = hash(key);
        Node* current = buckets[index];

        while (current != nullptr) {
            if (current->key == key) {
                return &(current->value);
            }
            current = current->next;
        }

        return nullptr;
    }

    bool contains(const K& key) const {
        int index = hash(key);
        Node* current = buckets[index];

        while (current != nullptr) {
            if (current->key == key) {
                return true;
            }
            current = current->next;
        }

        return false;
    }

    bool remove(const K& key) {
        int index = hash(key);
        Node* current = buckets[index];
        Node* prev = nullptr;

        while (current != nullptr) {
            if (current->key == key) {
                if (prev == nullptr) {
                    buckets[index] = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                size--;
                return true;
            }
            prev = current;
            current = current->next;
        }

        return false;
    }

    void clear() {
        for (int i = 0; i < capacity; i++) {
            Node* current = buckets[i];
            while (current != nullptr) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
            buckets[i] = nullptr;
        }
        size = 0;
    }

    int getSize() const {
        return size;
    }

    int getCapacity() const {
        return capacity;
    }

    double getLoadFactor() const {
        return static_cast<double>(size) / capacity;
    }

    bool isEmpty() const {
        return size == 0;
    }

    size_t getMemoryUsage() const {
        size_t memory = sizeof(*this);
        memory += capacity * sizeof(Node*);
        memory += size * sizeof(Node);
        return memory;
    }

    std::vector<K> getKeys() const {
        std::vector<K> keys;
        keys.reserve(size);

        for (int i = 0; i < capacity; i++) {
            Node* current = buckets[i];
            while (current != nullptr) {
                keys.push_back(current->key);
                current = current->next;
            }
        }

        return keys;
    }

    std::pair<int, double> getCollisionStats() const {
        int maxChainLength = 0;
        int usedBuckets = 0;
        int totalChainLength = 0;

        for (int i = 0; i < capacity; i++) {
            if (buckets[i] != nullptr) {
                usedBuckets++;
                int chainLength = 0;
                Node* current = buckets[i];
                while (current != nullptr) {
                    chainLength++;
                    current = current->next;
                }
                totalChainLength += chainLength;
                maxChainLength = std::max(maxChainLength, chainLength);
            }
        }

        double avgChainLength = usedBuckets > 0 ?
                                    static_cast<double>(totalChainLength) / usedBuckets : 0.0;

        return {maxChainLength, avgChainLength};
    }
};

#endif
