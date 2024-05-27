#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <iostream>
#include <stdexcept>
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

    void sort(std::function<bool(const T&, const T&)> comp) {
        head = mergeSort(head, comp);
        tail = head;
        if (tail) {
            while (tail->next) tail = tail->next;
        }
    }

    // // Fisher-Yates shuffle directly on the linked list
    // void fisherYatesShuffle(LinkedList& list) {
    //     int n = list.getSize();
    //     random_device rd;
    //     mt19937 gen(rd());

    //     Node* currentNode = list.head;
    //     for (int i = 0; i < n - 1 && currentNode != nullptr; i++) {
    //         uniform_int_distribution<int> dist(i, n - 1);
    //         int j = dist(gen);

    //         // Get the node at index j
    //         Node* nodeJ = list.getNodeAt(j);

    //         // Swap data of the current node and node at index j
    //         swap(currentNode->data, nodeJ->data);

    //         // Move to the next node
    //         currentNode = currentNode->next;
    //     }
    // }

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
};

#endif