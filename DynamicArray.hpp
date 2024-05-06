#include <iostream>
#include <cstring> // For using std::memcpy

template <typename T>
class DynamicArray {
private:
    T* array;
    size_t capacity;
    size_t currentSize;

    void resize() {
        capacity = (capacity == 0) ? 1 : capacity * 2;
        T* newArray = new T[capacity];

        // Copy the existing elements to the new array
        for (size_t i = 0; i < currentSize; ++i) {
            new (newArray + i) T(std::move(array[i]));
        }

        // Destroy the old elements and delete the old array
        for (size_t i = 0; i < currentSize; ++i) {
            array[i].~T();
        }
        delete[] array;

        array = newArray;
    }

public:
    DynamicArray() : array(nullptr), capacity(0), currentSize(0) {}

    ~DynamicArray() {
        delete[] array;
    }

    void add(const T& element) {
        if (currentSize == capacity) {
            resize();
        }
        array[currentSize++] = element;
    }

    T& operator[](size_t index) {
        if (index >= currentSize) throw std::out_of_range("Index out of range");
        return array[index];
    }

    size_t getSize() const {
        return currentSize;
    }
};