#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int size;

public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    void append(const T& value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = tail = newNode; // If list is empty
        } else {
            tail->next = newNode; // Append to end
            tail = newNode;       // Move tail pointer
        }
        size++;
    }

    void prepend(const T& value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = tail = newNode; // If list is empty
        } else {
            newNode->next = head; // New node points to former head
            head = newNode;       // Update head to new node
        }
        size++;
    }

    int getSize() const {
        return size;
    }

    T& operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range.");
        }
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    // Simple Bubble Sort using data's getTotalScore() method
    void sort(std::function<bool(const T&, const T&)> comp) {
    if (!head || !head->next) return; 

    bool swapped;
    do {
        swapped = false;
        Node* current = head;
        Node* prev = nullptr;
        Node* next = current->next;

        while (next) {
            if (comp(current->data, next->data)) {
                std::swap(current->data, next->data);
                swapped = true;
            }
            current = next;
            next = next->next;
        }
    } while (swapped);
}


    void forEach(std::function<void(const T&)> func) {
        Node* current = head;
        while (current != nullptr) {
            func(current->data);
            current = current->next;
        }
    }

    LinkedList<T> search(std::function<bool(const T&)> predicate) {
        LinkedList<T> results;
        Node* current = head;
        while (current != nullptr) {
            if (predicate(current->data)) {
                results.append(current->data);
            }
            current = current->next;
        }
        return results;
    }
};