#pragma once

#include <iostream>
#include <stdexcept>
#include <random>
#include <algorithm>
#include <functional>
using namespace std;
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

    // add data at the end of the linked list
    void append(const T& value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    // add data at the start of the linked list
    void prepend(const T& value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
        size++;
    }

    int getSize() const {
        return size;
    }

    T& get(int index) const {
        if (index < 0 || index >= size) throw out_of_range("Index out of range.");
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    // remove the last element from the linked list
    T popBack() {
        if (!head) throw out_of_range("List is empty.");

        if (head == tail) {
            T data = head->data;
            delete head;
            head = tail = nullptr;
            size--;
            return data;
        }

        Node* current = head;
        while (current->next != tail) {
            current = current->next;
        }

        T data = tail->data;
        delete tail;
        tail = current;
        tail->next = nullptr;
        size--;
        return data;
    }

    void shuffle() {
        int size = getSize();
        if (size <= 1) return; // No need to shuffle if the list has 0 or 1 element

        // Convert linked list to array
        T* array = new T[size];
        for (int i = 0; i < size; ++i) {
            array[i] = get(i);
        }

        // Shuffle array using Fisher-Yates algorithm
        srand(time(NULL)); // Seed for randomness
        for (int i = size - 1; i > 0; --i) {
            int j = rand() % (i + 1);
            swap(array[i], array[j]);
        }

        // Convert array back to linked list
        for (int i = 0; i < size; ++i) {
            get(i) = array[i];
        }

        delete[] array;
    }
};
