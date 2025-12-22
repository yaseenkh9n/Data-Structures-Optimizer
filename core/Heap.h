#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include <cmath>
#include <algorithm>

using namespace std;

template <typename T>
class Heap {
private:
    vector<T> data;
    bool isMinHeap;  // true = min-heap, false = max-heap

    // compare based on heap type
    bool compare(const T& a, const T& b) const {
        return isMinHeap ? (a < b) : (a > b);
    }

    // helper functions for indices
    int parent(int i) const { return (i - 1) / 2; }
    int leftChild(int i) const { return 2 * i + 1; }
    int rightChild(int i) const { return 2 * i + 2; }

    // heapify upward
    void heapifyUp(int i) {
        while (i > 0) {
            int p = parent(i);
            if (!compare(data[i], data[p]))
                break;
            swap(data[i], data[p]);
            i = p;
        }
    }

    // heapify downward
    void heapifyDown(int i) {
        int sz = data.size();
        while (true) {
            int l = leftChild(i);
            int r = rightChild(i);
            int best = i;

            if (l < sz && compare(data[l], data[best]))
                best = l;
            if (r < sz && compare(data[r], data[best]))
                best = r;

            if (best == i)
                break;

            swap(data[i], data[best]);
            i = best;
        }
    }

public:
    // constructor
    Heap(bool minHeap = true) : isMinHeap(minHeap) {}

    // insert element
    void insert(const T& value) {
        data.push_back(value);
        heapifyUp(data.size() - 1);
    }

    // get top element without removing
    T peek() const {
        if (data.empty())
            throw runtime_error("Heap is empty");
        return data[0];
    }

    // extract top element
    T extractTop() {
        if (data.empty())
            throw runtime_error("Heap is empty");

        T top = data[0];
        data[0] = data.back();
        data.pop_back();

        if (!data.empty())
            heapifyDown(0);

        return top;
    }

    // remove specific value
    void removeValue(const T& value) {
        int idx = -1;
        for (int i = 0; i < data.size(); i++) {
            if (data[i] == value) {
                idx = i;
                break;
            }
        }

        if (idx == -1)
            return;

        data[idx] = data.back();
        data.pop_back();

        if (idx < data.size()) {
            heapifyUp(idx);
            heapifyDown(idx);
        }
    }

    // build heap from vector
    void buildHeap(const vector<T>& values) {
        data = values;
        for (int i = data.size() / 2 - 1; i >= 0; i--)
            heapifyDown(i);
    }

    // search for value (linear time)
    bool search(const T& value) const {
        for (const auto& v : data) {
            if (v == value)
                return true;
        }
        return false;
    }

    // get size
    int size() const {
        return data.size();
    }

    // check if empty
    bool isEmpty() const {
        return data.empty();
    }

    // clear all elements
    void clear() {
        data.clear();
    }

    // get heap height
    int height() const {
        if (data.empty())
            return -1;
        return static_cast<int>(floor(log2(data.size())));
    }

    // get all elements
    vector<T> getElements() const {
        return data;
    }
};

#endif
