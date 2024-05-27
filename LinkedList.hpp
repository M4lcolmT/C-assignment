#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <iostream>
#include <stdexcept>
#include <random>
#include <algorithm>
#include <functional>

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

    // Custom merge function for linked list nodes
    Node* merge(Node* left, Node* right, std::function<bool(const T&, const T&)> comp) {
        if (!left) return right;
        if (!right) return left;

        Node* head = nullptr;
        if (comp(left->data, right->data)) {
            head = left;
            head->next = merge(left->next, right, comp);
        } else {
            head = right;
            head->next = merge(left, right->next, comp);
        }
        return head;
    }

    // Merge sort function
    Node* mergeSort(Node* h, std::function<bool(const T&, const T&)> comp) {
        if (!h || !h->next) return h;

        Node* slow = h;
        Node* fast = h->next;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        Node* mid = slow->next;
        slow->next = nullptr;

        Node* left = mergeSort(h, comp);
        Node* right = mergeSort(mid, comp);

        return merge(left, right, comp);
    }

public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

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

    T& get(int index) const {
        if (index < 0 || index >= size) throw std::out_of_range("Index out of range.");
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
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

    // Public method to initiate the sort
    void sort(std::function<bool(const T&, const T&)> comp) {
        head = mergeSort(head, comp);
        tail = head;
        if (tail) {
            while (tail->next) tail = tail->next;
        }
    }

    T popBack() {
        if (!head) throw std::out_of_range("List is empty.");

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

    // Shuffle method for the linked list
    void shuffle() {
        if (getSize() <= 1) return; // No need to shuffle if the list has 0 or 1 element

        // Convert linked list to array
        int size = getSize();
        T* array = new T[size];
        for (int i = 0; i < size; ++i) {
            array[i] = get(i);
        }

        // Shuffle array using Fisher-Yates algorithm
        std::random_device rd;
        std::mt19937 gen(rd());
        for (int i = size - 1; i > 0; --i) {
            std::uniform_int_distribution<> dis(0, i);
            int j = dis(gen);
            std::swap(array[i], array[j]);
        }

        // Convert array back to linked list
        for (int i = 0; i < size; ++i) {
            get(i) = array[i];
        }

        delete[] array;
    }
};

#endif