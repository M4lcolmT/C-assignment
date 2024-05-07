#include<iostream>
using namespace std;

template<typename T, int capacity>
class Stack {
private:
    T stack[capacity];
    int top = -1;

public:
    void push(Question pushedQuestion) {
        if (top >= capacity - 1) {
            cout << "Stack is overflow !! " << endl;
        }
        else {
            top = top + 1;
            stack[top] = pushedQuestion;
        }
    }

    Question pop() {
        if (top == -1) {
            cout << "Stack is underflow !! " << endl;
            // Assuming Question has a default constructor
            return Question(); // Return a default-constructed Question object
        }
        else {
            Question poppedQuestion = stack[top];
            top = top - 1;
            return poppedQuestion;
        }
    }


    void traverse() {
        if (top == -1) {
            cout << "Stack is empty !! " << endl;
        }
        else {
            for (int i = top; i >= 0; i--) {
                cout << stack[i] << endl;
            }
        }
    }

    bool isEmpty() {
        return top == -1;
    }

    int getSize() const {
        return top + 1;
    }
};