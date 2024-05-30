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


    // Custom merge function for linked list nodes
    Node* merge(Node* left, Node* right, function<bool(const T&, const T&)> comp) {
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
    Node* mergeSort(Node* h, function<bool(const T&, const T&)> comp) {
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


    T* search(const string& id) {
        Node* current = head;
        while (current) {
            if (current->data.getID() == id) {
                return &(current->data);
            }
            current = current->next;
        }
        return nullptr;
    }
};