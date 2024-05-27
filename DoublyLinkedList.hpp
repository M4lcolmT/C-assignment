#pragma once

#include <stdexcept>
#include <functional>

template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    int size;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void append(const T& value) {
        Node* newNode = new Node(value);
        if (tail) {
            tail->next = newNode;
            newNode->prev = tail;
        } else {
            head = newNode;
        }
        tail = newNode;
        size++;
    }

    int getSize() const {
        return size;
    }

    T& get(int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range.");
        }
        Node* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }

    void forEach(std::function<void(const T&)> callback) const {
        Node* current = head;
        while (current) {
            callback(current->data);
            current = current->next;
        }
    }

    void sort(std::function<bool(const T&, const T&)> comp) {
        if (!head || !head->next) return;

        bool swapped;
        do {
            swapped = false;
            Node* current = head;
            while (current && current->next) {
                if (comp(current->next->data, current->data)) {
                    std::swap(current->data, current->next->data);
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);
    }

    T* search(const std::string& id) {
        Node* current = head;
        while (current) {
            if (current->data.getID() == id) {
                return &(current->data);
            }
            current = current->next;
        }
        return nullptr;
    }

    class Iterator {
    private:
        Node* node;

    public:
        Iterator(Node* node) : node(node) {}

        T& operator*() {
            return node->data;
        }

        Iterator& operator++() {
            node = node->next;
            return *this;
        }

        Iterator& operator--() {
            node = node->prev;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return node != other.node;
        }
    };

    Iterator begin() {
        return Iterator(head);
    }

    Iterator end() {
        return Iterator(nullptr);
    }

    Iterator find(const std::string& id) {
        Node* current = head;
        while (current) {
            if (current->data.getID() == id) {
                return Iterator(current);
            }
            current = current->next;
        }
        return end();
    }
};