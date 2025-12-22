#ifndef HASHMAP_H
#define HASHMAP_H

#include <iostream>
#include <string>
#include <functional>
#include <cmath>
#include <algorithm>
#include <stdexcept>

/**
 * @brief HashMap implementation with separate chaining for collision resolution
 * @tparam K Key type (int, string, or any hashable type)
 * @tparam V Value type
 */
template<typename K, typename V>
class HashMap {
private:
    /**
     * @brief Node structure for linked list chaining
     */
    struct Node {
        K key;
        V value;
        Node* next;

        Node(const K& k, const V& v) : key(k), value(v), next(nullptr) {}
    };

    Node** buckets;           // Array of pointers to linked list heads
    int capacity;             // Number of buckets
    int size;                 // Number of elements stored
    double maxLoadFactor;     // Threshold for rehashing (default 0.75)

    /**
     * @brief Hash function for different key types
     * @param key The key to hash
     * @return Bucket index
     */
    int hash(const K& key) const {
        if constexpr (std::is_same_v<K, int>) {
            // Simple modulo hashing for integers
            return std::abs(key) % capacity;
        }
        else if constexpr (std::is_same_v<K, std::string>) {
            // DJB2 hash algorithm for strings
            unsigned long hashValue = 5381;
            for (char c : key) {
                hashValue = ((hashValue << 5) + hashValue) + c; // hash * 33 + c
            }
            return hashValue % capacity;
        }
        else {
            // Use std::hash for other types
            return std::hash<K>{}(key) % capacity;
        }
    }

    /**
     * @brief Rehash the table when load factor exceeds threshold
     * Time Complexity: O(n) where n is number of elements
     */
    void rehash() {
        int oldCapacity = capacity;
        Node** oldBuckets = buckets;

        // Double the capacity
        capacity *= 2;
        buckets = new Node*[capacity]();  // Initialize all to nullptr
        size = 0;  // Reset size, will be recounted during reinsertion

        // Reinsert all elements into new table
        for (int i = 0; i < oldCapacity; i++) {
            Node* current = oldBuckets[i];
            while (current != nullptr) {
                insert(current->key, current->value);  // Reinsert
                Node* temp = current;
                current = current->next;
                delete temp;  // Free old node
            }
        }

        delete[] oldBuckets;  // Free old bucket array

        std::cout << "[INFO] Rehashed: new capacity = " << capacity << std::endl;
    }

public:
    /**
     * @brief Constructor
     * @param initialCapacity Initial number of buckets (default 16)
     * @param loadFactor Maximum load factor before rehashing (default 0.75)
     */
    HashMap(int initialCapacity = 16, double loadFactor = 0.75)
        : capacity(initialCapacity), size(0), maxLoadFactor(loadFactor) {
        buckets = new Node*[capacity]();  // Initialize all pointers to nullptr
    }

    /**
     * @brief Destructor - frees all allocated memory
     */
    ~HashMap() {
        clear();
        delete[] buckets;
    }

    /**
     * @brief Insert or update a key-value pair
     * @param key The key to insert
     * @param value The value to associate with the key
     *
     * Time Complexity: O(1) average, O(n) worst case
     * Space Complexity: O(1)
     */
    void insert(const K& key, const V& value) {
        // Check if rehashing is needed
        if (getLoadFactor() >= maxLoadFactor) {
            rehash();
        }

        int index = hash(key);
        Node* current = buckets[index];

        // Check if key already exists (update value)
        while (current != nullptr) {
            if (current->key == key) {
                current->value = value;  // Update existing value
                return;
            }
            current = current->next;
        }

        // Key doesn't exist, insert new node at head of chain
        Node* newNode = new Node(key, value);
        newNode->next = buckets[index];
        buckets[index] = newNode;
        size++;
    }

    /**
     * @brief Search for a value by key
     * @param key The key to search for
     * @return Pointer to value if found, nullptr otherwise
     *
     * Time Complexity: O(1) average, O(n) worst case
     */
    V* search(const K& key) {
        int index = hash(key);
        Node* current = buckets[index];

        // Traverse the chain at this bucket
        while (current != nullptr) {
            if (current->key == key) {
                return &(current->value);  // Return pointer to value
            }
            current = current->next;
        }

        return nullptr;  // Key not found
    }

    /**
     * @brief Check if a key exists in the map
     * @param key The key to check
     * @return true if key exists, false otherwise
     */
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

    /**
     * @brief Remove a key-value pair
     * @param key The key to remove
     * @return true if key was found and removed, false otherwise
     *
     * Time Complexity: O(1) average, O(n) worst case
     */
    bool remove(const K& key) {
        int index = hash(key);
        Node* current = buckets[index];
        Node* prev = nullptr;

        while (current != nullptr) {
            if (current->key == key) {
                // Found the key, remove it
                if (prev == nullptr) {
                    // Removing first node in chain
                    buckets[index] = current->next;
                } else {
                    // Removing middle or end node
                    prev->next = current->next;
                }
                delete current;
                size--;
                return true;
            }
            prev = current;
            current = current->next;
        }

        return false;  // Key not found
    }

    /**
     * @brief Remove all elements from the map
     * Time Complexity: O(n)
     */
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

    /**
     * @brief Get the number of elements in the map
     * @return Number of key-value pairs
     */
    int getSize() const {
        return size;
    }

    /**
     * @brief Get the number of buckets
     * @return Current capacity
     */
    int getCapacity() const {
        return capacity;
    }

    /**
     * @brief Calculate current load factor
     * @return Load factor (size / capacity)
     */
    double getLoadFactor() const {
        return static_cast<double>(size) / capacity;
    }

    /**
     * @brief Check if map is empty
     * @return true if no elements, false otherwise
     */
    bool isEmpty() const {
        return size == 0;
    }

    /**
     * @brief Estimate memory usage in bytes
     * @return Approximate memory consumption
     */
    size_t getMemoryUsage() const {
        size_t memory = sizeof(*this);              // Object overhead
        memory += capacity * sizeof(Node*);         // Bucket array
        memory += size * sizeof(Node);              // All nodes
        return memory;
    }


    void printStats() const {
        std::cout << "\n┌─────────────────────────────────────┐" << std::endl;
        std::cout << "│     HashMap Statistics              │" << std::endl;
        std::cout << "├─────────────────────────────────────┤" << std::endl;
        std::cout << "│ Size:          " << size << " elements" << std::endl;
        std::cout << "│ Capacity:      " << capacity << " buckets" << std::endl;
        std::cout << "│ Load Factor:   " << getLoadFactor() << std::endl;
        std::cout << "│ Memory Usage:  " << getMemoryUsage() << " bytes" << std::endl;

        // Calculate collision statistics
        int usedBuckets = 0;
        int maxChainLength = 0;
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

        std::cout << "│ Used Buckets:  " << usedBuckets
                  << " (" << (100.0 * usedBuckets / capacity) << "%)" << std::endl;
        std::cout << "│ Max Chain:     " << maxChainLength << std::endl;
        std::cout << "│ Avg Chain:     " << avgChainLength << std::endl;
        std::cout << "└─────────────────────────────────────┘" << std::endl;
    }

    /**
     * @brief Get all keys in the map
     * @return Vector of all keys
     */
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

    /**
     * @brief Get collision statistics for benchmarking
     * @return Pair of (max_chain_length, average_chain_length)
     */
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

#endif // HASHMAP_H
