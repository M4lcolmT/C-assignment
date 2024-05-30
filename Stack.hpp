#pragma once
template<typename T, int capacity>
class Stack {
private:
    T stack[capacity];
    int topIndex = -1; // Renamed to topIndex to avoid naming conflicts

public:
    void push(const T& pushedQuestion) {
        if (topIndex >= capacity - 1) {
            cout << "Stack is overflow !! " << endl;
        }
        else {
            topIndex++;
            stack[topIndex] = pushedQuestion;
        }
    }

    T pop() {
        if (topIndex == -1) {
            cout << "Stack is underflow !! " << endl;
            // Assuming Question has a default constructor
            return T(); // Return a default-constructed T object
        }
        else {
            T poppedQuestion = stack[topIndex];
            topIndex--;
            return poppedQuestion;
        }
    }

    T& top() {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty");
        }
        return stack[topIndex];
    }

    bool isEmpty() {
        return topIndex == -1;
    }

    int getSize() const {
        return topIndex + 1;
    }
};
