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
    Queue() : frontPtr(nullptr), rearPtr(nullptr), count(0) {}

    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    bool isEmpty() const {
        return frontPtr == nullptr;
    }

    int size() const {
        return count;
    }

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

    T front() const {
        if (isEmpty()) {
            throw runtime_error("Queue is empty");
        }
        return frontPtr->data;
    }

    T back() const {
        if (isEmpty()) {
            throw runtime_error("Queue is empty");
        }
        return rearPtr->data;
    }


};

#endif
