#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class QNode {
public:
    T data;
    QNode* next;

    QNode(T val) : data(val), next(nullptr) {}
};

template <typename T>
class Queue {
private:
    QNode<T>* frontPtr;
    QNode<T>* rearPtr;
    int count;

public:
    // constructor
    Queue() : frontPtr(nullptr), rearPtr(nullptr), count(0) {}

    // destructor
    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    // check if empty
    bool isEmpty() const {
        return frontPtr == nullptr;
    }

    // get size
    int size() const {
        return count;
    }

    // add element at rear
    void enqueue(const T& val) {
        QNode<T>* newNode = new QNode<T>(val);

        if (isEmpty()) {
            frontPtr = rearPtr = newNode;
        } else {
            rearPtr->next = newNode;
            rearPtr = newNode;
        }
        count++;
    }

    // remove element from front
    void dequeue() {
        if (isEmpty()) {
            throw runtime_error("Queue is empty");
        }

        QNode<T>* temp = frontPtr;
        frontPtr = frontPtr->next;
        delete temp;
        count--;

        if (frontPtr == nullptr)
            rearPtr = nullptr;
    }

    // get front element
    T front() const {
        if (isEmpty()) {
            throw runtime_error("Queue is empty");
        }
        return frontPtr->data;
    }

    // get rear element
    T back() const {
        if (isEmpty()) {
            throw runtime_error("Queue is empty");
        }
        return rearPtr->data;
    }

    // print all elements

};

#endif
