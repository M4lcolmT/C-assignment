#pragma once
#include <stdexcept>
using namespace std;

template <typename T>

class Vector {
private:
    T* data;
    size_t size;
    size_t capacity;

public:
    Vector() {
        data = nullptr;
        size = 0;
        capacity = 0;
    }

    void push_back(const T& value) {
        if (size == capacity) {
            size_t new_capacity = (capacity == 0) ? 1 : capacity * 2;
            T* new_data = new T[new_capacity];
            
            for (size_t i = 0; i < size; ++i) {
                new_data[i] = data[i];
            }
            
            delete[] data;
            data = new_data;
            capacity = new_capacity;
        }
        
        data[size] = value;
        size++;
    }

    void pop_back() {
        if (size > 0) {
            size--;
        }
        else {
            throw out_of_range("Vector is empty, can't pop back");
        }
    }

    void clear() {
        while (size > 0) {
            size--;
        }
    }

    void insert(size_t index, const T& value) {
        if (index > size) {
            throw out_of_range("Index out of range");
        }

        if (size >= capacity) {
            size_t new_capacity = (capacity == 0) ? 1 : capacity * 2;
            T* new_data = new T[new_capacity];

            for (size_t i = 0; i < index; ++i) {
                new_data[i] = data[i];
            }

            new_data[index] = value;

            for (size_t i = index; i < size; ++i) {
                new_data[i + 1] = data[i];
            }

            delete[] data;
            data = new_data;
            capacity = new_capacity;
            size++;
        }
        else {
            // Shift elements to make space for the new value
            for (size_t i = size; i > index; --i) {
                data[i] = data[i - 1];
            }

            data[index] = value;
            size++;
        }
    }

    T& at(size_t index) {
        if (index >= size) {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }

    T& operator[](size_t index) {
        if (index >= size) {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }


    void erase(size_t index) {
        if (index >= size) {
            throw out_of_range("Index out of range");
        }

        for (size_t i = index; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }

        size--;
    }

    T* begin() {
        return data;
    }

    T* end() {
        return data + size;
    }


    size_t getSize() const {
        return size;
    }

    bool isEmpty() const {
        return size == 0;
    }
};
