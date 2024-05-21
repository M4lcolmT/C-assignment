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

    Node* merge(Node* left, Node* right) {
        if (!left) return right;
        if (!right) return left;

        // Determine the head of the merged list
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
    Node* mergeSort(Node* h) {
        if (!h || !h->next) return h;

        // Finding the middle of the list
        Node* slow = h;
        Node* fast = h->next;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        Node* mid = slow->next;
        slow->next = nullptr;

        // Recursively sort the two halves
        Node* left = mergeSort(h,comp);
        Node* right = mergeSort(mid,comp);

        // Merge the sorted halves
        return merge(left, right,comp);
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
    void sort() {
        head = mergeSort(head,comp);
        tail = head;
        if (tail) {
        while (tail->next) tail = tail->next;
        }
    }

    // LinkedList<T> search(std::function<bool(const T&)> predicate) {
    //     LinkedList<T> result;
    //     Node* current = head;
    //     while (current != nullptr) {
    //         if (predicate(current->data)) {
    //             result.append(current->data);
    //         }
    //         current = current->next;
    //     }
    //     return result;
    // }
};