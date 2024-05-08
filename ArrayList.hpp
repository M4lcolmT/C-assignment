#include <iostream>
#include <stdexcept>

template<typename T>
class ArrayList {
private:
    T* data;         // Pointer to the array of elements
    size_t capacity; // Total capacity of the list
    size_t length;   // Current number of elements in the list

    void resize() {
        capacity = (capacity == 0) ? 1 : capacity * 2;
        T* newData = new T[capacity];
        for (size_t i = 0; i < length; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }

public:
    ArrayList() : data(nullptr), capacity(0), length(0) {}

    ~ArrayList() {
        delete[] data;
    }

    void add(const T& value) {
        if (length == capacity) {
            resize();
        }
        data[length++] = value;
    }

    T& operator[](size_t index) {
        if (index >= length) throw std::out_of_range("Index out of range");
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= length) throw std::out_of_range("Index out of range");
        return data[index];
    }

    size_t getSize() const {
        return length;
    }
};

