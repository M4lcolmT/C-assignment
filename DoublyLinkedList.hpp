#pragma once

#include <stdexcept>
#include <functional>
using namespace std;

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

    // merge sort functions start here
    Node* split(Node* head) {
        Node* fast = head;
        Node* slow = head;
        while (fast->next && fast->next->next) {
            fast = fast->next->next;
            slow = slow->next;
        }
        Node* mid = slow->next;
        slow->next = nullptr;
        return mid;
    }

    Node* merge(Node* left, Node* right, function<bool(const T&, const T&)> comp) {
        if (!left) return right;
        if (!right) return left;
        
        if (comp(left->data, right->data)) {
            left->next = merge(left->next, right, comp);
            left->next->prev = left;
            left->prev = nullptr;
            return left;
        } else {
            right->next = merge(left, right->next, comp);
            right->next->prev = right;
            right->prev = nullptr;
            return right;
        }
    }

    Node* mergeSort(Node* node, function<bool(const T&, const T&)> comp) {
        if (!node || !node->next) return node;

        Node* second = split(node);

        node = mergeSort(node, comp);
        second = mergeSort(second, comp);

        return merge(node, second, comp);
    }

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
            throw out_of_range("Index out of range.");
        }
        Node* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }

    // Public method to initiate the sort
    void sort(function<bool(const T&, const T&)> comp) {
        head = mergeSort(head, comp);
        tail = head;
        if (tail) {
            while (tail->next) tail = tail->next;
        }
    }

    // Search student from the front and back
    T* search(const string& id) {
        Node* current = head;
        Node* reverse = tail;

        // Traverse from both ends simultaneously
        while (current && reverse) {
            if (current->data.getID() == id) {
                return &(current->data);
            }
            if (reverse->data.getID() == id) {
                return &(reverse->data);
            }
            current = current->next;
            reverse = reverse->prev;
        }

        if (current) {
            if (current->data.getID() == id) {
                return &(current->data);
            }
        }

        return nullptr;
    }

    void printList() const {
        Node* current = head;
        while (current) {
            cout << current->data << " "; // Assumes that T has an overloaded operator<<
            current = current->next;
        }
        cout << endl;
    }
};
