#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include "IndexOutOfRange.h"
#include "IEnumerator.h"

#include <iostream> 
#include <cmath>


template <class T> 
class DynamicArray {
    private:
        T *array;
        int size;
        int capacity;

    public:
        DynamicArray();
        DynamicArray(int size);
        DynamicArray(T *items, int count);
        DynamicArray(const DynamicArray<T> & dynamicArray); 
        ~DynamicArray();

        friend std::ostream& operator<<(std::ostream& os, const DynamicArray<T>& obj) {
            os << "[";
            for (int i = 0; i < obj.size; i++) {
                os << obj.array[i];
                if (i < obj.size - 1) {
                    os << ", ";
                }
            }
            os << "]";
            return os;
        }

        const T& operator[](int index) const {
            if (index < 0 || index >= size) {
                throw IndexOutOfRange();
            }
            return array[index];
        }

        T& operator[](int index) {
            if (index < 0 || index >= size) {
                throw IndexOutOfRange();
            }
            return array[index];
        }

        DynamicArray<T>& operator=(const DynamicArray<T> &other) {
            if (this != &other) {
                delete[] array;
                size = other.size;
                capacity = other.capacity;
                array = new T[capacity];
                for (int i = 0; i < size; i++) {
                    array[i] = other.array[i];
                }
            }
            return *this;
        }

        T get(int index) const;
        int getSize() const;
        bool isEmpty() const;
        void print() const;

        void resize(int newSize);
        void set(T item, int index);

        IEnumerator<T> *getEnumerator() const;
};

template <class T>
DynamicArray<T>::DynamicArray() : DynamicArray(nullptr, 0) {}

template <class T>
DynamicArray<T>::DynamicArray(int size) : DynamicArray(nullptr, size) {}

template <class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> & other) : DynamicArray(other.array, other.size) {}

template <class T>
DynamicArray<T>::DynamicArray(T *items, int count) : array(nullptr), size(count), capacity(count) {
    array = new T[capacity];
    if (items != nullptr) {
        for (int i = 0; i < count; i++) {
            array[i] = items[i];
        }
    }
    else {
        for (int i = 0; i < count; i++) {
            array[i] = T();
        }
    }
}

template <class T>
DynamicArray<T>::~DynamicArray() {
    if (array != nullptr) {
        delete[] array;
    }
}

template <class T>
T DynamicArray<T>::get(int index) const {
    if (index < size and index >= 0) {
        return array[index];
    }
    else {
        throw IndexOutOfRange();
    }
}

template <class T>
int DynamicArray<T>::getSize() const {
    return size;
}

template <class T>
bool DynamicArray<T>::isEmpty() const {
    return size == 0;
}

template <class T>
void DynamicArray<T>::print() const {
    for (int i = 0; i < size; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

template <class T>
void DynamicArray<T>::resize(int newSize) {
    if (newSize > capacity) {
        if (capacity == 0) {
            capacity = newSize;
        }
        else {
            capacity = std::ceil(static_cast<double>(newSize)/capacity) * capacity;
        }
        T *newArray = new T[capacity];
        for (int i = 0; i < size; i++) {
            newArray[i] = array[i];
        }
        delete[] array;
        array = newArray;
    }
    size = newSize;
}

template <class T>
void DynamicArray<T>::set(T item, int index) {
    if (index >= 0 && index < size) {
        array[index] = item;
    }
    else {
        throw IndexOutOfRange();
    }
}

template <class T>
IEnumerator<T> *DynamicArray<T>::getEnumerator() const {
    class DynamicArrayEnumerator : public IEnumerator<T> {
        private:
            T *data;
            int current_index;
            int length;
            
        public:
            DynamicArrayEnumerator(T *arr, int len) : data(arr), current_index(-1), length(len) {}
            
            ~DynamicArrayEnumerator() = default;
            
            bool moveNext() override {
                current_index++;
                return current_index < length;
            }
            
            T current() override {
                if (current_index < 0 || current_index >= length) {
                    throw IndexOutOfRange();
                }
                return data[current_index];
            }
    };
    
    return new DynamicArrayEnumerator(array, size);
}

#endif