#include <iostream>
#include <stdexcept>

template<typename T>
class ArrayList {
private:
    T* data;         // Pointer to the array of elements
    size_t capacity; // Total capacity of the list
    size_t length;   // Current number of elements in the list

    void resize() {
        size_t newCapacity = (capacity == 0) ? 1 : std::min(capacity * 2, size_t(101));
        T* newData = new T[newCapacity];
        for (size_t i = 0; i < length; i++) {
            newData[i] = std::move(data[i]); // Use move assignment for efficiency
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
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

    void set(size_t index, const T& value) {
        if (index >= length) {
            throw std::out_of_range("Index out of range");
        }
        data[index] = value;
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

