// #include <stdexcept>

// // Self-created linked list class
// template <typename T>
// class LinkedList {
// private:
//     struct Node {
//         T data;
//         Node* next;
//         Node(const T& value) : data(value), next(nullptr) {}
//     };

//     Node* head;
//     Node* tail;
//     int size;

// public:
//     LinkedList() : head(nullptr), tail(nullptr), size(0) {}

//     // Add more member functions as needed (e.g., append, remove, etc.)

//     // Function to add an element to the end of the list
//     void append(const T& value) {
//         Node* newNode = new Node(value);
//         if (head == nullptr) {
//             head = tail = newNode;
//         } else {
//             tail->next = newNode;
//             tail = newNode;
//         }
//         size++;
//     }

//     // Function to remove and return the last element of the list
//     T popBack() {
//         if (isEmpty()) {
//             throw std::out_of_range("List is empty. Cannot pop element.");
//         }
//         T value;
//         if (head == tail) {
//             value = head->data;
//             delete head;
//             head = tail = nullptr;
//         } else {
//             Node* current = head;
//             while (current->next != tail) {
//                 current = current->next;
//             }
//             value = tail->data;
//             delete tail;
//             tail = current;
//             tail->next = nullptr;
//         }
//         size--;
//         return value;
//     }

//     // Function to get the size of the list
//     int getSize() const {
//         return size;
//     }

//     // Function to check if the list is empty
//     bool isEmpty() const {
//         return size == 0;
//     }
// };

// template <typename T>
// class Stack {
// private:
//     LinkedList<T> list;

// public:
//     // Function to push an element onto the stack
//     void push(const T& value) {
//         list.append(value);
//     }

//     // Function to remove and return the top element from the stack
//     T pop() {
//         if (isEmpty()) {
//             throw std::out_of_range("Stack is empty. Cannot pop element.");
//         }
//         return list.popBack();
//     }

//     // Function to return the top element of the stack without removing it
//     T& top() {
//         if (isEmpty()) {
//             throw std::out_of_range("Stack is empty. Cannot access top element.");
//         }
//         // Assuming LinkedList has a function to access the last element
//         return list[list.getSize() - 1];
//     }

//     // Function to check if the stack is empty
//     bool isEmpty() const {
//         return list.isEmpty();
//     }

//     // Function to get the size of the stack
//     int size() const {
//         return list.getSize();
//     }
// };
