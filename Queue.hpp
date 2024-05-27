#pragma once

#include <stdexcept>

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* front;
    Node* rear;
    int size;

public:
    Queue() : front(nullptr), rear(nullptr), size(0) {}

    ~Queue() {
        while (front) {
            Node* temp = front;
            front = front->next;
            delete temp;
        }
    }

    void push(const T& value) {
        Node* newNode = new Node(value);
        if (rear) {
            rear->next = newNode;
        } else {
            front = newNode;
        }
        rear = newNode;
        size++;
    }

    void pop() {
        if (front) {
            Node* temp = front;
            front = front->next;
            if (!front) {
                rear = nullptr;
            }
            delete temp;
            size--;
        } else {
            throw std::out_of_range("Queue is empty. Cannot pop.");
        }
    }

    T& getFront() {
        if (!front) {
            throw std::out_of_range("Queue is empty. Cannot get front.");
        }
        return front->data;
    }

    bool isEmpty() const {
        return front == nullptr;
    }

    int getSize() const {
        return size;
    }
};
